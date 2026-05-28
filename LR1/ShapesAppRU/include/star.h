#pragma once
#include "shape.h"
#include <QPolygonF>

class Star : public Shape {
    Q_OBJECT
public:
    enum StarType { Five=5, Six=6, Eight=8 };

    explicit Star(StarType type=Five, const QPointF& center={0,0},
                  double outerR=60, double innerR=25,
                  double angleDeg=0, QObject* parent=nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override;
    QRectF boundingRect() const override;

    StarType starType() const { return m_type; }
    void setStarType(StarType t) { m_type=t; buildPoly(); emit changed(); }
    double outerR() const { return m_outerR; }
    double innerR() const { return m_innerR; }
    void setRadii(double outer, double inner) { m_outerR=outer; m_innerR=inner; buildPoly(); emit changed(); }

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    StarType m_type;
    QPointF m_center;
    double m_outerR, m_innerR, m_angle;
    QPolygonF m_poly;
    void buildPoly();
    static QPointF rotPt(const QPointF& p, double rad, const QPointF& c);
};
