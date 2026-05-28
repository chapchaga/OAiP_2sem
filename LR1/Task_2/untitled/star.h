#ifndef STAR_H
#define STAR_H
#include "polygon.h"

class star : public Polygon
{
    Q_OBJECT
public:
    star(const QPointF& center, double outerRadius, double innerRadius, int points = 5);

    void setOuterRadius(double radius);
    void setInnerRadius(double radius);
    void setPoints(int points);

    double outerRadius() const;
    double innerRadius() const;
    int points() const;

    QString getName() const override;

private:
    QPointF m_center;
    double m_outerRadius;
    double m_innerRadius;
    int m_points;
    void updateVertices();
};

#endif
