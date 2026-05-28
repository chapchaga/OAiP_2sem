#ifndef MOVINGRECTANGLE_H
#define MOVINGRECTANGLE_H

#include <QPainter>
#include <QPointF>
#include <QSizeF>

class MovingRectangle
{
protected:
    QPointF pos;
    QSizeF size;
    double speedX = 0;

public:
    MovingRectangle(QPointF p, QSizeF s);

    virtual void update();
    virtual void draw(QPainter &p);

    void setSpeed(double s);
    double left() const;
    double right() const;
};

#endif
