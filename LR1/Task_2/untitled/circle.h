#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class circle : public shape
{
    Q_OBJECT
public:
    circle();
    circle(const QPointF& center, double radius);

    double area() const override;
    double perimeter() const override;
    QPointF center() const override;
    void moveCenter(const QPointF& newCenter) override;
    void scale(double factor, const QPointF& centerPoint) override;
    void rotate(double angle, const QPointF& centerPoint) override;
    void paint(QPainter* painter) const override;
    QString getName() const override;

    void setRadius(double radius);
    double radius() const;
    void setCenter(const QPointF& center);

private:
    QPointF m_center;
    double m_radius;
};

#endif
