#include "ellipse.h"
#include <cmath>

ellipse::ellipse() : shape(), m_center(0, 0), m_rx(0), m_ry(0)
{
}

ellipse::ellipse(const QPointF& center, double rx, double ry)
    : shape(), m_center(center), m_rx(rx), m_ry(ry)
{
}

double ellipse::area() const
{
    return M_PI * m_rx * m_ry;
}

double ellipse::perimeter() const
{
    double a = m_rx;
    double b = m_ry;
    return M_PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
}

QPointF ellipse::center() const
{
    return m_center;
}

void ellipse::moveCenter(const QPointF& newCenter)
{
    m_center = newCenter;
}

void ellipse::scale(double factor, const QPointF& centerPoint)
{
    QPointF vector = m_center - centerPoint;
    m_center = centerPoint + vector * factor;
    m_rx *= factor;
    m_ry *= factor;
}

void ellipse::rotate(double angle, const QPointF& centerPoint)
{
    double rad = angle * M_PI / 180;
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);
    QPointF vector = m_center - centerPoint;
    double xNew = vector.x() * cosA - vector.y() * sinA;
    double yNew = vector.x() * sinA + vector.y() * cosA;
    m_center = centerPoint + QPointF(xNew, yNew);
}

void ellipse::paint(QPainter* painter) const
{
    painter->drawEllipse(m_center, m_rx, m_ry);
}

QString ellipse::getName() const
{
    return "Эллипс";
}

void ellipse::setRadiusX(double rx)
{
    m_rx = rx;
}

void ellipse::setRadiusY(double ry)
{
    m_ry = ry;
}

double ellipse::radiusX() const
{
    return m_rx;
}

double ellipse::radiusY() const
{
    return m_ry;
}

void ellipse::setCenter(const QPointF& center)
{
    m_center = center;
}
