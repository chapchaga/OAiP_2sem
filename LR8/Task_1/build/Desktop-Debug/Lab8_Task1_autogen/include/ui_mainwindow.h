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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *mainLayout;
    QGroupBox *controlBox;
    QVBoxLayout *controlLayout;
    QLabel *labelValue;
    QSpinBox *spinValue;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QPushButton *btnFind;
    QPushButton *btnTraverse;
    QFrame *line1;
    QLabel *labelParent;
    QSpinBox *spinParent;
    QCheckBox *checkLeft;
    QPushButton *btnInsertAt;
    QPushButton *btnRemoveBranch;
    QFrame *line2;
    QLabel *labelSubtree;
    QLineEdit *editSubtree;
    QPushButton *btnInsertSubtree;
    QPushButton *btnRemoveSubtree;
    QFrame *line3;
    QLabel *labelLCA;
    QLineEdit *editLCA;
    QPushButton *btnLCA;
    QFrame *line4;
    QPushButton *btnClear;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter;
    QGroupBox *treeBox;
    QVBoxLayout *vboxLayout;
    QGraphicsView *graphicsView;
    QGroupBox *logBox;
    QVBoxLayout *vboxLayout1;
    QPlainTextEdit *logOutput;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QHBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        controlBox = new QGroupBox(centralwidget);
        controlBox->setObjectName("controlBox");
        controlBox->setMaximumWidth(320);
        controlLayout = new QVBoxLayout(controlBox);
        controlLayout->setObjectName("controlLayout");
        labelValue = new QLabel(controlBox);
        labelValue->setObjectName("labelValue");

        controlLayout->addWidget(labelValue);

        spinValue = new QSpinBox(controlBox);
        spinValue->setObjectName("spinValue");
        spinValue->setMinimum(-9999);
        spinValue->setMaximum(9999);

        controlLayout->addWidget(spinValue);

        btnAdd = new QPushButton(controlBox);
        btnAdd->setObjectName("btnAdd");

        controlLayout->addWidget(btnAdd);

        btnRemove = new QPushButton(controlBox);
        btnRemove->setObjectName("btnRemove");

        controlLayout->addWidget(btnRemove);

        btnFind = new QPushButton(controlBox);
        btnFind->setObjectName("btnFind");

        controlLayout->addWidget(btnFind);

        btnTraverse = new QPushButton(controlBox);
        btnTraverse->setObjectName("btnTraverse");

        controlLayout->addWidget(btnTraverse);

        line1 = new QFrame(controlBox);
        line1->setObjectName("line1");
        line1->setFrameShape(QFrame::HLine);

        controlLayout->addWidget(line1);

        labelParent = new QLabel(controlBox);
        labelParent->setObjectName("labelParent");

        controlLayout->addWidget(labelParent);

        spinParent = new QSpinBox(controlBox);
        spinParent->setObjectName("spinParent");
        spinParent->setMinimum(-9999);
        spinParent->setMaximum(9999);

        controlLayout->addWidget(spinParent);

        checkLeft = new QCheckBox(controlBox);
        checkLeft->setObjectName("checkLeft");
        checkLeft->setChecked(true);

        controlLayout->addWidget(checkLeft);

        btnInsertAt = new QPushButton(controlBox);
        btnInsertAt->setObjectName("btnInsertAt");

        controlLayout->addWidget(btnInsertAt);

        btnRemoveBranch = new QPushButton(controlBox);
        btnRemoveBranch->setObjectName("btnRemoveBranch");

        controlLayout->addWidget(btnRemoveBranch);

        line2 = new QFrame(controlBox);
        line2->setObjectName("line2");
        line2->setFrameShape(QFrame::HLine);

        controlLayout->addWidget(line2);

        labelSubtree = new QLabel(controlBox);
        labelSubtree->setObjectName("labelSubtree");

        controlLayout->addWidget(labelSubtree);

        editSubtree = new QLineEdit(controlBox);
        editSubtree->setObjectName("editSubtree");

        controlLayout->addWidget(editSubtree);

        btnInsertSubtree = new QPushButton(controlBox);
        btnInsertSubtree->setObjectName("btnInsertSubtree");

        controlLayout->addWidget(btnInsertSubtree);

        btnRemoveSubtree = new QPushButton(controlBox);
        btnRemoveSubtree->setObjectName("btnRemoveSubtree");

        controlLayout->addWidget(btnRemoveSubtree);

        line3 = new QFrame(controlBox);
        line3->setObjectName("line3");
        line3->setFrameShape(QFrame::HLine);

        controlLayout->addWidget(line3);

        labelLCA = new QLabel(controlBox);
        labelLCA->setObjectName("labelLCA");

        controlLayout->addWidget(labelLCA);

        editLCA = new QLineEdit(controlBox);
        editLCA->setObjectName("editLCA");

        controlLayout->addWidget(editLCA);

        btnLCA = new QPushButton(controlBox);
        btnLCA->setObjectName("btnLCA");

        controlLayout->addWidget(btnLCA);

        line4 = new QFrame(controlBox);
        line4->setObjectName("line4");
        line4->setFrameShape(QFrame::HLine);

        controlLayout->addWidget(line4);

        btnClear = new QPushButton(controlBox);
        btnClear->setObjectName("btnClear");

        controlLayout->addWidget(btnClear);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        controlLayout->addItem(verticalSpacer);


        mainLayout->addWidget(controlBox);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        treeBox = new QGroupBox(splitter);
        treeBox->setObjectName("treeBox");
        vboxLayout = new QVBoxLayout(treeBox);
        vboxLayout->setObjectName("vboxLayout");
        graphicsView = new QGraphicsView(treeBox);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setRenderHints(QPainter::Antialiasing);

        vboxLayout->addWidget(graphicsView);

        splitter->addWidget(treeBox);
        logBox = new QGroupBox(splitter);
        logBox->setObjectName("logBox");
        logBox->setMaximumHeight(180);
        vboxLayout1 = new QVBoxLayout(logBox);
        vboxLayout1->setObjectName("vboxLayout1");
        logOutput = new QPlainTextEdit(logBox);
        logOutput->setObjectName("logOutput");
        logOutput->setReadOnly(true);

        vboxLayout1->addWidget(logOutput);

        splitter->addWidget(logBox);

        mainLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Binary Search Tree \342\200\224 Lab 8", nullptr));
        controlBox->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\264\320\265\321\200\320\265\320\262\320\276\320\274", nullptr));
        labelValue->setText(QCoreApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265:", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 (add)", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\203\320\267\320\265\320\273 (remove)", nullptr));
        btnFind->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \321\203\320\267\320\265\320\273 (find)", nullptr));
        btnTraverse->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\205\320\276\320\264 inorder (traverse)", nullptr));
        labelParent->setText(QCoreApplication::translate("MainWindow", "\320\240\320\276\320\264\320\270\321\202\320\265\320\273\321\214 (\320\264\320\273\321\217 \320\262\321\201\321\202\320\260\320\262\320\272\320\270):", nullptr));
        checkLeft->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\272\320\260\320\272 \320\273\320\265\320\262\320\276\320\263\320\276 \320\277\320\276\321\202\320\276\320\274\320\272\320\260", nullptr));
        btnInsertAt->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\262 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        btnRemoveBranch->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\320\265\321\202\320\262\321\214", nullptr));
        labelSubtree->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\264\320\265\321\200\320\265\320\262\320\276 (\320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \321\207\320\265\321\200\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273):", nullptr));
        editSubtree->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\275\320\260\320\277\321\200: 10 5 15", nullptr));
        btnInsertSubtree->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\264\320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        btnRemoveSubtree->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\320\264\320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        labelLCA->setText(QCoreApplication::translate("MainWindow", "\320\235\320\236\320\237 (\320\264\320\262\320\260 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \321\207\320\265\321\200\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273):", nullptr));
        editLCA->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\275\320\260\320\277\321\200: 3 7", nullptr));
        btnLCA->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\276\320\261\321\211\320\265\320\263\320\276 \320\277\321\200\320\265\320\264\320\272\320\260 (LCA)", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\264\320\265\321\200\320\265\320\262\320\276", nullptr));
        treeBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217 \320\264\320\265\321\200\320\265\320\262\320\260", nullptr));
        logBox->setTitle(QCoreApplication::translate("MainWindow", "\320\233\320\276\320\263 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\271", nullptr));
        logOutput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\321\203\321\202 \320\276\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214\321\201\321\217 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\276\320\277\320\265\321\200\320\260\321\206\320\270\320\271...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
