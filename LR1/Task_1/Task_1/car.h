#ifndef CAR_H
#define CAR_H

#include "movingrectangle.h"

class Car : public MovingRectangle
{
private:
    bool doorOpen = false;
    bool lightsOn = false;

public:
    Car(QPointF p, QSizeF s);

    void toggleDoor();
    void toggleLights();

    void draw(QPainter &p) override;
};

#endif
