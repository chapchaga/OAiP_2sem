#pragma once
#include "shape.h"
#include <array>

class Rectangle : public Shape {
    Q_OBJECT
public:
    explicit Rectangle(const QPointF& center={0,0}, double w=100, double h=60,
                       double angleDeg=0, QObject* parent=nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Прямоугольник"; }
    QRectF boundingRect() const override;

    double width() const { return m_w; }
    double height() const { return m_h; }
    void setSize(double w, double h) { m_w=w; m_h=h; updateCorners(); emit changed(); }

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

protected:
    QPointF m_center;
    double m_w, m_h, m_angle; // angle in degrees
    std::array<QPointF,4> m_corners;

    void updateCorners();
    static QPointF rotPt(const QPointF& p, double rad, const QPointF& c);
};
