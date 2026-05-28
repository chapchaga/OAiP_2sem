#pragma once
#include <QWidget>

class StatsWidget : public QWidget {
    Q_OBJECT
public:
    explicit StatsWidget(QWidget* parent = nullptr);
    void setWPM(double wpm);
    void setAccuracy(double accuracy);
    void setElapsed(int seconds);
    void setProgress(double progress);

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;

private:
    double m_wpm = 0;
    double m_accuracy = 100.0;
    int m_elapsed = 0;
    double m_progress = 0;

    void drawStatBox(QPainter& p, const QRect& rect, const QString& label,
                     const QString& value, const QColor& accent);
    void drawProgressBar(QPainter& p, const QRect& rect);
};
