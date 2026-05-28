QT += core gui widgets
TARGET   = StringApp
TEMPLATE = app
CONFIG  += c++17

SOURCES += main.cpp mainwindow.cpp
HEADERS += mainwindow.h

INCLUDEPATH += ../StringLib
LIBS        += -L../StringLib -lStringLib

# ── Fix: Qt 6.11.0 + Apple Silicon (arm64) — missing <arm_acle.h> ──────────
# Qt's qyieldcpu.h calls __yield() without including <arm_acle.h>.
# Clang on macOS treats this as -Werror, which breaks the build.
# Solution: suppress only that specific warning for the whole target.
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
