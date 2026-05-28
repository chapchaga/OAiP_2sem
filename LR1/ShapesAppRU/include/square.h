#pragma once
#include "rectangle.h"

class Square : public Rectangle {
    Q_OBJECT
public:
    explicit Square(const QPointF& center={0,0}, double side=80,
                    double angleDeg=0, QObject* parent=nullptr);

    QString typeName() const override { return "Квадрат"; }
    double side() const { return m_w; }
    void setSide(double s) { setSize(s,s); }

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;
};
