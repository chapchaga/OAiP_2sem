#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include <QVector>
#include <QPair>
#include <QString>
#include "dish.h"
#include "order.h"

class RestaurantManager {
private:
    QVector<Dish>  dishes;
    QVector<Order> orders;

    int dishIndexByName(const QString &name) const;

public:
    // ---------- Блюда ----------
    void addDish(const Dish &d);
    void removeDish(int index);           // бросает std::out_of_range
    void updateDish(int index, const Dish &d);
    void sortDishesByPrice();
    const QVector<Dish>  &getDishes() const;

    // ---------- Заказы ----------
    void addOrder(const Order &o);
    void removeOrder(int index);
    void updateOrder(int index, const Order &o);
    const QVector<Order> &getOrders() const;

    // ---------- Аналитика (Вариант 16) ----------
    double  orderTotal(int orderNum)                       const; // сумма заказа
    QString mostPopularDishInCategory(const QString &cat)  const; // самое популярное блюдо
    int     mostProfitableOrderNum()                       const; // самый прибыльный заказ
    // заказы, отсортированные по убыванию суммы
    QVector<QPair<int,double>> ordersSortedByTotal()       const;

    // ---------- Файлы ----------
    void loadDishes (const QString &path); // бросает std::runtime_error
    void saveDishes (const QString &path) const;
    void loadOrders (const QString &path);
    void saveOrders (const QString &path) const;
};

#endif // RESTAURANTMANAGER_H
