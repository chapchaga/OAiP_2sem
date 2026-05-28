#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
#include <QVector>

class Polygon : public shape
{
    Q_OBJECT
public:
    Polygon();
    Polygon(const QVector<QPointF>& vertices);
    virtual ~Polygon();

    double area() const override;
    double perimeter() const override;
    QPointF center() const override;
    void moveCenter(const QPointF& newCenter) override;
    void scale(double factor, const QPointF& centerPoint) override;
    void rotate(double angle, const QPointF& centerPoint) override;
    void paint(QPainter* painter) const override;
    QString getName() const override;

    virtual void setVertex(int index, const QPointF& point);
    virtual void addVertex(const QPointF& point);
    int vertexCount() const;
    QPointF getVertex(int index) const;

protected:
    QVector<QPointF> m_vertices;
};

#endif
