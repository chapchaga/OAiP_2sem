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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupGen;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpinBox *spinTableSize;
    QLabel *label1;
    QSpinBox *spinCount;
    QPushButton *btnGenerate;
    QPushButton *btnClear;
    QGroupBox *groupOps;
    QHBoxLayout *hboxLayout1;
    QLabel *label2;
    QLineEdit *editKey;
    QLabel *label3;
    QLineEdit *editValue;
    QPushButton *btnInsert;
    QPushButton *btnRemove;
    QPushButton *btnFind;
    QPushButton *btnFindMax;
    QLabel *labelResult;
    QLabel *label4;
    QPlainTextEdit *memoTable;
    QLabel *labelCount;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 560);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupGen = new QGroupBox(centralwidget);
        groupGen->setObjectName("groupGen");
        hboxLayout = new QHBoxLayout(groupGen);
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(groupGen);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        spinTableSize = new QSpinBox(groupGen);
        spinTableSize->setObjectName("spinTableSize");
        spinTableSize->setMinimum(4);
        spinTableSize->setMaximum(64);
        spinTableSize->setValue(8);

        hboxLayout->addWidget(spinTableSize);

        label1 = new QLabel(groupGen);
        label1->setObjectName("label1");

        hboxLayout->addWidget(label1);

        spinCount = new QSpinBox(groupGen);
        spinCount->setObjectName("spinCount");
        spinCount->setMinimum(1);
        spinCount->setMaximum(200);
        spinCount->setValue(12);

        hboxLayout->addWidget(spinCount);

        btnGenerate = new QPushButton(groupGen);
        btnGenerate->setObjectName("btnGenerate");

        hboxLayout->addWidget(btnGenerate);

        btnClear = new QPushButton(groupGen);
        btnClear->setObjectName("btnClear");

        hboxLayout->addWidget(btnClear);


        verticalLayout->addWidget(groupGen);

        groupOps = new QGroupBox(centralwidget);
        groupOps->setObjectName("groupOps");
        hboxLayout1 = new QHBoxLayout(groupOps);
        hboxLayout1->setObjectName("hboxLayout1");
        label2 = new QLabel(groupOps);
        label2->setObjectName("label2");

        hboxLayout1->addWidget(label2);

        editKey = new QLineEdit(groupOps);
        editKey->setObjectName("editKey");
        editKey->setMaximumWidth(80);

        hboxLayout1->addWidget(editKey);

        label3 = new QLabel(groupOps);
        label3->setObjectName("label3");

        hboxLayout1->addWidget(label3);

        editValue = new QLineEdit(groupOps);
        editValue->setObjectName("editValue");
        editValue->setMaximumWidth(120);

        hboxLayout1->addWidget(editValue);

        btnInsert = new QPushButton(groupOps);
        btnInsert->setObjectName("btnInsert");

        hboxLayout1->addWidget(btnInsert);

        btnRemove = new QPushButton(groupOps);
        btnRemove->setObjectName("btnRemove");

        hboxLayout1->addWidget(btnRemove);

        btnFind = new QPushButton(groupOps);
        btnFind->setObjectName("btnFind");

        hboxLayout1->addWidget(btnFind);

        btnFindMax = new QPushButton(groupOps);
        btnFindMax->setObjectName("btnFindMax");

        hboxLayout1->addWidget(btnFindMax);


        verticalLayout->addWidget(groupOps);

        labelResult = new QLabel(centralwidget);
        labelResult->setObjectName("labelResult");
        labelResult->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelResult);

        label4 = new QLabel(centralwidget);
        label4->setObjectName("label4");

        verticalLayout->addWidget(label4);

        memoTable = new QPlainTextEdit(centralwidget);
        memoTable->setObjectName("memoTable");
        memoTable->setReadOnly(true);
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(10);
        memoTable->setFont(font);

        verticalLayout->addWidget(memoTable);

        labelCount = new QLabel(centralwidget);
        labelCount->setObjectName("labelCount");
        labelCount->setAlignment(Qt::AlignRight);

        verticalLayout->addWidget(labelCount);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Hash Table \342\200\224 Stack Chaining (Variant 5: Find Max)", nullptr));
        groupGen->setTitle(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Table size:", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Count:", nullptr));
        btnGenerate->setText(QCoreApplication::translate("MainWindow", "Generate Random", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        groupOps->setTitle(QCoreApplication::translate("MainWindow", "Operations", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        editKey->setPlaceholderText(QCoreApplication::translate("MainWindow", "integer", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        editValue->setPlaceholderText(QCoreApplication::translate("MainWindow", "string", nullptr));
        btnInsert->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        btnFind->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        btnFindMax->setText(QCoreApplication::translate("MainWindow", "Find MAX Key", nullptr));
        labelResult->setText(QCoreApplication::translate("MainWindow", "Result will appear here.", nullptr));
        labelResult->setStyleSheet(QCoreApplication::translate("MainWindow", "font-weight: bold; color: #1a6e2e; font-size: 13px;", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "Hash Table (Array of Stacks):", nullptr));
        labelCount->setText(QCoreApplication::translate("MainWindow", "Total elements: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
