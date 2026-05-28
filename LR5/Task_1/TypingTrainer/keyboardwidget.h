#pragma once
#include <QWidget>
#include <QString>
#include <QVector>
#include "languagedata.h"

class KeyboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget* parent = nullptr);
    void setLanguage(Language lang);
    void highlightKey(const QString& key, bool correct);
    void clearHighlight();

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;

private:
    Language m_currentLang = Language::German;
    QVector<QVector<QString>> m_rows;
    QString m_highlightedKey;
    bool m_highlightCorrect = true;

    QRect keyRect(int row, int col) const;
    int rowOffset(int row) const;
    double keyWidth() const;
    double keyHeight() const;
};
