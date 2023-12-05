cmake_minimum_required(VERSION 3.26)
project(color_picker)

set(CMAKE_CXX_STANDARD 17)

set(ENV{OPENCV_DIR} "C:\\tools\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
        color_picker main.cpp
        pixel_info.h
        color_replacer.cpp
        color_replacer.h
        rec_selection.cpp
        rec_selection.h
)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
target_link_libraries(color_picker ${OpenCV_LIBS})
