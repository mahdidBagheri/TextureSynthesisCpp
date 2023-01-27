#cmake_minimum_required(VERSION 3.22)
#project(TextureSynthesis)
#
#set(CMAKE_CXX_STANDARD 14)
#set(ENV{OPENCV_DIR} "F:\\sofware\\opencv\\opencv\\build\\x64\\vc15\\libs\\")
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
#
#set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
#add_executable(TextureSynthesis main.cpp)
#target_link_libraries(TextureSynthesis ${OpenCV_LIBS})

project(TextureSynthesis)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Where to find CMake modules and OpenCV
set(OpenCV_DIR "F:\\sofware\\opencv\\opencv\\build\\x64\\vc15\\lib")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(test_cv main.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

# linking
target_link_libraries(test_cv ${OpenCV_LIBS})



