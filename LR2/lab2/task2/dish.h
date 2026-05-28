#ifndef DISH_H
#define DISH_H

#include <QString>

class Dish {
private:
    QString name;
    QString category;
    double  price;

public:
    Dish();
    Dish(const QString &name, const QString &category, double price);

    QString getName()     const;
    QString getCategory() const;
    double  getPrice()    const;

    void setName(const QString &n);
    void setCategory(const QString &c);
    void setPrice(double p);          // бросает std::invalid_argument если p < 0

    // CSV: "Борщ;Супы;5.50"
    QString toString()            const;
    bool    fromString(const QString &s);
};

#endif // DISH_H
