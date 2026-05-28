#include <QApplication>
#include "MainWindow2.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow2 w;
    w.show();
    return app.exec();
}
