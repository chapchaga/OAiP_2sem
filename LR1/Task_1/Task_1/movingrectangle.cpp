#include "movingrectangle.h"

MovingRectangle::MovingRectangle(QPointF p, QSizeF s)
    : pos(p), size(s)
{
}

void MovingRectangle::setSpeed(double s)
{
    speedX = s;
}

void MovingRectangle::update()
{
    pos.rx() += speedX;
}

void MovingRectangle::draw(QPainter &p)
{
    p.setBrush(Qt::blue);
    p.drawRect(pos.x(), pos.y(), size.width(), size.height());
}

double MovingRectangle::left() const
{
    return pos.x();
}

double MovingRectangle::right() const
{
    return pos.x() + size.width();
}
