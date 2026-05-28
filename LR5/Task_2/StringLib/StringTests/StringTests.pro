QT += testlib
QT -= gui
TARGET   = StringTests
TEMPLATE = app
CONFIG  += console c++17
CONFIG  -= app_bundle

SOURCES += tst_mystring.cpp

INCLUDEPATH += ../StringLib
LIBS        += -L../StringLib -lStringLib

macx {
    QMAKE_CXXFLAGS += -Wno-implicit-function-declaration
}

macx {
    QMAKE_LFLAGS += -Wl,-rpath,@executable_path/../Frameworks
    QMAKE_LFLAGS += -Wl,-rpath,$$PWD/../StringLib
}

unix:!macx {
    QMAKE_LFLAGS += -Wl,-rpath,$$PWD/../StringLib
}
