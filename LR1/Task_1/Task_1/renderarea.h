#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QTimer>
#include "car.h"

class RenderArea : public QWidget
{
    Q_OBJECT

private:
    QTimer *timer;
    Car car;

public:
    explicit RenderArea(QWidget *parent = nullptr);

    void stop();
    void toggleDoor();
    void toggleLights();
    void moveLeft();
    void moveRight();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onTick();
};

#endif
