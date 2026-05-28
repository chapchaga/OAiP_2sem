cmake_minimum_required(VERSION 3.16)
project(ListHeap)

set(CMAKE_CXX_STANDARD 17)

add_library(ListHeap SHARED ListHeap.cpp)
target_include_directories(ListHeap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
