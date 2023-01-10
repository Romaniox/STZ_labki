cmake_minimum_required(VERSION 3.16)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab3 main.cpp anti_terrorist_waffen.cpp anti_terrorist_waffen.h
        robotics.cpp robotics.h trackbar.cpp trackbar.h zavod.cpp zavod.h)

set(OpenCV_DIR "D:\\OpenCV\\mingw-build\\install")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(lab3 ${OpenCV_LIBS})