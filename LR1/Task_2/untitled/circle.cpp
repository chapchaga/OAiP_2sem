#include "circle.h"
#include <cmath>

circle::circle() : shape(), m_center(0, 0), m_radius(0)
{
}

circle::circle(const QPointF& center, double radius)
    : shape(), m_center(center), m_radius(radius)
{
}

double circle::area() const
{
    return M_PI * m_radius * m_radius;
}

double circle::perimeter() const
{
    return 2 * M_PI * m_radius;
}

QPointF circle::center() const
{
    return m_center;
}

void circle::moveCenter(const QPointF& newCenter)
{
    m_center = newCenter;
}

void circle::scale(double factor, const QPointF& centerPoint)
{
    QPointF vector = m_center - centerPoint;
    m_center = centerPoint + vector * factor;
    m_radius *= factor;
}

void circle::rotate(double angle, const QPointF& centerPoint)
{
    double rad = angle * M_PI / 180.0;
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);

    QPointF vector = m_center - centerPoint;
    double xNew = vector.x() * cosA - vector.y() * sinA;
    double yNew = vector.x() * sinA + vector.y() * cosA;

    m_center = centerPoint + QPointF(xNew, yNew);
}

void circle::paint(QPainter* painter) const
{
    painter->drawEllipse(m_center, m_radius, m_radius);
}

QString circle::getName() const
{
    return "Круг";
}

void circle::setRadius(double radius)
{
    m_radius = radius;
}

double circle::radius() const
{
    return m_radius;
}

void circle::setCenter(const QPointF& center)
{
    m_center = center;
}
