#pragma once
#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QString>
#include <QJsonObject>

class Shape : public QObject {
    Q_OBJECT
public:
    explicit Shape(QObject* parent = nullptr);
    virtual ~Shape() = default;

    // Core operations
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QPointF centroid() const = 0;
    virtual void setCentroid(const QPointF& pt);

    // Drawing
    virtual void draw(QPainter& painter) const = 0;

    // Transforms
    virtual void move(const QPointF& delta);
    virtual void rotate(double angleDeg, const QPointF& center);
    virtual void scale(double factor, const QPointF& center);

    // Animated transforms
    void animateMove(const QPointF& delta, int durationMs, int steps = 60);
    void animateRotate(double angleDeg, const QPointF& center, int durationMs, int steps = 60);
    void animateScale(double factor, const QPointF& center, int durationMs, int steps = 60);

    // Selection
    virtual bool contains(const QPointF& pt) const = 0;

    // Name
    virtual QString typeName() const = 0;

    // Colors
    QColor fillColor() const { return m_fillColor; }
    QColor strokeColor() const { return m_strokeColor; }
    void setFillColor(const QColor& c) { m_fillColor = c; emit changed(); }
    void setStrokeColor(const QColor& c) { m_strokeColor = c; emit changed(); }

    bool isSelected() const { return m_selected; }
    void setSelected(bool s) { m_selected = s; emit changed(); }

    // Serialization
    virtual QJsonObject toJson() const;
    virtual void fromJson(const QJsonObject& obj);

    // Returns bounding rect for selection handles
    virtual QRectF boundingRect() const = 0;

signals:
    void changed();
    void animationStep();

protected:
    QColor m_fillColor { QColor(100, 149, 237) };
    QColor m_strokeColor { Qt::black };
    bool m_selected { false };
};
