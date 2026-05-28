#include "rectangle.h"

rectangle::rectangle(const QPointF& center, double width, double height)
    : Polygon(), m_center(center), m_width(width), m_height(height)
{
    updateVertices();
}

void rectangle::updateVertices()
{
    m_vertices.clear();
    m_vertices.append(QPointF(m_center.x() - m_width/2, m_center.y() - m_height/2));
    m_vertices.append(QPointF(m_center.x() + m_width/2, m_center.y() - m_height/2));
    m_vertices.append(QPointF(m_center.x() + m_width/2, m_center.y() + m_height/2));
    m_vertices.append(QPointF(m_center.x() - m_width/2, m_center.y() + m_height/2));
}

void rectangle::setWidth(double width) { m_width = width; updateVertices(); }
void rectangle::setHeight(double height) { m_height = height; updateVertices(); }
double rectangle::width() const { return m_width; }
double rectangle::height() const { return m_height; }
QString rectangle::getName() const { return "Прямоугольник"; }
