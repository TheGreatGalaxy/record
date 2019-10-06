# record_window
Ideas worth spreading
## Purpose: Recording the window as a video in linux OS by xcbcomposite and OpenCV libraries
## Introduction 
This is a ｄerivative project of my main work. One demand of my main ｗｏｒｋ is to record the display window as a video which should by synchrnized with my test data within 200ms. So I have no choice but writing script. But I found it's not easy to do that like under Windows OS. I think this work may help someone who has same demand. That's why my work is here.
### How to record one window?
1.firstly, get the window id by xwininfo or xdotool or something like them.
2.then create two threads. One thread get the image of the window periodically, and put it into a vector or a list。
3.Another thread get the image from vector, ofcourse, write the image into a vedio.
### what's the struction of project?
In this project, I just find one way to get image from some window. The script is named  "record_by_image.cpp". The rest .cpp files is tring to find others way to get image. So you can ingore them.
### How to compile？
Just use CMAKE. Also can be done by other compiler e.g. g++,clang if you want.
## Join us, improve it together 
This work can be better. If you are interested in it, Join us！
###　Ｔｏ do
1. support .mp4, flv...
2. support H264, MPEG encoders...
3. add .sh file to install dependence libraries automaticlly
...

