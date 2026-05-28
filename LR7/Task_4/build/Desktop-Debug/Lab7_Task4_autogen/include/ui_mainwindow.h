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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vMain;
    QGroupBox *groupControls;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QComboBox *comboTableSize;
    QLabel *label1;
    QComboBox *comboHashType;
    QLabel *label2;
    QLineEdit *editKey;
    QLabel *label3;
    QLineEdit *editValue;
    QPushButton *btnInsert;
    QPushButton *btnSearch;
    QPushButton *btnClear;
    QPushButton *btnBenchmark;
    QSplitter *splitterMain;
    QPlainTextEdit *memoTable;
    QWidget *chartWidget;
    QVBoxLayout *vboxLayout;
    QLabel *labelChart;
    QPlainTextEdit *memoLog;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 680);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vMain = new QVBoxLayout(centralwidget);
        vMain->setObjectName("vMain");
        groupControls = new QGroupBox(centralwidget);
        groupControls->setObjectName("groupControls");
        hboxLayout = new QHBoxLayout(groupControls);
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(groupControls);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        comboTableSize = new QComboBox(groupControls);
        comboTableSize->setObjectName("comboTableSize");
        comboTableSize->setMaximumWidth(80);

        hboxLayout->addWidget(comboTableSize);

        label1 = new QLabel(groupControls);
        label1->setObjectName("label1");

        hboxLayout->addWidget(label1);

        comboHashType = new QComboBox(groupControls);
        comboHashType->setObjectName("comboHashType");
        comboHashType->setMaximumWidth(110);

        hboxLayout->addWidget(comboHashType);

        label2 = new QLabel(groupControls);
        label2->setObjectName("label2");

        hboxLayout->addWidget(label2);

        editKey = new QLineEdit(groupControls);
        editKey->setObjectName("editKey");
        editKey->setMaximumWidth(70);

        hboxLayout->addWidget(editKey);

        label3 = new QLabel(groupControls);
        label3->setObjectName("label3");

        hboxLayout->addWidget(label3);

        editValue = new QLineEdit(groupControls);
        editValue->setObjectName("editValue");
        editValue->setMaximumWidth(100);

        hboxLayout->addWidget(editValue);

        btnInsert = new QPushButton(groupControls);
        btnInsert->setObjectName("btnInsert");

        hboxLayout->addWidget(btnInsert);

        btnSearch = new QPushButton(groupControls);
        btnSearch->setObjectName("btnSearch");

        hboxLayout->addWidget(btnSearch);

        btnClear = new QPushButton(groupControls);
        btnClear->setObjectName("btnClear");

        hboxLayout->addWidget(btnClear);

        btnBenchmark = new QPushButton(groupControls);
        btnBenchmark->setObjectName("btnBenchmark");

        hboxLayout->addWidget(btnBenchmark);


        vMain->addWidget(groupControls);

        splitterMain = new QSplitter(centralwidget);
        splitterMain->setObjectName("splitterMain");
        splitterMain->setOrientation(Qt::Horizontal);
        memoTable = new QPlainTextEdit(splitterMain);
        memoTable->setObjectName("memoTable");
        memoTable->setMinimumWidth(280);
        QFont font;
        font.setFamilies({QString::fromUtf8("Courier New")});
        font.setPointSize(9);
        memoTable->setFont(font);
        memoTable->setReadOnly(true);
        splitterMain->addWidget(memoTable);
        chartWidget = new QWidget(splitterMain);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setMinimumWidth(500);
        vboxLayout = new QVBoxLayout(chartWidget);
        vboxLayout->setObjectName("vboxLayout");
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        labelChart = new QLabel(chartWidget);
        labelChart->setObjectName("labelChart");
        labelChart->setAlignment(Qt::AlignCenter);
        labelChart->setMinimumHeight(300);

        vboxLayout->addWidget(labelChart);

        splitterMain->addWidget(chartWidget);

        vMain->addWidget(splitterMain);

        memoLog = new QPlainTextEdit(centralwidget);
        memoLog->setObjectName("memoLog");
        memoLog->setMaximumHeight(140);
        memoLog->setReadOnly(true);
        memoLog->setFont(font);

        vMain->addWidget(memoLog);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Hash Table Open Addressing \342\200\224 Modular vs Universal (Variant 4)", nullptr));
        groupControls->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Table size:", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Hash type:", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        editKey->setPlaceholderText(QCoreApplication::translate("MainWindow", "int", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Value:", nullptr));
        editValue->setPlaceholderText(QCoreApplication::translate("MainWindow", "string", nullptr));
        btnInsert->setText(QCoreApplication::translate("MainWindow", "Insert", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnBenchmark->setText(QCoreApplication::translate("MainWindow", "Run Benchmark", nullptr));
        btnBenchmark->setStyleSheet(QCoreApplication::translate("MainWindow", "font-weight:bold; background:#2255aa; color:white; padding:4px 10px;", nullptr));
        labelChart->setText(QString());
        labelChart->setStyleSheet(QCoreApplication::translate("MainWindow", "background:#181820; border:1px solid #444;", nullptr));
        memoLog->setPlaceholderText(QCoreApplication::translate("MainWindow", "Log output...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
