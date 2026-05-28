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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *rootLayout;
    QLabel *titleLabel;
    QHBoxLayout *navLayout;
    QLabel *menuLabel;
    QComboBox *menuCombo;
    QSpacerItem *spacerItem;
    QStackedWidget *stackedWidget;
    QWidget *pageTask1;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QGroupBox *groupInput1;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *t1_size;
    QLabel *label1;
    QLineEdit *t1_price;
    QLabel *label2;
    QLineEdit *t1_gender;
    QLabel *label3;
    QCheckBox *t1_stock;
    QLabel *label4;
    QLineEdit *t1_brand;
    QLabel *label5;
    QLineEdit *t1_articles;
    QGroupBox *groupButtons1;
    QVBoxLayout *vboxLayout1;
    QPushButton *btnT1_1;
    QPushButton *btnT1_2;
    QPushButton *btnT1_3;
    QPushButton *btnT1_4;
    QPushButton *btnT1_5;
    QSpacerItem *spacerItem1;
    QWidget *pageTask21;
    QVBoxLayout *vboxLayout2;
    QGroupBox *group21;
    QVBoxLayout *vboxLayout3;
    QLabel *label6;
    QTextEdit *t21_input;
    QHBoxLayout *hboxLayout1;
    QPushButton *btnT21_save;
    QPushButton *btnT21_load;
    QWidget *pageTask22;
    QVBoxLayout *vboxLayout4;
    QGroupBox *group22;
    QVBoxLayout *vboxLayout5;
    QLabel *label7;
    QLineEdit *t22_input;
    QHBoxLayout *hboxLayout2;
    QPushButton *btnT22_save;
    QPushButton *btnT22_load;
    QWidget *pageTask23;
    QVBoxLayout *vboxLayout6;
    QGroupBox *group23;
    QVBoxLayout *vboxLayout7;
    QFormLayout *formLayout1;
    QLabel *label8;
    QLineEdit *t23_size;
    QLabel *label9;
    QLineEdit *t23_price;
    QLabel *label10;
    QLineEdit *t23_gender;
    QLabel *label11;
    QCheckBox *t23_stock;
    QLabel *label12;
    QLineEdit *t23_brand;
    QLabel *label13;
    QLineEdit *t23_articles;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnT23_save;
    QPushButton *btnT23_load;
    QWidget *pageTask24;
    QVBoxLayout *vboxLayout8;
    QGroupBox *group24;
    QVBoxLayout *vboxLayout9;
    QFormLayout *formLayout2;
    QLabel *label14;
    QLineEdit *t24_size;
    QLabel *label15;
    QLineEdit *t24_price;
    QLabel *label16;
    QLineEdit *t24_gender;
    QLabel *label17;
    QCheckBox *t24_stock;
    QLabel *label18;
    QLineEdit *t24_brand;
    QLabel *label19;
    QLineEdit *t24_articles;
    QHBoxLayout *hboxLayout4;
    QPushButton *btnT24_save;
    QPushButton *btnT24_load;
    QWidget *pageTask25;
    QVBoxLayout *vboxLayout10;
    QGroupBox *group25;
    QVBoxLayout *vboxLayout11;
    QLabel *label20;
    QLineEdit *t25_input;
    QHBoxLayout *hboxLayout5;
    QPushButton *btnT25_save;
    QPushButton *btnT25_load;
    QGroupBox *groupOutput;
    QVBoxLayout *vboxLayout12;
    QHBoxLayout *hboxLayout6;
    QLabel *filePathLabel;
    QSpacerItem *spacerItem2;
    QPushButton *btnClear;
    QTextEdit *outputEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(960, 780);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        rootLayout = new QVBoxLayout(centralwidget);
        rootLayout->setObjectName("rootLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        rootLayout->addWidget(titleLabel);

        navLayout = new QHBoxLayout();
        navLayout->setObjectName("navLayout");
        menuLabel = new QLabel(centralwidget);
        menuLabel->setObjectName("menuLabel");
        QFont font1;
        font1.setBold(true);
        menuLabel->setFont(font1);

        navLayout->addWidget(menuLabel);

        menuCombo = new QComboBox(centralwidget);
        menuCombo->addItem(QString());
        menuCombo->addItem(QString());
        menuCombo->addItem(QString());
        menuCombo->addItem(QString());
        menuCombo->addItem(QString());
        menuCombo->addItem(QString());
        menuCombo->setObjectName("menuCombo");

        navLayout->addWidget(menuCombo);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        navLayout->addItem(spacerItem);


        rootLayout->addLayout(navLayout);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageTask1 = new QWidget();
        pageTask1->setObjectName("pageTask1");
        vboxLayout = new QVBoxLayout(pageTask1);
        vboxLayout->setObjectName("vboxLayout");
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        groupInput1 = new QGroupBox(pageTask1);
        groupInput1->setObjectName("groupInput1");
        formLayout = new QFormLayout(groupInput1);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupInput1);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        t1_size = new QLineEdit(groupInput1);
        t1_size->setObjectName("t1_size");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, t1_size);

        label1 = new QLabel(groupInput1);
        label1->setObjectName("label1");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label1);

        t1_price = new QLineEdit(groupInput1);
        t1_price->setObjectName("t1_price");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, t1_price);

        label2 = new QLabel(groupInput1);
        label2->setObjectName("label2");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label2);

        t1_gender = new QLineEdit(groupInput1);
        t1_gender->setObjectName("t1_gender");
        t1_gender->setMaxLength(1);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, t1_gender);

        label3 = new QLabel(groupInput1);
        label3->setObjectName("label3");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label3);

        t1_stock = new QCheckBox(groupInput1);
        t1_stock->setObjectName("t1_stock");
        t1_stock->setChecked(true);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, t1_stock);

        label4 = new QLabel(groupInput1);
        label4->setObjectName("label4");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label4);

        t1_brand = new QLineEdit(groupInput1);
        t1_brand->setObjectName("t1_brand");
        t1_brand->setMaxLength(49);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, t1_brand);

        label5 = new QLabel(groupInput1);
        label5->setObjectName("label5");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label5);

        t1_articles = new QLineEdit(groupInput1);
        t1_articles->setObjectName("t1_articles");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, t1_articles);


        hboxLayout->addWidget(groupInput1);

        groupButtons1 = new QGroupBox(pageTask1);
        groupButtons1->setObjectName("groupButtons1");
        vboxLayout1 = new QVBoxLayout(groupButtons1);
        vboxLayout1->setObjectName("vboxLayout1");
        btnT1_1 = new QPushButton(groupButtons1);
        btnT1_1->setObjectName("btnT1_1");

        vboxLayout1->addWidget(btnT1_1);

        btnT1_2 = new QPushButton(groupButtons1);
        btnT1_2->setObjectName("btnT1_2");

        vboxLayout1->addWidget(btnT1_2);

        btnT1_3 = new QPushButton(groupButtons1);
        btnT1_3->setObjectName("btnT1_3");

        vboxLayout1->addWidget(btnT1_3);

        btnT1_4 = new QPushButton(groupButtons1);
        btnT1_4->setObjectName("btnT1_4");

        vboxLayout1->addWidget(btnT1_4);

        btnT1_5 = new QPushButton(groupButtons1);
        btnT1_5->setObjectName("btnT1_5");

        vboxLayout1->addWidget(btnT1_5);

        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout1->addItem(spacerItem1);


        hboxLayout->addWidget(groupButtons1);


        vboxLayout->addLayout(hboxLayout);

        stackedWidget->addWidget(pageTask1);
        pageTask21 = new QWidget();
        pageTask21->setObjectName("pageTask21");
        vboxLayout2 = new QVBoxLayout(pageTask21);
        vboxLayout2->setObjectName("vboxLayout2");
        group21 = new QGroupBox(pageTask21);
        group21->setObjectName("group21");
        vboxLayout3 = new QVBoxLayout(group21);
        vboxLayout3->setObjectName("vboxLayout3");
        label6 = new QLabel(group21);
        label6->setObjectName("label6");

        vboxLayout3->addWidget(label6);

        t21_input = new QTextEdit(group21);
        t21_input->setObjectName("t21_input");

        vboxLayout3->addWidget(t21_input);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName("hboxLayout1");
        btnT21_save = new QPushButton(group21);
        btnT21_save->setObjectName("btnT21_save");

        hboxLayout1->addWidget(btnT21_save);

        btnT21_load = new QPushButton(group21);
        btnT21_load->setObjectName("btnT21_load");

        hboxLayout1->addWidget(btnT21_load);


        vboxLayout3->addLayout(hboxLayout1);


        vboxLayout2->addWidget(group21);

        stackedWidget->addWidget(pageTask21);
        pageTask22 = new QWidget();
        pageTask22->setObjectName("pageTask22");
        vboxLayout4 = new QVBoxLayout(pageTask22);
        vboxLayout4->setObjectName("vboxLayout4");
        group22 = new QGroupBox(pageTask22);
        group22->setObjectName("group22");
        vboxLayout5 = new QVBoxLayout(group22);
        vboxLayout5->setObjectName("vboxLayout5");
        label7 = new QLabel(group22);
        label7->setObjectName("label7");

        vboxLayout5->addWidget(label7);

        t22_input = new QLineEdit(group22);
        t22_input->setObjectName("t22_input");

        vboxLayout5->addWidget(t22_input);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName("hboxLayout2");
        btnT22_save = new QPushButton(group22);
        btnT22_save->setObjectName("btnT22_save");

        hboxLayout2->addWidget(btnT22_save);

        btnT22_load = new QPushButton(group22);
        btnT22_load->setObjectName("btnT22_load");

        hboxLayout2->addWidget(btnT22_load);


        vboxLayout5->addLayout(hboxLayout2);


        vboxLayout4->addWidget(group22);

        stackedWidget->addWidget(pageTask22);
        pageTask23 = new QWidget();
        pageTask23->setObjectName("pageTask23");
        vboxLayout6 = new QVBoxLayout(pageTask23);
        vboxLayout6->setObjectName("vboxLayout6");
        group23 = new QGroupBox(pageTask23);
        group23->setObjectName("group23");
        vboxLayout7 = new QVBoxLayout(group23);
        vboxLayout7->setObjectName("vboxLayout7");
        formLayout1 = new QFormLayout();
        formLayout1->setObjectName("formLayout1");
        label8 = new QLabel(group23);
        label8->setObjectName("label8");

        formLayout1->setWidget(0, QFormLayout::ItemRole::LabelRole, label8);

        t23_size = new QLineEdit(group23);
        t23_size->setObjectName("t23_size");

        formLayout1->setWidget(0, QFormLayout::ItemRole::FieldRole, t23_size);

        label9 = new QLabel(group23);
        label9->setObjectName("label9");

        formLayout1->setWidget(1, QFormLayout::ItemRole::LabelRole, label9);

        t23_price = new QLineEdit(group23);
        t23_price->setObjectName("t23_price");

        formLayout1->setWidget(1, QFormLayout::ItemRole::FieldRole, t23_price);

        label10 = new QLabel(group23);
        label10->setObjectName("label10");

        formLayout1->setWidget(2, QFormLayout::ItemRole::LabelRole, label10);

        t23_gender = new QLineEdit(group23);
        t23_gender->setObjectName("t23_gender");
        t23_gender->setMaxLength(1);

        formLayout1->setWidget(2, QFormLayout::ItemRole::FieldRole, t23_gender);

        label11 = new QLabel(group23);
        label11->setObjectName("label11");

        formLayout1->setWidget(3, QFormLayout::ItemRole::LabelRole, label11);

        t23_stock = new QCheckBox(group23);
        t23_stock->setObjectName("t23_stock");
        t23_stock->setChecked(true);

        formLayout1->setWidget(3, QFormLayout::ItemRole::FieldRole, t23_stock);

        label12 = new QLabel(group23);
        label12->setObjectName("label12");

        formLayout1->setWidget(4, QFormLayout::ItemRole::LabelRole, label12);

        t23_brand = new QLineEdit(group23);
        t23_brand->setObjectName("t23_brand");
        t23_brand->setMaxLength(49);

        formLayout1->setWidget(4, QFormLayout::ItemRole::FieldRole, t23_brand);

        label13 = new QLabel(group23);
        label13->setObjectName("label13");

        formLayout1->setWidget(5, QFormLayout::ItemRole::LabelRole, label13);

        t23_articles = new QLineEdit(group23);
        t23_articles->setObjectName("t23_articles");

        formLayout1->setWidget(5, QFormLayout::ItemRole::FieldRole, t23_articles);


        vboxLayout7->addLayout(formLayout1);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName("hboxLayout3");
        btnT23_save = new QPushButton(group23);
        btnT23_save->setObjectName("btnT23_save");

        hboxLayout3->addWidget(btnT23_save);

        btnT23_load = new QPushButton(group23);
        btnT23_load->setObjectName("btnT23_load");

        hboxLayout3->addWidget(btnT23_load);


        vboxLayout7->addLayout(hboxLayout3);


        vboxLayout6->addWidget(group23);

        stackedWidget->addWidget(pageTask23);
        pageTask24 = new QWidget();
        pageTask24->setObjectName("pageTask24");
        vboxLayout8 = new QVBoxLayout(pageTask24);
        vboxLayout8->setObjectName("vboxLayout8");
        group24 = new QGroupBox(pageTask24);
        group24->setObjectName("group24");
        vboxLayout9 = new QVBoxLayout(group24);
        vboxLayout9->setObjectName("vboxLayout9");
        formLayout2 = new QFormLayout();
        formLayout2->setObjectName("formLayout2");
        label14 = new QLabel(group24);
        label14->setObjectName("label14");

        formLayout2->setWidget(0, QFormLayout::ItemRole::LabelRole, label14);

        t24_size = new QLineEdit(group24);
        t24_size->setObjectName("t24_size");

        formLayout2->setWidget(0, QFormLayout::ItemRole::FieldRole, t24_size);

        label15 = new QLabel(group24);
        label15->setObjectName("label15");

        formLayout2->setWidget(1, QFormLayout::ItemRole::LabelRole, label15);

        t24_price = new QLineEdit(group24);
        t24_price->setObjectName("t24_price");

        formLayout2->setWidget(1, QFormLayout::ItemRole::FieldRole, t24_price);

        label16 = new QLabel(group24);
        label16->setObjectName("label16");

        formLayout2->setWidget(2, QFormLayout::ItemRole::LabelRole, label16);

        t24_gender = new QLineEdit(group24);
        t24_gender->setObjectName("t24_gender");
        t24_gender->setMaxLength(1);

        formLayout2->setWidget(2, QFormLayout::ItemRole::FieldRole, t24_gender);

        label17 = new QLabel(group24);
        label17->setObjectName("label17");

        formLayout2->setWidget(3, QFormLayout::ItemRole::LabelRole, label17);

        t24_stock = new QCheckBox(group24);
        t24_stock->setObjectName("t24_stock");
        t24_stock->setChecked(true);

        formLayout2->setWidget(3, QFormLayout::ItemRole::FieldRole, t24_stock);

        label18 = new QLabel(group24);
        label18->setObjectName("label18");

        formLayout2->setWidget(4, QFormLayout::ItemRole::LabelRole, label18);

        t24_brand = new QLineEdit(group24);
        t24_brand->setObjectName("t24_brand");
        t24_brand->setMaxLength(49);

        formLayout2->setWidget(4, QFormLayout::ItemRole::FieldRole, t24_brand);

        label19 = new QLabel(group24);
        label19->setObjectName("label19");

        formLayout2->setWidget(5, QFormLayout::ItemRole::LabelRole, label19);

        t24_articles = new QLineEdit(group24);
        t24_articles->setObjectName("t24_articles");

        formLayout2->setWidget(5, QFormLayout::ItemRole::FieldRole, t24_articles);


        vboxLayout9->addLayout(formLayout2);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setObjectName("hboxLayout4");
        btnT24_save = new QPushButton(group24);
        btnT24_save->setObjectName("btnT24_save");

        hboxLayout4->addWidget(btnT24_save);

        btnT24_load = new QPushButton(group24);
        btnT24_load->setObjectName("btnT24_load");

        hboxLayout4->addWidget(btnT24_load);


        vboxLayout9->addLayout(hboxLayout4);


        vboxLayout8->addWidget(group24);

        stackedWidget->addWidget(pageTask24);
        pageTask25 = new QWidget();
        pageTask25->setObjectName("pageTask25");
        vboxLayout10 = new QVBoxLayout(pageTask25);
        vboxLayout10->setObjectName("vboxLayout10");
        group25 = new QGroupBox(pageTask25);
        group25->setObjectName("group25");
        vboxLayout11 = new QVBoxLayout(group25);
        vboxLayout11->setObjectName("vboxLayout11");
        label20 = new QLabel(group25);
        label20->setObjectName("label20");

        vboxLayout11->addWidget(label20);

        t25_input = new QLineEdit(group25);
        t25_input->setObjectName("t25_input");

        vboxLayout11->addWidget(t25_input);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setObjectName("hboxLayout5");
        btnT25_save = new QPushButton(group25);
        btnT25_save->setObjectName("btnT25_save");

        hboxLayout5->addWidget(btnT25_save);

        btnT25_load = new QPushButton(group25);
        btnT25_load->setObjectName("btnT25_load");

        hboxLayout5->addWidget(btnT25_load);


        vboxLayout11->addLayout(hboxLayout5);


        vboxLayout10->addWidget(group25);

        stackedWidget->addWidget(pageTask25);

        rootLayout->addWidget(stackedWidget);

        groupOutput = new QGroupBox(centralwidget);
        groupOutput->setObjectName("groupOutput");
        vboxLayout12 = new QVBoxLayout(groupOutput);
        vboxLayout12->setObjectName("vboxLayout12");
        hboxLayout6 = new QHBoxLayout();
        hboxLayout6->setObjectName("hboxLayout6");
        filePathLabel = new QLabel(groupOutput);
        filePathLabel->setObjectName("filePathLabel");

        hboxLayout6->addWidget(filePathLabel);

        spacerItem2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout6->addItem(spacerItem2);

        btnClear = new QPushButton(groupOutput);
        btnClear->setObjectName("btnClear");

        hboxLayout6->addWidget(btnClear);


        vboxLayout12->addLayout(hboxLayout6);

        outputEdit = new QTextEdit(groupOutput);
        outputEdit->setObjectName("outputEdit");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Courier New")});
        font2.setPointSize(11);
        outputEdit->setFont(font2);
        outputEdit->setReadOnly(true);

        vboxLayout12->addWidget(outputEdit);


        rootLayout->addWidget(groupOutput);

        rootLayout->setStretch(2, 1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
        QObject::connect(btnClear, &QPushButton::clicked, outputEdit, qOverload<>(&QTextEdit::clear));
        QObject::connect(menuCombo, SIGNAL(currentIndexChanged(int)), MainWindow, SLOT(onMenuChanged(int)));
        QObject::connect(btnT1_1, SIGNAL(clicked()), MainWindow, SLOT(onTask1_1Clicked()));
        QObject::connect(btnT1_2, SIGNAL(clicked()), MainWindow, SLOT(onTask1_2Clicked()));
        QObject::connect(btnT1_3, SIGNAL(clicked()), MainWindow, SLOT(onTask1_3Clicked()));
        QObject::connect(btnT1_4, SIGNAL(clicked()), MainWindow, SLOT(onTask1_4Clicked()));
        QObject::connect(btnT1_5, SIGNAL(clicked()), MainWindow, SLOT(onTask1_5Clicked()));
        QObject::connect(btnT21_save, SIGNAL(clicked()), MainWindow, SLOT(onTask2_TextSaveClicked()));
        QObject::connect(btnT21_load, SIGNAL(clicked()), MainWindow, SLOT(onTask2_TextLoadClicked()));
        QObject::connect(btnT22_save, SIGNAL(clicked()), MainWindow, SLOT(onTask2_ArraySaveClicked()));
        QObject::connect(btnT22_load, SIGNAL(clicked()), MainWindow, SLOT(onTask2_ArrayLoadClicked()));
        QObject::connect(btnT23_save, SIGNAL(clicked()), MainWindow, SLOT(onTask2_StructTxtSaveClicked()));
        QObject::connect(btnT23_load, SIGNAL(clicked()), MainWindow, SLOT(onTask2_StructTxtLoadClicked()));
        QObject::connect(btnT24_save, SIGNAL(clicked()), MainWindow, SLOT(onTask2_StructBinSaveClicked()));
        QObject::connect(btnT24_load, SIGNAL(clicked()), MainWindow, SLOT(onTask2_StructBinLoadClicked()));
        QObject::connect(btnT25_save, SIGNAL(clicked()), MainWindow, SLOT(onTask2_LineSaveClicked()));
        QObject::connect(btnT25_load, SIGNAL(clicked()), MainWindow, SLOT(onTask2_LineLoadClicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\260\321\217 \342\204\2266 \342\200\224 \320\222\320\260\321\200\320\270\320\260\320\275\321\202 20 \342\200\224 \320\236\320\264\320\265\320\266\320\264\320\260", nullptr));
        titleLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 6px; background: #2b2d42; color: #edf2f4; border-radius: 4px;", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\260\321\217 \321\200\320\260\320\261\320\276\321\202\320\260 \342\204\2266", nullptr));
        menuLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\264\320\265\320\273 \320\274\320\265\320\275\321\216:", nullptr));
        menuCombo->setItemText(0, QCoreApplication::translate("MainWindow", "1. \320\227\320\260\320\264\320\260\320\275\320\270\320\265 1 \342\200\224 \320\241\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\260 (\320\277\320\265\321\200\320\265\320\274\320\265\320\275\320\275\321\213\320\265 / \321\203\320\272\320\260\320\267\320\260\321\202\320\265\320\273\321\214 / \321\201\321\201\321\213\320\273\320\272\320\260)", nullptr));
        menuCombo->setItemText(1, QCoreApplication::translate("MainWindow", "2.1 \342\200\224 \320\242\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273 (\320\277\320\276\321\201\320\270\320\274\320\262\320\276\320\273\321\214\320\275\320\276)", nullptr));
        menuCombo->setItemText(2, QCoreApplication::translate("MainWindow", "2.2 \342\200\224 \320\234\320\260\321\201\321\201\320\270\320\262 \320\262 \321\204\320\260\320\271\320\273 (\320\277\320\276\321\202\320\276\320\272\320\276\320\262\320\276)", nullptr));
        menuCombo->setItemText(3, QCoreApplication::translate("MainWindow", "2.3 \342\200\224 \320\241\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\260 \320\262 \321\202\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
        menuCombo->setItemText(4, QCoreApplication::translate("MainWindow", "2.4 \342\200\224 \320\241\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\260 \320\262 \320\261\320\270\320\275\320\260\321\200\320\275\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
        menuCombo->setItemText(5, QCoreApplication::translate("MainWindow", "2.5 \342\200\224 \320\241\321\202\321\200\320\276\320\272\320\270 \320\262 \321\202\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273 (\320\277\320\276\321\201\321\202\321\200\320\276\321\207\320\275\320\276)", nullptr));

        groupInput1->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\264\320\260\320\275\320\275\321\213\321\205 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\321\213 (\320\264\320\273\321\217 \320\277\321\203\320\275\320\272\321\202\320\260 3)", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 (int):", nullptr));
        t1_size->setPlaceholderText(QCoreApplication::translate("MainWindow", "42", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260 (double):", nullptr));
        t1_price->setPlaceholderText(QCoreApplication::translate("MainWindow", "1299.99", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273 (char: M/F/U):", nullptr));
        t1_gender->setPlaceholderText(QCoreApplication::translate("MainWindow", "M", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "\320\222 \320\275\320\260\320\273\320\270\321\207\320\270\320\270:", nullptr));
        t1_stock->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "\320\221\321\200\320\265\320\275\320\264 (char[50]):", nullptr));
        t1_brand->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nike", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "\320\220\321\200\321\202\320\270\320\272\321\203\320\273\321\213 (5 \321\207\320\270\321\201\320\265\320\273):", nullptr));
        t1_articles->setPlaceholderText(QCoreApplication::translate("MainWindow", "1001 1002 1003 1004 1005", nullptr));
        groupButtons1->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\203\320\275\320\272\321\202\321\213 \320\267\320\260\320\264\320\260\320\275\320\270\321\217 1", nullptr));
        btnT1_1->setText(QCoreApplication::translate("MainWindow", "1. \320\257\320\262\320\275\320\260\321\217 \320\270\320\275\320\270\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        btnT1_2->setText(QCoreApplication::translate("MainWindow", "2. \320\237\321\200\320\270\321\201\320\262\320\276\320\265\320\275\320\270\320\265 \320\277\320\276\320\273\320\265\320\271 \320\277\320\276 \320\276\320\264\320\275\320\276\320\274\321\203", nullptr));
        btnT1_3->setText(QCoreApplication::translate("MainWindow", "3. \320\222\320\262\320\276\320\264 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217 (\320\270\320\267 \321\204\320\276\321\200\320\274\321\213)", nullptr));
        btnT1_4->setText(QCoreApplication::translate("MainWindow", "4. \320\240\320\260\320\261\320\276\321\202\320\260 \321\207\320\265\321\200\320\265\320\267 \321\203\320\272\320\260\320\267\320\260\321\202\320\265\320\273\321\214", nullptr));
        btnT1_5->setText(QCoreApplication::translate("MainWindow", "5. \320\240\320\260\320\261\320\276\321\202\320\260 \321\207\320\265\321\200\320\265\320\267 \321\201\321\201\321\213\320\273\320\272\321\203", nullptr));
        group21->setTitle(QCoreApplication::translate("MainWindow", "2.1 \342\200\224 \320\237\320\276\321\201\320\270\320\274\320\262\320\276\320\273\321\214\320\275\320\260\321\217 \320\267\320\260\320\277\320\270\321\201\321\214/\321\207\321\202\320\265\320\275\320\270\320\265 \321\202\320\265\320\272\321\201\321\202\320\276\320\262\320\276\320\263\320\276 \321\204\320\260\320\271\320\273\320\260 (\320\244\320\260\320\274\320\270\320\273\320\270\321\217\320\233\320\260\320\26120.txt)", nullptr));
        label6->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\260\320\261\320\267\320\260\321\206 \321\202\320\265\320\272\321\201\321\202\320\260:", nullptr));
        t21_input->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\265\320\272\321\201\321\202 \320\267\320\264\320\265\321\201\321\214...", nullptr));
        btnT21_save->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \320\277\320\276\321\201\320\270\320\274\320\262\320\276\320\273\321\214\320\275\320\276 \320\262 \321\204\320\260\320\271\320\273", nullptr));
        btnT21_load->setText(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\277\320\276\321\201\320\270\320\274\320\262\320\276\320\273\321\214\320\275\320\276 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        group22->setTitle(QCoreApplication::translate("MainWindow", "2.2 \342\200\224 \320\234\320\260\321\201\321\201\320\270\320\262 int \320\262 \321\204\320\260\320\271\320\273 \320\277\320\276\321\202\320\276\320\272\320\276\320\262\320\276, \321\200\320\260\320\267\320\264\320\265\320\273\320\270\321\202\320\265\320\273\321\214 ' (\320\244\320\260\320\274\320\270\320\273\320\270\321\217\320\233\320\260\320\26120_0.txt)", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213 \320\274\320\260\321\201\321\201\320\270\320\262\320\260 (\321\207\320\265\321\200\320\265\320\267 \320\277\321\200\320\276\320\261\320\265\320\273):", nullptr));
        t22_input->setPlaceholderText(QCoreApplication::translate("MainWindow", "10 20 30 40 50", nullptr));
        btnT22_save->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \320\274\320\260\321\201\321\201\320\270\320\262 \320\262 \321\204\320\260\320\271\320\273 (<<)", nullptr));
        btnT22_load->setText(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\274\320\260\321\201\321\201\320\270\320\262 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260 (>>)", nullptr));
        group23->setTitle(QCoreApplication::translate("MainWindow", "2.3 \342\200\224 \320\241\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\260 \320\262 \321\202\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273 (\320\264\320\276\320\267\320\260\320\277\320\270\321\201\321\214, \320\244\320\260\320\274\320\270\320\273\320\270\321\217\320\233\320\260\320\26120_1.txt)", nullptr));
        label8->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200:", nullptr));
        t23_size->setPlaceholderText(QCoreApplication::translate("MainWindow", "42", nullptr));
        label9->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260:", nullptr));
        t23_price->setPlaceholderText(QCoreApplication::translate("MainWindow", "999.99", nullptr));
        label10->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273 (M/F/U):", nullptr));
        t23_gender->setPlaceholderText(QCoreApplication::translate("MainWindow", "M", nullptr));
        label11->setText(QCoreApplication::translate("MainWindow", "\320\222 \320\275\320\260\320\273\320\270\321\207\320\270\320\270:", nullptr));
        t23_stock->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260", nullptr));
        label12->setText(QCoreApplication::translate("MainWindow", "\320\221\321\200\320\265\320\275\320\264:", nullptr));
        t23_brand->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nike", nullptr));
        label13->setText(QCoreApplication::translate("MainWindow", "\320\220\321\200\321\202\320\270\320\272\321\203\320\273\321\213 (5 \321\207\320\270\321\201\320\265\320\273):", nullptr));
        t23_articles->setPlaceholderText(QCoreApplication::translate("MainWindow", "1 2 3 4 5", nullptr));
        btnT23_save->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\267\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\321\203 \320\262 \321\202\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
        btnT23_load->setText(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\262\321\201\320\265 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\321\213 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        group24->setTitle(QCoreApplication::translate("MainWindow", "2.4 \342\200\224 \320\241\321\202\321\200\321\203\320\272\321\202\321\203\321\200\320\260 \320\262 \320\261\320\270\320\275\320\260\321\200\320\275\321\213\320\271 \321\204\320\260\320\271\320\273 (\320\264\320\276\320\267\320\260\320\277\320\270\321\201\321\214, \320\244\320\260\320\274\320\270\320\273\320\270\321\217\320\233\320\260\320\26120_2.bin)", nullptr));
        label14->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200:", nullptr));
        t24_size->setPlaceholderText(QCoreApplication::translate("MainWindow", "42", nullptr));
        label15->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260:", nullptr));
        t24_price->setPlaceholderText(QCoreApplication::translate("MainWindow", "999.99", nullptr));
        label16->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273 (M/F/U):", nullptr));
        t24_gender->setPlaceholderText(QCoreApplication::translate("MainWindow", "M", nullptr));
        label17->setText(QCoreApplication::translate("MainWindow", "\320\222 \320\275\320\260\320\273\320\270\321\207\320\270\320\270:", nullptr));
        t24_stock->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260", nullptr));
        label18->setText(QCoreApplication::translate("MainWindow", "\320\221\321\200\320\265\320\275\320\264:", nullptr));
        t24_brand->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nike", nullptr));
        label19->setText(QCoreApplication::translate("MainWindow", "\320\220\321\200\321\202\320\270\320\272\321\203\320\273\321\213 (5 \321\207\320\270\321\201\320\265\320\273):", nullptr));
        t24_articles->setPlaceholderText(QCoreApplication::translate("MainWindow", "1 2 3 4 5", nullptr));
        btnT24_save->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\267\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\321\203 \320\262 \320\261\320\270\320\275\320\260\321\200\320\275\321\213\320\271 \321\204\320\260\320\271\320\273", nullptr));
        btnT24_load->setText(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\262\321\201\320\265 \321\201\321\202\321\200\321\203\320\272\321\202\321\203\321\200\321\213 \320\270\320\267 \320\261\320\270\320\275\320\260\321\200\320\275\320\276\320\263\320\276 \321\204\320\260\320\271\320\273\320\260", nullptr));
        group25->setTitle(QCoreApplication::translate("MainWindow", "2.5 \342\200\224 \320\237\320\276\321\201\321\202\321\200\320\276\321\207\320\275\320\260\321\217 \320\264\320\276\320\267\320\260\320\277\320\270\321\201\321\214/\321\207\321\202\320\265\320\275\320\270\320\265 \321\201\321\202\321\200\320\276\320\272 (\320\244\320\260\320\274\320\270\320\273\320\270\321\217\320\233\320\260\320\26120_3.txt)", nullptr));
        label20->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\321\200\320\265\320\264\320\273\320\276\320\266\320\265\320\275\320\270\320\265 (\320\261\321\203\320\264\320\265\321\202 \320\264\320\276\320\277\320\270\321\201\320\260\320\275\320\276 \320\262 \321\204\320\260\320\271\320\273 \320\272\320\260\320\272 \320\275\320\276\320\262\320\260\321\217 \321\201\321\202\321\200\320\276\320\272\320\260):", nullptr));
        t25_input->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\270\320\274\320\265\321\200: \320\241\320\265\320\263\320\276\320\264\320\275\321\217 \321\205\320\276\321\200\320\276\321\210\320\260\321\217 \320\277\320\276\320\263\320\276\320\264\320\260", nullptr));
        btnT25_save->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\267\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \321\201\321\202\321\200\320\276\320\272\321\203 \320\262 \321\204\320\260\320\271\320\273", nullptr));
        btnT25_load->setText(QCoreApplication::translate("MainWindow", "\320\241\321\207\320\270\321\202\320\260\321\202\321\214 \320\262\321\201\320\265 \321\201\321\202\321\200\320\276\320\272\320\270 \320\270\320\267 \321\204\320\260\320\271\320\273\320\260", nullptr));
        groupOutput->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        filePathLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "color: gray; font-size: 11px;", nullptr));
        filePathLabel->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273\321\213 \321\201\320\276\321\205\321\200\320\260\320\275\321\217\321\216\321\202\321\201\321\217 \321\200\321\217\320\264\320\276\320\274 \321\201 \320\270\321\201\320\277\320\276\320\273\320\275\321\217\320\265\320\274\321\213\320\274 \321\204\320\260\320\271\320\273\320\276\320\274", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\213\320\262\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
