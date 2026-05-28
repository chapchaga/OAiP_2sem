cmake_minimum_required(VERSION 3.16)
project(HeapApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_subdirectory(${ROOT_DIR}/ArrayHeap ${CMAKE_BINARY_DIR}/ArrayHeap)
add_subdirectory(${ROOT_DIR}/ListHeap  ${CMAKE_BINARY_DIR}/ListHeap)

add_executable(HeapApp
    src/main.cpp
    src/mainwindow.cpp
    ui/mainwindow.ui
)

target_include_directories(HeapApp PRIVATE
    src
    ${ROOT_DIR}/ArrayHeap
    ${ROOT_DIR}/ListHeap
)

target_link_libraries(HeapApp PRIVATE
    Qt6::Widgets
    ArrayHeap
    ListHeap
)
