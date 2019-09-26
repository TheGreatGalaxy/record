#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/composite.h> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <semaphore.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <time.h>
#include <ctype.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

class Record{
    public:
    xcb_window_t req_win_id;
    xcb_connection_t *connection;
    xcb_generic_error_t *err, *err2;// = NULL, *err2 = NULL;
    xcb_composite_query_version_cookie_t comp_ver_cookie;
    xcb_composite_query_version_reply_t *comp_ver_reply;
    const xcb_setup_t *setup;
    xcb_screen_iterator_t screen_iter;
    xcb_screen_t *screen;// = screen_iter.data;
    int win_h, win_w, win_d;
    xcb_get_geometry_cookie_t gg_cookie;
    xcb_get_geometry_reply_t *gg_reply;
    xcb_pixmap_t win_pixmap;
    xcb_get_image_cookie_t gi_cookie;
    xcb_get_image_reply_t *gi_reply;
    int data_len;
    uint8_t *data;
    std::vector<cv::Mat> image_vector;
    std::string path;
    int count;
    sem_t lock_count;
    bool vedio_write_init;
    bool need_exit;
    //link window
    int init();
    int get_image();
    int write_vedio();
    void start();
    Record(char* vedio_path, const char* window_id);
    ~Record();
};
Record::Record(char* vedio_path, const char *window_id){
    path = vedio_path;
    req_win_id = strtoul(window_id, NULL, 0);
    err = NULL;
    err2 = NULL;
    count = 0;
    vedio_write_init = false;
    need_exit=false;
    // path = "/home/zhenwei-qian/rviz/";
    sem_init(&lock_count,0,0);
    start();
}
Record::~Record(){
}
int Record::init(){
    
    connection = xcb_connect(NULL, NULL);
    //Delivers a request to the X server. 
    comp_ver_cookie = xcb_composite_query_version(connection, 0, 2); 
    /*Returns the reply of the request asked by
    The parameter e supplied to this function must be NULL if xcb_composite_query_version_unchecked(). is used. 
    Otherwise, it stores the error if any.The returned value must be freed by the caller using free(). */
    comp_ver_reply = xcb_composite_query_version_reply(connection, comp_ver_cookie, &err);
    if (comp_ver_reply)
    {
        if (comp_ver_reply->minor_version < 2) {
            fprintf(stderr, "query composite failure: server returned v%d.%d\n", comp_ver_reply->major_version, comp_ver_reply->minor_version);
            free(comp_ver_reply);
            return EXIT_FAILURE;
        }
        free(comp_ver_reply);
    }else if (err)
    {
        fprintf(stderr, "xcb error: %d\n", err->error_code);
        free(err);
        return EXIT_FAILURE;
    }
}
int Record::get_image(){
    while(true){ 

        setup = xcb_get_setup(connection);
        screen_iter = xcb_setup_roots_iterator(setup);
        screen = screen_iter.data;
        // request redirection of window
        xcb_composite_redirect_window(connection, req_win_id, XCB_COMPOSITE_REDIRECT_AUTOMATIC);
        gg_cookie = xcb_get_geometry(connection, req_win_id);
        gg_reply = xcb_get_geometry_reply(connection, gg_cookie, &err);
        if (gg_reply) {
            win_w = gg_reply->width;
            win_h = gg_reply->height;
            win_d = gg_reply->depth;
            free(gg_reply);
        } else {
            if (err) {
                fprintf(stderr, "get geometry: XCB error %d\n", err->error_code);
                free(err);
            }
            return EXIT_FAILURE;
        }
        // create a pixmap
        win_pixmap = xcb_generate_id(connection);
        xcb_composite_name_window_pixmap(connection, req_win_id, win_pixmap);
        // get the image
        gi_cookie = xcb_get_image(connection, XCB_IMAGE_FORMAT_Z_PIXMAP, win_pixmap, 0, 0, win_w, win_h, (uint32_t)(~0UL));
        gi_reply = xcb_get_image_reply(connection, gi_cookie, &err);
        if(err){
            printf("get image failed!\n");
            return EXIT_FAILURE;
        }
        if (gi_reply) {
            int data_len = xcb_get_image_data_length(gi_reply);
            // fprintf(stderr, "data_len = %d\n", data_len);
            // fprintf(stderr, "visual = %u\n", gi_reply->visual);
            // fprintf(stderr, "depth = %u\n", gi_reply->depth);
            // fprintf(stderr, "size = %dx%d\n", win_w, win_h);
            uint8_t *data = xcb_get_image_data(gi_reply);
            cv::Mat mat(win_h, win_w, CV_8UC3);
            int index=0;
            for(int i=0;i<win_h;i++){
                for(int j=0;j<win_w;j++){
                    index = i*win_w*4+j*4;//计算的data的索引，返回的是四通道的数据，bgra，视频三个通道
                    cv::Vec3b& bgra = mat.at<cv::Vec3b>(i,j);
                    bgra[0] = data[index];
                    bgra[1] = data[index+1]; 
                    bgra[2] = data[index+2]; 
                    // bgra[3] = data[index+3]; 
                }
            }
            // cv::imwrite(im_path,mat);
            image_vector.push_back(mat);
            sem_post(&lock_count);
            // fwrite(data, data_len, 1, stdout);
            free(gi_reply);
        }
        if(need_exit)
            exit(0);
        usleep(100000);//100ms
    }
}
int Record::write_vedio(){
    cv::VideoWriter video;
    while(true){
        while(true){
            if(sem_wait(&lock_count)==-1){
                continue;
            }
            break;
        }
        // cv::VideoWriter::
        if(!vedio_write_init){
            std::string mk = "touch "+ path;
            system(mk.c_str());
            std::cout<<"video path: "<<path<<" video size: "<<win_w<<" "<<win_h<<std::endl;
            if(video.open(path,CV_FOURCC('D','I','V','X'),10, cv::Size(win_w,win_h)) ){
                vedio_write_init = true;
            }else{
                std::cout<<"Failed to create vedio!"<<std::endl;
            }
        }
        cv::Mat image = image_vector.front();
        image_vector.erase(image_vector.begin());
        printf("count: %d\n",count++);
        // std::string name = path + std::to_string(++count) +".jpg";
        // cv::imwrite(name,image);
        cv::imshow("image",image);
        cvWaitKey(100);
        video.write(image);
        usleep(5000);//5ms
        if(count>100){
            need_exit = true;
            video.release();
            cv::destroyAllWindows();
            exit(0);
        }
    }
}
void Record::start(){
    init();
    boost::thread get(boost::bind(&Record::get_image,this));
    boost::thread vedio(boost::bind(&Record::write_vedio,this));
    get.join();
}
int get_window_id(FILE* result,char* window_id){ //返回0，成功获取到window_id;1,失败；
    if(result==NULL){
        printf("Execute command failed!\n");
        return 1;
    }
    for(int i=0;i<70;i++)
        window_id[i]='\0';
    if(fgets(window_id, 70, result)==NULL)
        return 1;
    for(int i=0;i<70;i++){
        if(window_id[i]!='\0' && window_id[i]!='\n'){
            if(int(window_id[i])<48 || int(window_id[i])>57){ //0~9 ascii码48~57
                printf("window id is not invalid!\n");
                return 1;
            }
        }
    }
    return 0;

}



int main(int argc, char **argv) {

    char command0[]="xwininfo -int -name RViz | grep -Po '(?<=Window id: )[0-9]+';";
    char command1[]="xwininfo -int -name RViz* | grep -Po '(?<=Window id: )[0-9]+';";
    char command2[]="xwininfo -int | grep -Po '(?<=Window id: )[0-9]+'";
    char window_id[70]={'\0'};
    FILE* result = popen(command0,"r");
    if(get_window_id(result,window_id)==1){
        result = NULL;
        result = popen(command1,"r");
        if(get_window_id(result,window_id)==1){
            printf("Please confirm that the RViz is running! And rerun this node!\n");
            return EXIT_FAILURE;
        }
    }
    char vedio_path[] = "/home/zhenwei-qian/rviz/rviz.avi";
    Record record(vedio_path,window_id);

    return EXIT_SUCCESS;
}