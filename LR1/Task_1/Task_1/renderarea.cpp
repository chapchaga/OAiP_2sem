#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent),
    car(QPointF(50,150), QSizeF(120,60))
{
    setMinimumSize(800, 400);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &RenderArea::onTick);
    timer->start(16);
}

void RenderArea::toggleDoor()
{
    car.toggleDoor();
}

void RenderArea::toggleLights()
{
    car.toggleLights();
}

void RenderArea::moveLeft()
{
    car.setSpeed(-3);
}

void RenderArea::moveRight()
{
    car.setSpeed(3);
}

void RenderArea::stop()
{
    car.setSpeed(0);
}

void RenderArea::onTick()
{
    car.update();

    // Правая граница
    if (car.right() > width())
    {
        car.setSpeed(0);
    }

    // Левая граница
    if (car.left() < 0)
    {
        car.setSpeed(0);
    }

    update();
}
void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    car.draw(p);
}
