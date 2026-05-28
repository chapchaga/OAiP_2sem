#include "restaurantmanager.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QPair>
#include <algorithm>
#include <stdexcept>

// -------- private --------

int RestaurantManager::dishIndexByName(const QString &name) const {
    for (int i = 0; i < dishes.size(); ++i)
        if (dishes[i].getName() == name) return i;
    return -1;
}

// -------- Блюда --------

void RestaurantManager::addDish(const Dish &d)  { dishes.append(d); }

void RestaurantManager::removeDish(int index) {
    if (index < 0 || index >= dishes.size())
        throw std::out_of_range("Неверный индекс блюда");
    dishes.removeAt(index);
}

void RestaurantManager::updateDish(int index, const Dish &d) {
    if (index < 0 || index >= dishes.size())
        throw std::out_of_range("Неверный индекс блюда");
    dishes[index] = d;
}

void RestaurantManager::sortDishesByPrice() {
    std::sort(dishes.begin(), dishes.end(), [](const Dish &a, const Dish &b){
        return a.getPrice() < b.getPrice();
    });
}

const QVector<Dish> &RestaurantManager::getDishes() const { return dishes; }

// -------- Заказы --------

void RestaurantManager::addOrder(const Order &o)  { orders.append(o); }

void RestaurantManager::removeOrder(int index) {
    if (index < 0 || index >= orders.size())
        throw std::out_of_range("Неверный индекс заказа");
    orders.removeAt(index);
}

void RestaurantManager::updateOrder(int index, const Order &o) {
    if (index < 0 || index >= orders.size())
        throw std::out_of_range("Неверный индекс заказа");
    orders[index] = o;
}

const QVector<Order> &RestaurantManager::getOrders() const { return orders; }

// -------- Аналитика --------

double RestaurantManager::orderTotal(int orderNum) const {
    double total = 0.0;
    for (const Order &o : orders) {
        if (o.getOrderNum() != orderNum) continue;
        int idx = dishIndexByName(o.getDishName());
        if (idx >= 0)
            total += dishes[idx].getPrice() * o.getQuantity();
    }
    return total;
}

QString RestaurantManager::mostPopularDishInCategory(const QString &cat) const {
    // считаем суммарное количество порций для каждого блюда в категории
    QVector<QPair<QString,int>> counts; // name, qty
    for (const Order &o : orders) {
        int idx = dishIndexByName(o.getDishName());
        if (idx < 0 || dishes[idx].getCategory() != cat) continue;
        bool found = false;
        for (auto &p : counts)
            if (p.first == o.getDishName()) { p.second += o.getQuantity(); found = true; break; }
        if (!found) counts.append(qMakePair(o.getDishName(), o.getQuantity()));
    }
    if (counts.isEmpty()) return QString();
    auto best = std::max_element(counts.begin(), counts.end(),
        [](const QPair<QString,int> &a, const QPair<QString,int> &b){ return a.second < b.second; });
    return best->first;
}

int RestaurantManager::mostProfitableOrderNum() const {
    // собираем уникальные номера заказов
    QVector<int> nums;
    for (const Order &o : orders) {
        if (!nums.contains(o.getOrderNum()))
            nums.append(o.getOrderNum());
    }
    if (nums.isEmpty()) return -1;
    int bestNum = nums[0];
    double bestTotal = orderTotal(bestNum);
    for (int i = 1; i < nums.size(); ++i) {
        double t = orderTotal(nums[i]);
        if (t > bestTotal) { bestTotal = t; bestNum = nums[i]; }
    }
    return bestNum;
}

QVector<QPair<int,double>> RestaurantManager::ordersSortedByTotal() const {
    QVector<int> nums;
    for (const Order &o : orders)
        if (!nums.contains(o.getOrderNum()))
            nums.append(o.getOrderNum());

    QVector<QPair<int,double>> result;
    for (int num : nums)
        result.append(qMakePair(num, orderTotal(num)));

    std::sort(result.begin(), result.end(),
        [](const QPair<int,double> &a, const QPair<int,double> &b){ return a.second > b.second; });
    return result;
}

// -------- Файлы --------

void RestaurantManager::loadDishes(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(QString("Не удалось открыть: %1").arg(path).toStdString());
    dishes.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        Dish d;
        if (d.fromString(line)) dishes.append(d);
    }
}

void RestaurantManager::saveDishes(const QString &path) const {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Не удалось сохранить блюда");
    QTextStream out(&file);
    for (const Dish &d : dishes) out << d.toString() << "\n";
}

void RestaurantManager::loadOrders(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error(QString("Не удалось открыть: %1").arg(path).toStdString());
    orders.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        Order o;
        if (o.fromString(line)) orders.append(o);
    }
}

void RestaurantManager::saveOrders(const QString &path) const {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Не удалось сохранить заказы");
    QTextStream out(&file);
    for (const Order &o : orders) out << o.toString() << "\n";
}
