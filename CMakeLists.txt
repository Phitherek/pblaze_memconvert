cmake_minimum_required(VERSION 3.3)
project(pblaze_memconvert)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")

set(SOURCE_FILES main.cpp)
add_executable(pblaze_memconvert ${SOURCE_FILES})