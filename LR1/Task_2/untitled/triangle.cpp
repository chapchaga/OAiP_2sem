#include "triangle.h"
#include <cmath>
#include <stdexcept>

triangle::triangle(const QPointF& p1, const QPointF& p2, const QPointF& p3)
    : Polygon()
{
    if (arePointsCollinear(p1, p2, p3)) {
        throw std::invalid_argument("Точки лежат на одной прямой");
    }
    m_vertices.append(p1);
    m_vertices.append(p2);
    m_vertices.append(p3);
}

QString triangle::getName() const
{
    return "Треугольник";
}

bool triangle::arePointsCollinear(const QPointF& p1, const QPointF& p2, const QPointF& p3) const
{
    double area = p1.x() * (p2.y() - p3.y()) +
                  p2.x() * (p3.y() - p1.y()) +
                  p3.x() * (p1.y() - p2.y());

    return std::abs(area) < 1e-7;
}
