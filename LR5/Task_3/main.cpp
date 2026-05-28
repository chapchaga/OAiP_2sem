#define _ARM_ACLE_H 1
#if defined(__arm64__) || defined(__aarch64__)
#include <arm_acle.h>
#endif

#include <QApplication>
#include "mainwindow.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    // Nice dark-ish palette
    QPalette p;
    p.setColor(QPalette::Window,          QColor(40,  44,  52));
    p.setColor(QPalette::WindowText,      QColor(220, 220, 220));
    p.setColor(QPalette::Base,            QColor(30,  33,  39));
    p.setColor(QPalette::AlternateBase,   QColor(50,  55,  65));
    p.setColor(QPalette::ToolTipBase,     QColor(220, 220, 220));
    p.setColor(QPalette::ToolTipText,     QColor(20,  20,  20));
    p.setColor(QPalette::Text,            QColor(220, 220, 220));
    p.setColor(QPalette::Button,          QColor(55,  60,  72));
    p.setColor(QPalette::ButtonText,      QColor(220, 220, 220));
    p.setColor(QPalette::Highlight,       QColor(80, 140, 230));
    p.setColor(QPalette::HighlightedText, Qt::white);
    app.setPalette(p);

    MainWindow w;
    w.show();
    return app.exec();
}
