cmake_minimum_required(VERSION 3.0)

project(hello-opencv)

find_package(OpenCV REQUIRED)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}
)

add_executable(
    hello-opencv
    src/main.cpp
)

target_include_directories(
    hello-opencv PRIVATE 
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    hello-opencv
    ${OpenCV_LIBRARIES}
)

message ("OpenCV_LIBRARIES = " ${OpenCV_LIBRARIES})
message ("OpenCV_INCLUDE_DIRS = " ${OpenCV_INCLUDE_DIRS})
