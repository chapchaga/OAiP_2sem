#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"

class ellipse : public shape
{
    Q_OBJECT
public:
    ellipse();
    ellipse(const QPointF& center, double rx, double ry);

    double area() const override;
    double perimeter() const override;
    QPointF center() const override;
    void moveCenter(const QPointF& newCenter) override;
    void scale(double factor, const QPointF& centerPoint) override;
    void rotate(double angle, const QPointF& centerPoint) override;
    void paint(QPainter* painter) const override;
    QString getName() const override;

    void setRadiusX(double rx);
    void setRadiusY(double ry);
    double radiusX() const;
    double radiusY() const;
    void setCenter(const QPointF& center);

private:
    QPointF m_center;
    double m_rx;
    double m_ry;
};

#endif
