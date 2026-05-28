#include "shape.h"
#include <QTimer>
#include <QJsonObject>
#include <cmath>

Shape::Shape(QObject* parent) : QObject(parent) {}

void Shape::setCentroid(const QPointF& pt) {
    QPointF delta = pt - centroid();
    move(delta);
}

void Shape::move(const QPointF& delta) {
    // Subclasses override — base does nothing
    Q_UNUSED(delta)
}

void Shape::rotate(double angleDeg, const QPointF& center) {
    Q_UNUSED(angleDeg) Q_UNUSED(center)
}

void Shape::scale(double factor, const QPointF& center) {
    Q_UNUSED(factor) Q_UNUSED(center)
}

void Shape::animateMove(const QPointF& delta, int durationMs, int steps) {
    QPointF stepDelta = delta / steps;
    int interval = durationMs / steps;
    int* count = new int(0);
    QTimer* t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=]() mutable {
        move(stepDelta);
        emit animationStep();
        emit changed();
        if (++(*count) >= steps) {
            t->stop();
            t->deleteLater();
            delete count;
        }
    });
    t->start(interval);
}

void Shape::animateRotate(double angleDeg, const QPointF& center, int durationMs, int steps) {
    double stepAngle = angleDeg / steps;
    int interval = durationMs / steps;
    int* count = new int(0);
    QTimer* t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=]() mutable {
        rotate(stepAngle, center);
        emit animationStep();
        emit changed();
        if (++(*count) >= steps) {
            t->stop();
            t->deleteLater();
            delete count;
        }
    });
    t->start(interval);
}

void Shape::animateScale(double factor, const QPointF& center, int durationMs, int steps) {
    double stepFactor = std::pow(factor, 1.0 / steps);
    int interval = durationMs / steps;
    int* count = new int(0);
    QTimer* t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=]() mutable {
        scale(stepFactor, center);
        emit animationStep();
        emit changed();
        if (++(*count) >= steps) {
            t->stop();
            t->deleteLater();
            delete count;
        }
    });
    t->start(interval);
}

QJsonObject Shape::toJson() const {
    QJsonObject obj;
    obj["fillColor"] = m_fillColor.name();
    obj["strokeColor"] = m_strokeColor.name();
    return obj;
}

void Shape::fromJson(const QJsonObject& obj) {
    if (obj.contains("fillColor"))   m_fillColor   = QColor(obj["fillColor"].toString());
    if (obj.contains("strokeColor")) m_strokeColor = QColor(obj["strokeColor"].toString());
}
