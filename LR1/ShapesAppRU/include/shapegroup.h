#pragma once
#include "shape.h"
#include <QVector>
#include <memory>

class ShapeGroup : public Shape {
    Q_OBJECT
public:
    explicit ShapeGroup(QObject* parent = nullptr);

    void addShape(std::shared_ptr<Shape> s);
    void removeShape(std::shared_ptr<Shape> s);
    QVector<std::shared_ptr<Shape>> shapes() const { return m_shapes; }
    void clear() { m_shapes.clear(); emit changed(); }
    int count() const { return m_shapes.size(); }

    double area() const override;
    double perimeter() const override;
    QPointF centroid() const override;
    void move(const QPointF& delta) override;
    void rotate(double angleDeg, const QPointF& center) override;
    void scale(double factor, const QPointF& center) override;
    bool contains(const QPointF& pt) const override;
    void draw(QPainter& painter) const override;
    QString typeName() const override { return "Группа"; }
    QRectF boundingRect() const override;

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject& obj) override;

private:
    QVector<std::shared_ptr<Shape>> m_shapes;
};
