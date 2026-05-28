#pragma once
#include <QMainWindow>
#include "hashtable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onRunBenchmark();
    void onInsertManual();
    void onSearchManual();
    void onClear();
    void onTableSizeChanged(int idx);

private:
    Ui::MainWindow* ui;
    OpenHashTable* currentTable;
    std::vector<BenchResult> lastResults;

    void refreshTableView();
    void drawChart();
    void appendLog(const QString& msg);
};
