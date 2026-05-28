/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QGroupBox *groupFile;
    QHBoxLayout *hboxLayout;
    QPushButton *btnLoad;
    QSpacerItem *spacerItem;
    QLabel *labelSize;
    QListWidget *listWidget;
    QGroupBox *groupOps;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLabel *label_2;
    QLineEdit *lineEditInput;
    QPushButton *btnPushBack;
    QPushButton *btnPushFront;
    QHBoxLayout *hboxLayout2;
    QPushButton *btnPopFront;
    QPushButton *btnPopBack;
    QPushButton *btnClear;
    QSpacerItem *spacerItem1;
    QGroupBox *groupMove;
    QHBoxLayout *hboxLayout3;
    QLabel *label;
    QSpinBox *spinStart;
    QLabel *label1;
    QSpinBox *spinEnd;
    QLabel *label2;
    QSpinBox *spinTarget;
    QPushButton *btnMove;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 580);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        groupFile = new QGroupBox(centralwidget);
        groupFile->setObjectName("groupFile");
        hboxLayout = new QHBoxLayout(groupFile);
        hboxLayout->setObjectName("hboxLayout");
        btnLoad = new QPushButton(groupFile);
        btnLoad->setObjectName("btnLoad");

        hboxLayout->addWidget(btnLoad);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);

        labelSize = new QLabel(groupFile);
        labelSize->setObjectName("labelSize");

        hboxLayout->addWidget(labelSize);


        mainLayout->addWidget(groupFile);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");

        mainLayout->addWidget(listWidget);

        groupOps = new QGroupBox(centralwidget);
        groupOps->setObjectName("groupOps");
        vboxLayout = new QVBoxLayout(groupOps);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        label_2 = new QLabel(groupOps);
        label_2->setObjectName("label_2");

        hboxLayout1->addWidget(label_2);

        lineEditInput = new QLineEdit(groupOps);
        lineEditInput->setObjectName("lineEditInput");

        hboxLayout1->addWidget(lineEditInput);

        btnPushBack = new QPushButton(groupOps);
        btnPushBack->setObjectName("btnPushBack");

        hboxLayout1->addWidget(btnPushBack);

        btnPushFront = new QPushButton(groupOps);
        btnPushFront->setObjectName("btnPushFront");

        hboxLayout1->addWidget(btnPushFront);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        btnPopFront = new QPushButton(groupOps);
        btnPopFront->setObjectName("btnPopFront");

        hboxLayout2->addWidget(btnPopFront);

        btnPopBack = new QPushButton(groupOps);
        btnPopBack->setObjectName("btnPopBack");

        hboxLayout2->addWidget(btnPopBack);

        btnClear = new QPushButton(groupOps);
        btnClear->setObjectName("btnClear");

        hboxLayout2->addWidget(btnClear);

        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem1);


        vboxLayout->addLayout(hboxLayout2);


        mainLayout->addWidget(groupOps);

        groupMove = new QGroupBox(centralwidget);
        groupMove->setObjectName("groupMove");
        hboxLayout3 = new QHBoxLayout(groupMove);
        hboxLayout3->setObjectName("hboxLayout3");
        label = new QLabel(groupMove);
        label->setObjectName("label");

        hboxLayout3->addWidget(label);

        spinStart = new QSpinBox(groupMove);
        spinStart->setObjectName("spinStart");
        spinStart->setMinimum(1);
        spinStart->setMaximum(9999);
        spinStart->setValue(1);

        hboxLayout3->addWidget(spinStart);

        label1 = new QLabel(groupMove);
        label1->setObjectName("label1");

        hboxLayout3->addWidget(label1);

        spinEnd = new QSpinBox(groupMove);
        spinEnd->setObjectName("spinEnd");
        spinEnd->setMinimum(1);
        spinEnd->setMaximum(9999);
        spinEnd->setValue(2);

        hboxLayout3->addWidget(spinEnd);

        label2 = new QLabel(groupMove);
        label2->setObjectName("label2");

        hboxLayout3->addWidget(label2);

        spinTarget = new QSpinBox(groupMove);
        spinTarget->setObjectName("spinTarget");
        spinTarget->setMinimum(0);
        spinTarget->setMaximum(9999);
        spinTarget->setValue(0);

        hboxLayout3->addWidget(spinTarget);

        btnMove = new QPushButton(groupMove);
        btnMove->setObjectName("btnMove");

        hboxLayout3->addWidget(btnMove);


        mainLayout->addWidget(groupMove);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lab7 Task1 \342\200\224 Doubly Linked Queue", nullptr));
        groupFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "Load from file\342\200\246", nullptr));
        labelSize->setText(QCoreApplication::translate("MainWindow", "Size: 0", nullptr));
        groupOps->setTitle(QCoreApplication::translate("MainWindow", "Queue operations", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Text:", nullptr));
        lineEditInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter a line of text", nullptr));
        btnPushBack->setText(QCoreApplication::translate("MainWindow", "Push Back", nullptr));
        btnPushFront->setText(QCoreApplication::translate("MainWindow", "Push Front", nullptr));
        btnPopFront->setText(QCoreApplication::translate("MainWindow", "Pop Front", nullptr));
        btnPopBack->setText(QCoreApplication::translate("MainWindow", "Pop Back", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        groupMove->setTitle(QCoreApplication::translate("MainWindow", "Move block (variant task)", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Start line:", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "End line:", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Insert after position:", nullptr));
        btnMove->setText(QCoreApplication::translate("MainWindow", "Move Block", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
