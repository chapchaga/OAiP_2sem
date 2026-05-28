#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef __ARM_ARCH
#include <arm_acle.h>
#endif

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QComboBox>
#include "bitset.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onCreateBitSet();
    void onSetBit();
    void onResetBit();
    void onFlipBit();
    void onTestBit();
    void onSetAll();
    void onResetAll();
    void onFlipAll();
    void onQueryAll();
    void onQueryAny();
    void onQueryNone();
    void onQueryCount();
    void onToString();
    void onToUlong();
    void onToUllong();
    void onBitwiseOp();
    void onRunTests();

private:
    void updateDisplay();
    void log(const QString& msg, bool ok = true);

    // Widgets
    QSpinBox*    spinSize_;
    QLineEdit*   editInitVal_;
    QPushButton* btnCreate_;
    QLabel*      lblBits_;
    QLabel*      lblInfo_;

    QSpinBox*    spinPos_;
    QPushButton* btnSet_;
    QPushButton* btnReset_;
    QPushButton* btnFlip_;
    QPushButton* btnTest_;

    QPushButton* btnSetAll_;
    QPushButton* btnResetAll_;
    QPushButton* btnFlipAll_;

    QPushButton* btnAll_;
    QPushButton* btnAny_;
    QPushButton* btnNone_;
    QPushButton* btnCount_;
    QPushButton* btnToStr_;
    QPushButton* btnToUlong_;
    QPushButton* btnToUllong_;

    // Bitwise op widgets
    QLineEdit*   editSecond_;
    QComboBox*   cmbOp_;
    QPushButton* btnBitOp_;

    QPushButton* btnRunTests_;
    QTextEdit*   logEdit_;

    BitSet bs_{8, 0ULL};
};

#endif // MAINWINDOW_H
