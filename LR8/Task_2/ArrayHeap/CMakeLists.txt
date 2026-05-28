cmake_minimum_required(VERSION 3.16)
project(ArrayHeap)

set(CMAKE_CXX_STANDARD 17)

add_library(ArrayHeap STATIC ArrayHeap.cpp)
target_include_directories(ArrayHeap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
