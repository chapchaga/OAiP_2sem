#include "square.h"
#include <QJsonObject>

Square::Square(const QPointF& center, double side, double angleDeg, QObject* parent)
    : Rectangle(center, side, side, angleDeg, parent) {}

QJsonObject Square::toJson() const {
    QJsonObject obj = Rectangle::toJson();
    obj["type"] = "Square";
    return obj;
}

void Square::fromJson(const QJsonObject& obj) {
    Rectangle::fromJson(obj);
}
