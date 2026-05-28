#pragma once

#include <QMainWindow>
#include <QString>
#include <cstring>

struct Odezhda {
    int size;
    double price;
    char gender;
    bool inStock;
    char brand[50];
    int articleNumbers[5];
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMenuChanged(int index);

    void onTask1_1Clicked();
    void onTask1_2Clicked();
    void onTask1_3Clicked();
    void onTask1_4Clicked();
    void onTask1_5Clicked();

    void onTask2_TextSaveClicked();
    void onTask2_TextLoadClicked();
    void onTask2_ArraySaveClicked();
    void onTask2_ArrayLoadClicked();
    void onTask2_StructTxtSaveClicked();
    void onTask2_StructTxtLoadClicked();
    void onTask2_StructBinSaveClicked();
    void onTask2_StructBinLoadClicked();
    void onTask2_LineSaveClicked();
    void onTask2_LineLoadClicked();

private:
    Ui::MainWindow *ui;

    QString formatOdezhda(const Odezhda &o, const QString &sep = " | ");
    Odezhda odezhdaFromForm();
    void appendOutput(const QString &text);
    QString filesDir();
};
