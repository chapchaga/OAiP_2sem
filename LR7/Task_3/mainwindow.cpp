#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ht(nullptr)
{
    ui->setupUi(this);
    ht = new HashTable(ui->spinTableSize->value());

    connect(ui->btnGenerate, &QPushButton::clicked, this, &MainWindow::onGenerate);
    connect(ui->btnInsert,   &QPushButton::clicked, this, &MainWindow::onInsert);
    connect(ui->btnRemove,   &QPushButton::clicked, this, &MainWindow::onRemove);
    connect(ui->btnFind,     &QPushButton::clicked, this, &MainWindow::onFind);
    connect(ui->btnFindMax,  &QPushButton::clicked, this, &MainWindow::onFindMax);
    connect(ui->btnClear,    &QPushButton::clicked, this, &MainWindow::onClear);

    refreshTable();
}

MainWindow::~MainWindow() {
    delete ht;
    delete ui;
}

void MainWindow::refreshTable() {
    ui->memoTable->setPlainText(QString::fromStdString(ht->toString()));
    ui->labelCount->setText(QString("Total elements: %1").arg(ht->totalCount()));
}

void MainWindow::onGenerate() {
    delete ht;
    ht = new HashTable(ui->spinTableSize->value());
    int n = ui->spinCount->value();
    for (int i = 0; i < n; i++) {
        int key = QRandomGenerator::global()->bounded(-100, 101);
        ht->insert(key, "val" + std::to_string(i));
    }
    ui->labelResult->setText("Generated " + QString::number(n) + " random elements.");
    refreshTable();
}

void MainWindow::onInsert() {
    bool ok;
    int key = ui->editKey->text().toInt(&ok);
    if (!ok) { ui->labelResult->setText("Invalid key."); return; }
    QString val = ui->editValue->text();
    if (val.isEmpty()) val = "item";
    ht->insert(key, val.toStdString());
    ui->labelResult->setText(QString("Inserted key=%1").arg(key));
    refreshTable();
}

void MainWindow::onRemove() {
    bool ok;
    int key = ui->editKey->text().toInt(&ok);
    if (!ok) { ui->labelResult->setText("Invalid key."); return; }
    if (ht->remove(key))
        ui->labelResult->setText(QString("Removed key=%1").arg(key));
    else
        ui->labelResult->setText(QString("Key=%1 not found.").arg(key));
    refreshTable();
}

void MainWindow::onFind() {
    bool ok;
    int key = ui->editKey->text().toInt(&ok);
    if (!ok) { ui->labelResult->setText("Invalid key."); return; }
    StackNode* node = ht->find(key);
    if (node)
        ui->labelResult->setText(QString("Found: key=%1, value=%2")
            .arg(node->key).arg(QString::fromStdString(node->value)));
    else
        ui->labelResult->setText(QString("Key=%1 not found.").arg(key));
}

void MainWindow::onFindMax() {
    StackNode* node = ht->findMax();
    if (node) {
        int idx = ht->hashFunc(node->key);
        ui->labelResult->setText(
            QString("MAX: key=%1, value=%2, bucket=%3")
            .arg(node->key)
            .arg(QString::fromStdString(node->value))
            .arg(idx));
    } else {
        ui->labelResult->setText("Table is empty.");
    }
}

void MainWindow::onClear() {
    ht->clear();
    ui->labelResult->setText("Table cleared.");
    refreshTable();
}
