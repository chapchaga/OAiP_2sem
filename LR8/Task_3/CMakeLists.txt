cmake_minimum_required(VERSION 3.16)
project(Lab8_Task3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
)

set(HEADERS
    include/BSTNode.h
    include/Map.h
    include/Set.h
    include/HashTable.h
    include/MainWindow.h
)

set(UI_FILES
    ui/mainwindow.ui
)

add_executable(Lab8_Task3
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
)

target_include_directories(Lab8_Task3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(Lab8_Task3 PRIVATE Qt6::Widgets)
else()
    target_link_libraries(Lab8_Task3 PRIVATE Qt5::Widgets)
endif()
