#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include "keyboardwidget.h"
#include "textdisplaywidget.h"
#include "statswidget.h"
#include "languagedata.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void onLanguageChanged(int index);
    void onStartReset();
    void onLoadFile();
    void onTimerTick();

private:
    void setupUI();
    void setupStyle();
    void startSession();
    void resetSession();
    void processChar(QChar typed);
    void updateStats();
    void checkCompletion();

    // UI
    QWidget*          m_central = nullptr;
    QComboBox*        m_langCombo = nullptr;
    QPushButton*      m_startBtn = nullptr;
    QPushButton*      m_loadBtn = nullptr;
    QLabel*           m_statusLabel = nullptr;
    TextDisplayWidget* m_textDisplay = nullptr;
    StatsWidget*      m_stats = nullptr;
    KeyboardWidget*   m_keyboard = nullptr;

    // State
    Language          m_currentLang = Language::German;
    bool              m_running = false;
    int               m_currentIndex = 0;
    int               m_correctCount = 0;
    int               m_totalTyped = 0;
    int               m_wordCount = 0;
    QTimer*           m_timer = nullptr;
    QElapsedTimer     m_elapsed;
    int               m_seconds = 0;
    QString           m_currentText;

    QMap<Language, LanguageInfo> m_langData;
};
