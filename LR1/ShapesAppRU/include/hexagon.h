#pragma once
#include "shape.h"
#include <QPolygonF>

class Hexagon : public Shape {
    Q_OBJECT
public:
    explicit Hexagon(const QPointF& center={0,0}, double radius=50,
                     double angleDeg=0, QObject* parent=nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Шестиугольник"; }
    QRectF boundingRect() const override;

    double radius() const { return m_radius; }
    void setRadius(double r) { m_radius=r; buildPoly(); emit changed(); }

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    QPointF m_center;
    double m_radius, m_angle;
    QPolygonF m_poly;
    void buildPoly();
    static QPointF rotPt(const QPointF& p, double rad, const QPointF& c);
};
