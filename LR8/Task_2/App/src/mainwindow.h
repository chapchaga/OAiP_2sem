#pragma once
#include <QMainWindow>
#include "ArrayHeap.h"
#include "ListHeap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onArrayInsert();
    void onArrayExtract();
    void onArrayClear();

    void onListInsert();
    void onListExtract();
    void onListClear();

private:
    Ui::MainWindow* ui;
    ArrayHeap arrayHeap_;
    ListHeap  listHeap_;

    void refreshArrayView();
    void refreshListView();
    void setStatus(const QString& msg);
};
