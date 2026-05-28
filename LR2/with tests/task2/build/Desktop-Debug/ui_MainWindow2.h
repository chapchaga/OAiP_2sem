/********************************************************************************
** Form generated from reading UI file 'MainWindow2.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

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

class Ui_MainWindow2
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *toolbarLayout;
    QPushButton *btnOpen;
    QPushButton *btnSave;
    QPushButton *btnSaveAs;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnSort;
    QPushButton *btnSearch;
    QPushButton *btnBulletin;
    QPushButton *btnRunTests;
    QSpacerItem *spacerToolbar;
    QHBoxLayout *searchLayout;
    QLabel *labelSearch;
    QLineEdit *editSearch;
    QTableWidget *tableWidget;
    QLabel *labelStatus;

    void setupUi(QMainWindow *MainWindow2)
    {
        if (MainWindow2->objectName().isEmpty())
            MainWindow2->setObjectName("MainWindow2");
        MainWindow2->resize(1000, 650);
        centralwidget = new QWidget(MainWindow2);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setObjectName("toolbarLayout");
        btnOpen = new QPushButton(centralwidget);
        btnOpen->setObjectName("btnOpen");

        toolbarLayout->addWidget(btnOpen);

        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");

        toolbarLayout->addWidget(btnSave);

        btnSaveAs = new QPushButton(centralwidget);
        btnSaveAs->setObjectName("btnSaveAs");

        toolbarLayout->addWidget(btnSaveAs);

        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");

        toolbarLayout->addWidget(btnAdd);

        btnEdit = new QPushButton(centralwidget);
        btnEdit->setObjectName("btnEdit");

        toolbarLayout->addWidget(btnEdit);

        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName("btnDelete");

        toolbarLayout->addWidget(btnDelete);

        btnSort = new QPushButton(centralwidget);
        btnSort->setObjectName("btnSort");

        toolbarLayout->addWidget(btnSort);

        btnSearch = new QPushButton(centralwidget);
        btnSearch->setObjectName("btnSearch");

        toolbarLayout->addWidget(btnSearch);

        btnBulletin = new QPushButton(centralwidget);
        btnBulletin->setObjectName("btnBulletin");

        toolbarLayout->addWidget(btnBulletin);

        btnRunTests = new QPushButton(centralwidget);
        btnRunTests->setObjectName("btnRunTests");

        toolbarLayout->addWidget(btnRunTests);

        spacerToolbar = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        toolbarLayout->addItem(spacerToolbar);


        verticalLayout->addLayout(toolbarLayout);

        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        labelSearch = new QLabel(centralwidget);
        labelSearch->setObjectName("labelSearch");

        searchLayout->addWidget(labelSearch);

        editSearch = new QLineEdit(centralwidget);
        editSearch->setObjectName("editSearch");

        searchLayout->addWidget(editSearch);


        verticalLayout->addLayout(searchLayout);

        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(tableWidget);

        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName("labelStatus");

        verticalLayout->addWidget(labelStatus);

        MainWindow2->setCentralWidget(centralwidget);

        retranslateUi(MainWindow2);

        QMetaObject::connectSlotsByName(MainWindow2);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow2)
    {
        MainWindow2->setWindowTitle(QCoreApplication::translate("MainWindow2", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2 \342\200\224 \320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217 \320\272\320\260\320\275\320\264\320\270\320\264\320\260\321\202\320\276\320\262 (\320\222\320\260\321\200\320\270\320\260\320\275\321\202 22)", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow2", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214...", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow2", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        btnSaveAs->setText(QCoreApplication::translate("MainWindow2", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow2", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnEdit->setText(QCoreApplication::translate("MainWindow2", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow2", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnSort->setText(QCoreApplication::translate("MainWindow2", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214...", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow2", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        btnBulletin->setText(QCoreApplication::translate("MainWindow2", "\320\221\321\216\320\273\320\273\320\265\321\202\320\265\320\275\321\214", nullptr));
        btnRunTests->setText(QCoreApplication::translate("MainWindow2", "\320\242\320\265\321\201\321\202\321\213 (xlsx)", nullptr));
        labelSearch->setText(QCoreApplication::translate("MainWindow2", "\320\237\320\276\320\270\321\201\320\272 \320\277\320\276 \320\244\320\230\320\236 / \320\277\320\260\321\200\321\202\320\270\320\270:", nullptr));
        editSearch->setPlaceholderText(QCoreApplication::translate("MainWindow2", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\265\320\272\321\201\321\202 \320\264\320\273\321\217 \320\277\320\276\320\270\321\201\320\272\320\260...", nullptr));
        labelStatus->setText(QCoreApplication::translate("MainWindow2", "\320\223\320\276\321\202\320\276\320\262\320\276. \320\236\321\202\320\272\321\200\320\276\320\271\321\202\320\265 \321\204\320\260\320\271\320\273 \320\270\320\273\320\270 \320\264\320\276\320\261\320\260\320\262\321\214\321\202\320\265 \320\272\320\260\320\275\320\264\320\270\320\264\320\260\321\202\320\276\320\262.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow2: public Ui_MainWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
