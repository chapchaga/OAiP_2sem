#pragma once

#include <QPainter>

#include "MovingRectangle.h"

class Car : public MovingRectangle
{
public:
    Car() = default;

    void toggleHeadlights();
    void toggleDoors();

    bool headlightsOn() const noexcept { return headlightsOn_; }
    bool doorsOpen() const noexcept { return doorsOpen_; }

    void draw(QPainter& painter) const override;

private:
    bool headlightsOn_ = false;
    bool doorsOpen_ = false;
    double doorOpenOffset_ = 16.0;
};

