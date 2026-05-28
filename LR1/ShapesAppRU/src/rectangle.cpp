#include "rectangle.h"
#include <QPainter>
#include <QJsonObject>
#include <cmath>

Rectangle::Rectangle(const QPointF& center, double w, double h, double angleDeg, QObject* parent)
    : Shape(parent), m_center(center), m_w(w), m_h(h), m_angle(angleDeg) { updateCorners(); }

void Rectangle::updateCorners() {
    double rad = m_angle * M_PI / 180.0;
    double hw=m_w/2, hh=m_h/2;
    std::array<QPointF,4> local = {QPointF{-hw,-hh},{hw,-hh},{hw,hh},{-hw,hh}};
    for (int i=0;i<4;i++) {
        double x=local[i].x()*cos(rad)-local[i].y()*sin(rad);
        double y=local[i].x()*sin(rad)+local[i].y()*cos(rad);
        m_corners[i]=m_center+QPointF(x,y);
    }
}

QPointF Rectangle::rotPt(const QPointF& p, double rad, const QPointF& c) {
    QPointF d=p-c;
    return c+QPointF(d.x()*cos(rad)-d.y()*sin(rad), d.x()*sin(rad)+d.y()*cos(rad));
}

double Rectangle::area() const { return m_w*m_h; }
double Rectangle::perimeter() const { return 2*(m_w+m_h); }
QPointF Rectangle::centroid() const { return m_center; }

void Rectangle::move(const QPointF& delta) {
    m_center+=delta;
    for (auto& c:m_corners) c+=delta;
    emit changed();
}

void Rectangle::rotate(double angleDeg, const QPointF& center) {
    double rad=angleDeg*M_PI/180.0;
    m_center=rotPt(m_center,rad,center);
    m_angle+=angleDeg;
    updateCorners();
    emit changed();
}

void Rectangle::scale(double factor, const QPointF& center) {
    m_center=center+(m_center-center)*factor;
    m_w*=factor; m_h*=factor;
    updateCorners();
    emit changed();
}

bool Rectangle::contains(const QPointF& pt) const {
    // Transform point to local space
    double rad=-m_angle*M_PI/180.0;
    QPointF d=pt-m_center;
    double lx=d.x()*cos(rad)-d.y()*sin(rad);
    double ly=d.x()*sin(rad)+d.y()*cos(rad);
    return std::abs(lx)<=m_w/2 && std::abs(ly)<=m_h/2;
}

void Rectangle::draw(QPainter& painter) const {
    QPolygonF poly;
    for (auto& c:m_corners) poly<<c;
    painter.save();
    painter.setBrush(m_fillColor);
    QPen pen(m_strokeColor, m_selected?2.5:1.5);
    if (m_selected) pen.setStyle(Qt::DashLine);
    painter.setPen(pen);
    painter.drawPolygon(poly);
    if (m_selected) {
        painter.setPen(QPen(Qt::blue,1)); painter.setBrush(Qt::white);
        double s=6;
        for (auto& c:m_corners)
            painter.drawRect(QRectF(c.x()-s/2,c.y()-s/2,s,s));
    }
    painter.restore();
}

QRectF Rectangle::boundingRect() const {
    double minX=m_corners[0].x(),minY=m_corners[0].y(),maxX=minX,maxY=minY;
    for (auto& c:m_corners){minX=std::min(minX,c.x());minY=std::min(minY,c.y());
                              maxX=std::max(maxX,c.x());maxY=std::max(maxY,c.y());}
    return {minX,minY,maxX-minX,maxY-minY};
}

QJsonObject Rectangle::toJson() const {
    QJsonObject obj=Shape::toJson();
    obj["type"]="Rectangle";
    obj["cx"]=m_center.x(); obj["cy"]=m_center.y();
    obj["w"]=m_w; obj["h"]=m_h; obj["angle"]=m_angle;
    return obj;
}

void Rectangle::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_center={obj["cx"].toDouble(),obj["cy"].toDouble()};
    m_w=obj["w"].toDouble(); m_h=obj["h"].toDouble(); m_angle=obj["angle"].toDouble();
    updateCorners();
}
