#include "shapegraphicsitem.h"
#include <QStyleOptionGraphicsItem>
#include "shape.h"

shapegraphicsitem::shapegraphicsitem(class shape* shapeItem, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_shape(shapeItem)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF shapegraphicsitem::boundingRect() const
{
    if (!m_shape) return QRectF(0, 0, 0, 0);
    QPointF center = m_shape->center();
    return QRectF(center.x() - 100, center.y() - 100, 200, 200);
}

void shapegraphicsitem::paint(QPainter* painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget)
{
    Q_UNUSED(widget);

    if (!m_shape) return;

    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
    } else {
        painter->setPen(QPen(Qt::black, 1));
    }

    m_shape->paint(painter);
}
