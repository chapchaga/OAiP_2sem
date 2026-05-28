#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnLoad,      &QPushButton::clicked, this, &MainWindow::onLoadFile);
    connect(ui->btnPushBack,  &QPushButton::clicked, this, &MainWindow::onPushBack);
    connect(ui->btnPushFront, &QPushButton::clicked, this, &MainWindow::onPushFront);
    connect(ui->btnPopFront,  &QPushButton::clicked, this, &MainWindow::onPopFront);
    connect(ui->btnPopBack,   &QPushButton::clicked, this, &MainWindow::onPopBack);
    connect(ui->btnMove,      &QPushButton::clicked, this, &MainWindow::onMoveBlock);
    connect(ui->btnClear,     &QPushButton::clicked, this, &MainWindow::onClear);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::refreshList() {
    ui->listWidget->clear();
    Node* cur = queue.getHead();
    int i = 1;
    while (cur) {
        ui->listWidget->addItem(QString("%1: %2").arg(i++).arg(QString::fromStdString(cur->data)));
        cur = cur->next;
    }
    ui->labelSize->setText(QString("Size: %1").arg(queue.size()));
}

void MainWindow::onLoadFile() {
    QString path = QFileDialog::getOpenFileName(this, "Open file", "", "All files (*)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file.");
        return;
    }

    queue.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        queue.pushBack(line.toStdString());
    }
    file.close();
    refreshList();
}

void MainWindow::onPushBack() {
    QString text = ui->lineEditInput->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input error", "Enter text first.");
        return;
    }
    queue.pushBack(text.toStdString());
    ui->lineEditInput->clear();
    refreshList();
}

void MainWindow::onPushFront() {
    QString text = ui->lineEditInput->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Input error", "Enter text first.");
        return;
    }
    queue.pushFront(text.toStdString());
    ui->lineEditInput->clear();
    refreshList();
}

void MainWindow::onPopFront() {
    try {
        queue.popFront();
        refreshList();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onPopBack() {
    try {
        queue.popBack();
        refreshList();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onMoveBlock() {
    bool ok1, ok2, ok3;
    int start  = ui->spinStart->value();
    int end    = ui->spinEnd->value();
    int target = ui->spinTarget->value();
    ok1 = ok2 = ok3 = true;

    if (queue.empty()) {
        QMessageBox::warning(this, "Error", "Queue is empty.");
        return;
    }

    try {
        queue.moveBlock(start, end, target);
        refreshList();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void MainWindow::onClear() {
    queue.clear();
    refreshList();
}
