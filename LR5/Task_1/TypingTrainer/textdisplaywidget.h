#pragma once
#include <QWidget>
#include <QString>
#include <QVector>

enum class CharState {
    Pending,
    Correct,
    Wrong,
    Current
};

struct CharInfo {
    QChar ch;
    CharState state;
};

class TextDisplayWidget : public QWidget {
    Q_OBJECT
public:
    explicit TextDisplayWidget(QWidget* parent = nullptr);
    void setText(const QString& text);
    void setCurrentIndex(int idx);
    void setCharState(int idx, CharState state);
    QString getText() const { return m_text; }
    int charCount() const { return m_chars.size(); }

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;

private:
    QString m_text;
    QVector<CharInfo> m_chars;
    int m_currentIndex = 0;
    bool m_rtl = false;

    void rebuildChars();
    QFont textFont() const;
};
