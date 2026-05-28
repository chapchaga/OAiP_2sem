#include "keyboardwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>
#include <cmath>

KeyboardWidget::KeyboardWidget(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(180);
    setLanguage(Language::German);
}

void KeyboardWidget::setLanguage(Language lang) {
    m_currentLang = lang;
    auto data = getLanguageData();
    m_rows = data[lang].keyboardRows;
    m_highlightedKey.clear();
    update();
}

void KeyboardWidget::highlightKey(const QString& key, bool correct) {
    m_highlightedKey = key.toLower();
    m_highlightCorrect = correct;
    update();
}

void KeyboardWidget::clearHighlight() {
    m_highlightedKey.clear();
    update();
}

QSize KeyboardWidget::sizeHint() const {
    return QSize(800, 200);
}

double KeyboardWidget::keyWidth() const {
    return (width() - 40.0) / 14.0;
}

double KeyboardWidget::keyHeight() const {
    return (height() - 20.0) / 5.0;
}

int KeyboardWidget::rowOffset(int row) const {
    // Stagger offsets per row (like real keyboard)
    const double kw = keyWidth();
    switch(row) {
        case 0: return 0;
        case 1: return static_cast<int>(kw * 0.5);
        case 2: return static_cast<int>(kw * 0.75);
        case 3: return static_cast<int>(kw * 1.0);
        case 4: return static_cast<int>(kw * 3.5); // Space bar row
        default: return 0;
    }
}

QRect KeyboardWidget::keyRect(int row, int col) const {
    const double kw = keyWidth();
    const double kh = keyHeight();
    const int margin = 10;
    const int gap = 3;

    int x = margin + rowOffset(row) + col * (kw + gap);
    int y = margin + row * (kh + gap);

    if (row == 4) { // Space bar
        return QRect(x, y, static_cast<int>(kw * 6), static_cast<int>(kh));
    }

    return QRect(x, y, static_cast<int>(kw), static_cast<int>(kh));
}

void KeyboardWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // Background
    QLinearGradient bg(0, 0, 0, height());
    bg.setColorAt(0, QColor(28, 32, 48));
    bg.setColorAt(1, QColor(18, 20, 32));
    p.fillRect(rect(), bg);

    // Draw rounded border
    p.setPen(QPen(QColor(60, 70, 100), 1));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(rect().adjusted(1,1,-2,-2), 10, 10);

    QFont keyFont = p.font();
    keyFont.setPixelSize(12);
    keyFont.setBold(true);
    p.setFont(keyFont);

    for (int row = 0; row < m_rows.size(); ++row) {
        for (int col = 0; col < m_rows[row].size(); ++col) {
            QString keyLabel = m_rows[row][col];
            QRect kr = keyRect(row, col);

            bool isHighlighted = (!m_highlightedKey.isEmpty() &&
                                  keyLabel.toLower() == m_highlightedKey);
            bool isSpace = (keyLabel == "SPACE");

            // Key shadow
            QRect shadowRect = kr.adjusted(1, 2, 1, 2);
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(0, 0, 0, 80));
            p.drawRoundedRect(shadowRect, 5, 5);

            // Key gradient
            QLinearGradient keyGrad(kr.topLeft(), kr.bottomLeft());

            if (isHighlighted) {
                if (m_highlightCorrect) {
                    keyGrad.setColorAt(0, QColor(80, 220, 130));
                    keyGrad.setColorAt(1, QColor(40, 160, 90));
                } else {
                    keyGrad.setColorAt(0, QColor(255, 100, 100));
                    keyGrad.setColorAt(1, QColor(200, 50, 50));
                }
            } else if (isSpace) {
                keyGrad.setColorAt(0, QColor(70, 80, 110));
                keyGrad.setColorAt(1, QColor(50, 60, 90));
            } else {
                keyGrad.setColorAt(0, QColor(55, 65, 95));
                keyGrad.setColorAt(1, QColor(38, 45, 72));
            }

            p.setBrush(keyGrad);

            // Key border
            if (isHighlighted) {
                p.setPen(QPen(m_highlightCorrect ? QColor(100, 255, 160) : QColor(255, 130, 130), 1.5));
            } else {
                p.setPen(QPen(QColor(80, 95, 135), 1));
            }
            p.drawRoundedRect(kr, 5, 5);

            // Key top shine
            QLinearGradient shine(kr.topLeft(), QPoint(kr.left(), kr.top() + kr.height()/3));
            shine.setColorAt(0, QColor(255,255,255,30));
            shine.setColorAt(1, QColor(255,255,255,0));
            p.setPen(Qt::NoPen);
            p.setBrush(shine);
            QRect shineRect = kr.adjusted(2, 2, -2, -kr.height()/2);
            p.drawRoundedRect(shineRect, 4, 4);

            // Key label
            if (isHighlighted) {
                p.setPen(QColor(255, 255, 255));
            } else if (isSpace) {
                p.setPen(QColor(140, 160, 200));
            } else {
                p.setPen(QColor(200, 215, 245));
            }

            if (isSpace) {
                p.drawText(kr, Qt::AlignCenter, "SPACE");
            } else {
                p.drawText(kr, Qt::AlignCenter, keyLabel);
            }
        }
    }
}
