QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CFLAGS += -include arm_acle.h
QMAKE_CXXFLAGS += -include arm_acle.h

CONFIG += c++17

TARGET   = task2_restaurant
TEMPLATE = app

SOURCES += \
    main.cpp           \
    mainwindow.cpp     \
    dish.cpp           \
    order.cpp          \
    restaurantmanager.cpp

HEADERS += \
    mainwindow.h        \
    dish.h              \
    order.h             \
    restaurantmanager.h \
    glasstests.h        \
    xlsxwriter.h

FORMS += \
    mainwindow.ui
