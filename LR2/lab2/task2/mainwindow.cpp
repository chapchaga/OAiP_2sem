#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glasstests.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QColor>
#include <stdexcept>

// ============================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Задание 2 — Ресторан (Вариант 16)");

    // --- сигналы файлов ---
    connect(ui->btnLoadDishes, &QPushButton::clicked, this, &MainWindow::onLoadDishes);
    connect(ui->btnSaveDishes, &QPushButton::clicked, this, &MainWindow::onSaveDishes);
    connect(ui->btnLoadOrders, &QPushButton::clicked, this, &MainWindow::onLoadOrders);
    connect(ui->btnSaveOrders, &QPushButton::clicked, this, &MainWindow::onSaveOrders);

    // --- сигналы блюд ---
    connect(ui->btnAddDish,    &QPushButton::clicked, this, &MainWindow::onAddDish);
    connect(ui->btnRemoveDish, &QPushButton::clicked, this, &MainWindow::onRemoveDish);
    connect(ui->btnUpdateDish, &QPushButton::clicked, this, &MainWindow::onUpdateDish);
    connect(ui->btnSortDishes, &QPushButton::clicked, this, &MainWindow::onSortDishes);
    connect(ui->tableDishes, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::onDishSelected);

    // --- сигналы заказов ---
    connect(ui->btnAddOrder,    &QPushButton::clicked, this, &MainWindow::onAddOrder);
    connect(ui->btnRemoveOrder, &QPushButton::clicked, this, &MainWindow::onRemoveOrder);
    connect(ui->btnUpdateOrder, &QPushButton::clicked, this, &MainWindow::onUpdateOrder);
    connect(ui->tableOrders, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::onOrderSelected);

    // --- аналитика ---
    connect(ui->btnOrderTotal,  &QPushButton::clicked, this, &MainWindow::onOrderTotal);
    connect(ui->btnMostPopular, &QPushButton::clicked, this, &MainWindow::onMostPopular);
    connect(ui->btnBestOrder,   &QPushButton::clicked, this, &MainWindow::onBestOrder);
    connect(ui->btnSortOrders,  &QPushButton::clicked, this, &MainWindow::onSortOrders);

    // --- тесты ---
    connect(ui->btnRunTests, &QPushButton::clicked, this, &MainWindow::onRunTests);

    // демо-данные
    manager.addDish(Dish("Борщ",    "Супы",             5.50));
    manager.addDish(Dish("Стейк",   "Горячие блюда",   18.00));
    manager.addDish(Dish("Тирамису","Десерты",           7.00));
    manager.addDish(Dish("Цезарь",  "Холодные закуски",  8.50));
    manager.addDish(Dish("Пельмени","Горячие блюда",     9.00));
    manager.addOrder(Order(1, 3, "Борщ",     2));
    manager.addOrder(Order(1, 3, "Стейк",    1));
    manager.addOrder(Order(2, 5, "Тирамису", 3));
    manager.addOrder(Order(2, 5, "Цезарь",   1));
    manager.addOrder(Order(3, 1, "Пельмени", 4));

    refreshDishes();
    refreshOrders();
}

MainWindow::~MainWindow() { delete ui; }

// ============================================================
void MainWindow::showError(const QString &msg) {
    QMessageBox::warning(this, "Ошибка", msg);
}

// -------- Вспомогательные таблицы --------

void MainWindow::refreshDishes() {
    const QVector<Dish> &v = manager.getDishes();
    ui->tableDishes->setRowCount(0);
    ui->tableDishes->setColumnCount(3);
    ui->tableDishes->setHorizontalHeaderLabels({"Название", "Категория", "Цена"});
    for (const Dish &d : v) {
        int row = ui->tableDishes->rowCount();
        ui->tableDishes->insertRow(row);
        ui->tableDishes->setItem(row, 0, new QTableWidgetItem(d.getName()));
        ui->tableDishes->setItem(row, 1, new QTableWidgetItem(d.getCategory()));
        ui->tableDishes->setItem(row, 2, new QTableWidgetItem(
            QString::number(d.getPrice(), 'f', 2)));
    }
    ui->tableDishes->resizeColumnsToContents();
}

void MainWindow::refreshOrders() {
    const QVector<Order> &v = manager.getOrders();
    ui->tableOrders->setRowCount(0);
    ui->tableOrders->setColumnCount(4);
    ui->tableOrders->setHorizontalHeaderLabels({"№ Заказа","Стол","Блюдо","Кол-во"});
    for (const Order &o : v) {
        int row = ui->tableOrders->rowCount();
        ui->tableOrders->insertRow(row);
        ui->tableOrders->setItem(row, 0, new QTableWidgetItem(QString::number(o.getOrderNum())));
        ui->tableOrders->setItem(row, 1, new QTableWidgetItem(QString::number(o.getTableNum())));
        ui->tableOrders->setItem(row, 2, new QTableWidgetItem(o.getDishName()));
        ui->tableOrders->setItem(row, 3, new QTableWidgetItem(QString::number(o.getQuantity())));
    }
    ui->tableOrders->resizeColumnsToContents();
}

