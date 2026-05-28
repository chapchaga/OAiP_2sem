/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *toolbarLayout;
    QPushButton *btnOpen;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnRunTests;
    QSpacerItem *spacerTop;
    QTableWidget *tableWidget;
    QHBoxLayout *funcLayout;
    QPushButton *btnNextDay;
    QPushButton *btnPrevDay;
    QPushButton *btnWeekNum;
    QPushButton *btnDuration;
    QHBoxLayout *birthdayLayout;
    QLabel *labelBD;
    QLineEdit *editBirthday;
    QPushButton *btnBirthday;
    QSpacerItem *spacerBottom;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setObjectName("toolbarLayout");
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName("btnOpen");

        toolbarLayout->addWidget(btnOpen);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");

        toolbarLayout->addWidget(btnAdd);

        btnEdit = new QPushButton(centralwidget);
        btnEdit->setObjectName("btnEdit");

        toolbarLayout->addWidget(btnEdit);

        btnRunTests = new QPushButton(centralwidget);
        btnRunTests->setObjectName("btnRunTests");

        toolbarLayout->addWidget(btnRunTests);

        spacerTop = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        toolbarLayout->addItem(spacerTop);


        verticalLayout->addLayout(toolbarLayout);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableWidget);

        funcLayout = new QHBoxLayout();
        funcLayout->setObjectName("funcLayout");
        btnNextDay = new QPushButton(centralwidget);
        btnNextDay->setObjectName("btnNextDay");

        funcLayout->addWidget(btnNextDay);

        btnPrevDay = new QPushButton(centralwidget);
        btnPrevDay->setObjectName("btnPrevDay");

        funcLayout->addWidget(btnPrevDay);

        btnWeekNum = new QPushButton(centralwidget);
        btnWeekNum->setObjectName("btnWeekNum");

        funcLayout->addWidget(btnWeekNum);

        btnDuration = new QPushButton(centralwidget);
        btnDuration->setObjectName("btnDuration");

        funcLayout->addWidget(btnDuration);


        verticalLayout->addLayout(funcLayout);

        birthdayLayout = new QHBoxLayout();
        birthdayLayout->setObjectName("birthdayLayout");
        labelBD = new QLabel(centralwidget);
        labelBD->setObjectName("labelBD");

        birthdayLayout->addWidget(labelBD);

        editBirthday = new QLineEdit(centralwidget);
        editBirthday->setObjectName("editBirthday");

        birthdayLayout->addWidget(editBirthday);

        btnBirthday = new QPushButton(centralwidget);
        btnBirthday->setObjectName("btnBirthday");

        birthdayLayout->addWidget(btnBirthday);

        spacerBottom = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        birthdayLayout->addItem(spacerBottom);


        verticalLayout->addLayout(birthdayLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 1 \342\200\224 \320\232\320\273\320\260\321\201\321\201 Date", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273...", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
        btnRunTests->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \321\202\320\265\321\201\321\202\321\213 (\320\273\320\276\320\263)", nullptr));
        btnNextDay->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        btnPrevDay->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\320\271 \320\264\320\265\320\275\321\214", nullptr));
        btnWeekNum->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\275\320\265\320\264\320\265\320\273\320\270", nullptr));
        btnDuration->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\275\320\270\321\206\320\260 \320\264\320\260\321\202", nullptr));
        labelBD->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217 (\320\264\320\264.\320\274\320\274.\320\263\320\263\320\263\320\263):", nullptr));
        editBirthday->setPlaceholderText(QCoreApplication::translate("MainWindow", "01.01.2000", nullptr));
        btnBirthday->setText(QCoreApplication::translate("MainWindow", "\320\224\320\275\320\265\320\271 \320\264\320\276 \320\224\320\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
