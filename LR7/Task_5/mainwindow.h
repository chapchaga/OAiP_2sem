#pragma once
#include <QMainWindow>
#include "mydeque.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushBack();
    void onPushFront();
    void onPopBack();
    void onPopFront();
    void onClear();
    void onGetByIndex();
    void onFillRandom();

private:
    Ui::MainWindow *ui;
    MyDeque<int> deque;

    void refreshView();
    void updateInfo();
};