// -------- Выбор строки --------

void MainWindow::onDishSelected() {
    int row = ui->tableDishes->currentRow();
    if (row < 0 || row >= manager.getDishes().size()) return;
    const Dish &d = manager.getDishes()[row];
    ui->editDishName->setText(d.getName());
    ui->editDishCat->setText(d.getCategory());
    ui->editDishPrice->setText(QString::number(d.getPrice(), 'f', 2));
}

void MainWindow::onOrderSelected() {
    int row = ui->tableOrders->currentRow();
    if (row < 0 || row >= manager.getOrders().size()) return;
    const Order &o = manager.getOrders()[row];
    ui->editOrderNum->setText(QString::number(o.getOrderNum()));
    ui->editOrderTable->setText(QString::number(o.getTableNum()));
    ui->editOrderDish->setText(o.getDishName());
    ui->editOrderQty->setText(QString::number(o.getQuantity()));
}

// -------- Файлы --------

void MainWindow::onLoadDishes() {
    QString path = QFileDialog::getOpenFileName(
        this, "Открыть файл блюд", "", "Text Files (*.txt);;All Files (*)");
    if (path.isEmpty()) return;
    try { manager.loadDishes(path); refreshDishes(); }
    catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onSaveDishes() {
    QString path = QFileDialog::getSaveFileName(
        this, "Сохранить блюда", "dishes.txt", "Text Files (*.txt)");
    if (path.isEmpty()) return;
    try { manager.saveDishes(path); statusBar()->showMessage("Блюда сохранены: " + path, 3000); }
    catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onLoadOrders() {
    QString path = QFileDialog::getOpenFileName(
        this, "Открыть файл заказов", "", "Text Files (*.txt);;All Files (*)");
    if (path.isEmpty()) return;
    try { manager.loadOrders(path); refreshOrders(); }
    catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onSaveOrders() {
    QString path = QFileDialog::getSaveFileName(
        this, "Сохранить заказы", "orders.txt", "Text Files (*.txt)");
    if (path.isEmpty()) return;
    try { manager.saveOrders(path); statusBar()->showMessage("Заказы сохранены: " + path, 3000); }
    catch (std::exception &e) { showError(e.what()); }
}

// -------- CRUD блюда --------

void MainWindow::onAddDish() {
    try {
        QString name = ui->editDishName->text().trimmed();
        QString cat  = ui->editDishCat->text().trimmed();
        if (name.isEmpty() || cat.isEmpty())
            throw std::invalid_argument("Заполните Название и Категорию");
        bool ok;
        double price = ui->editDishPrice->text().toDouble(&ok);
        if (!ok) throw std::invalid_argument("Введите корректную цену");
        manager.addDish(Dish(name, cat, price));
        refreshDishes();
        statusBar()->showMessage("Блюдо добавлено", 2000);
    } catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onRemoveDish() {
    int row = ui->tableDishes->currentRow();
    if (row < 0) { showError("Выберите блюдо в таблице"); return; }
    try { manager.removeDish(row); refreshDishes(); }
    catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onUpdateDish() {
    int row = ui->tableDishes->currentRow();
    if (row < 0) { showError("Выберите блюдо в таблице"); return; }
    try {
        QString name = ui->editDishName->text().trimmed();
        QString cat  = ui->editDishCat->text().trimmed();
        if (name.isEmpty() || cat.isEmpty())
            throw std::invalid_argument("Заполните Название и Категорию");
        bool ok;
        double price = ui->editDishPrice->text().toDouble(&ok);
        if (!ok) throw std::invalid_argument("Введите корректную цену");
        manager.updateDish(row, Dish(name, cat, price));
        refreshDishes();
        statusBar()->showMessage("Блюдо обновлено", 2000);
    } catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onSortDishes() {
    manager.sortDishesByPrice();
    refreshDishes();
    statusBar()->showMessage("Блюда отсортированы по цене", 2000);
}

// -------- CRUD заказы --------

void MainWindow::onAddOrder() {
    try {
        bool ok1, ok2, ok3;
        int num = ui->editOrderNum->text().toInt(&ok1);
        int tbl = ui->editOrderTable->text().toInt(&ok2);
        int qty = ui->editOrderQty->text().toInt(&ok3);
        QString dish = ui->editOrderDish->text().trimmed();
        if (!ok1 || !ok2 || !ok3 || dish.isEmpty())
            throw std::invalid_argument("Заполните все поля корректно");
        manager.addOrder(Order(num, tbl, dish, qty));
        refreshOrders();
        statusBar()->showMessage("Заказ добавлен", 2000);
    } catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onRemoveOrder() {
    int row = ui->tableOrders->currentRow();
    if (row < 0) { showError("Выберите заказ в таблице"); return; }
    try { manager.removeOrder(row); refreshOrders(); }
    catch (std::exception &e) { showError(e.what()); }
}

void MainWindow::onUpdateOrder() {
    int row = ui->tableOrders->currentRow();
    if (row < 0) { showError("Выберите заказ в таблице"); return; }
    try {
        bool ok1, ok2, ok3;
        int num = ui->editOrderNum->text().toInt(&ok1);
        int tbl = ui->editOrderTable->text().toInt(&ok2);
        int qty = ui->editOrderQty->text().toInt(&ok3);
        QString dish = ui->editOrderDish->text().trimmed();
        if (!ok1 || !ok2 || !ok3 || dish.isEmpty())
            throw std::invalid_argument("Заполните все поля корректно");
        manager.updateOrder(row, Order(num, tbl, dish, qty));
        refreshOrders();
        statusBar()->showMessage("Заказ обновлён", 2000);
    } catch (std::exception &e) { showError(e.what()); }
}

// -------- Аналитика --------

void MainWindow::onOrderTotal() {
    bool ok;
    int num = ui->editAnalyticsNum->text().toInt(&ok);
    if (!ok) { showError("Введите номер заказа"); return; }
    double total = manager.orderTotal(num);
    ui->labelAnalytics->setText(
        QString("Сумма заказа №%1:  %2 руб.").arg(num).arg(total, 0, 'f', 2));
}

void MainWindow::onMostPopular() {
    QString cat = ui->editAnalyticsCat->text().trimmed();
    if (cat.isEmpty()) { showError("Введите категорию"); return; }
    QString dish = manager.mostPopularDishInCategory(cat);
    ui->labelAnalytics->setText(
        dish.isEmpty() ? "Нет данных для категории: " + cat
                       : "Самое популярное в «" + cat + "»: " + dish);
}

void MainWindow::onBestOrder() {
    int best = manager.mostProfitableOrderNum();
    if (best < 0) { ui->labelAnalytics->setText("Заказов нет"); return; }
    double total = manager.orderTotal(best);
    ui->labelAnalytics->setText(
        QString("Самый прибыльный заказ: №%1  (сумма: %2 руб.)").arg(best).arg(total,0,'f',2));
}

void MainWindow::onSortOrders() {
    auto sorted = manager.ordersSortedByTotal();
    ui->tableAnalytics->setRowCount(0);
    ui->tableAnalytics->setColumnCount(2);
    ui->tableAnalytics->setHorizontalHeaderLabels({"№ Заказа", "Сумма (руб.)"});
    for (const QPair<int,double> &p : sorted) {
        int row = ui->tableAnalytics->rowCount();
        ui->tableAnalytics->insertRow(row);
        ui->tableAnalytics->setItem(row, 0, new QTableWidgetItem(QString::number(p.first)));
        ui->tableAnalytics->setItem(row, 1, new QTableWidgetItem(
            QString::number(p.second, 'f', 2)));
    }
    ui->tableAnalytics->resizeColumnsToContents();
    ui->labelAnalytics->setText("Заказы отсортированы по убыванию суммы");
}

// -------- Тесты (стеклянный ящик) --------

void MainWindow::onRunTests() {
    GlassBoxTests tests;
    tests.runAll();

    // показать в таблице
    const QVector<TestResult> &res = tests.getResults();
    ui->tableTests->setRowCount(0);
    ui->tableTests->setColumnCount(3);
    ui->tableTests->setHorizontalHeaderLabels({"Тест", "Эталон", "ok?"});
    int passed = 0;
    for (const TestResult &r : res) {
        if (r.passed) ++passed;
        int row = ui->tableTests->rowCount();
        ui->tableTests->insertRow(row);
        ui->tableTests->setItem(row, 0, new QTableWidgetItem(r.name));
        ui->tableTests->setItem(row, 1, new QTableWidgetItem(r.expected));
        QTableWidgetItem *statusItem = new QTableWidgetItem(r.passed ? "ok" : "fail");
        statusItem->setBackground(r.passed ? QColor("#c8e6c9") : QColor("#ffcdd2"));
        ui->tableTests->setItem(row, 2, statusItem);
    }
    ui->tableTests->resizeColumnsToContents();

    // сохранить Excel
    QString path = QFileDialog::getSaveFileName(
        this, "Сохранить результаты тестов", "test_results.xlsx",
        "Excel Files (*.xlsx)");
    if (!path.isEmpty()) {
        try {
            tests.saveXlsx(path);
            QMessageBox::information(this, "Тесты завершены",
                QString("Результат: %1 / %2 пройдено\nФайл сохранён:\n%3")
                    .arg(passed).arg(res.size()).arg(path));
        } catch (std::exception &e) { showError(e.what()); }
    }
}
