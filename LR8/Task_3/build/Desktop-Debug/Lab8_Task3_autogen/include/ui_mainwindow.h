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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QTabWidget *tabWidget;
    QWidget *tabMap;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *mapKeyInput;
    QLabel *label1;
    QLineEdit *mapValueInput;
    QPushButton *mapInsertBtn;
    QPushButton *mapEraseBtn;
    QPushButton *mapFindBtn;
    QPushButton *mapClearBtn;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout1;
    QLabel *label2;
    QListWidget *mapTreeList;
    QVBoxLayout *vboxLayout2;
    QLabel *label3;
    QListWidget *mapLinkedList;
    QLabel *mapStatusLabel;
    QWidget *tabSet;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout2;
    QLabel *label4;
    QLineEdit *setKeyInput;
    QPushButton *setInsertBtn;
    QPushButton *setEraseBtn;
    QPushButton *setContainsBtn;
    QPushButton *setClearBtn;
    QHBoxLayout *hboxLayout3;
    QVBoxLayout *vboxLayout4;
    QLabel *label5;
    QListWidget *setTreeList;
    QVBoxLayout *vboxLayout5;
    QLabel *label6;
    QListWidget *setLinkedList;
    QLabel *setStatusLabel;
    QWidget *tabHash;
    QVBoxLayout *vboxLayout6;
    QHBoxLayout *hboxLayout4;
    QLabel *label7;
    QLineEdit *hashKeyInput;
    QLabel *label8;
    QLineEdit *hashValueInput;
    QPushButton *hashInsertBtn;
    QPushButton *hashEraseBtn;
    QPushButton *hashFindBtn;
    QPushButton *hashClearBtn;
    QHBoxLayout *hboxLayout5;
    QVBoxLayout *vboxLayout7;
    QLabel *label9;
    QListWidget *hashList;
    QVBoxLayout *vboxLayout8;
    QLabel *label10;
    QLabel *hashStatsLabel;
    QLabel *hashStatusLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(960, 680);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setObjectName("mainLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabMap = new QWidget();
        tabMap->setObjectName("tabMap");
        vboxLayout = new QVBoxLayout(tabMap);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(tabMap);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        mapKeyInput = new QLineEdit(tabMap);
        mapKeyInput->setObjectName("mapKeyInput");

        hboxLayout->addWidget(mapKeyInput);

        label1 = new QLabel(tabMap);
        label1->setObjectName("label1");

        hboxLayout->addWidget(label1);

        mapValueInput = new QLineEdit(tabMap);
        mapValueInput->setObjectName("mapValueInput");

        hboxLayout->addWidget(mapValueInput);

        mapInsertBtn = new QPushButton(tabMap);
        mapInsertBtn->setObjectName("mapInsertBtn");

        hboxLayout->addWidget(mapInsertBtn);

        mapEraseBtn = new QPushButton(tabMap);
        mapEraseBtn->setObjectName("mapEraseBtn");

        hboxLayout->addWidget(mapEraseBtn);

        mapFindBtn = new QPushButton(tabMap);
        mapFindBtn->setObjectName("mapFindBtn");

        hboxLayout->addWidget(mapFindBtn);

        mapClearBtn = new QPushButton(tabMap);
        mapClearBtn->setObjectName("mapClearBtn");

        hboxLayout->addWidget(mapClearBtn);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName("vboxLayout1");
        label2 = new QLabel(tabMap);
        label2->setObjectName("label2");

        vboxLayout1->addWidget(label2);

        mapTreeList = new QListWidget(tabMap);
        mapTreeList->setObjectName("mapTreeList");

        vboxLayout1->addWidget(mapTreeList);


        hboxLayout1->addLayout(vboxLayout1);

        vboxLayout2 = new QVBoxLayout();
        vboxLayout2->setObjectName("vboxLayout2");
        label3 = new QLabel(tabMap);
        label3->setObjectName("label3");

        vboxLayout2->addWidget(label3);

        mapLinkedList = new QListWidget(tabMap);
        mapLinkedList->setObjectName("mapLinkedList");

        vboxLayout2->addWidget(mapLinkedList);


        hboxLayout1->addLayout(vboxLayout2);


        vboxLayout->addLayout(hboxLayout1);

        mapStatusLabel = new QLabel(tabMap);
        mapStatusLabel->setObjectName("mapStatusLabel");

        vboxLayout->addWidget(mapStatusLabel);

        tabWidget->addTab(tabMap, QString());
        tabSet = new QWidget();
        tabSet->setObjectName("tabSet");
        vboxLayout3 = new QVBoxLayout(tabSet);
        vboxLayout3->setObjectName("vboxLayout3");
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        label4 = new QLabel(tabSet);
        label4->setObjectName("label4");

        hboxLayout2->addWidget(label4);

        setKeyInput = new QLineEdit(tabSet);
        setKeyInput->setObjectName("setKeyInput");

        hboxLayout2->addWidget(setKeyInput);

        setInsertBtn = new QPushButton(tabSet);
        setInsertBtn->setObjectName("setInsertBtn");

        hboxLayout2->addWidget(setInsertBtn);

        setEraseBtn = new QPushButton(tabSet);
        setEraseBtn->setObjectName("setEraseBtn");

        hboxLayout2->addWidget(setEraseBtn);

        setContainsBtn = new QPushButton(tabSet);
        setContainsBtn->setObjectName("setContainsBtn");

        hboxLayout2->addWidget(setContainsBtn);

        setClearBtn = new QPushButton(tabSet);
        setClearBtn->setObjectName("setClearBtn");

        hboxLayout2->addWidget(setClearBtn);


        vboxLayout3->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        vboxLayout4 = new QVBoxLayout();
        vboxLayout4->setObjectName("vboxLayout4");
        label5 = new QLabel(tabSet);
        label5->setObjectName("label5");

        vboxLayout4->addWidget(label5);

        setTreeList = new QListWidget(tabSet);
        setTreeList->setObjectName("setTreeList");

        vboxLayout4->addWidget(setTreeList);


        hboxLayout3->addLayout(vboxLayout4);

        vboxLayout5 = new QVBoxLayout();
        vboxLayout5->setObjectName("vboxLayout5");
        label6 = new QLabel(tabSet);
        label6->setObjectName("label6");

        vboxLayout5->addWidget(label6);

        setLinkedList = new QListWidget(tabSet);
        setLinkedList->setObjectName("setLinkedList");

        vboxLayout5->addWidget(setLinkedList);


        hboxLayout3->addLayout(vboxLayout5);


        vboxLayout3->addLayout(hboxLayout3);

        setStatusLabel = new QLabel(tabSet);
        setStatusLabel->setObjectName("setStatusLabel");

        vboxLayout3->addWidget(setStatusLabel);

        tabWidget->addTab(tabSet, QString());
        tabHash = new QWidget();
        tabHash->setObjectName("tabHash");
        vboxLayout6 = new QVBoxLayout(tabHash);
        vboxLayout6->setObjectName("vboxLayout6");
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setObjectName("hboxLayout4");
        label7 = new QLabel(tabHash);
        label7->setObjectName("label7");

        hboxLayout4->addWidget(label7);

        hashKeyInput = new QLineEdit(tabHash);
        hashKeyInput->setObjectName("hashKeyInput");

        hboxLayout4->addWidget(hashKeyInput);

        label8 = new QLabel(tabHash);
        label8->setObjectName("label8");

        hboxLayout4->addWidget(label8);

        hashValueInput = new QLineEdit(tabHash);
        hashValueInput->setObjectName("hashValueInput");

        hboxLayout4->addWidget(hashValueInput);

        hashInsertBtn = new QPushButton(tabHash);
        hashInsertBtn->setObjectName("hashInsertBtn");

        hboxLayout4->addWidget(hashInsertBtn);

        hashEraseBtn = new QPushButton(tabHash);
        hashEraseBtn->setObjectName("hashEraseBtn");

        hboxLayout4->addWidget(hashEraseBtn);

        hashFindBtn = new QPushButton(tabHash);
        hashFindBtn->setObjectName("hashFindBtn");

        hboxLayout4->addWidget(hashFindBtn);

        hashClearBtn = new QPushButton(tabHash);
        hashClearBtn->setObjectName("hashClearBtn");

        hboxLayout4->addWidget(hashClearBtn);


        vboxLayout6->addLayout(hboxLayout4);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setObjectName("hboxLayout5");
        vboxLayout7 = new QVBoxLayout();
        vboxLayout7->setObjectName("vboxLayout7");
        label9 = new QLabel(tabHash);
        label9->setObjectName("label9");

        vboxLayout7->addWidget(label9);

        hashList = new QListWidget(tabHash);
        hashList->setObjectName("hashList");

        vboxLayout7->addWidget(hashList);


        hboxLayout5->addLayout(vboxLayout7);

        vboxLayout8 = new QVBoxLayout();
        vboxLayout8->setObjectName("vboxLayout8");
        label10 = new QLabel(tabHash);
        label10->setObjectName("label10");

        vboxLayout8->addWidget(label10);

        hashStatsLabel = new QLabel(tabHash);
        hashStatsLabel->setObjectName("hashStatsLabel");

        vboxLayout8->addWidget(hashStatsLabel);


        hboxLayout5->addLayout(vboxLayout8);


        vboxLayout6->addLayout(hboxLayout5);

        hashStatusLabel = new QLabel(tabHash);
        hashStatusLabel->setObjectName("hashStatusLabel");

        vboxLayout6->addWidget(hashStatusLabel);

        tabWidget->addTab(tabHash, QString());

        mainLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lab 8 \342\200\224 Map / Set / HashTable", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        mapInsertBtn->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        mapEraseBtn->setText(QCoreApplication::translate("MainWindow", "Erase", nullptr));
        mapFindBtn->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        mapClearBtn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Tree Iterator (in-order):", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Linked List Iterator:", nullptr));
        mapStatusLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabMap), QCoreApplication::translate("MainWindow", "Map", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        setInsertBtn->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        setEraseBtn->setText(QCoreApplication::translate("MainWindow", "Erase", nullptr));
        setContainsBtn->setText(QCoreApplication::translate("MainWindow", "Contains?", nullptr));
        setClearBtn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "Tree Iterator:", nullptr));
        label6->setText(QCoreApplication::translate("MainWindow", "Linked List Iterator:", nullptr));
        setStatusLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabSet), QCoreApplication::translate("MainWindow", "Set", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        label8->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        hashInsertBtn->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        hashEraseBtn->setText(QCoreApplication::translate("MainWindow", "Erase", nullptr));
        hashFindBtn->setText(QCoreApplication::translate("MainWindow", "Contains?", nullptr));
        hashClearBtn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label9->setText(QCoreApplication::translate("MainWindow", "Contents:", nullptr));
        label10->setText(QCoreApplication::translate("MainWindow", "Stats:", nullptr));
        hashStatsLabel->setText(QCoreApplication::translate("MainWindow", "Size: 0  Capacity: 16", nullptr));
        hashStatusLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabHash), QCoreApplication::translate("MainWindow", "HashTable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
