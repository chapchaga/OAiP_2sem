/********************************************************************************
** Form generated from reading UI file 'CandidateDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CANDIDATEDIALOG_H
#define UI_CANDIDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CandidateDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinDistrict;
    QLabel *label1;
    QLineEdit *editName;
    QLabel *label2;
    QLineEdit *editParty;
    QLabel *label3;
    QSpinBox *spinAge;
    QLabel *label4;
    QLineEdit *editProfession;
    QLabel *label5;
    QDoubleSpinBox *spinIncome;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CandidateDialog)
    {
        if (CandidateDialog->objectName().isEmpty())
            CandidateDialog->setObjectName("CandidateDialog");
        CandidateDialog->resize(400, 300);
        formLayout = new QFormLayout(CandidateDialog);
        formLayout->setObjectName("formLayout");
        label = new QLabel(CandidateDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinDistrict = new QSpinBox(CandidateDialog);
        spinDistrict->setObjectName("spinDistrict");
        spinDistrict->setMinimum(1);
        spinDistrict->setMaximum(9999);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinDistrict);

        label1 = new QLabel(CandidateDialog);
        label1->setObjectName("label1");

        formLayout->setWidget(1, QFormLayout::LabelRole, label1);

        editName = new QLineEdit(CandidateDialog);
        editName->setObjectName("editName");

        formLayout->setWidget(1, QFormLayout::FieldRole, editName);

        label2 = new QLabel(CandidateDialog);
        label2->setObjectName("label2");

        formLayout->setWidget(2, QFormLayout::LabelRole, label2);

        editParty = new QLineEdit(CandidateDialog);
        editParty->setObjectName("editParty");

        formLayout->setWidget(2, QFormLayout::FieldRole, editParty);

        label3 = new QLabel(CandidateDialog);
        label3->setObjectName("label3");

        formLayout->setWidget(3, QFormLayout::LabelRole, label3);

        spinAge = new QSpinBox(CandidateDialog);
        spinAge->setObjectName("spinAge");
        spinAge->setMinimum(18);
        spinAge->setMaximum(120);

        formLayout->setWidget(3, QFormLayout::FieldRole, spinAge);

        label4 = new QLabel(CandidateDialog);
        label4->setObjectName("label4");

        formLayout->setWidget(4, QFormLayout::LabelRole, label4);

        editProfession = new QLineEdit(CandidateDialog);
        editProfession->setObjectName("editProfession");

        formLayout->setWidget(4, QFormLayout::FieldRole, editProfession);

        label5 = new QLabel(CandidateDialog);
        label5->setObjectName("label5");

        formLayout->setWidget(5, QFormLayout::LabelRole, label5);

        spinIncome = new QDoubleSpinBox(CandidateDialog);
        spinIncome->setObjectName("spinIncome");
        spinIncome->setMinimum(0);
        spinIncome->setMaximum(99999999);
        spinIncome->setDecimals(2);

        formLayout->setWidget(5, QFormLayout::FieldRole, spinIncome);

        buttonBox = new QDialogButtonBox(CandidateDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(6, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(CandidateDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CandidateDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CandidateDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CandidateDialog);
    } // setupUi

    void retranslateUi(QDialog *CandidateDialog)
    {
        CandidateDialog->setWindowTitle(QCoreApplication::translate("CandidateDialog", "\320\232\320\260\320\275\320\264\320\270\320\264\320\260\321\202", nullptr));
        label->setText(QCoreApplication::translate("CandidateDialog", "\320\235\320\276\320\274\320\265\321\200 \320\276\320\272\321\200\321\203\320\263\320\260:", nullptr));
        label1->setText(QCoreApplication::translate("CandidateDialog", "\320\244\320\230\320\236:", nullptr));
        label2->setText(QCoreApplication::translate("CandidateDialog", "\320\237\320\260\321\200\321\202\320\270\321\217:", nullptr));
        label3->setText(QCoreApplication::translate("CandidateDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202:", nullptr));
        label4->setText(QCoreApplication::translate("CandidateDialog", "\320\237\321\200\320\276\321\204\320\265\321\201\321\201\320\270\321\217:", nullptr));
        label5->setText(QCoreApplication::translate("CandidateDialog", "\320\224\320\276\321\205\320\276\320\264 (\321\200\321\203\320\261.):", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CandidateDialog: public Ui_CandidateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANDIDATEDIALOG_H
