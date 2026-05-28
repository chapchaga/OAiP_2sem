#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnArrayInsert,  &QPushButton::clicked, this, &MainWindow::onArrayInsert);
    connect(ui->btnArrayExtract, &QPushButton::clicked, this, &MainWindow::onArrayExtract);
    connect(ui->btnArrayClear,   &QPushButton::clicked, this, &MainWindow::onArrayClear);

    connect(ui->btnListInsert,   &QPushButton::clicked, this, &MainWindow::onListInsert);
    connect(ui->btnListExtract,  &QPushButton::clicked, this, &MainWindow::onListExtract);
    connect(ui->btnListClear,    &QPushButton::clicked, this, &MainWindow::onListClear);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onArrayInsert() {
    int v = ui->spinArray->value();
    arrayHeap_.insert(v);
    refreshArrayView();
    setStatus(QString("Array Heap: inserted %1").arg(v));
}

void MainWindow::onArrayExtract() {
    try {
        int m = arrayHeap_.getMax();
        arrayHeap_.extractMax();
        refreshArrayView();
        setStatus(QString("Array Heap: extracted max = %1").arg(m));
    } catch (const std::exception& e) {
        setStatus(QString("Array Heap: %1").arg(e.what()));
    }
}

void MainWindow::onArrayClear() {
    arrayHeap_.clear();
    refreshArrayView();
    setStatus("Array Heap: cleared");
}

void MainWindow::onListInsert() {
    int v = ui->spinList->value();
    listHeap_.insert(v);
    refreshListView();
    setStatus(QString("List Heap: inserted %1").arg(v));
}

void MainWindow::onListExtract() {
    try {
        int m = listHeap_.getMax();
        listHeap_.extractMax();
        refreshListView();
        setStatus(QString("List Heap: extracted max = %1").arg(m));
    } catch (const std::exception& e) {
        setStatus(QString("List Heap: %1").arg(e.what()));
    }
}

void MainWindow::onListClear() {
    listHeap_.clear();
    refreshListView();
    setStatus("List Heap: cleared");
}

void MainWindow::refreshArrayView() {
    ui->listArray->clear();
    const auto& d = arrayHeap_.data();
    for (int i = 0; i < static_cast<int>(d.size()); ++i)
        ui->listArray->addItem(QString("[%1] = %2").arg(i).arg(d[i]));
    ui->lblArrayMax->setText(arrayHeap_.isEmpty() ? "Max: —"
                             : QString("Max: %1").arg(arrayHeap_.getMax()));
}

void MainWindow::refreshListView() {
    ui->listList->clear();
    auto lo = listHeap_.levelOrder();
    for (int i = 0; i < static_cast<int>(lo.size()); ++i)
        ui->listList->addItem(QString("[%1] = %2").arg(i).arg(lo[i]));
    ui->lblListMax->setText(listHeap_.isEmpty() ? "Max: —"
                            : QString("Max: %1").arg(listHeap_.getMax()));
}

void MainWindow::setStatus(const QString& msg) {
    ui->statusLabel->setText(msg);
}
