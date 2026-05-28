#pragma once
#include <QMainWindow>
#include "DoublyLinkedQueue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLoadFile();
    void onPushBack();
    void onPushFront();
    void onPopFront();
    void onPopBack();
    void onMoveBlock();
    void onClear();

private:
    Ui::MainWindow* ui;
    DoublyLinkedQueue queue;

    void refreshList();
};
