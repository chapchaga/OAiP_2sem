cmake_minimum_required(VERSION 3.16)
project(Lab7_Task4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
    hashtable.h
)

set(UI_FILES
    mainwindow.ui
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_add_executable(Lab7_Task4 ${SOURCES} ${HEADERS} ${UI_FILES})
    target_link_libraries(Lab7_Task4 PRIVATE Qt6::Widgets)
else()
    add_executable(Lab7_Task4 ${SOURCES} ${HEADERS} ${UI_FILES})
    target_link_libraries(Lab7_Task4 PRIVATE Qt5::Widgets)
endif()
