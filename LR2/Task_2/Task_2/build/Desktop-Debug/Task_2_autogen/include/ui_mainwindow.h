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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *editDistrict;
    QLineEdit *editName;
    QLineEdit *editParty;
    QLineEdit *editAge;
    QLineEdit *editProfession;
    QLineEdit *editIncome;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnSave;
    QPushButton *btnOpen;
    QPushButton *btnShow;
    QPushButton *btnStats;
    QTextEdit *memo;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        editDistrict = new QLineEdit(centralwidget);
        editDistrict->setObjectName("editDistrict");
        editDistrict->setGeometry(QRect(110, 20, 441, 26));
        editName = new QLineEdit(centralwidget);
        editName->setObjectName("editName");
        editName->setGeometry(QRect(110, 60, 441, 26));
        editParty = new QLineEdit(centralwidget);
        editParty->setObjectName("editParty");
        editParty->setGeometry(QRect(110, 100, 441, 26));
        editAge = new QLineEdit(centralwidget);
        editAge->setObjectName("editAge");
        editAge->setGeometry(QRect(110, 140, 441, 26));
        editProfession = new QLineEdit(centralwidget);
        editProfession->setObjectName("editProfession");
        editProfession->setGeometry(QRect(110, 180, 441, 26));
        editIncome = new QLineEdit(centralwidget);
        editIncome->setObjectName("editIncome");
        editIncome->setGeometry(QRect(110, 220, 441, 26));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(650, 10, 141, 26));
        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(650, 50, 141, 26));
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");
        btnSave->setGeometry(QRect(650, 90, 141, 26));
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName("btnOpen");
        btnOpen->setGeometry(QRect(650, 130, 141, 26));
        btnShow = new QPushButton(centralwidget);
        btnShow->setObjectName("btnShow");
        btnShow->setGeometry(QRect(650, 170, 141, 26));
        btnStats = new QPushButton(centralwidget);
        btnStats->setObjectName("btnStats");
        btnStats->setGeometry(QRect(650, 210, 141, 26));
        memo = new QTextEdit(centralwidget);
        memo->setObjectName("memo");
        memo->setGeometry(QRect(0, 260, 801, 291));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 66, 18));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 60, 66, 18));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 100, 66, 18));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 140, 66, 18));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 180, 81, 20));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 220, 66, 18));
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
        editDistrict->setText(QString());
        editName->setText(QString());
        editParty->setText(QString());
        editAge->setText(QString());
        editProfession->setText(QString());
        editIncome->setText(QString());
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        btnShow->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\262\321\201\320\265\321\205", nullptr));
        btnStats->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260 \320\277\320\260\321\200\321\202\320\270\320\270", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\236\320\272\321\200\321\203\320\263", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\244\320\230\320\236", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\321\202\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\204\320\265\321\201\321\201\320\270\321\217", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
