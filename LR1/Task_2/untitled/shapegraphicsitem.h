#ifndef SHAPEGRAPHICSITEM_H
#define SHAPEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>

class shape;

class shapegraphicsitem : public QGraphicsItem
{
public:
    shapegraphicsitem(class shape* shapeItem, QGraphicsItem* parent = nullptr);
    ~shapegraphicsitem() {}

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    class shape* getShape() const { return m_shape; }

private:
    class shape* m_shape;
};

#endif
