#include "statswidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>

StatsWidget::StatsWidget(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(100);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void StatsWidget::setWPM(double wpm) {
    m_wpm = wpm;
    update();
}

void StatsWidget::setAccuracy(double accuracy) {
    m_accuracy = accuracy;
    update();
}

void StatsWidget::setElapsed(int seconds) {
    m_elapsed = seconds;
    update();
}

void StatsWidget::setProgress(double progress) {
    m_progress = progress;
    update();
}

QSize StatsWidget::sizeHint() const {
    return QSize(800, 100);
}

void StatsWidget::drawStatBox(QPainter& p, const QRect& rect, const QString& label,
                               const QString& value, const QColor& accent) {
    // Box background
    QLinearGradient bg(rect.topLeft(), rect.bottomLeft());
    bg.setColorAt(0, QColor(35, 42, 65));
    bg.setColorAt(1, QColor(25, 30, 50));
    p.setPen(QPen(QColor(accent.red(), accent.green(), accent.blue(), 80), 1));
    p.setBrush(bg);
    p.drawRoundedRect(rect, 8, 8);

    // Accent line at top
    p.setPen(Qt::NoPen);
    p.setBrush(accent);
    p.drawRoundedRect(rect.left() + 8, rect.top() + 1, rect.width() - 16, 3, 2, 2);

    // Value
    QFont valFont;
    valFont.setPixelSize(28);
    valFont.setBold(true);
    p.setFont(valFont);
    p.setPen(QColor(230, 235, 255));
    QRect valRect = rect.adjusted(0, 8, 0, -24);
    p.drawText(valRect, Qt::AlignCenter, value);

    // Label
    QFont lblFont;
    lblFont.setPixelSize(11);
    lblFont.setLetterSpacing(QFont::AbsoluteSpacing, 1.5);
    p.setFont(lblFont);
    p.setPen(QColor(130, 145, 185));
    QRect lblRect(rect.left(), rect.bottom() - 22, rect.width(), 20);
    p.drawText(lblRect, Qt::AlignCenter, label.toUpper());
}

void StatsWidget::drawProgressBar(QPainter& p, const QRect& rect) {
    // Background
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(30, 36, 58));
    p.drawRoundedRect(rect, 4, 4);

    // Fill
    if (m_progress > 0) {
        int fillW = static_cast<int>(rect.width() * m_progress);
        QLinearGradient fill(rect.left(), 0, rect.right(), 0);
        fill.setColorAt(0, QColor(80, 150, 255));
        fill.setColorAt(0.5, QColor(120, 100, 255));
        fill.setColorAt(1.0, QColor(80, 220, 160));
        p.setBrush(fill);
        p.drawRoundedRect(rect.left(), rect.top(), fillW, rect.height(), 4, 4);
    }

    // Progress text
    QFont f;
    f.setPixelSize(10);
    p.setFont(f);
    p.setPen(QColor(180, 190, 220));
    p.drawText(rect, Qt::AlignCenter,
               QString("%1%").arg(static_cast<int>(m_progress * 100)));
}

void StatsWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    // Background
    p.fillRect(rect(), QColor(20, 24, 38));

    const int boxH = 80;
    const int boxW = 140;
    const int gap = 12;
    const int topY = (height() - boxH) / 2;

    // Minutes elapsed
    int mins = m_elapsed / 60;
    int secs = m_elapsed % 60;
    QString timeStr = QString("%1:%2")
                        .arg(mins, 2, 10, QLatin1Char('0'))
                        .arg(secs, 2, 10, QLatin1Char('0'));

    // Draw 3 stat boxes centered
    int totalW = boxW * 3 + gap * 2;
    int startX = (width() - totalW) / 2;

    drawStatBox(p, QRect(startX, topY, boxW, boxH),
                "Time", timeStr, QColor(100, 160, 255));

    drawStatBox(p, QRect(startX + boxW + gap, topY, boxW, boxH),
                "WPM", QString::number(static_cast<int>(m_wpm)), QColor(80, 220, 160));

    drawStatBox(p, QRect(startX + (boxW + gap)*2, topY, boxW, boxH),
                "Accuracy", QString("%1%").arg(static_cast<int>(m_accuracy)), QColor(255, 180, 60));

    // Progress bar at bottom
    int pbY = height() - 14;
    int pbX = 20;
    int pbW = width() - 40;
    drawProgressBar(p, QRect(pbX, pbY, pbW, 8));
}
