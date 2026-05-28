#include "CanvasWidget.h"

#include <QPainter>
#include <QPaintEvent>

#include "Exceptions.h"

CanvasWidget::CanvasWidget(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(preferredSize_);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CanvasWidget::setFigure(MovingRectangle* figure)
{
    figure_ = figure;
}

QSize CanvasWidget::drawAreaSize() const noexcept
{
    return preferredSize_;
}

void CanvasWidget::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(rect(), Qt::white);

    // Рамка холста
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(rect().adjusted(1, 1, -2, -2));

    // Тонкая разметка
    painter.setPen(QPen(QColor(0, 0, 0, 30), 1));
    const int step = 50;
    for (int x = 0; x < width(); x += step)
        painter.drawLine(x, 0, x, height());
    for (int y = 0; y < height(); y += step)
        painter.drawLine(0, y, width(), y);

    if (!figure_)
        return;

    try
    {
        figure_->draw(painter);
    }
    catch (const std::exception& e)
    {
        painter.setPen(Qt::red);
        painter.drawText(QPoint(12, 28), QStringLiteral("Ошибка: ") + e.what());
    }
}

