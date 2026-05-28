#include "rhombus.h"
#include <QPainter>
#include <QJsonObject>
#include <array>
#include <cmath>

Rhombus::Rhombus(const QPointF& center, double d1, double d2, double angleDeg, QObject* parent)
    : Shape(parent), m_center(center), m_d1(d1), m_d2(d2), m_angle(angleDeg) { updateVertices(); }

QPointF Rhombus::rotPt(const QPointF& p, double rad, const QPointF& c) {
    QPointF d=p-c;
    return c+QPointF(d.x()*cos(rad)-d.y()*sin(rad), d.x()*sin(rad)+d.y()*cos(rad));
}

void Rhombus::updateVertices() {
    double rad=m_angle*M_PI/180.0;
    std::array<QPointF,4> local={QPointF{0,-m_d1/2},{m_d2/2,0},{0,m_d1/2},{-m_d2/2,0}};
    for(int i=0;i<4;i++){
        double x=local[i].x()*cos(rad)-local[i].y()*sin(rad);
        double y=local[i].x()*sin(rad)+local[i].y()*cos(rad);
        m_verts[i]=m_center+QPointF(x,y);
    }
}

double Rhombus::area() const { return m_d1*m_d2/2; }
double Rhombus::perimeter() const {
    double s=std::sqrt((m_d1/2)*(m_d1/2)+(m_d2/2)*(m_d2/2));
    return 4*s;
}
QPointF Rhombus::centroid() const { return m_center; }

void Rhombus::move(const QPointF& delta) {
    m_center+=delta;
    for(auto& v:m_verts) v+=delta;
    emit changed();
}

void Rhombus::rotate(double angleDeg, const QPointF& center) {
    double rad=angleDeg*M_PI/180.0;
    m_center=rotPt(m_center,rad,center);
    m_angle+=angleDeg;
    updateVertices();
    emit changed();
}

void Rhombus::scale(double factor, const QPointF& center) {
    m_center=center+(m_center-center)*factor;
    m_d1*=factor; m_d2*=factor;
    updateVertices();
    emit changed();
}

bool Rhombus::contains(const QPointF& pt) const {
    double rad=-m_angle*M_PI/180.0;
    QPointF d=pt-m_center;
    double lx=d.x()*cos(rad)-d.y()*sin(rad);
    double ly=d.x()*sin(rad)+d.y()*cos(rad);
    return std::abs(lx)/(m_d2/2)+std::abs(ly)/(m_d1/2)<=1.0;
}

void Rhombus::draw(QPainter& painter) const {
    QPolygonF poly; for(auto& v:m_verts) poly<<v;
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected?2.5:1.5);
    if(m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawPolygon(poly);
    if(m_selected){
        painter.setPen(QPen(Qt::blue,1)); painter.setBrush(Qt::white);
        double s=6;
        for(auto& v:m_verts) painter.drawRect(QRectF(v.x()-s/2,v.y()-s/2,s,s));
    }
    painter.restore();
}

QRectF Rhombus::boundingRect() const {
    double minX=m_verts[0].x(),minY=m_verts[0].y(),maxX=minX,maxY=minY;
    for(auto& v:m_verts){minX=std::min(minX,v.x());minY=std::min(minY,v.y());
                          maxX=std::max(maxX,v.x());maxY=std::max(maxY,v.y());}
    return {minX,minY,maxX-minX,maxY-minY};
}

QJsonObject Rhombus::toJson() const {
    QJsonObject obj=Shape::toJson();
    obj["type"]="Rhombus";
    obj["cx"]=m_center.x(); obj["cy"]=m_center.y();
    obj["d1"]=m_d1; obj["d2"]=m_d2; obj["angle"]=m_angle;
    return obj;
}

void Rhombus::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_center={obj["cx"].toDouble(),obj["cy"].toDouble()};
    m_d1=obj["d1"].toDouble(); m_d2=obj["d2"].toDouble(); m_angle=obj["angle"].toDouble();
    updateVertices();
}
