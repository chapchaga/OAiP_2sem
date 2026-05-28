#include "dish.h"
#include <QStringList>
#include <stdexcept>

Dish::Dish() : price(0.0) {}

Dish::Dish(const QString &name, const QString &category, double price)
    : name(name), category(category), price(0.0)
{
    setPrice(price);
}

QString Dish::getName()     const { return name; }
QString Dish::getCategory() const { return category; }
double  Dish::getPrice()    const { return price; }

void Dish::setName(const QString &n)     { name = n; }
void Dish::setCategory(const QString &c) { category = c; }

void Dish::setPrice(double p) {
    if (p < 0.0)
        throw std::invalid_argument("Цена не может быть отрицательной");
    price = p;
}

QString Dish::toString() const {
    return name + ";" + category + ";" + QString::number(price, 'f', 2);
}

bool Dish::fromString(const QString &s) {
    QStringList parts = s.split(';');
    if (parts.size() < 3) return false;
    bool ok;
    double p = parts[2].trimmed().toDouble(&ok);
    if (!ok || p < 0) return false;
    name     = parts[0].trimmed();
    category = parts[1].trimmed();
    price    = p;
    return true;
}
