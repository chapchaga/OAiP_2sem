cmake_minimum_required(VERSION 3.16)
project(Lab8_Task2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/App/ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# --- Static library: ArrayHeap ---
add_library(ArrayHeap STATIC
    ArrayHeap/ArrayHeap.cpp
)
target_include_directories(ArrayHeap PUBLIC ArrayHeap)

# --- Shared library: ListHeap ---
add_library(ListHeap SHARED
    ListHeap/ListHeap.cpp
)
target_include_directories(ListHeap PUBLIC ListHeap)

# --- Qt Application ---
add_executable(HeapApp
    App/src/main.cpp
    App/src/mainwindow.cpp
    App/ui/mainwindow.ui
)

target_include_directories(HeapApp PRIVATE
    App/src
    ArrayHeap
    ListHeap
)

target_link_libraries(HeapApp PRIVATE
    Qt6::Widgets
    ArrayHeap
    ListHeap
)
