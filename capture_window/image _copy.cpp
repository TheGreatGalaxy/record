#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/composite.h> 
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/composite.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv2/opencv.hpp>
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s windowId\n", argv[0]);
        return EXIT_FAILURE;
    }
    xcb_window_t req_win_id = strtoul(argv[1], NULL, 0);
    xcb_connection_t *connection = xcb_connect(NULL, NULL);
    xcb_generic_error_t *err = NULL, *err2 = NULL;
    xcb_composite_query_version_cookie_t comp_ver_cookie = xcb_composite_query_version(connection, 0, 2);
    xcb_composite_query_version_reply_t *comp_ver_reply = xcb_composite_query_version_reply(connection, comp_ver_cookie, &err);
    if (comp_ver_reply)
    {
        if (comp_ver_reply->minor_version < 2) {
            fprintf(stderr, "query composite failure: server returned v%d.%d\n", comp_ver_reply->major_version, comp_ver_reply->minor_version);
            free(comp_ver_reply);
            return EXIT_FAILURE;
        }
        free(comp_ver_reply);
    }
    else if (err)
    {
        fprintf(stderr, "xcb error: %d\n", err->error_code);
        free(err);
        return EXIT_FAILURE;
    }
    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t *screen = screen_iter.data;
    // request redirection of window
    xcb_composite_redirect_window(connection, req_win_id, XCB_COMPOSITE_REDIRECT_AUTOMATIC);
    int win_h, win_w, win_d;
    xcb_get_geometry_cookie_t gg_cookie = xcb_get_geometry(connection, req_win_id);
    xcb_get_geometry_reply_t *gg_reply = xcb_get_geometry_reply(connection, gg_cookie, &err);
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
    xcb_pixmap_t win_pixmap = xcb_generate_id(connection);
    xcb_composite_name_window_pixmap(connection, req_win_id, win_pixmap);
    // get the image
    xcb_get_image_cookie_t gi_cookie = xcb_get_image(connection, XCB_IMAGE_FORMAT_Z_PIXMAP, win_pixmap, 0, 0, win_w, win_h, (uint32_t)(~0UL));
    xcb_get_image_reply_t *gi_reply = xcb_get_image_reply(connection, gi_cookie, &err);
    if (gi_reply) {
        int data_len = xcb_get_image_data_length(gi_reply);
        fprintf(stderr, "data_len = %d\n", data_len);
        fprintf(stderr, "visual = %u\n", gi_reply->visual);
        fprintf(stderr, "depth = %u\n", gi_reply->depth);
        fprintf(stderr, "size = %dx%d\n", win_w, win_h);
        uint8_t *data = xcb_get_image_data(gi_reply);
        cv::Mat mat(win_h, win_w, CV_8UC4);
        int index=0;
        for(int i=0;i<win_h;i++){
            for(int j=0;j<win_w;j++){
                index = i*win_w*4+j*4;
                cv::Vec4b& bgra = mat.at<cv::Vec4b>(i,j);
                bgra[0] = data[index];
                bgra[1] = data[index+1]; 
                bgra[2] = data[index+2]; 
                bgra[3] = data[index+3]; 
            }
        }
        cv::imwrite("/home/zhenwei-qian/rviz.jpg",mat);
        // fwrite(data, data_len, 1, stdout);
        free(gi_reply);
    }
    return EXIT_SUCCESS;
}