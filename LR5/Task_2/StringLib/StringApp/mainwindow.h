#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QSplitter>
#include <QFrame>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    // ── Tab pages ─────────────────────────────────────────────────
    QWidget* buildMemoryTab();
    QWidget* buildCopyTab();
    QWidget* buildConcatTab();
    QWidget* buildCompareTab();
    QWidget* buildMiscTab();
    QWidget* buildObjectTab();
    QWidget* buildTestsTab();

    // ── Helper builders ───────────────────────────────────────────
    QGroupBox* makeGroup(const QString& title, QLayout* layout);
    QWidget*   makeRow(const QString& label, QWidget* widget, int labelWidth = 120);
    void       appendResult(QTextEdit* log, const QString& func,
                            const QString& input, const QString& result,
                            bool ok = true);

    // ── Log widgets (one per tab for clarity) ─────────────────────
    QTextEdit* memLog_;
    QTextEdit* copyLog_;
    QTextEdit* catLog_;
    QTextEdit* cmpLog_;
    QTextEdit* miscLog_;
    QTextEdit* objLog_;
    QTextEdit* testLog_;

    // ── Input fields ──────────────────────────────────────────────
    // Memory tab
    QLineEdit* memSrc_;
    QLineEdit* memDst_;
    QSpinBox*  memN_;
    QLineEdit* memSetChar_;
    QSpinBox*  memSetN_;

    // Copy tab
    QLineEdit* cpySrc_;
    QLineEdit* cpyDst_;
    QSpinBox*  cpyN_;

    // Concat tab
    QLineEdit* catSrc_;
    QLineEdit* catDst_;
    QSpinBox*  catN_;

    // Compare tab
    QLineEdit* cmpS1_;
    QLineEdit* cmpS2_;
    QSpinBox*  cmpN_;

    // Misc tab
    QLineEdit* tokStr_;
    QLineEdit* tokDelim_;
    QSpinBox*  errNum_;

    // Object tab
    QLineEdit* objS1_;
    QLineEdit* objS2_;

private slots:
    // Memory
    void doMemcpy();
    void doMemmove();
    void doMemcmp();
    void doMemset();

    // Copy
    void doStrcpy();
    void doStrncpy();

    // Concat
    void doStrcat();
    void doStrncat();

    // Compare
    void doStrcmp();
    void doStrcoll();
    void doStrncmp();
    void doStrxfrm();

    // Misc
    void doStrtok();
    void doStrerror();
    void doStrlen();

    // Object demo
    void doObjDemo();

    // Tests
    void runAllTests();
};

#endif // MAINWINDOW_H
