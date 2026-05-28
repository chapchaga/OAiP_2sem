#pragma once

#include <QPainter>

#include "Exceptions.h"

class MovingRectangle
{
public:
    MovingRectangle();
    virtual ~MovingRectangle() = default;

    virtual void setPosition(double x, double y);
    virtual void moveBy(double dx, double dy);

    double x() const noexcept { return x_; }
    double y() const noexcept { return y_; }
    double width() const noexcept { return w_; }
    double height() const noexcept { return h_; }

    // Рисование фигуры на холсте.
    virtual void draw(QPainter& painter) const;

protected:
    double x_ = 100.0;
    double y_ = 100.0;
    double w_ = 140.0;
    double h_ = 70.0;
};

