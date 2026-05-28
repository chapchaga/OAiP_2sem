#include "shapegroup.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "star.h"
#include "hexagon.h"
#include "arrow.h"
#include <QPainter>
#include <QJsonObject>
#include <QJsonArray>
#include <numeric>

ShapeGroup::ShapeGroup(QObject* parent) : Shape(parent) {}

void ShapeGroup::addShape(std::shared_ptr<Shape> s) {
    m_shapes.push_back(s);
    connect(s.get(), &Shape::changed, this, &Shape::changed);
    emit changed();
}

void ShapeGroup::removeShape(std::shared_ptr<Shape> s) {
    m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), s), m_shapes.end());
    emit changed();
}

double ShapeGroup::area() const {
    double a=0; for(auto& s:m_shapes) a+=s->area(); return a;
}

double ShapeGroup::perimeter() const {
    double p=0; for(auto& s:m_shapes) p+=s->perimeter(); return p;
}

QPointF ShapeGroup::centroid() const {
    if(m_shapes.isEmpty()) return {0,0};
    double totalA=0; QPointF weighted{0,0};
    for(auto& s:m_shapes){
        double a=s->area(); totalA+=a; weighted+=a*s->centroid();
    }
    return totalA>0 ? weighted/totalA : weighted/m_shapes.size();
}

void ShapeGroup::move(const QPointF& delta) {
    for(auto& s:m_shapes) s->move(delta); emit changed();
}

void ShapeGroup::rotate(double angleDeg, const QPointF& center) {
    for(auto& s:m_shapes) s->rotate(angleDeg, center); emit changed();
}

void ShapeGroup::scale(double factor, const QPointF& center) {
    for(auto& s:m_shapes) s->scale(factor, center); emit changed();
}

bool ShapeGroup::contains(const QPointF& pt) const {
    for(auto& s:m_shapes) if(s->contains(pt)) return true;
    return false;
}

void ShapeGroup::draw(QPainter& painter) const {
    for(auto& s:m_shapes) s->draw(painter);
    if(m_selected){
        auto br=boundingRect().adjusted(-4,-4,4,4);
        painter.save();
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(Qt::blue, 1.5, Qt::DashLine));
        painter.drawRect(br);
        painter.restore();
    }
}

QRectF ShapeGroup::boundingRect() const {
    if(m_shapes.isEmpty()) return {};
    QRectF r=m_shapes[0]->boundingRect();
    for(auto& s:m_shapes) r=r.united(s->boundingRect());
    return r;
}

static std::shared_ptr<Shape> shapeFromJson(const QJsonObject& obj) {
    QString t=obj["type"].toString();
    std::shared_ptr<Shape> s;
    if(t=="Circle")    { auto c=std::make_shared<Circle>(); c->fromJson(obj); s=c; }
    else if(t=="Triangle")   { auto c=std::make_shared<Triangle>(); c->fromJson(obj); s=c; }
    else if(t=="Square")     { auto c=std::make_shared<Square>(); c->fromJson(obj); s=c; }
    else if(t=="Rectangle")  { auto c=std::make_shared<Rectangle>(); c->fromJson(obj); s=c; }
    else if(t=="Rhombus")    { auto c=std::make_shared<Rhombus>(); c->fromJson(obj); s=c; }
    else if(t=="Star")       { auto c=std::make_shared<Star>(); c->fromJson(obj); s=c; }
    else if(t=="Hexagon")    { auto c=std::make_shared<Hexagon>(); c->fromJson(obj); s=c; }
    else if(t=="Arrow")      { auto c=std::make_shared<Arrow>(); c->fromJson(obj); s=c; }
    else if(t=="Group")      { auto c=std::make_shared<ShapeGroup>(); c->fromJson(obj); s=c; }
    return s;
}

QJsonObject ShapeGroup::toJson() const {
    QJsonObject obj=Shape::toJson();
    obj["type"]="Group";
    QJsonArray arr;
    for(auto& s:m_shapes) arr.append(s->toJson());
    obj["shapes"]=arr;
    return obj;
}

void ShapeGroup::fromJson(const QJsonObject& obj) {
    Shape::fromJson(obj);
    m_shapes.clear();
    for(auto v:obj["shapes"].toArray()){
        auto s=shapeFromJson(v.toObject());
        if(s) addShape(s);
    }
}
