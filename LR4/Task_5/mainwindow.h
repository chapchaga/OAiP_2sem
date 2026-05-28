#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>
#include <QTextEdit>
#include <QSpinBox>

#include "vector.h"
#include "pair.h"
#include "algorithms.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QTabWidget* tabs;

    // === Вкладка 1: Pair / Матрицы ===
    QTableWidget* matrixTable1;
    QTableWidget* matrixTable2;
    QLabel*       nestedPairLabel;
    QPushButton*  generateMatrixBtn;

    // === Вкладка 2: Методы Vector ===
    QTextEdit*    logEdit;
    QTableWidget* vectorTable;
    QLabel*       statsLabel;

    // Поля ввода с подсказками
    QSpinBox*    pushValSpin;
    QSpinBox*    insertPosSpin;
    QSpinBox*    insertValSpin;
    QSpinBox*    erasePosSpin;
    QSpinBox*    resizeSpin;
    QSpinBox*    searchSpin;

    // Кнопки
    QPushButton* pushBackBtn;
    QPushButton* popBackBtn;
    QPushButton* insertBtn;
    QPushButton* eraseBtn;
    QPushButton* clearBtn;
    QPushButton* sortBtn;
    QPushButton* searchBtn;
    QPushButton* resizeBtn;
    QPushButton* swapBtn;
    QPushButton* assignBtn;
    QPushButton* shrinkBtn;
    QPushButton* iteratorBtn;
    QPushButton* reverseIterBtn;
    QPushButton* frontBackBtn;
    QPushButton* resetBtn;

    Vector<int> vec;
    Vector<int> swapVec;

    Pair< Vector<int>, Vector<Pair<int,double>> > complexData;

public:
    MainWindow(QWidget* parent = nullptr);

private:
    void buildMatrixTab();
    void buildVectorTab();
    void updateMatrixTables();
    void updateVectorTable();
    void updateStats();
    void log(const QString& msg);

private slots:
    void generateMatrix();
    void doPushBack();
    void doPopBack();
    void doInsert();
    void doErase();
    void doClear();
    void doSort();
    void doSearch();
    void doResize();
    void doSwap();
    void doAssign();
    void doShrink();
    void doIterator();
    void doReverseIter();
    void doFrontBack();
    void doReset();
};
