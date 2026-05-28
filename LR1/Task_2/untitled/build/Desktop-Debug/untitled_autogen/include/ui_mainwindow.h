/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QComboBox *shapeTypeCombo;
    QLineEdit *xLineEdit;
    QLineEdit *yLineEdit;
    QLineEdit *param1LineEdit;
    QLineEdit *param2LineEdit;
    QLineEdit *dxLineEdit;
    QLineEdit *dyLineEdit;
    QLineEdit *angleLineEdit;
    QLineEdit *factorLineEdit;
    QPushButton *createButton;
    QPushButton *moveButton;
    QPushButton *rotateButton;
    QPushButton *scaleButton;
    QListWidget *shapeList;
    QCheckBox *animationCheckBox;
    QLabel *areaLabel;
    QLabel *perimeterLabel;
    QLabel *centerLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(0, 0, 471, 331));
        shapeTypeCombo = new QComboBox(centralwidget);
        shapeTypeCombo->setObjectName("shapeTypeCombo");
        shapeTypeCombo->setGeometry(QRect(580, 20, 86, 26));
        xLineEdit = new QLineEdit(centralwidget);
        xLineEdit->setObjectName("xLineEdit");
        xLineEdit->setGeometry(QRect(560, 60, 113, 26));
        yLineEdit = new QLineEdit(centralwidget);
        yLineEdit->setObjectName("yLineEdit");
        yLineEdit->setGeometry(QRect(560, 100, 113, 26));
        param1LineEdit = new QLineEdit(centralwidget);
        param1LineEdit->setObjectName("param1LineEdit");
        param1LineEdit->setGeometry(QRect(560, 140, 113, 26));
        param2LineEdit = new QLineEdit(centralwidget);
        param2LineEdit->setObjectName("param2LineEdit");
        param2LineEdit->setGeometry(QRect(560, 180, 113, 26));
        dxLineEdit = new QLineEdit(centralwidget);
        dxLineEdit->setObjectName("dxLineEdit");
        dxLineEdit->setGeometry(QRect(560, 220, 113, 26));
        dyLineEdit = new QLineEdit(centralwidget);
        dyLineEdit->setObjectName("dyLineEdit");
        dyLineEdit->setGeometry(QRect(560, 260, 113, 26));
        angleLineEdit = new QLineEdit(centralwidget);
        angleLineEdit->setObjectName("angleLineEdit");
        angleLineEdit->setGeometry(QRect(560, 310, 113, 26));
        factorLineEdit = new QLineEdit(centralwidget);
        factorLineEdit->setObjectName("factorLineEdit");
        factorLineEdit->setGeometry(QRect(560, 340, 113, 26));
        createButton = new QPushButton(centralwidget);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(10, 340, 88, 26));
        moveButton = new QPushButton(centralwidget);
        moveButton->setObjectName("moveButton");
        moveButton->setGeometry(QRect(110, 340, 88, 26));
        rotateButton = new QPushButton(centralwidget);
        rotateButton->setObjectName("rotateButton");
        rotateButton->setGeometry(QRect(200, 340, 88, 26));
        scaleButton = new QPushButton(centralwidget);
        scaleButton->setObjectName("scaleButton");
        scaleButton->setGeometry(QRect(300, 340, 88, 26));
        shapeList = new QListWidget(centralwidget);
        shapeList->setObjectName("shapeList");
        shapeList->setGeometry(QRect(0, 370, 256, 192));
        animationCheckBox = new QCheckBox(centralwidget);
        animationCheckBox->setObjectName("animationCheckBox");
        animationCheckBox->setGeometry(QRect(290, 450, 92, 24));
        areaLabel = new QLabel(centralwidget);
        areaLabel->setObjectName("areaLabel");
        areaLabel->setGeometry(QRect(460, 440, 66, 18));
        perimeterLabel = new QLabel(centralwidget);
        perimeterLabel->setObjectName("perimeterLabel");
        perimeterLabel->setGeometry(QRect(460, 470, 66, 18));
        centerLabel = new QLabel(centralwidget);
        centerLabel->setObjectName("centerLabel");
        centerLabel->setGeometry(QRect(570, 450, 66, 18));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        createButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214", nullptr));
        rotateButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        scaleButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        animationCheckBox->setText(QCoreApplication::translate("MainWindow", "\320\220\320\275\320\270\320\274\320\260\321\206\320\270\321\217", nullptr));
        areaLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214", nullptr));
        perimeterLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\270\320\274\320\265\321\202\321\200", nullptr));
        centerLabel->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\321\202\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
