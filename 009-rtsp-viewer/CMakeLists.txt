cmake_minimum_required(VERSION 3.0)

project(rtsp-viewer)

find_package(OpenCV REQUIRED)

set(
    CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_HOME_DIRECTORY}
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
 PRIVATE 
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBRARIES}
)

message ("OpenCV_LIBRARIES = " ${OpenCV_LIBRARIES})
message ("OpenCV_INCLUDE_DIRS = " ${OpenCV_INCLUDE_DIRS})
