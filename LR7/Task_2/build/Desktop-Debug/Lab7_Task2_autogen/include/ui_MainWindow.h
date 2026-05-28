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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QGroupBox *groupAdd;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinKey;
    QLabel *label1;
    QLineEdit *editAuthor;
    QLabel *label2;
    QLineEdit *editTitle;
    QLabel *label3;
    QSpinBox *spinYear;
    QLabel *label4;
    QLineEdit *editLanguage;
    QPushButton *btnAdd;
    QGroupBox *groupSearch;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *label5;
    QSpinBox *spinSearchKey;
    QHBoxLayout *hboxLayout2;
    QPushButton *btnFind;
    QPushButton *btnRemove;
    QGroupBox *groupTree;
    QVBoxLayout *vboxLayout2;
    QPushButton *btnBalance;
    QPushButton *btnClear;
    QGroupBox *groupTraverse;
    QVBoxLayout *vboxLayout3;
    QPushButton *btnPreOrder;
    QPushButton *btnInOrder;
    QPushButton *btnPostOrder;
    QGroupBox *groupVariant;
    QVBoxLayout *vboxLayout4;
    QPushButton *btnNodesPerLevel;
    QSpacerItem *spacerItem;
    QVBoxLayout *vboxLayout5;
    QLabel *label6;
    QTreeWidget *treeWidget;
    QLabel *label7;
    QPlainTextEdit *memoOutput;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 680);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName("vboxLayout");
        groupAdd = new QGroupBox(centralwidget);
        groupAdd->setObjectName("groupAdd");
        formLayout = new QFormLayout(groupAdd);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupAdd);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        spinKey = new QSpinBox(groupAdd);
        spinKey->setObjectName("spinKey");
        spinKey->setMinimum(1);
        spinKey->setMaximum(99999);
        spinKey->setValue(11);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, spinKey);

        label1 = new QLabel(groupAdd);
        label1->setObjectName("label1");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label1);

        editAuthor = new QLineEdit(groupAdd);
        editAuthor->setObjectName("editAuthor");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, editAuthor);

        label2 = new QLabel(groupAdd);
        label2->setObjectName("label2");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label2);

        editTitle = new QLineEdit(groupAdd);
        editTitle->setObjectName("editTitle");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, editTitle);

        label3 = new QLabel(groupAdd);
        label3->setObjectName("label3");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label3);

        spinYear = new QSpinBox(groupAdd);
        spinYear->setObjectName("spinYear");
        spinYear->setMinimum(1000);
        spinYear->setMaximum(2100);
        spinYear->setValue(2024);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, spinYear);

        label4 = new QLabel(groupAdd);
        label4->setObjectName("label4");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label4);

        editLanguage = new QLineEdit(groupAdd);
        editLanguage->setObjectName("editLanguage");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, editLanguage);

        btnAdd = new QPushButton(groupAdd);
        btnAdd->setObjectName("btnAdd");

        formLayout->setWidget(5, QFormLayout::ItemRole::SpanningRole, btnAdd);


        vboxLayout->addWidget(groupAdd);

        groupSearch = new QGroupBox(centralwidget);
        groupSearch->setObjectName("groupSearch");
        vboxLayout1 = new QVBoxLayout(groupSearch);
        vboxLayout1->setObjectName("vboxLayout1");
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        label5 = new QLabel(groupSearch);
        label5->setObjectName("label5");

        hboxLayout1->addWidget(label5);

        spinSearchKey = new QSpinBox(groupSearch);
        spinSearchKey->setObjectName("spinSearchKey");
        spinSearchKey->setMinimum(1);
        spinSearchKey->setMaximum(99999);
        spinSearchKey->setValue(5);

        hboxLayout1->addWidget(spinSearchKey);


        vboxLayout1->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        btnFind = new QPushButton(groupSearch);
        btnFind->setObjectName("btnFind");

        hboxLayout2->addWidget(btnFind);

        btnRemove = new QPushButton(groupSearch);
        btnRemove->setObjectName("btnRemove");

        hboxLayout2->addWidget(btnRemove);


        vboxLayout1->addLayout(hboxLayout2);


        vboxLayout->addWidget(groupSearch);

        groupTree = new QGroupBox(centralwidget);
        groupTree->setObjectName("groupTree");
        vboxLayout2 = new QVBoxLayout(groupTree);
        vboxLayout2->setObjectName("vboxLayout2");
        btnBalance = new QPushButton(groupTree);
        btnBalance->setObjectName("btnBalance");

        vboxLayout2->addWidget(btnBalance);

        btnClear = new QPushButton(groupTree);
        btnClear->setObjectName("btnClear");

        vboxLayout2->addWidget(btnClear);


        vboxLayout->addWidget(groupTree);

        groupTraverse = new QGroupBox(centralwidget);
        groupTraverse->setObjectName("groupTraverse");
        vboxLayout3 = new QVBoxLayout(groupTraverse);
        vboxLayout3->setObjectName("vboxLayout3");
        btnPreOrder = new QPushButton(groupTraverse);
        btnPreOrder->setObjectName("btnPreOrder");

        vboxLayout3->addWidget(btnPreOrder);

        btnInOrder = new QPushButton(groupTraverse);
        btnInOrder->setObjectName("btnInOrder");

        vboxLayout3->addWidget(btnInOrder);

        btnPostOrder = new QPushButton(groupTraverse);
        btnPostOrder->setObjectName("btnPostOrder");

        vboxLayout3->addWidget(btnPostOrder);


        vboxLayout->addWidget(groupTraverse);

        groupVariant = new QGroupBox(centralwidget);
        groupVariant->setObjectName("groupVariant");
        vboxLayout4 = new QVBoxLayout(groupVariant);
        vboxLayout4->setObjectName("vboxLayout4");
        btnNodesPerLevel = new QPushButton(groupVariant);
        btnNodesPerLevel->setObjectName("btnNodesPerLevel");

        vboxLayout4->addWidget(btnNodesPerLevel);


        vboxLayout->addWidget(groupVariant);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem);


        hboxLayout->addLayout(vboxLayout);

        vboxLayout5 = new QVBoxLayout();
        vboxLayout5->setObjectName("vboxLayout5");
        label6 = new QLabel(centralwidget);
        label6->setObjectName("label6");

        vboxLayout5->addWidget(label6);

        treeWidget = new QTreeWidget(centralwidget);
        treeWidget->setObjectName("treeWidget");
        treeWidget->setAlternatingRowColors(true);

        vboxLayout5->addWidget(treeWidget);

        label7 = new QLabel(centralwidget);
        label7->setObjectName("label7");

        vboxLayout5->addWidget(label7);

        memoOutput = new QPlainTextEdit(centralwidget);
        memoOutput->setObjectName("memoOutput");
        memoOutput->setReadOnly(true);
        memoOutput->setMaximumHeight(180);

        vboxLayout5->addWidget(memoOutput);


        hboxLayout->addLayout(vboxLayout5);


        mainLayout->addLayout(hboxLayout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Lab7 Task2 \342\200\224 Binary Search Tree (Library)", nullptr));
        groupAdd->setTitle(QCoreApplication::translate("MainWindow", "Add book", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Author:", nullptr));
        editAuthor->setPlaceholderText(QCoreApplication::translate("MainWindow", "Last F.M.", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "Title:", nullptr));
        editTitle->setPlaceholderText(QCoreApplication::translate("MainWindow", "Book title", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "Year:", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "Language:", nullptr));
        editLanguage->setPlaceholderText(QCoreApplication::translate("MainWindow", "English", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Add to tree", nullptr));
        groupSearch->setTitle(QCoreApplication::translate("MainWindow", "Find / Remove by key", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "Key:", nullptr));
        btnFind->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        groupTree->setTitle(QCoreApplication::translate("MainWindow", "Tree operations", nullptr));
        btnBalance->setText(QCoreApplication::translate("MainWindow", "Balance tree", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "Clear tree", nullptr));
        groupTraverse->setTitle(QCoreApplication::translate("MainWindow", "Traversal", nullptr));
        btnPreOrder->setText(QCoreApplication::translate("MainWindow", "Pre-order (direct)", nullptr));
        btnInOrder->setText(QCoreApplication::translate("MainWindow", "In-order (ascending)", nullptr));
        btnPostOrder->setText(QCoreApplication::translate("MainWindow", "Post-order (reverse)", nullptr));
        groupVariant->setTitle(QCoreApplication::translate("MainWindow", "Variant task", nullptr));
        btnNodesPerLevel->setText(QCoreApplication::translate("MainWindow", "Nodes per level", nullptr));
        label6->setText(QCoreApplication::translate("MainWindow", "Tree structure (root \342\206\222 children):", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("MainWindow", "Language", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("MainWindow", "Year", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("MainWindow", "Title", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Author", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Key", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "Output / Traversal log:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
