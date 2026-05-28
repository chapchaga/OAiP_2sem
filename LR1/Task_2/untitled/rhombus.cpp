#include "rhombus.h"

rhombus::rhombus(const QPointF& center, double diagonal1, double diagonal2)
    : Polygon(), m_center(center), m_d1(diagonal1), m_d2(diagonal2)
{
    updateVertices();
}

void rhombus::updateVertices()
{
    m_vertices.clear();
    m_vertices.append(QPointF(m_center.x(), m_center.y() - m_d1/2));
    m_vertices.append(QPointF(m_center.x() + m_d2/2, m_center.y()));
    m_vertices.append(QPointF(m_center.x(), m_center.y() + m_d1/2));
    m_vertices.append(QPointF(m_center.x() - m_d2/2, m_center.y()));
}

void rhombus::setDiagonals(double d1, double d2) { m_d1 = d1; m_d2 = d2; updateVertices(); }
double rhombus::diagonal1() const { return m_d1; }
double rhombus::diagonal2() const { return m_d2; }
QString rhombus::getName() const { return "Ромб"; }
