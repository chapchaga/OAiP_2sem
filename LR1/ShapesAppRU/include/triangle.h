#pragma once
#include "shape.h"
#include <QPolygonF>

class Triangle : public Shape {
    Q_OBJECT
public:
    explicit Triangle(const QPointF& a={0,-60}, const QPointF& b={-50,40},
                      const QPointF& c={50,40}, QObject* parent=nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Треугольник"; }
    QRectF boundingRect() const override;

    QPointF a() const { return m_a; }
    QPointF b() const { return m_b; }
    QPointF c() const { return m_c; }
    void setVertices(const QPointF& a, const QPointF& b, const QPointF& c);

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    QPointF m_a, m_b, m_c;
    static QPointF rotatePoint(const QPointF& p, double rad, const QPointF& center);
};
