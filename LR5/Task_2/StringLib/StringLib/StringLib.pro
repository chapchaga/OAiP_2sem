QT -= gui
TARGET = StringLib
TEMPLATE = lib
CONFIG += shared c++17
DEFINES += STRINGLIB_LIBRARY

HEADERS += \
    mystring.h

SOURCES += \
    mystring.cpp

macx {
    QMAKE_CXXFLAGS += -Wno-implicit-function-declaration
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
