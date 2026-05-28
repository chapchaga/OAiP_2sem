QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET   = BitSetVisualizer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    bitset.cpp

HEADERS += \
    mainwindow.h \
    bitset.h

# Suppress deprecation warnings
DEFINES += QT_DEPRECATED_WARNINGS

# Compiler flags
QMAKE_CXXFLAGS += -O2
