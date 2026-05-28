#include "MovingRectangle.h"

#include <cmath>

MovingRectangle::MovingRectangle() = default;

void MovingRectangle::setPosition(double x, double y)
{
    if (!std::isfinite(x) || !std::isfinite(y))
    {
        throw ValidationError("Некорректные координаты: ожидаются конечные числа.");
    }
    if (x < 0.0 || y < 0.0)
    {
        throw ValidationError("Координаты должны быть >= 0.");
    }

    x_ = x;
    y_ = y;
}

void MovingRectangle::moveBy(double dx, double dy)
{
    setPosition(x_ + dx, y_ + dy);
}

void MovingRectangle::draw(QPainter& painter) const
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::black);
    painter.setBrush(QColor(90, 160, 240, 120));
    painter.drawRect(QRectF(x_, y_, w_, h_));

    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRectF(x_, y_, w_, h_));

    painter.restore();
}

