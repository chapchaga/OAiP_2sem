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
#include <QtWidgets/QPlainTextEdit>
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
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *inputLayout;
    QLabel *valueLabel;
    QSpinBox *valueSpinBox;
    QPushButton *pushBackBtn;
    QPushButton *pushFrontBtn;
    QPushButton *popBackBtn;
    QPushButton *popFrontBtn;
    QHBoxLayout *actionLayout;
    QPushButton *fillRandomBtn;
    QPushButton *clearBtn;
    QSpacerItem *spacerItem;
    QLabel *indexLabel;
    QSpinBox *indexSpinBox;
    QPushButton *getIndexBtn;
    QLabel *infoLabel;
    QLabel *resultLabel;
    QLabel *listLabel;
    QListWidget *dequeList;
    QLabel *logLabel;
    QPlainTextEdit *logEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(700, 560);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        inputLayout = new QHBoxLayout();
        inputLayout->setObjectName("inputLayout");
        valueLabel = new QLabel(centralwidget);
        valueLabel->setObjectName("valueLabel");

        inputLayout->addWidget(valueLabel);

        valueSpinBox = new QSpinBox(centralwidget);
        valueSpinBox->setObjectName("valueSpinBox");
        valueSpinBox->setMinimum(-9999);
        valueSpinBox->setMaximum(9999);
        valueSpinBox->setValue(42);
        valueSpinBox->setMinimumWidth(90);

        inputLayout->addWidget(valueSpinBox);

        pushBackBtn = new QPushButton(centralwidget);
        pushBackBtn->setObjectName("pushBackBtn");

        inputLayout->addWidget(pushBackBtn);

        pushFrontBtn = new QPushButton(centralwidget);
        pushFrontBtn->setObjectName("pushFrontBtn");

        inputLayout->addWidget(pushFrontBtn);

        popBackBtn = new QPushButton(centralwidget);
        popBackBtn->setObjectName("popBackBtn");

        inputLayout->addWidget(popBackBtn);

        popFrontBtn = new QPushButton(centralwidget);
        popFrontBtn->setObjectName("popFrontBtn");

        inputLayout->addWidget(popFrontBtn);


        verticalLayout->addLayout(inputLayout);

        actionLayout = new QHBoxLayout();
        actionLayout->setObjectName("actionLayout");
        fillRandomBtn = new QPushButton(centralwidget);
        fillRandomBtn->setObjectName("fillRandomBtn");

        actionLayout->addWidget(fillRandomBtn);

        clearBtn = new QPushButton(centralwidget);
        clearBtn->setObjectName("clearBtn");

        actionLayout->addWidget(clearBtn);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        actionLayout->addItem(spacerItem);

        indexLabel = new QLabel(centralwidget);
        indexLabel->setObjectName("indexLabel");

        actionLayout->addWidget(indexLabel);

        indexSpinBox = new QSpinBox(centralwidget);
        indexSpinBox->setObjectName("indexSpinBox");
        indexSpinBox->setMinimum(0);
        indexSpinBox->setMaximum(9999);
        indexSpinBox->setMinimumWidth(70);

        actionLayout->addWidget(indexSpinBox);

        getIndexBtn = new QPushButton(centralwidget);
        getIndexBtn->setObjectName("getIndexBtn");

        actionLayout->addWidget(getIndexBtn);


        verticalLayout->addLayout(actionLayout);

        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName("infoLabel");

        verticalLayout->addWidget(infoLabel);

        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName("resultLabel");

        verticalLayout->addWidget(resultLabel);

        listLabel = new QLabel(centralwidget);
        listLabel->setObjectName("listLabel");

        verticalLayout->addWidget(listLabel);

        dequeList = new QListWidget(centralwidget);
        dequeList->setObjectName("dequeList");

        verticalLayout->addWidget(dequeList);

        logLabel = new QLabel(centralwidget);
        logLabel->setObjectName("logLabel");

        verticalLayout->addWidget(logLabel);

        logEdit = new QPlainTextEdit(centralwidget);
        logEdit->setObjectName("logEdit");
        logEdit->setMaximumHeight(110);
        logEdit->setReadOnly(true);

        verticalLayout->addWidget(logEdit);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lab7 \342\200\224 Task5: Deque", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "MyDeque \342\200\224 Block-Based Double-Ended Queue", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 16px; font-weight: bold; padding: 6px; background: #2c3e50; color: white; border-radius: 4px;", nullptr));
        valueLabel->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        pushBackBtn->setText(QCoreApplication::translate("MainWindow", "push_back", nullptr));
        pushBackBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#27ae60; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        pushFrontBtn->setText(QCoreApplication::translate("MainWindow", "push_front", nullptr));
        pushFrontBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#2980b9; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        popBackBtn->setText(QCoreApplication::translate("MainWindow", "pop_back", nullptr));
        popBackBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#e74c3c; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        popFrontBtn->setText(QCoreApplication::translate("MainWindow", "pop_front", nullptr));
        popFrontBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#c0392b; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        fillRandomBtn->setText(QCoreApplication::translate("MainWindow", "Fill Random (10)", nullptr));
        fillRandomBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#8e44ad; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        clearBtn->setText(QCoreApplication::translate("MainWindow", "clear()", nullptr));
        clearBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#7f8c8d; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        indexLabel->setText(QCoreApplication::translate("MainWindow", "Index:", nullptr));
        getIndexBtn->setText(QCoreApplication::translate("MainWindow", "operator[]", nullptr));
        getIndexBtn->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#d35400; color:white; font-weight:bold; padding:5px 10px; border-radius:4px;", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "size: 0  |  empty: true", nullptr));
        infoLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 13px; padding: 4px; background: #ecf0f1; border-radius: 3px; color: #2c3e50;", nullptr));
        resultLabel->setText(QCoreApplication::translate("MainWindow", "Result: \342\200\224", nullptr));
        resultLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 13px; padding: 4px; background: #ffeaa7; border-radius: 3px; color: #2c3e50;", nullptr));
        listLabel->setText(QCoreApplication::translate("MainWindow", "Deque contents (front \342\206\222 back):", nullptr));
        dequeList->setStyleSheet(QCoreApplication::translate("MainWindow", "font-family: monospace; font-size: 13px;", nullptr));
        logLabel->setText(QCoreApplication::translate("MainWindow", "Log:", nullptr));
        logEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "font-family: monospace; font-size: 12px; background: #1e2b38; color: #00e676;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
