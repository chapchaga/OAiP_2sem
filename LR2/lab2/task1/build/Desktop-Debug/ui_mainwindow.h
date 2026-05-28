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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *btnOpenFile;
    QPushButton *btnSave;
    QPushButton *btnRunTests;
    QTableWidget *tableWidget;
    QHBoxLayout *hboxLayout1;
    QPushButton *btnNextDay;
    QPushButton *btnPrevDay;
    QPushButton *btnWeekNumber;
    QPushButton *btnDuration;
    QHBoxLayout *hboxLayout2;
    QLabel *label;
    QLineEdit *lineEditBirthday;
    QPushButton *btnBirthday;
    QHBoxLayout *hboxLayout3;
    QLabel *label1;
    QLineEdit *lineEditNewDate;
    QPushButton *btnAddDate;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        btnOpenFile = new QPushButton(centralwidget);
        btnOpenFile->setObjectName("btnOpenFile");

        hboxLayout->addWidget(btnOpenFile);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");

        hboxLayout->addWidget(btnSave);

        btnRunTests = new QPushButton(centralwidget);
        btnRunTests->setObjectName("btnRunTests");

        hboxLayout->addWidget(btnRunTests);


        vboxLayout->addLayout(hboxLayout);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        vboxLayout->addWidget(tableWidget);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        btnNextDay = new QPushButton(centralwidget);
        btnNextDay->setObjectName("btnNextDay");

        hboxLayout1->addWidget(btnNextDay);

        btnPrevDay = new QPushButton(centralwidget);
        btnPrevDay->setObjectName("btnPrevDay");

        hboxLayout1->addWidget(btnPrevDay);

        btnWeekNumber = new QPushButton(centralwidget);
        btnWeekNumber->setObjectName("btnWeekNumber");

        hboxLayout1->addWidget(btnWeekNumber);

        btnDuration = new QPushButton(centralwidget);
        btnDuration->setObjectName("btnDuration");

        hboxLayout1->addWidget(btnDuration);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        hboxLayout2->addWidget(label);

        lineEditBirthday = new QLineEdit(centralwidget);
        lineEditBirthday->setObjectName("lineEditBirthday");

        hboxLayout2->addWidget(lineEditBirthday);

        btnBirthday = new QPushButton(centralwidget);
        btnBirthday->setObjectName("btnBirthday");

        hboxLayout2->addWidget(btnBirthday);


        vboxLayout->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        label1 = new QLabel(centralwidget);
        label1->setObjectName("label1");

        hboxLayout3->addWidget(label1);

        lineEditNewDate = new QLineEdit(centralwidget);
        lineEditNewDate->setObjectName("lineEditNewDate");

        hboxLayout3->addWidget(lineEditNewDate);

        btnAddDate = new QPushButton(centralwidget);
        btnAddDate->setObjectName("btnAddDate");

        hboxLayout3->addWidget(btnAddDate);


        vboxLayout->addLayout(hboxLayout3);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1 \342\200\224 \320\232\320\273\320\260\321\201\321\201 Date", nullptr));
        btnOpenFile->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        btnRunTests->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \321\202\320\265\321\201\321\202\321\213 (\320\273\320\276\320\263)", nullptr));
        btnNextDay->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        btnPrevDay->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        btnWeekNumber->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\275\320\265\320\264\320\265\320\273\320\270 / \320\222\320\270\321\201\320\276\320\272\320\276\321\201\320\275\321\213\320\271", nullptr));
        btnDuration->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\275\320\270\321\206\320\260 \321\201\320\276 \321\201\320\273\320\265\320\264\321\203\321\216\321\211\320\265\320\271", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217 (\320\224\320\224.\320\234\320\234.\320\223\320\223\320\223\320\223):", nullptr));
        lineEditBirthday->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200 15.05.1995", nullptr));
        btnBirthday->setText(QCoreApplication::translate("MainWindow", "\320\224\320\275\320\265\320\271 \320\264\320\276 \320\224\320\240", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \320\264\320\260\321\202\320\260:", nullptr));
        lineEditNewDate->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\224\320\224.\320\234\320\234.\320\223\320\223\320\223\320\223", nullptr));
        btnAddDate->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
