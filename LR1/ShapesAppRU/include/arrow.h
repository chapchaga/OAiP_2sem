#pragma once
#include "shape.h"
#include <QPolygonF>

// Arrow: a custom non-standard shape
class Arrow : public Shape {
    Q_OBJECT
public:
    explicit Arrow(const QPointF& center={0,0}, double length=100, double width=40,
                   double headRatio=0.35, double angleDeg=0, QObject* parent=nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Стрелка"; }
    QRectF boundingRect() const override;

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    QPointF m_center;
    double m_length, m_width, m_headRatio, m_angle;
    QPolygonF m_poly;
    void buildPoly();
    static QPointF rotPt(const QPointF& p, double rad, const QPointF& c);
};
