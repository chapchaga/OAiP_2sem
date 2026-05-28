/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabArray;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QSpinBox *spinArray;
    QPushButton *btnArrayInsert;
    QPushButton *btnArrayExtract;
    QPushButton *btnArrayClear;
    QLabel *lblArrayMax;
    QListWidget *listArray;
    QWidget *tabList;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QSpinBox *spinList;
    QPushButton *btnListInsert;
    QPushButton *btnListExtract;
    QPushButton *btnListClear;
    QLabel *lblListMax;
    QListWidget *listList;
    QLabel *statusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 520);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabArray = new QWidget();
        tabArray->setObjectName("tabArray");
        vboxLayout = new QVBoxLayout(tabArray);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        spinArray = new QSpinBox(tabArray);
        spinArray->setObjectName("spinArray");
        spinArray->setMinimum(-9999);
        spinArray->setMaximum(9999);

        hboxLayout->addWidget(spinArray);

        btnArrayInsert = new QPushButton(tabArray);
        btnArrayInsert->setObjectName("btnArrayInsert");

        hboxLayout->addWidget(btnArrayInsert);

        btnArrayExtract = new QPushButton(tabArray);
        btnArrayExtract->setObjectName("btnArrayExtract");

        hboxLayout->addWidget(btnArrayExtract);

        btnArrayClear = new QPushButton(tabArray);
        btnArrayClear->setObjectName("btnArrayClear");

        hboxLayout->addWidget(btnArrayClear);


        vboxLayout->addLayout(hboxLayout);

        lblArrayMax = new QLabel(tabArray);
        lblArrayMax->setObjectName("lblArrayMax");
        lblArrayMax->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(lblArrayMax);

        listArray = new QListWidget(tabArray);
        listArray->setObjectName("listArray");

        vboxLayout->addWidget(listArray);

        tabWidget->addTab(tabArray, QString());
        tabList = new QWidget();
        tabList->setObjectName("tabList");
        vboxLayout1 = new QVBoxLayout(tabList);
        vboxLayout1->setObjectName("vboxLayout1");
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        spinList = new QSpinBox(tabList);
        spinList->setObjectName("spinList");
        spinList->setMinimum(-9999);
        spinList->setMaximum(9999);

        hboxLayout1->addWidget(spinList);

        btnListInsert = new QPushButton(tabList);
        btnListInsert->setObjectName("btnListInsert");

        hboxLayout1->addWidget(btnListInsert);

        btnListExtract = new QPushButton(tabList);
        btnListExtract->setObjectName("btnListExtract");

        hboxLayout1->addWidget(btnListExtract);

        btnListClear = new QPushButton(tabList);
        btnListClear->setObjectName("btnListClear");

        hboxLayout1->addWidget(btnListClear);


        vboxLayout1->addLayout(hboxLayout1);

        lblListMax = new QLabel(tabList);
        lblListMax->setObjectName("lblListMax");
        lblListMax->setAlignment(Qt::AlignCenter);

        vboxLayout1->addWidget(lblListMax);

        listList = new QListWidget(tabList);
        listList->setObjectName("listList");

        vboxLayout1->addWidget(listList);

        tabWidget->addTab(tabList, QString());

        verticalLayout->addWidget(tabWidget);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Binary Heap Visualizer", nullptr));
        btnArrayInsert->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        btnArrayExtract->setText(QCoreApplication::translate("MainWindow", "Extract Max", nullptr));
        btnArrayClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        lblArrayMax->setText(QCoreApplication::translate("MainWindow", "Max: \342\200\224", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabArray), QCoreApplication::translate("MainWindow", "Array Heap (Static Lib)", nullptr));
        btnListInsert->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        btnListExtract->setText(QCoreApplication::translate("MainWindow", "Extract Max", nullptr));
        btnListClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        lblListMax->setText(QCoreApplication::translate("MainWindow", "Max: \342\200\224", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabList), QCoreApplication::translate("MainWindow", "List Heap (Dynamic Lib)", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
