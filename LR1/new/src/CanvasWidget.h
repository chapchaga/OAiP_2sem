#pragma once

#include <QWidget>

#include "MovingRectangle.h"

class CanvasWidget : public QWidget
{
public:
    explicit CanvasWidget(QWidget* parent = nullptr);
    ~CanvasWidget() override = default;

    void setFigure(MovingRectangle* figure);
    QSize drawAreaSize() const noexcept;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    MovingRectangle* figure_ = nullptr; // не владеем объектом
    QSize preferredSize_ { 800, 600 };
};

