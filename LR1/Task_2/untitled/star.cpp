#include "star.h"
#include <cmath>

star::star(const QPointF& center, double outerRadius, double innerRadius, int points)
    : Polygon(), m_center(center), m_outerRadius(outerRadius), m_innerRadius(innerRadius), m_points(points)
{
    updateVertices();
}

void star::updateVertices()
{
    m_vertices.clear();

    for (int i = 0; i < m_points * 2; i++) {
        double radius = (i % 2 == 0) ? m_outerRadius : m_innerRadius;
        double angle = 2 * M_PI * i / (m_points * 2);
        double px = m_center.x() + radius * cos(angle);
        double py = m_center.y() + radius * sin(angle);
        m_vertices.append(QPointF(px, py));
    }
}

void star::setOuterRadius(double r) { m_outerRadius = r; updateVertices(); }
void star::setInnerRadius(double r) { m_innerRadius = r; updateVertices(); }
void star::setPoints(int p) { m_points = p; updateVertices(); }
double star::outerRadius() const { return m_outerRadius; }
double star::innerRadius() const { return m_innerRadius; }
int star::points() const { return m_points; }
QString star::getName() const { return QString("%1-конечная звезда").arg(m_points); }
