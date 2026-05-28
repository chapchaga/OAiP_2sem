#include "hexagon.h"
#include <QPainter>
#include <QJsonObject>
#include <cmath>

Hexagon::Hexagon(const QPointF& center, double radius, double angleDeg, QObject* parent)
    : Shape(parent), m_center(center), m_radius(radius), m_angle(angleDeg) { buildPoly(); }

QPointF Hexagon::rotPt(const QPointF& p, double rad, const QPointF& c) {
    QPointF d=p-c;
    return c+QPointF(d.x()*cos(rad)-d.y()*sin(rad), d.x()*sin(rad)+d.y()*cos(rad));
}

void Hexagon::buildPoly() {
    m_poly.clear();
    double baseRad=m_angle*M_PI/180.0;
    for(int i=0;i<6;i++){
        double a=baseRad+i*M_PI/3;
        m_poly<<m_center+QPointF(m_radius*cos(a),m_radius*sin(a));
    }
}

double Hexagon::area() const { return 3*std::sqrt(3.0)/2*m_radius*m_radius; }
double Hexagon::perimeter() const { return 6*m_radius; }
QPointF Hexagon::centroid() const { return m_center; }

void Hexagon::move(const QPointF& delta) {
    m_center+=delta; for(auto& p:m_poly) p+=delta; emit changed();
}

void Hexagon::rotate(double angleDeg, const QPointF& center) {
    double rad=angleDeg*M_PI/180.0;
    m_center=rotPt(m_center,rad,center);
    m_angle+=angleDeg; buildPoly(); emit changed();
}

void Hexagon::scale(double factor, const QPointF& center) {
    m_center=center+(m_center-center)*factor;
    m_radius*=factor; buildPoly(); emit changed();
}

bool Hexagon::contains(const QPointF& pt) const {
    return m_poly.containsPoint(pt, Qt::OddEvenFill);
}

void Hexagon::draw(QPainter& painter) const {
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected?2.5:1.5);
    if(m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawPolygon(m_poly);
    if(m_selected){
        painter.setPen(QPen(Qt::blue,1)); painter.setBrush(Qt::white);
        double s=6;
        for(auto& v:m_poly) painter.drawRect(QRectF(v.x()-s/2,v.y()-s/2,s,s));
    }
    painter.restore();
}

QRectF Hexagon::boundingRect() const {
    return QRectF(m_center.x()-m_radius, m_center.y()-m_radius, 2*m_radius, 2*m_radius);
}

QJsonObject Hexagon::toJson() const {
    QJsonObject obj=Shape::toJson();
    obj["type"]="Hexagon";
    obj["cx"]=m_center.x(); obj["cy"]=m_center.y();
    obj["radius"]=m_radius; obj["angle"]=m_angle;
    return obj;
}

void Hexagon::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_center={obj["cx"].toDouble(),obj["cy"].toDouble()};
    m_radius=obj["radius"].toDouble(); m_angle=obj["angle"].toDouble();
    buildPoly();
}
