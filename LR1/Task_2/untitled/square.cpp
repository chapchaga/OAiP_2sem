#include "square.h"

square::square(const QPointF& center, double side)
    : Polygon(), m_center(center), m_side(side)
{
    updateVertices();
}

void square::updateVertices()
{
    m_vertices.clear();
    m_vertices.append(QPointF(m_center.x() - m_side/2, m_center.y() - m_side/2));
    m_vertices.append(QPointF(m_center.x() + m_side/2, m_center.y() - m_side/2));
    m_vertices.append(QPointF(m_center.x() + m_side/2, m_center.y() + m_side/2));
    m_vertices.append(QPointF(m_center.x() - m_side/2, m_center.y() + m_side/2));
}

void square::setSide(double side) { m_side = side; updateVertices(); }
double square::side() const { return m_side; }
QString square::getName() const { return "Квадрат"; }
