#include "order.h"
#include <QStringList>
#include <stdexcept>

Order::Order() : orderNum(0), tableNum(0), quantity(1) {}

Order::Order(int orderNum, int tableNum, const QString &dishName, int quantity)
    : orderNum(orderNum), tableNum(tableNum), dishName(dishName), quantity(1)
{
    setQuantity(quantity);
}

int     Order::getOrderNum() const { return orderNum; }
int     Order::getTableNum() const { return tableNum; }
QString Order::getDishName() const { return dishName; }
int     Order::getQuantity() const { return quantity; }

void Order::setOrderNum(int n)           { orderNum = n; }
void Order::setTableNum(int n)           { tableNum = n; }
void Order::setDishName(const QString &d){ dishName = d; }

void Order::setQuantity(int q) {
    if (q <= 0)
        throw std::invalid_argument("Количество должно быть больше нуля");
    quantity = q;
}

QString Order::toString() const {
    return QString::number(orderNum) + ";" +
           QString::number(tableNum) + ";" +
           dishName + ";" +
           QString::number(quantity);
}

bool Order::fromString(const QString &s) {
    QStringList parts = s.split(';');
    if (parts.size() < 4) return false;
    bool ok1, ok2, ok4;
    int on = parts[0].trimmed().toInt(&ok1);
    int tn = parts[1].trimmed().toInt(&ok2);
    int  q = parts[3].trimmed().toInt(&ok4);
    if (!ok1 || !ok2 || !ok4 || q <= 0) return false;
    orderNum = on;
    tableNum = tn;
    dishName = parts[2].trimmed();
    quantity = q;
    return true;
}
