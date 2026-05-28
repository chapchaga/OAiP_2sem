#ifndef RHOMBUS_H
#define RHOMBUS_H
#include "polygon.h"

class rhombus : public Polygon
{
    Q_OBJECT
public:
    rhombus(const QPointF& center, double diagonal1, double diagonal2);

    void setDiagonals(double d1, double d2);
    double diagonal1() const;
    double diagonal2() const;

    QString getName() const override;

private:
    QPointF m_center;
    double m_d1;
    double m_d2;
    void updateVertices();
};

#endif
