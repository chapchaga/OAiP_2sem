cmake_minimum_required(VERSION 3.16)
project(ShapesApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/canvas.cpp
    src/shape.cpp
    src/circle.cpp
    src/triangle.cpp
    src/rectangle.cpp
    src/square.cpp
    src/rhombus.cpp
    src/star.cpp
    src/hexagon.cpp
    src/arrow.cpp
    src/shapegroup.cpp
    src/animationsequence.cpp
    src/animationstep.cpp
)

set(HEADERS
    include/mainwindow.h
    include/canvas.h
    include/shape.h
    include/circle.h
    include/triangle.h
    include/rectangle.h
    include/square.h
    include/rhombus.h
    include/star.h
    include/hexagon.h
    include/arrow.h
    include/shapegroup.h
    include/animationsequence.h
    include/animationstep.h
)

add_executable(ShapesApp ${SOURCES} ${HEADERS})

target_include_directories(ShapesApp PRIVATE include)
target_link_libraries(ShapesApp Qt6::Core Qt6::Widgets)
