cmake_minimum_required(VERSION 3.16)
project(LR1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(LR1
    src/main.cpp
    src/MainWindow.cpp
    src/CanvasWidget.cpp
    src/MovingRectangle.cpp
    src/Car.cpp
)

target_link_libraries(LR1 PRIVATE Qt6::Widgets)

