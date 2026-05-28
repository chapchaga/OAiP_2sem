#pragma once
#include <QString>
#include <QPointF>
#include <QJsonObject>

struct AnimationStep {
    enum Type { Move, Rotate, Scale, Group, Ungroup };
    Type type;
    QPointF delta;       // for Move
    double angle = 0;    // for Rotate
    double factor = 1.0; // for Scale
    int durationMs = 600;
    int shapeIndex = -1; // -1 = all selected / group

    QString describe() const;
    QJsonObject toJson() const;
    static AnimationStep fromJson(const QJsonObject& obj);
};
