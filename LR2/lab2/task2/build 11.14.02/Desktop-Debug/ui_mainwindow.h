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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *fileLayout;
    QPushButton *btnLoadDishes;
    QPushButton *btnSaveDishes;
    QPushButton *btnLoadOrders;
    QPushButton *btnSaveOrders;
    QSpacerItem *fileSpacer;
    QPushButton *btnRunTests;
    QTabWidget *tabWidget;
    QWidget *tabDishes;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLineEdit *editDishName;
    QLabel *label1;
    QLineEdit *editDishCat;
    QLabel *label2;
    QLineEdit *editDishPrice;
    QHBoxLayout *hboxLayout1;
    QPushButton *btnAddDish;
    QPushButton *btnUpdateDish;
    QPushButton *btnRemoveDish;
    QPushButton *btnSortDishes;
    QSpacerItem *spacerItem;
    QTableWidget *tableDishes;
    QWidget *tabOrders;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *label3;
    QLineEdit *editOrderNum;
    QLabel *label4;
    QLineEdit *editOrderTable;
    QLabel *label5;
    QLineEdit *editOrderDish;
    QLabel *label6;
    QLineEdit *editOrderQty;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnAddOrder;
    QPushButton *btnUpdateOrder;
    QPushButton *btnRemoveOrder;
    QSpacerItem *spacerItem1;
    QTableWidget *tableOrders;
    QWidget *tabAnalytics;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout4;
    QLabel *label7;
    QLineEdit *editAnalyticsNum;
    QPushButton *btnOrderTotal;
    QLabel *label8;
    QLineEdit *editAnalyticsCat;
    QPushButton *btnMostPopular;
    QPushButton *btnBestOrder;
    QPushButton *btnSortOrders;
    QLabel *labelAnalytics;
    QTableWidget *tableAnalytics;
    QWidget *tabTests;
    QVBoxLayout *vboxLayout3;
    QLabel *label9;
    QTableWidget *tableTests;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1050, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        fileLayout = new QHBoxLayout();
        fileLayout->setObjectName("fileLayout");
        btnLoadDishes = new QPushButton(centralwidget);
        btnLoadDishes->setObjectName("btnLoadDishes");

        fileLayout->addWidget(btnLoadDishes);

        btnSaveDishes = new QPushButton(centralwidget);
        btnSaveDishes->setObjectName("btnSaveDishes");

        fileLayout->addWidget(btnSaveDishes);

        btnLoadOrders = new QPushButton(centralwidget);
        btnLoadOrders->setObjectName("btnLoadOrders");

        fileLayout->addWidget(btnLoadOrders);

        btnSaveOrders = new QPushButton(centralwidget);
        btnSaveOrders->setObjectName("btnSaveOrders");

        fileLayout->addWidget(btnSaveOrders);

        fileSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        fileLayout->addItem(fileSpacer);

        btnRunTests = new QPushButton(centralwidget);
        btnRunTests->setObjectName("btnRunTests");

        fileLayout->addWidget(btnRunTests);


        mainLayout->addLayout(fileLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabDishes = new QWidget();
        tabDishes->setObjectName("tabDishes");
        vboxLayout = new QVBoxLayout(tabDishes);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        label = new QLabel(tabDishes);
        label->setObjectName("label");

        hboxLayout->addWidget(label);

        editDishName = new QLineEdit(tabDishes);
        editDishName->setObjectName("editDishName");

        hboxLayout->addWidget(editDishName);

        label1 = new QLabel(tabDishes);
        label1->setObjectName("label1");

        hboxLayout->addWidget(label1);

        editDishCat = new QLineEdit(tabDishes);
        editDishCat->setObjectName("editDishCat");

        hboxLayout->addWidget(editDishCat);

        label2 = new QLabel(tabDishes);
        label2->setObjectName("label2");

        hboxLayout->addWidget(label2);

        editDishPrice = new QLineEdit(tabDishes);
        editDishPrice->setObjectName("editDishPrice");

        hboxLayout->addWidget(editDishPrice);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        btnAddDish = new QPushButton(tabDishes);
        btnAddDish->setObjectName("btnAddDish");

        hboxLayout1->addWidget(btnAddDish);

        btnUpdateDish = new QPushButton(tabDishes);
        btnUpdateDish->setObjectName("btnUpdateDish");

        hboxLayout1->addWidget(btnUpdateDish);

        btnRemoveDish = new QPushButton(tabDishes);
        btnRemoveDish->setObjectName("btnRemoveDish");

        hboxLayout1->addWidget(btnRemoveDish);

        btnSortDishes = new QPushButton(tabDishes);
        btnSortDishes->setObjectName("btnSortDishes");

        hboxLayout1->addWidget(btnSortDishes);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout1->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout1);

        tableDishes = new QTableWidget(tabDishes);
        if (tableDishes->columnCount() < 3)
            tableDishes->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableDishes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableDishes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableDishes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableDishes->setObjectName("tableDishes");
        tableDishes->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableDishes->setEditTriggers(QAbstractItemView::NoEditTriggers);

        vboxLayout->addWidget(tableDishes);

        tabWidget->addTab(tabDishes, QString());
        tabOrders = new QWidget();
        tabOrders->setObjectName("tabOrders");
        vboxLayout1 = new QVBoxLayout(tabOrders);
        vboxLayout1->setObjectName("vboxLayout1");
        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        label3 = new QLabel(tabOrders);
        label3->setObjectName("label3");

        hboxLayout2->addWidget(label3);

        editOrderNum = new QLineEdit(tabOrders);
        editOrderNum->setObjectName("editOrderNum");

        hboxLayout2->addWidget(editOrderNum);

        label4 = new QLabel(tabOrders);
        label4->setObjectName("label4");

        hboxLayout2->addWidget(label4);

        editOrderTable = new QLineEdit(tabOrders);
        editOrderTable->setObjectName("editOrderTable");

        hboxLayout2->addWidget(editOrderTable);

        label5 = new QLabel(tabOrders);
        label5->setObjectName("label5");

        hboxLayout2->addWidget(label5);

        editOrderDish = new QLineEdit(tabOrders);
        editOrderDish->setObjectName("editOrderDish");

        hboxLayout2->addWidget(editOrderDish);

        label6 = new QLabel(tabOrders);
        label6->setObjectName("label6");

        hboxLayout2->addWidget(label6);

        editOrderQty = new QLineEdit(tabOrders);
        editOrderQty->setObjectName("editOrderQty");

        hboxLayout2->addWidget(editOrderQty);


        vboxLayout1->addLayout(hboxLayout2);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        btnAddOrder = new QPushButton(tabOrders);
        btnAddOrder->setObjectName("btnAddOrder");

        hboxLayout3->addWidget(btnAddOrder);

        btnUpdateOrder = new QPushButton(tabOrders);
        btnUpdateOrder->setObjectName("btnUpdateOrder");

        hboxLayout3->addWidget(btnUpdateOrder);

        btnRemoveOrder = new QPushButton(tabOrders);
        btnRemoveOrder->setObjectName("btnRemoveOrder");

        hboxLayout3->addWidget(btnRemoveOrder);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem1);


        vboxLayout1->addLayout(hboxLayout3);

        tableOrders = new QTableWidget(tabOrders);
        if (tableOrders->columnCount() < 4)
            tableOrders->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableOrders->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableOrders->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableOrders->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableOrders->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        tableOrders->setObjectName("tableOrders");
        tableOrders->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableOrders->setEditTriggers(QAbstractItemView::NoEditTriggers);

        vboxLayout1->addWidget(tableOrders);

        tabWidget->addTab(tabOrders, QString());
        tabAnalytics = new QWidget();
        tabAnalytics->setObjectName("tabAnalytics");
        vboxLayout2 = new QVBoxLayout(tabAnalytics);
        vboxLayout2->setObjectName("vboxLayout2");
        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setObjectName("hboxLayout4");
        label7 = new QLabel(tabAnalytics);
        label7->setObjectName("label7");

        hboxLayout4->addWidget(label7);

        editAnalyticsNum = new QLineEdit(tabAnalytics);
        editAnalyticsNum->setObjectName("editAnalyticsNum");

        hboxLayout4->addWidget(editAnalyticsNum);

        btnOrderTotal = new QPushButton(tabAnalytics);
        btnOrderTotal->setObjectName("btnOrderTotal");

        hboxLayout4->addWidget(btnOrderTotal);

        label8 = new QLabel(tabAnalytics);
        label8->setObjectName("label8");

        hboxLayout4->addWidget(label8);

        editAnalyticsCat = new QLineEdit(tabAnalytics);
        editAnalyticsCat->setObjectName("editAnalyticsCat");

        hboxLayout4->addWidget(editAnalyticsCat);

        btnMostPopular = new QPushButton(tabAnalytics);
        btnMostPopular->setObjectName("btnMostPopular");

        hboxLayout4->addWidget(btnMostPopular);

        btnBestOrder = new QPushButton(tabAnalytics);
        btnBestOrder->setObjectName("btnBestOrder");

        hboxLayout4->addWidget(btnBestOrder);

        btnSortOrders = new QPushButton(tabAnalytics);
        btnSortOrders->setObjectName("btnSortOrders");

        hboxLayout4->addWidget(btnSortOrders);


        vboxLayout2->addLayout(hboxLayout4);

        labelAnalytics = new QLabel(tabAnalytics);
        labelAnalytics->setObjectName("labelAnalytics");
        QFont font;
        font.setPointSize(11);
        labelAnalytics->setFont(font);

        vboxLayout2->addWidget(labelAnalytics);

        tableAnalytics = new QTableWidget(tabAnalytics);
        if (tableAnalytics->columnCount() < 2)
            tableAnalytics->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableAnalytics->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableAnalytics->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        tableAnalytics->setObjectName("tableAnalytics");
        tableAnalytics->setEditTriggers(QAbstractItemView::NoEditTriggers);

        vboxLayout2->addWidget(tableAnalytics);

        tabWidget->addTab(tabAnalytics, QString());
        tabTests = new QWidget();
        tabTests->setObjectName("tabTests");
        vboxLayout3 = new QVBoxLayout(tabTests);
        vboxLayout3->setObjectName("vboxLayout3");
        label9 = new QLabel(tabTests);
        label9->setObjectName("label9");

        vboxLayout3->addWidget(label9);

        tableTests = new QTableWidget(tabTests);
        if (tableTests->columnCount() < 3)
            tableTests->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        tableTests->setObjectName("tableTests");
        tableTests->setEditTriggers(QAbstractItemView::NoEditTriggers);

        vboxLayout3->addWidget(tableTests);

        tabWidget->addTab(tabTests, QString());

        mainLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 2 \342\200\224 \320\240\320\265\321\201\321\202\320\276\321\200\320\260\320\275 (\320\222\320\260\321\200\320\270\320\260\320\275\321\202 16)", nullptr));
        btnLoadDishes->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 \320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\261\320\273\321\216\320\264\320\260", nullptr));
        btnSaveDishes->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 \320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\261\320\273\321\216\320\264\320\260", nullptr));
        btnLoadOrders->setText(QCoreApplication::translate("MainWindow", "\360\237\223\202 \320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267\321\213", nullptr));
        btnSaveOrders->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 \320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267\321\213", nullptr));
        btnRunTests->setText(QCoreApplication::translate("MainWindow", "\360\237\247\252 \320\242\320\265\321\201\321\202\321\213 (\321\201\321\202\320\265\320\272\320\273. \321\217\321\211\320\270\320\272)", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265:", nullptr));
        editDishName->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\221\320\276\321\200\321\211", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217:", nullptr));
        editDishCat->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\277\321\213", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260:", nullptr));
        editDishPrice->setPlaceholderText(QCoreApplication::translate("MainWindow", "5.50", nullptr));
        btnAddDish->setText(QCoreApplication::translate("MainWindow", "\342\236\225 \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnUpdateDish->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btnRemoveDish->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 \320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        btnSortDishes->setText(QCoreApplication::translate("MainWindow", "\360\237\224\203 \320\241\320\276\321\200\321\202. \320\277\320\276 \321\206\320\265\320\275\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableDishes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableDishes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableDishes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDishes), QCoreApplication::translate("MainWindow", "\320\221\320\273\321\216\320\264\320\260", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "\342\204\226 \320\227\320\260\320\272\320\260\320\267\320\260:", nullptr));
        editOrderNum->setPlaceholderText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273:", nullptr));
        editOrderTable->setPlaceholderText(QCoreApplication::translate("MainWindow", "3", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "\320\221\320\273\321\216\320\264\320\276:", nullptr));
        editOrderDish->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\221\320\276\321\200\321\211", nullptr));
        label6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276:", nullptr));
        editOrderQty->setPlaceholderText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btnAddOrder->setText(QCoreApplication::translate("MainWindow", "\342\236\225 \320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        btnUpdateOrder->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 \320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        btnRemoveOrder->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 \320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableOrders->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\342\204\226 \320\227\320\260\320\272\320\260\320\267\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableOrders->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableOrders->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\221\320\273\321\216\320\264\320\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableOrders->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOrders), QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\260\320\267\321\213", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "\342\204\226 \320\227\320\260\320\272\320\260\320\267\320\260:", nullptr));
        editAnalyticsNum->setPlaceholderText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btnOrderTotal->setText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\260 \320\267\320\260\320\272\320\260\320\267\320\260", nullptr));
        label8->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217:", nullptr));
        editAnalyticsCat->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\321\217\321\207\320\270\320\265 \320\261\320\273\321\216\320\264\320\260", nullptr));
        btnMostPopular->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\277\321\203\320\273\321\217\321\200\320\275\320\276\320\265 \320\262 \320\272\320\260\321\202.", nullptr));
        btnBestOrder->setText(QCoreApplication::translate("MainWindow", "\320\233\321\203\321\207\321\210\320\270\320\271 \320\267\320\260\320\272\320\260\320\267", nullptr));
        btnSortOrders->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\260\320\267\321\213 \320\277\320\276 \321\201\321\203\320\274\320\274\320\265 \342\206\223", nullptr));
        labelAnalytics->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202: \342\200\224", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableAnalytics->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\342\204\226 \320\227\320\260\320\272\320\260\320\267\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableAnalytics->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\320\241\321\203\320\274\320\274\320\260 (\321\200\321\203\320\261.)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAnalytics), QCoreApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\321\202\320\270\320\272\320\260", nullptr));
        label9->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\266\320\274\320\270\321\202\320\265 \320\272\320\275\320\276\320\277\320\272\321\203 \302\253\320\242\320\265\321\201\321\202\321\213 (\321\201\321\202\320\265\320\272\320\273. \321\217\321\211\320\270\320\272)\302\273 \342\200\224 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\277\320\276\321\217\320\262\321\217\321\202\321\201\321\217 \320\267\320\264\320\265\321\201\321\214 \320\270 \321\201\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\201\321\217 \320\262 XML.", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableTests->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableTests->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\320\255\321\202\320\260\320\273\320\276\320\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableTests->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "ok?", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTests), QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\321\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
