cmake_minimum_required(VERSION 3.16)
project(Lab7_Task1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Lab7_Task1
    main.cpp
    MainWindow.cpp
    DoublyLinkedQueue.cpp
    MainWindow.h
    DoublyLinkedQueue.h
    MainWindow.ui
)

target_link_libraries(Lab7_Task1 PRIVATE Qt6::Widgets)
