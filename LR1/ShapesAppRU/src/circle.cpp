#include "circle.h"
#include <QPainter>
#include <QJsonObject>
#include <cmath>

Circle::Circle(const QPointF& center, double radius, QObject* parent)
    : Shape(parent), m_center(center), m_radius(radius) {}

double Circle::area() const { return M_PI * m_radius * m_radius; }
double Circle::perimeter() const { return 2 * M_PI * m_radius; }
QPointF Circle::centroid() const { return m_center; }

void Circle::move(const QPointF& delta) {
    m_center += delta;
    emit changed();
}

void Circle::rotate(double angleDeg, const QPointF& center) {
    double rad = angleDeg * M_PI / 180.0;
    QPointF d = m_center - center;
    double nx = d.x() * cos(rad) - d.y() * sin(rad);
    double ny = d.x() * sin(rad) + d.y() * cos(rad);
    m_center = center + QPointF(nx, ny);
    emit changed();
}

void Circle::scale(double factor, const QPointF& center) {
    m_center = center + (m_center - center) * factor;
    m_radius *= factor;
    emit changed();
}

bool Circle::contains(const QPointF& pt) const {
    return QLineF(m_center, pt).length() <= m_radius;
}

void Circle::draw(QPainter& painter) const {
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected ? 2.5 : 1.5);
    if (m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawEllipse(m_center, m_radius, m_radius);
    if (m_selected) {
        painter.setPen(QPen(Qt::blue, 1));
        painter.setBrush(Qt::white);
        double s = 6;
        painter.drawRect(QRectF(m_center.x()-s/2, m_center.y()-m_radius-s/2, s, s));
        painter.drawRect(QRectF(m_center.x()-s/2, m_center.y()+m_radius-s/2, s, s));
        painter.drawRect(QRectF(m_center.x()-m_radius-s/2, m_center.y()-s/2, s, s));
        painter.drawRect(QRectF(m_center.x()+m_radius-s/2, m_center.y()-s/2, s, s));
    }
    painter.restore();
}

QRectF Circle::boundingRect() const {
    return QRectF(m_center.x()-m_radius, m_center.y()-m_radius, 2*m_radius, 2*m_radius);
}

QJsonObject Circle::toJson() const {
    QJsonObject obj = Shape::toJson();
    obj["type"] = "Circle";
    obj["cx"] = m_center.x(); obj["cy"] = m_center.y();
    obj["radius"] = m_radius;
    return obj;
}

void Circle::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_center = {obj["cx"].toDouble(), obj["cy"].toDouble()};
    m_radius = obj["radius"].toDouble();
}
