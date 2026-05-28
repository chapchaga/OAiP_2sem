#include "triangle.h"
#include <QPainter>
#include <QJsonObject>
#include <cmath>

Triangle::Triangle(const QPointF& a, const QPointF& b, const QPointF& c, QObject* parent)
    : Shape(parent), m_a(a), m_b(b), m_c(c) {}

double Triangle::area() const {
    return std::abs((m_b.x()-m_a.x())*(m_c.y()-m_a.y())
                  -(m_c.x()-m_a.x())*(m_b.y()-m_a.y())) / 2.0;
}

double Triangle::perimeter() const {
    return QLineF(m_a,m_b).length() + QLineF(m_b,m_c).length() + QLineF(m_c,m_a).length();
}

QPointF Triangle::centroid() const {
    return { (m_a.x()+m_b.x()+m_c.x())/3, (m_a.y()+m_b.y()+m_c.y())/3 };
}

void Triangle::setVertices(const QPointF& a, const QPointF& b, const QPointF& c) {
    m_a=a; m_b=b; m_c=c; emit changed();
}

void Triangle::move(const QPointF& delta) {
    m_a+=delta; m_b+=delta; m_c+=delta; emit changed();
}

QPointF Triangle::rotatePoint(const QPointF& p, double rad, const QPointF& center) {
    QPointF d = p - center;
    return center + QPointF(d.x()*cos(rad)-d.y()*sin(rad), d.x()*sin(rad)+d.y()*cos(rad));
}

void Triangle::rotate(double angleDeg, const QPointF& center) {
    double rad = angleDeg * M_PI / 180.0;
    m_a = rotatePoint(m_a, rad, center);
    m_b = rotatePoint(m_b, rad, center);
    m_c = rotatePoint(m_c, rad, center);
    emit changed();
}

void Triangle::scale(double factor, const QPointF& center) {
    m_a = center + (m_a - center) * factor;
    m_b = center + (m_b - center) * factor;
    m_c = center + (m_c - center) * factor;
    emit changed();
}

bool Triangle::contains(const QPointF& pt) const {
    auto sign = [](const QPointF& p1, const QPointF& p2, const QPointF& p3) {
        return (p1.x()-p3.x())*(p2.y()-p3.y()) - (p2.x()-p3.x())*(p1.y()-p3.y());
    };
    double d1 = sign(pt,m_a,m_b), d2 = sign(pt,m_b,m_c), d3 = sign(pt,m_c,m_a);
    bool hasNeg = (d1<0)||(d2<0)||(d3<0);
    bool hasPos = (d1>0)||(d2>0)||(d3>0);
    return !(hasNeg && hasPos);
}

void Triangle::draw(QPainter& painter) const {
    QPolygonF poly; poly << m_a << m_b << m_c;
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected ? 2.5 : 1.5);
    if (m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawPolygon(poly);
    if (m_selected) {
        painter.setPen(QPen(Qt::blue,1)); painter.setBrush(Qt::white);
        double s=6;
        for (auto& p : {m_a,m_b,m_c})
            painter.drawRect(QRectF(p.x()-s/2,p.y()-s/2,s,s));
    }
    painter.restore();
}

QRectF Triangle::boundingRect() const {
    double minX = std::min({m_a.x(),m_b.x(),m_c.x()});
    double minY = std::min({m_a.y(),m_b.y(),m_c.y()});
    double maxX = std::max({m_a.x(),m_b.x(),m_c.x()});
    double maxY = std::max({m_a.y(),m_b.y(),m_c.y()});
    return {minX, minY, maxX-minX, maxY-minY};
}

QJsonObject Triangle::toJson() const {
    QJsonObject obj = Shape::toJson();
    obj["type"]="Triangle";
    obj["ax"]=m_a.x(); obj["ay"]=m_a.y();
    obj["bx"]=m_b.x(); obj["by"]=m_b.y();
    obj["cx"]=m_c.x(); obj["cy"]=m_c.y();
    return obj;
}

void Triangle::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_a={obj["ax"].toDouble(),obj["ay"].toDouble()};
    m_b={obj["bx"].toDouble(),obj["by"].toDouble()};
    m_c={obj["cx"].toDouble(),obj["cy"].toDouble()};
}
