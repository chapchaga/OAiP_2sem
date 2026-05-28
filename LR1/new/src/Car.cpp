#include "Car.h"

#include <algorithm>

void Car::toggleHeadlights()
{
    headlightsOn_ = !headlightsOn_;
}

void Car::toggleDoors()
{
    doorsOpen_ = !doorsOpen_;
}

void Car::draw(QPainter& painter) const
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);

    const QRectF body(x_, y_, w_, h_);

    // Кузов
    painter.setPen(Qt::black);
    painter.setBrush(QColor(200, 70, 70, 170));
    painter.drawRoundedRect(body, 10.0, 10.0);

    // Колёса
    const double wheelR = std::min(w_, h_) * 0.09;
    const QPointF leftWheelCenter(x_ + w_ * 0.18, y_ + h_ * 0.93);
    const QPointF rightWheelCenter(x_ + w_ * 0.82, y_ + h_ * 0.93);
    painter.setBrush(Qt::black);
    painter.drawEllipse(leftWheelCenter, wheelR, wheelR);
    painter.drawEllipse(rightWheelCenter, wheelR, wheelR);

    // Двери (2 панели + линия стыка)
    const QRectF leftDoorBase(body.left(), body.top() + 12.0, body.width() / 2.0, body.height() - 22.0);
    const QRectF rightDoorBase(body.left() + body.width() / 2.0, body.top() + 12.0, body.width() / 2.0, body.height() - 22.0);

    const double shift = doorsOpen_ ? doorOpenOffset_ : 0.0;
    const QRectF leftDoor(leftDoorBase.translated(-shift, 0.0));
    const QRectF rightDoor(rightDoorBase.translated(+shift, 0.0));

    painter.setBrush(QColor(40, 40, 40, 160));
    painter.drawRect(leftDoor);
    painter.drawRect(rightDoor);

    // Стыковая линия (показываем даже при открытии)
    painter.setPen(QPen(Qt::black, 2));
    const QPointF seamStart(x_ + w_ / 2.0, y_ + 10.0);
    const QPointF seamEnd(x_ + w_ / 2.0, y_ + h_ - 6.0);
    painter.drawLine(seamStart, seamEnd);

    // Ручки дверей
    painter.setPen(Qt::black);
    if (doorsOpen_)
    {
        painter.drawLine(QPointF(leftDoor.right() - 5.0, leftDoor.center().y()), QPointF(leftDoor.right() + 2.0, leftDoor.center().y()));
        painter.drawLine(QPointF(rightDoor.left() + 3.0, rightDoor.center().y()), QPointF(rightDoor.left() - 2.0, rightDoor.center().y()));
    }
    else
    {
        painter.drawLine(QPointF(x_ + w_ * 0.5 - 6.0, y_ + h_ * 0.52), QPointF(x_ + w_ * 0.5 - 1.0, y_ + h_ * 0.52));
        painter.drawLine(QPointF(x_ + w_ * 0.5 + 1.0, y_ + h_ * 0.52), QPointF(x_ + w_ * 0.5 + 6.0, y_ + h_ * 0.52));
    }

    // Фары (пусть перед автомобиля находится справа)
    const double headY = y_ + h_ * 0.40;
    const double headX = x_ + w_ - 14.0;
    if (headlightsOn_)
    {
        painter.setBrush(QColor(255, 220, 100, 220));
        painter.drawEllipse(QPointF(headX, headY), 6.0, 6.0);
        painter.drawEllipse(QPointF(headX, headY + 22.0), 6.0, 6.0);

        QPen rayPen(QColor(255, 220, 100, 180), 2);
        painter.setPen(rayPen);
        // Лучи "вперёд" (вправо)
        painter.drawLine(QPointF(headX + 6.0, headY), QPointF(headX + 70.0, headY - 2.0));
        painter.drawLine(QPointF(headX + 6.0, headY + 22.0), QPointF(headX + 70.0, headY + 24.0));
    }
    else
    {
        painter.setBrush(Qt::darkGray);
        painter.drawEllipse(QPointF(headX, headY), 4.0, 4.0);
        painter.drawEllipse(QPointF(headX, headY + 22.0), 4.0, 4.0);
    }

    painter.restore();
}

