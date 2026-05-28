#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "polygon.h"

class triangle : public Polygon
{
    Q_OBJECT
public:
    triangle(const QPointF& p1, const QPointF& p2, const QPointF& p3);
    QString getName() const override;

private:
    bool arePointsCollinear(const QPointF& p1, const QPointF& p2, const QPointF& p3) const;
};

#endif
