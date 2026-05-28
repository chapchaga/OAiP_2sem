#pragma once
#include "shape.h"

class Circle : public Shape {
    Q_OBJECT
public:
    explicit Circle(const QPointF& center = {0,0}, double radius = 50, QObject* parent = nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Круг"; }
    QRectF boundingRect() const override;

    double radius() const { return m_radius; }
    void setRadius(double r) { m_radius = r; emit changed(); }

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    QPointF m_center;
    double m_radius;
};
