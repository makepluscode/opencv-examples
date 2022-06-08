cmake_minimum_required(VERSION 3.0)

project(multi-image-concat)

find_package(OpenCV REQUIRED)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}
)

add_executable(
    multi-image-concat
    src/main.cpp
)

target_include_directories(
    multi-image-concat
 PRIVATE 
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    multi-image-concat
    ${OpenCV_LIBRARIES}
)

message ("OpenCV_LIBRARIES = " ${OpenCV_LIBRARIES})
message ("OpenCV_INCLUDE_DIRS = " ${OpenCV_INCLUDE_DIRS})
