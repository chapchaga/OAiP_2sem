#include "textdisplaywidget.h"
#include <QPainter>
#include <QFontMetrics>
#include <QTextLayout>
#include <QVector>

TextDisplayWidget::TextDisplayWidget(QWidget* parent) : QWidget(parent) {
    setMinimumHeight(150);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QFont TextDisplayWidget::textFont() const {
    QFont f;
    f.setPixelSize(26);
    f.setFamily("Courier New");
    return f;
}

void TextDisplayWidget::setText(const QString& text) {
    m_text = text;
    m_currentIndex = 0;
    rebuildChars();
    update();
}

void TextDisplayWidget::rebuildChars() {
    m_chars.clear();
    for (const QChar& c : m_text) {
        CharInfo ci;
        ci.ch = c;
        ci.state = CharState::Pending;
        m_chars.append(ci);
    }
    if (!m_chars.isEmpty()) {
        m_chars[0].state = CharState::Current;
    }
}

void TextDisplayWidget::setCurrentIndex(int idx) {
    if (idx >= 0 && idx < m_chars.size()) {
        if (m_currentIndex >= 0 && m_currentIndex < m_chars.size()) {
            if (m_chars[m_currentIndex].state == CharState::Current) {
                m_chars[m_currentIndex].state = CharState::Pending;
            }
        }
        m_currentIndex = idx;
        m_chars[idx].state = CharState::Current;
    }
    update();
}

void TextDisplayWidget::setCharState(int idx, CharState state) {
    if (idx >= 0 && idx < m_chars.size()) {
        m_chars[idx].state = state;
    }
    update();
}

QSize TextDisplayWidget::sizeHint() const {
    return QSize(800, 200);
}

void TextDisplayWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    // Background
    QLinearGradient bg(0, 0, 0, height());
    bg.setColorAt(0, QColor(22, 26, 42));
    bg.setColorAt(1, QColor(18, 22, 36));
    p.fillRect(rect(), bg);

    // Border
    p.setPen(QPen(QColor(60, 75, 110), 1.5));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(rect().adjusted(1,1,-2,-2), 10, 10);

    QFont f = textFont();
    p.setFont(f);
    QFontMetrics fm(f);

    const int padding = 24;
    const int lineH = fm.height() + 12;
    int x = padding;
    int y = padding + fm.ascent();
    int maxWidth = width() - padding * 2;

    // Draw words - wrap lines
    for (int i = 0; i < m_chars.size(); ++i) {
        const CharInfo& ci = m_chars[i];
        int charW = fm.horizontalAdvance(ci.ch);

        // Check line wrap
        if (x + charW > maxWidth + padding) {
            x = padding;
            y += lineH;
            if (y > height() - padding) break;
        }

        // Draw character background for current
        if (ci.state == CharState::Current) {
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(100, 160, 255, 80));
            p.drawRoundedRect(x - 1, y - fm.ascent() - 2, charW + 2, fm.height() + 4, 3, 3);
            // Blinking cursor line
            p.setPen(QPen(QColor(120, 180, 255), 2));
            p.drawLine(x - 1, y - fm.ascent(), x - 1, y + fm.descent());
        }

        // Choose color based on state
        QColor color;
        switch (ci.state) {
            case CharState::Pending:
                color = QColor(160, 170, 200);
                break;
            case CharState::Correct:
                color = QColor(80, 220, 130);
                break;
            case CharState::Wrong:
                color = QColor(255, 90, 90);
                break;
            case CharState::Current:
                color = QColor(200, 220, 255);
                break;
        }

        // Draw background for wrong
        if (ci.state == CharState::Wrong) {
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(200, 50, 50, 40));
            p.drawRoundedRect(x, y - fm.ascent() - 2, charW, fm.height() + 4, 2, 2);
        }

        p.setPen(color);
        p.drawText(x, y, QString(ci.ch));
        x += charW;
    }
}
