#include "car.h"

Car::Car(QPointF p, QSizeF s)
    : MovingRectangle(p, s)
{
}

void Car::toggleDoor()
{
    doorOpen = !doorOpen;
}

void Car::toggleLights()
{
    lightsOn = !lightsOn;
}

void Car::draw(QPainter &p)
{
    // Кузов
    p.setBrush(Qt::blue);
    p.drawRect(pos.x(), pos.y(), size.width(), size.height());

    // Колёса
    p.setBrush(Qt::black);
    p.drawEllipse(pos.x() + 10, pos.y() + size.height(), 20, 20);
    p.drawEllipse(pos.x() + size.width() - 30, pos.y() + size.height(), 20, 20);

    // Дверь
    if (doorOpen)
    {
        p.setBrush(Qt::darkBlue);
        p.drawRect(pos.x() + size.width(), pos.y() + 10, 30, size.height() - 20);
    }

    // Фары
    if (lightsOn)
    {
        p.setBrush(Qt::yellow);
        p.drawEllipse(pos.x() + size.width() - 5, pos.y() + 20, 15, 15);
    }
}
