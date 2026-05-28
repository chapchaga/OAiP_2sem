#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QFrame>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_langData = getLanguageData();
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    setupUI();
    setupStyle();

    // Set initial language
    m_currentLang = Language::German;
    m_currentText = m_langData[m_currentLang].sampleText;
    m_textDisplay->setText(m_currentText);
    m_keyboard->setLanguage(m_currentLang);

    setWindowTitle("✦ Typing Trainer");
    resize(900, 720);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void MainWindow::setupUI() {
    m_central = new QWidget(this);
    setCentralWidget(m_central);

    QVBoxLayout* mainLayout = new QVBoxLayout(m_central);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // ── HEADER ──────────────────────────────────────────────────────────────
    QWidget* header = new QWidget();
    header->setFixedHeight(70);
    header->setObjectName("header");
    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(24, 0, 24, 0);
    headerLayout->setSpacing(16);

    // Title
    QLabel* title = new QLabel("⌨ TYPING TRAINER");
    title->setObjectName("titleLabel");
    headerLayout->addWidget(title);

    headerLayout->addStretch();

    // Language selector
    QLabel* langLabel = new QLabel("Language:");
    langLabel->setObjectName("headerLabel");
    headerLayout->addWidget(langLabel);

    m_langCombo = new QComboBox();
    m_langCombo->setObjectName("langCombo");
    m_langCombo->addItem("🇩🇪  Deutsch", static_cast<int>(Language::German));
    m_langCombo->addItem("🇫🇷  Français", static_cast<int>(Language::French));
    m_langCombo->addItem("🇸🇦  العربية", static_cast<int>(Language::Arabic));
    m_langCombo->addItem("🇨🇳  中文", static_cast<int>(Language::Chinese));
    m_langCombo->addItem("🇧🇾  Беларуская", static_cast<int>(Language::Belarusian));
    m_langCombo->addItem("🇮🇱  עברית", static_cast<int>(Language::Hebrew));
    m_langCombo->addItem("🇬🇧  English", static_cast<int>(Language::English));
    m_langCombo->setFixedWidth(200);
    connect(m_langCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onLanguageChanged);
    headerLayout->addWidget(m_langCombo);

    // Load file button
    m_loadBtn = new QPushButton("📂  Load File");
    m_loadBtn->setObjectName("loadBtn");
    m_loadBtn->setFixedWidth(130);
    connect(m_loadBtn, &QPushButton::clicked, this, &MainWindow::onLoadFile);
    headerLayout->addWidget(m_loadBtn);

    // Start/Reset button
    m_startBtn = new QPushButton("▶  Start");
    m_startBtn->setObjectName("startBtn");
    m_startBtn->setFixedWidth(120);
    connect(m_startBtn, &QPushButton::clicked, this, &MainWindow::onStartReset);
    headerLayout->addWidget(m_startBtn);

    mainLayout->addWidget(header);

    // ── SEPARATOR ───────────────────────────────────────────────────────────
    QFrame* sep = new QFrame();
    sep->setFrameShape(QFrame::HLine);
    sep->setObjectName("separator");
    sep->setFixedHeight(1);
    mainLayout->addWidget(sep);

    // ── CONTENT AREA ────────────────────────────────────────────────────────
    QWidget* content = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(content);
    contentLayout->setSpacing(16);
    contentLayout->setContentsMargins(20, 20, 20, 20);

    // Stats widget
    m_stats = new StatsWidget();
    m_stats->setFixedHeight(100);
    contentLayout->addWidget(m_stats);

    // Text display
    m_textDisplay = new TextDisplayWidget();
    m_textDisplay->setMinimumHeight(180);
    contentLayout->addWidget(m_textDisplay);

    // Status label
    m_statusLabel = new QLabel("Press Start to begin or just start typing...");
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(m_statusLabel);

    // Keyboard
    m_keyboard = new KeyboardWidget();
    m_keyboard->setMinimumHeight(190);
    contentLayout->addWidget(m_keyboard);

    mainLayout->addWidget(content);
}

void MainWindow::setupStyle() {
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #12141E;
        }
        QWidget {
            background-color: #12141E;
            color: #E0E5FF;
            font-family: 'SF Pro Display', 'Segoe UI', 'Helvetica Neue', Arial, sans-serif;
        }
        #header {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
                stop:0 #1C2035, stop:1 #161828);
            border-bottom: 1px solid #2A3255;
        }
        #titleLabel {
            font-size: 18px;
            font-weight: 800;
            color: #9ABBFF;
            letter-spacing: 3px;
        }
        #headerLabel {
            font-size: 12px;
            color: #7080A8;
            font-weight: 500;
        }
        #separator {
            background: #2A3255;
            border: none;
        }
        #langCombo {
            background: #1E2540;
            color: #C8D5FF;
            border: 1px solid #3A4870;
            border-radius: 8px;
            padding: 6px 12px;
            font-size: 13px;
            font-weight: 500;
        }
        #langCombo::drop-down {
            border: none;
            width: 20px;
        }
        #langCombo:hover {
            border-color: #6080C0;
            background: #232A50;
        }
        QComboBox QAbstractItemView {
            background: #1E2540;
            border: 1px solid #3A4870;
            border-radius: 8px;
            color: #C8D5FF;
            selection-background-color: #3050A0;
            padding: 4px;
        }
        #startBtn {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
                stop:0 #4A90E2, stop:1 #2E5FAA);
            color: white;
            border: none;
            border-radius: 8px;
            padding: 8px 16px;
            font-size: 13px;
            font-weight: 700;
            letter-spacing: 0.5px;
        }
        #startBtn:hover {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
                stop:0 #5AA0EF, stop:1 #3870C0);
        }
        #startBtn:pressed {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
                stop:0 #2E5FAA, stop:1 #1E4080);
        }
        #loadBtn {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
                stop:0 #3A4060, stop:1 #282E4C);
            color: #A8B8E0;
            border: 1px solid #4A5880;
            border-radius: 8px;
            padding: 8px 16px;
            font-size: 13px;
            font-weight: 600;
        }
        #loadBtn:hover {
            background: qlineargradient(x1:0,y1:0,x2:0,y2:1,
                stop:0 #454C72, stop:1 #333860);
            color: #C0D0FF;
        }
        #statusLabel {
            font-size: 13px;
            color: #6070A0;
            font-style: italic;
            padding: 4px;
        }
        QPushButton:focus {
            outline: none;
        }
    )");
}

