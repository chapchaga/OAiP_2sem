#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->mapInsertBtn,  &QPushButton::clicked, this, &MainWindow::onMapInsert);
    connect(ui->mapEraseBtn,   &QPushButton::clicked, this, &MainWindow::onMapErase);
    connect(ui->mapFindBtn,    &QPushButton::clicked, this, &MainWindow::onMapFind);
    connect(ui->mapClearBtn,   &QPushButton::clicked, this, &MainWindow::onMapClear);

    connect(ui->setInsertBtn,  &QPushButton::clicked, this, &MainWindow::onSetInsert);
    connect(ui->setEraseBtn,   &QPushButton::clicked, this, &MainWindow::onSetErase);
    connect(ui->setContainsBtn,&QPushButton::clicked, this, &MainWindow::onSetContains);
    connect(ui->setClearBtn,   &QPushButton::clicked, this, &MainWindow::onSetClear);

    connect(ui->hashInsertBtn, &QPushButton::clicked, this, &MainWindow::onHashInsert);
    connect(ui->hashEraseBtn,  &QPushButton::clicked, this, &MainWindow::onHashErase);
    connect(ui->hashFindBtn,   &QPushButton::clicked, this, &MainWindow::onHashFind);
    connect(ui->hashClearBtn,  &QPushButton::clicked, this, &MainWindow::onHashClear);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onMapInsert() {
    bool ok1, ok2;
    int key = ui->mapKeyInput->text().toInt(&ok1);
    QString val = ui->mapValueInput->text();
    if (!ok1) { ui->mapStatusLabel->setText("Invalid key (integer required)"); return; }
    map_.insert(key, val);
    ui->mapStatusLabel->setText(QString("Inserted: %1 → %2").arg(key).arg(val));
    refreshMapView();
}

void MainWindow::onMapErase() {
    bool ok;
    int key = ui->mapKeyInput->text().toInt(&ok);
    if (!ok) { ui->mapStatusLabel->setText("Invalid key"); return; }
    if (!map_.contains(key)) { ui->mapStatusLabel->setText("Key not found"); return; }
    map_.erase(key);
    ui->mapStatusLabel->setText(QString("Erased key: %1").arg(key));
    refreshMapView();
}

void MainWindow::onMapFind() {
    bool ok;
    int key = ui->mapKeyInput->text().toInt(&ok);
    if (!ok) { ui->mapStatusLabel->setText("Invalid key"); return; }
    if (map_.contains(key)) {
        ui->mapStatusLabel->setText(QString("Found: %1 → %2").arg(key).arg(map_[key]));
    } else {
        ui->mapStatusLabel->setText(QString("Key %1 not found").arg(key));
    }
}

void MainWindow::onMapClear() {
    map_.clear();
    ui->mapStatusLabel->setText("Map cleared");
    refreshMapView();
}

void MainWindow::refreshMapView() {
    ui->mapTreeList->clear();
    ui->mapLinkedList->clear();

    for (auto it = map_.begin(false); it != map_.end(false); ++it)
        ui->mapTreeList->addItem(QString("%1 → %2").arg(it->first).arg(it->second));

    for (auto it = map_.begin(true); it != map_.end(true); ++it)
        ui->mapLinkedList->addItem(QString("%1 → %2").arg(it->first).arg(it->second));
}

void MainWindow::onSetInsert() {
    bool ok;
    int key = ui->setKeyInput->text().toInt(&ok);
    if (!ok) { ui->setStatusLabel->setText("Invalid key"); return; }
    set_.insert(key);
    ui->setStatusLabel->setText(QString("Inserted: %1").arg(key));
    refreshSetView();
}

void MainWindow::onSetErase() {
    bool ok;
    int key = ui->setKeyInput->text().toInt(&ok);
    if (!ok) { ui->setStatusLabel->setText("Invalid key"); return; }
    set_.erase(key);
    ui->setStatusLabel->setText(QString("Erased: %1").arg(key));
    refreshSetView();
}

void MainWindow::onSetContains() {
    bool ok;
    int key = ui->setKeyInput->text().toInt(&ok);
    if (!ok) { ui->setStatusLabel->setText("Invalid key"); return; }
    ui->setStatusLabel->setText(
        set_.contains(key)
        ? QString("Key %1 IS in the set").arg(key)
        : QString("Key %1 is NOT in the set").arg(key)
    );
}

void MainWindow::onSetClear() {
    set_.clear();
    ui->setStatusLabel->setText("Set cleared");
    refreshSetView();
}

void MainWindow::refreshSetView() {
    ui->setTreeList->clear();
    ui->setLinkedList->clear();

    for (auto it = set_.begin(false); it != set_.end(false); ++it)
        ui->setTreeList->addItem(QString::number(it->first));

    for (auto it = set_.begin(true); it != set_.end(true); ++it)
        ui->setLinkedList->addItem(QString::number(it->first));
}

void MainWindow::onHashInsert() {
    bool ok;
    int key = ui->hashKeyInput->text().toInt(&ok);
    QString val = ui->hashValueInput->text();
    if (!ok) { ui->hashStatusLabel->setText("Invalid key"); return; }
    hashTable_.insert(key, val);
    ui->hashStatusLabel->setText(QString("Inserted: %1 → %2").arg(key).arg(val));
    refreshHashView();
}

void MainWindow::onHashErase() {
    bool ok;
    int key = ui->hashKeyInput->text().toInt(&ok);
    if (!ok) { ui->hashStatusLabel->setText("Invalid key"); return; }
    hashTable_.erase(key);
    ui->hashStatusLabel->setText(QString("Erased key: %1").arg(key));
    refreshHashView();
}

void MainWindow::onHashFind() {
    bool ok;
    int key = ui->hashKeyInput->text().toInt(&ok);
    if (!ok) { ui->hashStatusLabel->setText("Invalid key"); return; }
    if (hashTable_.contains(key)) {
        ui->hashStatusLabel->setText(
            QString("Found: %1 → %2").arg(key).arg(hashTable_[key])
        );
    } else {
        ui->hashStatusLabel->setText(QString("Key %1 not found").arg(key));
    }
}

void MainWindow::onHashClear() {
    hashTable_.clear();
    ui->hashStatusLabel->setText("HashTable cleared");
    refreshHashView();
}

void MainWindow::refreshHashView() {
    ui->hashList->clear();
    auto items = hashTable_.toVector();
    for (auto& p : items)
        ui->hashList->addItem(QString("%1 → %2").arg(p.first).arg(p.second));
    ui->hashStatsLabel->setText(
        QString("Size: %1   Capacity: %2").arg(hashTable_.size()).arg(hashTable_.capacity())
    );
}
