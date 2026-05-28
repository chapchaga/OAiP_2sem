#include "polygon.h"
#include <cmath>
#include <QPolygonF>

Polygon::Polygon() : shape()
{
}

Polygon::Polygon(const QVector<QPointF>& vertices)
    : shape(), m_vertices(vertices)
{
}

Polygon::~Polygon()
{
}

double Polygon::area() const
{
    if (m_vertices.size() < 3) return 0.0;

    double area = 0.0;
    int n = m_vertices.size();

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += m_vertices[i].x() * m_vertices[j].y();
        area -= m_vertices[j].x() * m_vertices[i].y();
    }

    return std::abs(area) / 2.0;
}

double Polygon::perimeter() const
{
    if (m_vertices.size() < 2) return 0.0;

    double perimeter = 0.0;
    int n = m_vertices.size();

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double dx = m_vertices[j].x() - m_vertices[i].x();
        double dy = m_vertices[j].y() - m_vertices[i].y();
        perimeter += std::sqrt(dx * dx + dy * dy);
    }

    return perimeter;
}

QPointF Polygon::center() const
{
    if (m_vertices.isEmpty()) return QPointF(0, 0);

    double sumX = 0, sumY = 0;
    for (const QPointF& vertex : m_vertices) {
        sumX += vertex.x();
        sumY += vertex.y();
    }

    return QPointF(sumX / m_vertices.size(), sumY / m_vertices.size());
}

void Polygon::moveCenter(const QPointF& newCenter)
{
    QPointF oldCenter = center();
    QPointF delta = newCenter - oldCenter;

    for (QPointF& vertex : m_vertices) {
        vertex += delta;
    }
}

void Polygon::scale(double factor, const QPointF& centerPoint)
{
    for (QPointF& vertex : m_vertices) {
        QPointF vector = vertex - centerPoint;
        vertex = centerPoint + vector * factor;
    }
}

void Polygon::rotate(double angle, const QPointF& centerPoint)
{
    double rad = angle * M_PI / 180.0;
    double cosA = std::cos(rad);
    double sinA = std::sin(rad);

    for (QPointF& vertex : m_vertices) {
        QPointF vector = vertex - centerPoint;
        double xNew = vector.x() * cosA - vector.y() * sinA;
        double yNew = vector.x() * sinA + vector.y() * cosA;
        vertex = centerPoint + QPointF(xNew, yNew);
    }
}

void Polygon::paint(QPainter* painter) const
{
    QPolygonF polygon;
    for (const QPointF& vertex : m_vertices) {
        polygon << vertex;
    }
    painter->drawPolygon(polygon);
}

QString Polygon::getName() const
{
    return "Многоугольник";
}

void Polygon::setVertex(int index, const QPointF& point)
{
    if (index >= 0 && index < m_vertices.size()) {
        m_vertices[index] = point;
    }
}

void Polygon::addVertex(const QPointF& point)
{
    m_vertices.append(point);
}

int Polygon::vertexCount() const
{
    return m_vertices.size();
}

QPointF Polygon::getVertex(int index) const
{
    if (index >= 0 && index < m_vertices.size()) {
        return m_vertices[index];
    }
    return QPointF(0, 0);
}
