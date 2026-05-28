cmake_minimum_required(VERSION 3.16)
project(Lab6_Task1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Lab6_Task1
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(Lab6_Task1 PRIVATE Qt6::Widgets)

# ──────────────────────────────────────────────
# Функциональные тесты (без Qt)
# Запуск: cmake --build . && ctest -V
#         или напрямую: ./test_lab6
# ──────────────────────────────────────────────
enable_testing()

add_executable(test_lab6
    tests/test_lab6.cpp
)

target_compile_features(test_lab6 PRIVATE cxx_std_17)

add_test(NAME lab6_functional_tests COMMAND test_lab6)
