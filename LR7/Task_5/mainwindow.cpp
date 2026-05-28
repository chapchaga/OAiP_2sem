#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    connect(ui->pushBackBtn,  &QPushButton::clicked, this, &MainWindow::onPushBack);
    connect(ui->pushFrontBtn, &QPushButton::clicked, this, &MainWindow::onPushFront);
    connect(ui->popBackBtn,   &QPushButton::clicked, this, &MainWindow::onPopBack);
    connect(ui->popFrontBtn,  &QPushButton::clicked, this, &MainWindow::onPopFront);
    connect(ui->clearBtn,     &QPushButton::clicked, this, &MainWindow::onClear);
    connect(ui->getIndexBtn,  &QPushButton::clicked, this, &MainWindow::onGetByIndex);
    connect(ui->fillRandomBtn,&QPushButton::clicked, this, &MainWindow::onFillRandom);

    updateInfo();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::refreshView() {
    ui->dequeList->clear();
    for (int i = 0; i < deque.size(); i++) {
        QString prefix;
        if (i == 0) prefix = "[front] ";
        else if (i == deque.size() - 1) prefix = "[back]  ";
        else prefix = QString("[%1]     ").arg(i);
        ui->dequeList->addItem(prefix + QString::number(deque[i]));
    }
    updateInfo();
}

void MainWindow::updateInfo() {
    QString info = QString("size: %1  |  empty: %2")
        .arg(deque.size())
        .arg(deque.empty() ? "true" : "false");
    if (!deque.empty()) {
        info += QString("  |  front: %1  |  back: %2")
            .arg(deque.front()).arg(deque.back());
    }
    ui->infoLabel->setText(info);
}

void MainWindow::onPushBack() {
    int val = ui->valueSpinBox->value();
    deque.push_back(val);
    ui->logEdit->appendPlainText(QString("push_back(%1)  → size=%2").arg(val).arg(deque.size()));
    refreshView();
}

void MainWindow::onPushFront() {
    int val = ui->valueSpinBox->value();
    deque.push_front(val);
    ui->logEdit->appendPlainText(QString("push_front(%1)  → size=%2").arg(val).arg(deque.size()));
    refreshView();
}

void MainWindow::onPopBack() {
    if (deque.empty()) {
        ui->logEdit->appendPlainText("pop_back()  → ERROR: deque is empty");
        return;
    }
    int val = deque.back();
    deque.pop_back();
    ui->logEdit->appendPlainText(QString("pop_back()  removed %1  → size=%2").arg(val).arg(deque.size()));
    refreshView();
}

void MainWindow::onPopFront() {
    if (deque.empty()) {
        ui->logEdit->appendPlainText("pop_front()  → ERROR: deque is empty");
        return;
    }
    int val = deque.front();
    deque.pop_front();
    ui->logEdit->appendPlainText(QString("pop_front()  removed %1  → size=%2").arg(val).arg(deque.size()));
    refreshView();
}

void MainWindow::onClear() {
    deque.clear();
    ui->logEdit->appendPlainText("clear()  → size=0");
    ui->resultLabel->setText("Result: —");
    refreshView();
}

void MainWindow::onGetByIndex() {
    int idx = ui->indexSpinBox->value();
    if (idx < 0 || idx >= deque.size()) {
        ui->resultLabel->setText(QString("Result: index %1 out of range (size=%2)").arg(idx).arg(deque.size()));
        ui->logEdit->appendPlainText(QString("operator[%1]  → OUT OF RANGE").arg(idx));
        return;
    }
    int val = deque[idx];
    ui->resultLabel->setText(QString("Result: deque[%1] = %2").arg(idx).arg(val));
    ui->logEdit->appendPlainText(QString("operator[%1]  → %2").arg(idx).arg(val));
    ui->dequeList->setCurrentRow(idx);
}

void MainWindow::onFillRandom() {
    deque.clear();
    for (int i = 0; i < 10; i++) {
        int v = (std::rand() % 201) - 100;
        deque.push_back(v);
    }
    ui->logEdit->appendPlainText("fillRandom(10)  → filled with 10 random values in [-100,100]");
    refreshView();
}
