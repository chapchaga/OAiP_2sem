#include <QApplication>
#include <QScreen>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Enable high DPI support
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Set application metadata
    app.setApplicationName("Typing Trainer");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("LabWork5");

    MainWindow window;

    // Center on screen
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - window.width()) / 2;
    int y = (screenGeometry.height() - window.height()) / 2;
    window.move(x, y);

    window.show();
    return app.exec();
}
