#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Order {
private:
    int     orderNum;
    int     tableNum;
    QString dishName;
    int     quantity;

public:
    Order();
    Order(int orderNum, int tableNum, const QString &dishName, int quantity);

    int     getOrderNum() const;
    int     getTableNum() const;
    QString getDishName() const;
    int     getQuantity() const;

    void setOrderNum(int n);
    void setTableNum(int n);
    void setDishName(const QString &d);
    void setQuantity(int q);   // бросает std::invalid_argument если q <= 0

    // CSV: "1;3;Борщ;2"
    QString toString()            const;
    bool    fromString(const QString &s);
};

#endif // ORDER_H
