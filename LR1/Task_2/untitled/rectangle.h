#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "polygon.h"

class rectangle : public Polygon
{
    Q_OBJECT
public:
    rectangle(const QPointF& center, double width, double height);

    void setWidth(double width);
    void setHeight(double height);
    double width() const;
    double height() const;

    QString getName() const override;

private:
    QPointF m_center;
    double m_width;
    double m_height;
    void updateVertices();
};

#endif
