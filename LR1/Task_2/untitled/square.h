#ifndef SQUARE_H
#define SQUARE_H
#include "polygon.h"

class square : public Polygon
{
    Q_OBJECT
public:
    square(const QPointF& center, double side);

    void setSide(double side);
    double side() const;

    QString getName() const override;

private:
    QPointF m_center;
    double m_side;
    void updateVertices();
};

#endif
