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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QTextEdit *textExplain;
    QGroupBox *groupBox1;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QComboBox *cmbLeft;
    QLabel *label1;
    QComboBox *cmbRight;
    QPushButton *btnCheck;
    QPushButton *btnRunAllTests;
    QGroupBox *groupBox2;
    QVBoxLayout *vboxLayout2;
    QTableWidget *tableResults;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(850, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setObjectName("vboxLayout1");
        textExplain = new QTextEdit(groupBox);
        textExplain->setObjectName("textExplain");
        textExplain->setReadOnly(true);
        textExplain->setMaximumHeight(120);

        vboxLayout1->addWidget(textExplain);


        vboxLayout->addWidget(groupBox);

        groupBox1 = new QGroupBox(centralwidget);
        groupBox1->setObjectName("groupBox1");
        hboxLayout = new QHBoxLayout(groupBox1);
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(groupBox1);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        cmbLeft = new QComboBox(groupBox1);
        cmbLeft->setObjectName("cmbLeft");

        hboxLayout->addWidget(cmbLeft);

        label1 = new QLabel(groupBox1);
        label1->setObjectName("label1");

        hboxLayout->addWidget(label1);

        cmbRight = new QComboBox(groupBox1);
        cmbRight->setObjectName("cmbRight");

        hboxLayout->addWidget(cmbRight);

        btnCheck = new QPushButton(groupBox1);
        btnCheck->setObjectName("btnCheck");

        hboxLayout->addWidget(btnCheck);

        btnRunAllTests = new QPushButton(groupBox1);
        btnRunAllTests->setObjectName("btnRunAllTests");

        hboxLayout->addWidget(btnRunAllTests);


        vboxLayout->addWidget(groupBox1);

        groupBox2 = new QGroupBox(centralwidget);
        groupBox2->setObjectName("groupBox2");
        vboxLayout2 = new QVBoxLayout(groupBox2);
        vboxLayout2->setObjectName("vboxLayout2");
        tableResults = new QTableWidget(groupBox2);
        tableResults->setObjectName("tableResults");
        tableResults->setSelectionBehavior(QAbstractItemView::SelectRows);

        vboxLayout2->addWidget(tableResults);


        vboxLayout->addWidget(groupBox2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 4 \342\200\224 check_equals", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\212\321\217\321\201\320\275\320\265\320\275\320\270\320\265 \321\200\320\265\320\260\320\273\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260 check_equals \320\262\321\200\321\203\321\207\320\275\321\203\321\216", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\233\320\265\320\262\321\213\320\271 \320\276\320\261\321\212\320\265\320\272\321\202:", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\321\213\320\271 \320\276\320\261\321\212\320\265\320\272\321\202:", nullptr));
        btnCheck->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214", nullptr));
        btnRunAllTests->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\272\320\276\320\274\320\261\320\270\320\275\320\260\321\206\320\270\320\270", nullptr));
        groupBox2->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