void MainWindow::onLanguageChanged(int index) {
    Language lang = static_cast<Language>(m_langCombo->itemData(index).toInt());
    m_currentLang = lang;
    m_keyboard->setLanguage(lang);
    m_currentText = m_langData[lang].sampleText;
    resetSession();
}

void MainWindow::onStartReset() {
    if (m_running) {
        resetSession();
    } else {
        startSession();
    }
}

void MainWindow::onLoadFile() {
    QString path = QFileDialog::getOpenFileName(this, "Open Text File", "",
                                                 "Text Files (*.txt);;All Files (*)");
    if (path.isEmpty()) return;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + path);
        return;
    }

    QTextStream stream(&file);
    stream.setEncoding(QStringConverter::Utf8);
    QString text = stream.readAll().simplified();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "File is empty.");
        return;
    }

    m_currentText = text.left(500); // Limit to 500 chars
    resetSession();
    m_statusLabel->setText(QString("Loaded: %1 | Press Start to begin").arg(QFileInfo(path).fileName()));
}

void MainWindow::startSession() {
    if (m_currentText.isEmpty()) return;

    m_running = true;
    m_currentIndex = 0;
    m_correctCount = 0;
    m_totalTyped = 0;
    m_wordCount = 0;
    m_seconds = 0;

    m_textDisplay->setText(m_currentText);
    m_stats->setWPM(0);
    m_stats->setAccuracy(100);
    m_stats->setElapsed(0);
    m_stats->setProgress(0);

    m_startBtn->setText("↺  Reset");
    m_statusLabel->setText("⌨  Type the text above...");
    m_keyboard->clearHighlight();

    m_elapsed.start();
    m_timer->start();
    setFocus();
}

void MainWindow::resetSession() {
    m_running = false;
    m_timer->stop();
    m_currentIndex = 0;
    m_correctCount = 0;
    m_totalTyped = 0;
    m_seconds = 0;

    m_textDisplay->setText(m_currentText);
    m_stats->setWPM(0);
    m_stats->setAccuracy(100);
    m_stats->setElapsed(0);
    m_stats->setProgress(0);

    m_startBtn->setText("▶  Start");
    m_statusLabel->setText("Press Start to begin or just start typing...");
    m_keyboard->clearHighlight();
}

void MainWindow::onTimerTick() {
    m_seconds++;
    m_stats->setElapsed(m_seconds);
    updateStats();
}

void MainWindow::updateStats() {
    double minutes = m_seconds / 60.0;
    double wpm = minutes > 0 ? (m_wordCount / minutes) : 0;
    double accuracy = m_totalTyped > 0
                      ? (m_correctCount * 100.0 / m_totalTyped)
                      : 100.0;
    double progress = m_currentText.isEmpty() ? 0
                      : static_cast<double>(m_currentIndex) / m_currentText.length();

    m_stats->setWPM(wpm);
    m_stats->setAccuracy(accuracy);
    m_stats->setProgress(progress);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    QString key = event->text();
    if (key.isEmpty()) return;

    // Auto-start on first keypress
    if (!m_running) {
        startSession();
    }

    if (m_currentIndex >= m_currentText.length()) return;

    QChar expected = m_currentText[m_currentIndex];
    QChar typed = key[0];

    m_totalTyped++;

    if (typed == expected) {
        m_correctCount++;
        m_textDisplay->setCharState(m_currentIndex, CharState::Correct);
        m_keyboard->highlightKey(key, true);

        // Count words (space = word boundary)
        if (typed == ' ') m_wordCount++;

        m_currentIndex++;
        if (m_currentIndex < m_currentText.length()) {
            m_textDisplay->setCurrentIndex(m_currentIndex);
        }
    } else {
        m_textDisplay->setCharState(m_currentIndex, CharState::Wrong);
        m_keyboard->highlightKey(key, false);
    }

    updateStats();
    checkCompletion();
}

void MainWindow::checkCompletion() {
    if (m_currentIndex >= m_currentText.length()) {
        m_timer->stop();
        m_running = false;
        m_wordCount++; // Count last word

        double minutes = m_seconds / 60.0;
        double wpm = minutes > 0 ? (m_wordCount / minutes) : m_wordCount * 60;
        double accuracy = m_totalTyped > 0
                          ? (m_correctCount * 100.0 / m_totalTyped)
                          : 100.0;

        m_stats->setProgress(1.0);
        m_stats->setWPM(wpm);
        m_stats->setAccuracy(accuracy);

        m_startBtn->setText("▶  Start");
        m_statusLabel->setText(
            QString("🎉  Finished! WPM: %1  |  Accuracy: %2%  |  Time: %3s")
                .arg(static_cast<int>(wpm))
                .arg(static_cast<int>(accuracy))
                .arg(m_seconds)
        );
        m_keyboard->clearHighlight();
    }
}
