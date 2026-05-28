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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
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
    QLabel *label;
    QLabel *label1;
    QHBoxLayout *hboxLayout;
    QLineEdit *lineEditExpr;
    QPushButton *btnEvaluate;
    QPushButton *btnExample;
    QPushButton *btnClear;
    QLabel *labelResult;
    QGroupBox *groupBox1;
    QVBoxLayout *vboxLayout2;
    QTextEdit *textLog;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 550);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName("vboxLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setObjectName("vboxLayout1");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        vboxLayout1->addWidget(label);

        label1 = new QLabel(groupBox);
        label1->setObjectName("label1");

        vboxLayout1->addWidget(label1);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        lineEditExpr = new QLineEdit(groupBox);
        lineEditExpr->setObjectName("lineEditExpr");

        hboxLayout->addWidget(lineEditExpr);

        btnEvaluate = new QPushButton(groupBox);
        btnEvaluate->setObjectName("btnEvaluate");

        hboxLayout->addWidget(btnEvaluate);

        btnExample = new QPushButton(groupBox);
        btnExample->setObjectName("btnExample");

        hboxLayout->addWidget(btnExample);

        btnClear = new QPushButton(groupBox);
        btnClear->setObjectName("btnClear");

        hboxLayout->addWidget(btnClear);


        vboxLayout1->addLayout(hboxLayout);

        labelResult = new QLabel(groupBox);
        labelResult->setObjectName("labelResult");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        labelResult->setFont(font);

        vboxLayout1->addWidget(labelResult);


        vboxLayout->addWidget(groupBox);

        groupBox1 = new QGroupBox(centralwidget);
        groupBox1->setObjectName("groupBox1");
        vboxLayout2 = new QVBoxLayout(groupBox1);
        vboxLayout2->setObjectName("vboxLayout2");
        textLog = new QTextEdit(groupBox1);
        textLog->setObjectName("textLog");
        textLog->setReadOnly(true);

        vboxLayout2->addWidget(textLog);


        vboxLayout->addWidget(groupBox1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 3 \342\200\224 \320\230\320\265\321\200\320\260\321\200\321\205\320\270\321\217 Expression", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\230\320\265\321\200\320\260\321\200\321\205\320\270\321\217 \320\272\320\273\320\260\321\201\321\201\320\276\320\262", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Expression (abstract) \342\206\222 Number | BinaryOperation (+, -, *, /)", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\260\321\200\320\270\321\204\320\274\320\265\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\262\321\213\321\200\320\260\320\266\320\265\320\275\320\270\320\265 (\320\277\320\276\320\264\320\264\320\265\321\200\320\266\320\270\320\262\320\260\321\216\321\202\321\201\321\217 +, -, *, /, \321\201\320\272\320\276\320\261\320\272\320\270):", nullptr));
        lineEditExpr->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200: 3 + 4.5 * 5  \320\270\320\273\320\270  (10 - 2) / 4", nullptr));
        btnEvaluate->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\207\320\270\321\201\320\273\320\270\321\202\321\214", nullptr));
        btnExample->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\321\200 \320\270\320\267 \321\203\321\201\320\273\320\276\320\262\320\270\321\217", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        labelResult->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202: \342\200\224", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("MainWindow", "\320\233\320\276\320\263 \320\262\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\320\271 \320\270 \320\264\320\265\320\274\320\276\320\275\321\201\321\202\321\200\320\260\321\206\320\270\321\217 \320\270\320\265\321\200\320\260\321\200\321\205\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
