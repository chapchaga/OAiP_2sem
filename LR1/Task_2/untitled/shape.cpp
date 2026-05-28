#include "shape.h"
#include <QTimer>
#include <cmath>

shape::shape(QObject* parent) : QObject(parent)
{
    m_animTimer = new QTimer(this);
    m_animTimer->setInterval(50);
    connect(m_animTimer, &QTimer::timeout, this, &shape::onAnimationTick);
}

void shape::animateMove(const QPointF& delta, int durationMs)
{
    m_anim.isActive = true;
    m_anim.step = 0;
    m_anim.totalSteps = durationMs / 50;
    m_anim.moveDelta = delta;
    m_anim.rotateAngle = 0;
    m_anim.scaleFactor = 1;
    m_animTimer->start();
}

void shape::animateRotate(double angle, int durationMs)
{
    m_anim.isActive = true;
    m_anim.step = 0;
    m_anim.totalSteps = durationMs / 50;
    m_anim.rotateAngle = angle;
    m_anim.centerPoint = center();
    m_anim.moveDelta = QPointF(0, 0);
    m_anim.scaleFactor = 1;
    m_animTimer->start();
}

void shape::animateScale(double factor, int durationMs)
{
    m_anim.isActive = true;
    m_anim.step = 0;
    m_anim.totalSteps = durationMs / 50;
    m_anim.scaleFactor = factor;
    m_anim.centerPoint = center();
    m_anim.moveDelta = QPointF(0, 0);
    m_anim.rotateAngle = 0;
    m_animTimer->start();
}

void shape::onAnimationTick()
{
    if (!m_anim.isActive) return;

    m_anim.step++;
    double progress = static_cast<double>(m_anim.step) / m_anim.totalSteps;

    if (m_anim.moveDelta != QPointF(0, 0)) {
        QPointF stepDelta = m_anim.moveDelta * (1.0 / m_anim.totalSteps);
        moveCenter(center() + stepDelta);
    }
    if (m_anim.rotateAngle != 0) {
        double stepAngle = m_anim.rotateAngle / m_anim.totalSteps;
        rotate(stepAngle, m_anim.centerPoint);
    }
    if (m_anim.scaleFactor != 1 && m_anim.moveDelta == QPointF(0,0) && m_anim.rotateAngle == 0) {
        double stepFactor = 1 + (m_anim.scaleFactor - 1) / m_anim.totalSteps;
        scale(stepFactor, m_anim.centerPoint);
    }

    emit transformStep();

    if (m_anim.step >= m_anim.totalSteps) {
        if (m_anim.moveDelta != QPointF(0, 0)) {
            moveCenter(center() + m_anim.moveDelta * (1 - progress));
        }
        if (m_anim.rotateAngle != 0) {
            rotate(m_anim.rotateAngle * (1 - progress), m_anim.centerPoint);
        }
        if (m_anim.scaleFactor != 1) {
            double remainingFactor = m_anim.scaleFactor / (1 + (m_anim.scaleFactor - 1) * progress);
            scale(remainingFactor, m_anim.centerPoint);
        }
        m_anim.isActive = false;
        m_animTimer->stop();
        emit transformFinished();
    }
}
