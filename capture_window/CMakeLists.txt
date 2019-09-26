# 指定 cmake 版本，跟安装的版本保持一致
cmake_minimum_required(VERSION 3.4.1)
project(record)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(OpenCV_DIR /opt/ros/kinetic/share/OpenCV-3.3.1-dev)
find_package(OpenCV REQUIRED)
# find_library(OPENCV_LIBRARY OpenCV HINTS /opt/ros/kinetic/lib/x86_64-linux-gnu)
message("-- OpenCV Version: " ${OpenCV_VERSION})
message(" =====" ${OpenCV_INCLUDE_DIRS} )
# find_package(Boost REQUIRED)
# find_package(Threads)
include_directories("/usr/include/qt4/QtGui"
"/usr/include/xcb"
"/opt/ros/kinetic/include/opencv-3.3.1-dev/opencv2"
${OpenCV_INCLUDE_DIRS}
)
set(SRC_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
message("CMake root path: " ${SRC_ROOT_PATH})


# link_libraries(
#     # "/usr/lib/x86_64-linux-gnu/libX11.so"
#     # "/usr/lib/x86_64-linux-gnu/libXcomposite.so" 
#     # "/usr/lib/x86_64-linux-gnu/libXrender.so"
#     # "/usr/lib/x86_64-linux-gnu/libpng.so"
#     # "/usr/lib/x86_64-linux-gnu/libxcb.so"
#     # "/usr/lib/x86_64-linux-gnu/libxcb-composite.so"
# )
# add_executable(cw capture_window.cpp)  
add_executable(co co.cpp)
target_link_libraries(co X11 Xcomposite Xrender)   

add_executable(ds draw_string.cpp)
target_link_libraries(ds X11)

add_executable(dpng displaypng.cpp)
target_link_libraries(dpng X11 png)
link_directories("/opt/ros/kinetic/lib/x86_64-linux-gnu")
add_executable(record_by_image record_by_image.cpp)
target_link_libraries(record_by_image 
    # ${OpenCV_LIBS} 
    # ${Boost_LIBS}
    ${OpenCV_LIBRARIES} 
    pthread
    boost_system
    boost_thread
    xcb
    xcb-composite
)