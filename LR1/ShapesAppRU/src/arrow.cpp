#include "arrow.h"
#include <QPainter>
#include <QJsonObject>
#include <cmath>

Arrow::Arrow(const QPointF& center, double length, double width,
             double headRatio, double angleDeg, QObject* parent)
    : Shape(parent), m_center(center), m_length(length), m_width(width),
      m_headRatio(headRatio), m_angle(angleDeg) { buildPoly(); }

QPointF Arrow::rotPt(const QPointF& p, double rad, const QPointF& c) {
    QPointF d=p-c;
    return c+QPointF(d.x()*cos(rad)-d.y()*sin(rad), d.x()*sin(rad)+d.y()*cos(rad));
}

void Arrow::buildPoly() {
    // Arrow pointing right, centered at origin
    double L=m_length, W=m_width, H=m_headRatio*L;
    double shaft=W*0.45;
    QPolygonF local;
    local << QPointF{-L/2, -shaft}  // bottom-left of shaft
          << QPointF{L/2-H, -shaft} // bottom of shaft before head
          << QPointF{L/2-H, -W/2}   // outer bottom of head
          << QPointF{L/2,   0}       // tip
          << QPointF{L/2-H,  W/2}   // outer top of head
          << QPointF{L/2-H,  shaft} // top of shaft
          << QPointF{-L/2,   shaft};
    double rad=m_angle*M_PI/180.0;
    m_poly.clear();
    for(auto& p:local){
        double rx=p.x()*cos(rad)-p.y()*sin(rad);
        double ry=p.x()*sin(rad)+p.y()*cos(rad);
        m_poly<<m_center+QPointF(rx,ry);
    }
}

double Arrow::area() const {
    double a=0; int n=m_poly.size();
    for(int i=0;i<n;i++){
        const QPointF& p1=m_poly[i],&p2=m_poly[(i+1)%n];
        a+=p1.x()*p2.y()-p2.x()*p1.y();
    }
    return std::abs(a)/2.0;
}

double Arrow::perimeter() const {
    double p=0; int n=m_poly.size();
    for(int i=0;i<n;i++) p+=QLineF(m_poly[i],m_poly[(i+1)%n]).length();
    return p;
}

QPointF Arrow::centroid() const { return m_center; }

void Arrow::move(const QPointF& delta) {
    m_center+=delta; for(auto& p:m_poly) p+=delta; emit changed();
}

void Arrow::rotate(double angleDeg, const QPointF& center) {
    double rad=angleDeg*M_PI/180.0;
    m_center=rotPt(m_center,rad,center);
    m_angle+=angleDeg; buildPoly(); emit changed();
}

void Arrow::scale(double factor, const QPointF& center) {
    m_center=center+(m_center-center)*factor;
    m_length*=factor; m_width*=factor; buildPoly(); emit changed();
}

bool Arrow::contains(const QPointF& pt) const {
    return m_poly.containsPoint(pt, Qt::OddEvenFill);
}

void Arrow::draw(QPainter& painter) const {
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected?2.5:1.5);
    if(m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawPolygon(m_poly);
    painter.restore();
}

QRectF Arrow::boundingRect() const {
    double minX=m_poly[0].x(),minY=m_poly[0].y(),maxX=minX,maxY=minY;
    for(auto& p:m_poly){minX=std::min(minX,p.x());minY=std::min(minY,p.y());
                         maxX=std::max(maxX,p.x());maxY=std::max(maxY,p.y());}
    return {minX,minY,maxX-minX,maxY-minY};
}

QJsonObject Arrow::toJson() const {
    QJsonObject obj=Shape::toJson();
    obj["type"]="Arrow";
    obj["cx"]=m_center.x(); obj["cy"]=m_center.y();
    obj["length"]=m_length; obj["width"]=m_width;
    obj["headRatio"]=m_headRatio; obj["angle"]=m_angle;
    return obj;
}

void Arrow::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_center={obj["cx"].toDouble(),obj["cy"].toDouble()};
    m_length=obj["length"].toDouble(); m_width=obj["width"].toDouble();
    m_headRatio=obj["headRatio"].toDouble(); m_angle=obj["angle"].toDouble();
    buildPoly();
}
