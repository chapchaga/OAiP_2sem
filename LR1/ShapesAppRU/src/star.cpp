#include "star.h"
#include <QPainter>
#include <QJsonObject>
#include <cmath>

Star::Star(StarType type, const QPointF& center, double outerR, double innerR,
           double angleDeg, QObject* parent)
    : Shape(parent), m_type(type), m_center(center),
      m_outerR(outerR), m_innerR(innerR), m_angle(angleDeg)
{ buildPoly(); }

QPointF Star::rotPt(const QPointF& p, double rad, const QPointF& c) {
    QPointF d=p-c;
    return c+QPointF(d.x()*cos(rad)-d.y()*sin(rad), d.x()*sin(rad)+d.y()*cos(rad));
}

void Star::buildPoly() {
    m_poly.clear();
    int n = (int)m_type;
    double baseRad = m_angle*M_PI/180.0 - M_PI/2;
    double step = M_PI/n;
    for(int i=0; i<2*n; i++){
        double r = (i%2==0) ? m_outerR : m_innerR;
        double a = baseRad + i*step;
        m_poly << m_center + QPointF(r*cos(a), r*sin(a));
    }
}

double Star::area() const {
    double a=0;
    int n=m_poly.size();
    for(int i=0;i<n;i++){
        const QPointF& p1=m_poly[i], &p2=m_poly[(i+1)%n];
        a+=p1.x()*p2.y()-p2.x()*p1.y();
    }
    return std::abs(a)/2.0;
}

double Star::perimeter() const {
    double p=0;
    int n=m_poly.size();
    for(int i=0;i<n;i++) p+=QLineF(m_poly[i],m_poly[(i+1)%n]).length();
    return p;
}

QPointF Star::centroid() const { return m_center; }

void Star::move(const QPointF& delta) {
    m_center+=delta;
    for(auto& p:m_poly) p+=delta;
    emit changed();
}

void Star::rotate(double angleDeg, const QPointF& center) {
    double rad=angleDeg*M_PI/180.0;
    m_center=rotPt(m_center,rad,center);
    m_angle+=angleDeg;
    buildPoly();
    emit changed();
}

void Star::scale(double factor, const QPointF& center) {
    m_center=center+(m_center-center)*factor;
    m_outerR*=factor; m_innerR*=factor;
    buildPoly();
    emit changed();
}

bool Star::contains(const QPointF& pt) const {
    return m_poly.containsPoint(pt, Qt::OddEvenFill);
}

void Star::draw(QPainter& painter) const {
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected?2.5:1.5);
    if(m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawPolygon(m_poly);
    if(m_selected){
        painter.setPen(QPen(Qt::blue,1)); painter.setBrush(Qt::white);
        double s=6;
        painter.drawRect(QRectF(m_center.x()-s/2,m_center.y()-m_outerR-s/2,s,s));
    }
    painter.restore();
}

QRectF Star::boundingRect() const {
    return QRectF(m_center.x()-m_outerR, m_center.y()-m_outerR, 2*m_outerR, 2*m_outerR);
}

QString Star::typeName() const {
    return QString("Звезда (%1-конечная)").arg((int)m_type);
}

QJsonObject Star::toJson() const {
    QJsonObject obj=Shape::toJson();
    obj["type"]="Star";
    obj["starType"]=(int)m_type;
    obj["cx"]=m_center.x(); obj["cy"]=m_center.y();
    obj["outerR"]=m_outerR; obj["innerR"]=m_innerR; obj["angle"]=m_angle;
    return obj;
}

void Star::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_type=(StarType)obj["starType"].toInt();
    m_center={obj["cx"].toDouble(),obj["cy"].toDouble()};
    m_outerR=obj["outerR"].toDouble(); m_innerR=obj["innerR"].toDouble();
    m_angle=obj["angle"].toDouble();
    buildPoly();
}
