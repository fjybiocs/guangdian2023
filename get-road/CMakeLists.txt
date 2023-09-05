cmake_minimum_required(VERSION 3.23)
project(guangdian)

set(CMAKE_CXX_STANDARD 17)

message(${CMAKE_SOURCE_DIR})

# 添加头文件路径
include_directories(${CMAKE_SOURCE_DIR})

add_executable(guangdian maze.cpp mazeTravel.cpp main.cpp)
