#ifndef SHAPE_H
#define SHAPE_H
#include <QPointF>
#include <QPainter>
#include <QString>
#include <QObject>
#include <QTimer>

class shape : public QObject
{
    Q_OBJECT
public:
    explicit shape(QObject* parent = nullptr);
    virtual ~shape() {};

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual QPointF center() const = 0;
    virtual void moveCenter(const QPointF& newCenter) = 0;
    virtual void scale(double factor, const QPointF& centerPoint) = 0;
    virtual void rotate(double angle, const QPointF& centerPoint) = 0;
    virtual void paint(QPainter* painter) const = 0;
    virtual QString getName() const = 0;

    // Методы для анимации
    void animateMove(const QPointF& delta, int durationMs);
    void animateRotate(double angle, int durationMs);
    void animateScale(double factor, int durationMs);

    // Геттеры для анимации
    bool isAnimating() const { return m_anim.isActive; }
    void stopAnimation() {
        m_anim.isActive = false;
        if (m_animTimer) m_animTimer->stop();
    }
    int getAnimationProgress() const {
        if (m_anim.totalSteps == 0) return 0;
        return (m_anim.step * 100) / m_anim.totalSteps;
    }

signals:
    void transformStep();
    void transformFinished();

protected slots:
    virtual void onAnimationTick();

protected:
    struct AnimationData {
        bool isActive = false;
        int step = 0;
        int totalSteps = 0;
        QPointF moveDelta;
        double rotateAngle = 0;
        double scaleFactor = 1;
        QPointF centerPoint;
        QPointF originalCenter;
        double originalScale = 1;
    };

    AnimationData m_anim;
    QTimer* m_animTimer;
};

#endif
