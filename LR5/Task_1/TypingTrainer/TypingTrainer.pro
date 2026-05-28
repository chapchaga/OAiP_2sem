QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = TypingTrainer
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    keyboardwidget.cpp \
    textdisplaywidget.cpp \
    statswidget.cpp

HEADERS += \
    mainwindow.h \
    keyboardwidget.h \
    textdisplaywidget.h \
    statswidget.h \
    languagedata.h

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CC = /usr/bin/clang
QMAKE_CXX = /usr/bin/clang++
QMAKE_LINK = /usr/bin/clang++
QMAKE_CXXFLAGS += -Wno-implicit-function-declaration
QMAKE_CFLAGS += -Wno-implicit-function-declaration
