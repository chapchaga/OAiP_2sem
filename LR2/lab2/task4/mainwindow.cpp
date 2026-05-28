#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Expression.h"
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Задание 4 — check_equals");

    ui->cmbLeft->addItems({"Number(5)", "Number(10)", "BinaryOperation(1+2)", "BinaryOperation(3*4)"});
    ui->cmbRight->addItems({"Number(5)", "Number(10)", "BinaryOperation(1+2)", "BinaryOperation(3*4)"});

    ui->textExplain->setHtml(
        "<b>Задание 4:</b> реализовать <code>bool check_equals(Expression const* left, Expression const* right)</code><br>"
        "Возвращает <b>true</b>, если оба указателя указывают на объекты <b>одного класса</b>.<br><br>"
        "<b>Решение:</b> добавлен виртуальный метод <code>getTypeTag()</code>, который возвращает адрес "
        "статической переменной, уникальной для каждого класса.<br>"
        "Сравнение адресов тегов — эквивалентно сравнению типов.<br><br>"
        "<b>Запрет:</b> <code>typeid</code> и <code>dynamic_cast</code> — не используются."
    );

    // Настройка таблицы
    ui->tableResults->setColumnCount(4);
    ui->tableResults->setHorizontalHeaderLabels({"Левый объект", "Правый объект", "Результат", "Ожидалось"});
    ui->tableResults->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow() { delete ui; }

static Expression* createFromIndex(int idx) {
    switch (idx) {
        case 0: return new Number(5);
        case 1: return new Number(10);
        case 2: return new BinaryOperation(new Number(1), '+', new Number(2));
        case 3: return new BinaryOperation(new Number(3), '*', new Number(4));
        default: return new Number(0);
    }
}

static QString nameFromIndex(int idx) {
    switch (idx) {
        case 0: return "Number(5)";
        case 1: return "Number(10)";
        case 2: return "BinaryOperation(1+2)";
        case 3: return "BinaryOperation(3*4)";
        default: return "?";
    }
}

static bool isNumber(int idx)   { return idx == 0 || idx == 1; }

void MainWindow::on_btnCheck_clicked() {
    int li = ui->cmbLeft->currentIndex();
    int ri = ui->cmbRight->currentIndex();

    Expression* l = createFromIndex(li);
    Expression* r = createFromIndex(ri);

    bool result   = check_equals(l, r);
    bool expected = (isNumber(li) == isNumber(ri));

    logResult(nameFromIndex(li), nameFromIndex(ri), result, expected);

    delete l;
    delete r;
}

void MainWindow::on_btnRunAllTests_clicked() {
    ui->tableResults->setRowCount(0);

    // Все комбинации
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Expression* l = createFromIndex(i);
            Expression* r = createFromIndex(j);
            bool result   = check_equals(l, r);
            bool expected = (isNumber(i) == isNumber(j));
            logResult(nameFromIndex(i), nameFromIndex(j), result, expected);
            delete l;
            delete r;
        }
    }
}

void MainWindow::logResult(const QString& lName, const QString& rName,
                           bool result, bool expected) {
    int row = ui->tableResults->rowCount();
    ui->tableResults->insertRow(row);
    ui->tableResults->setItem(row, 0, new QTableWidgetItem(lName));
    ui->tableResults->setItem(row, 1, new QTableWidgetItem(rName));

    QString resStr = result ? "true" : "false";
    QString expStr = expected ? "true" : "false";

    QTableWidgetItem* resItem = new QTableWidgetItem(resStr);
    resItem->setForeground(result == expected ? Qt::darkGreen : Qt::red);
    ui->tableResults->setItem(row, 2, resItem);

    QTableWidgetItem* expItem = new QTableWidgetItem(expStr);
    ui->tableResults->setItem(row, 3, expItem);

    ui->tableResults->resizeColumnsToContents();
}

void MainWindow::on_cmbLeft_currentIndexChanged(int) {}
void MainWindow::on_cmbRight_currentIndexChanged(int) {}
