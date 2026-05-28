#pragma once
#include "shape.h"

class Rhombus : public Shape {
    Q_OBJECT
public:
    explicit Rhombus(const QPointF& center={0,0}, double d1=100, double d2=60,
                     double angleDeg=0, QObject* parent=nullptr);

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Ромб"; }
    QRectF boundingRect() const override;

    double diag1() const { return m_d1; }
    double diag2() const { return m_d2; }
    void setDiagonals(double d1, double d2) { m_d1=d1; m_d2=d2; updateVertices(); emit changed(); }

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    QPointF m_center;
    double m_d1, m_d2, m_angle;
    std::array<QPointF,4> m_verts;
    void updateVertices();
    static QPointF rotPt(const QPointF& p, double rad, const QPointF& c);
};
