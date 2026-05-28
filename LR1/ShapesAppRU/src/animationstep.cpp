#include "animationstep.h"
#include <QJsonObject>

QString AnimationStep::describe() const {
    switch(type){
    case Move:    return QString("Перемещение (Δx=%1, Δy=%2, %3мс)").arg(delta.x()).arg(delta.y()).arg(durationMs);
    case Rotate:  return QString("Поворот %1° (%2мс)").arg(angle).arg(durationMs);
    case Scale:   return QString("Масштаб ×%1 (%2мс)").arg(factor).arg(durationMs);
    case Group:   return "Сгруппировать выделенное";
    case Ungroup: return "Разгруппировать";
    }
    return "";
}

QJsonObject AnimationStep::toJson() const {
    QJsonObject o;
    o["type"]=(int)type;
    o["dx"]=delta.x(); o["dy"]=delta.y();
    o["angle"]=angle; o["factor"]=factor;
    o["duration"]=durationMs; o["shapeIndex"]=shapeIndex;
    return o;
}

AnimationStep AnimationStep::fromJson(const QJsonObject& o) {
    AnimationStep s;
    s.type=(Type)o["type"].toInt();
    s.delta={o["dx"].toDouble(),o["dy"].toDouble()};
    s.angle=o["angle"].toDouble(); s.factor=o["factor"].toDouble();
    s.durationMs=o["duration"].toInt(); s.shapeIndex=o["shapeIndex"].toInt();
    return s;
}
