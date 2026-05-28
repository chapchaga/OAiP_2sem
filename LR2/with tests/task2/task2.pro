QT       += core gui widgets
CONFIG   += c++17
TARGET    = task2
TEMPLATE  = app

SOURCES  += main.cpp \
            Candidate.cpp \
            MainWindow2.cpp \
            CandidateDialog.cpp \
            GlassBoxTest.cpp \
            XlsxWriter.cpp

HEADERS  += Candidate.h \
            MainWindow2.h \
            CandidateDialog.h \
            GlassBoxTest.h \
            XlsxWriter.h

FORMS    += MainWindow2.ui \
            CandidateDialog.ui
