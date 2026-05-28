#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "restaurantmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Файлы — блюда
    void onLoadDishes();
    void onSaveDishes();
    // Файлы — заказы
    void onLoadOrders();
    void onSaveOrders();

    // CRUD — блюда
    void onAddDish();
    void onRemoveDish();
    void onUpdateDish();
    void onSortDishes();

    // CRUD — заказы
    void onAddOrder();
    void onRemoveOrder();
    void onUpdateOrder();

    // Аналитика
    void onOrderTotal();
    void onMostPopular();
    void onBestOrder();
    void onSortOrders();

    // Тесты
    void onRunTests();

    // Выбор строки в таблице — заполнить поля
    void onDishSelected();
    void onOrderSelected();

private:
    Ui::MainWindow *ui;
    RestaurantManager manager;

    void refreshDishes();
    void refreshOrders();
    void showError(const QString &msg);
};

#endif // MAINWINDOW_H
