#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QFontMetrics>
#include <algorithm>
#include <sstream>

static const int TABLE_SIZES[] = {16, 64, 128, 2048};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), currentTable(nullptr)
{
    ui->setupUi(this);

    ui->comboTableSize->addItem("16");
    ui->comboTableSize->addItem("64");
    ui->comboTableSize->addItem("128");
    ui->comboTableSize->addItem("2048");
    ui->comboTableSize->setCurrentIndex(0);

    ui->comboHashType->addItem("Modular");
    ui->comboHashType->addItem("Universal");

    currentTable = new OpenHashTable(16, HashType::MODULAR);
    refreshTableView();

    connect(ui->btnBenchmark,    &QPushButton::clicked, this, &MainWindow::onRunBenchmark);
    connect(ui->btnInsert,       &QPushButton::clicked, this, &MainWindow::onInsertManual);
    connect(ui->btnSearch,       &QPushButton::clicked, this, &MainWindow::onSearchManual);
    connect(ui->btnClear,        &QPushButton::clicked, this, &MainWindow::onClear);
    connect(ui->comboTableSize,  QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onTableSizeChanged);
    connect(ui->comboHashType,   QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onTableSizeChanged);
}

MainWindow::~MainWindow() {
    delete currentTable;
    delete ui;
}

void MainWindow::onTableSizeChanged(int) {
    int sz = TABLE_SIZES[ui->comboTableSize->currentIndex()];
    HashType ht = ui->comboHashType->currentIndex() == 0 ? HashType::MODULAR : HashType::UNIVERSAL;
    delete currentTable;
    currentTable = new OpenHashTable(sz, ht);
    refreshTableView();
    appendLog(QString("New table: size=%1, type=%2")
        .arg(sz)
        .arg(ht == HashType::MODULAR ? "Modular" : "Universal"));
}

void MainWindow::onInsertManual() {
    bool ok;
    int key = ui->editKey->text().toInt(&ok);
    if (!ok) { appendLog("Invalid key."); return; }
    QString val = ui->editValue->text().isEmpty() ? "v" + QString::number(key) : ui->editValue->text();
    if (currentTable->insert(key, val.toStdString()))
        appendLog(QString("Inserted key=%1 val=%2 | load=%.2f | collisions=%3")
            .arg(key).arg(val)
            .arg(currentTable->loadFactor())
            .arg(currentTable->collisionCount));
    else
        appendLog("Table full, cannot insert.");
    refreshTableView();
}

void MainWindow::onSearchManual() {
    bool ok;
    int key = ui->editKey->text().toInt(&ok);
    if (!ok) { appendLog("Invalid key."); return; }
    long long t = currentTable->searchTime(key);
    appendLog(QString("Search key=%1 | time=%2 ns | hash=%3")
        .arg(key).arg(t).arg(currentTable->hashFunc(key)));
}

void MainWindow::onClear() {
    currentTable->clear();
    appendLog("Table cleared.");
    refreshTableView();
}

void MainWindow::onRunBenchmark() {
    appendLog("=== Running Benchmark ===");
    int N = 2000;
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(-100000, 100000);
    std::vector<int> keys(N);
    std::vector<std::string> vals(N);
    for (int i = 0; i < N; i++) {
        keys[i] = dist(rng);
        vals[i] = "v" + std::to_string(i);
    }
    std::vector<int> searchKeys(keys.begin(), keys.begin() + 100);

    lastResults.clear();
    for (int sz : TABLE_SIZES) {
        int fill = (int)(sz * 0.75);
        BenchResult r = runBenchmark(sz, fill, keys, vals, searchKeys);
        lastResults.push_back(r);
        appendLog(QString("Size=%1 | MOD: %2 ns, %3 col | UNI: %4 ns, %5 col")
            .arg(r.tableSize)
            .arg(r.timeModular)
            .arg(r.collisionsModular)
            .arg(r.timeUniversal)
            .arg(r.collisionsUniversal));
    }
    drawChart();
    appendLog("=== Done ===");
}

void MainWindow::refreshTableView() {
    std::ostringstream oss;
    int sz = currentTable->tableSize;
    int show = std::min(sz, 64);
    for (int i = 0; i < show; i++) {
        const Slot& s = currentTable->table[i];
        oss << "[" << i << "] ";
        if (s.state == SlotState::OCCUPIED)
            oss << "KEY=" << s.key << " VAL=" << s.value << " (probes=" << s.probeCount << ")";
        else if (s.state == SlotState::DELETED)
            oss << "<deleted>";
        else
            oss << "(empty)";
        oss << "\n";
    }
    if (sz > 64) oss << "... (" << sz - 64 << " more slots)\n";
    oss << "\nLoad factor: " << currentTable->loadFactor();
    oss << "\nCollisions: " << currentTable->collisionCount;
    oss << "\nHash: " << currentTable->getDescription();
    ui->memoTable->setPlainText(QString::fromStdString(oss.str()));
}

void MainWindow::drawChart() {
    if (lastResults.empty()) return;

    QWidget* canvas = ui->chartWidget;
    int W = canvas->width();
    int H = canvas->height();
    if (W < 10 || H < 10) return;

    QPixmap pix(W, H);
    pix.fill(QColor(24, 24, 32));
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);

    int marginL = 80, marginR = 20, marginT = 30, marginB = 50;
    int chartW = W - marginL - marginR;
    int chartH = H - marginT - marginB;

    p.setPen(QColor(80, 80, 100));
    p.drawRect(marginL, marginT, chartW, chartH);

    long long maxTime = 1;
    for (auto& r : lastResults) {
        maxTime = std::max(maxTime, std::max(r.timeModular, r.timeUniversal));
    }
    maxTime = (long long)(maxTime * 1.1);

    int n = (int)lastResults.size();
    int barW = chartW / (n * 3 + 1);
    int gap = barW;

    for (int i = 0; i < n; i++) {
        auto& r = lastResults[i];
        int x0 = marginL + gap + i * (barW * 2 + gap);

        int hMod = (int)((double)r.timeModular / maxTime * chartH);
        int hUni = (int)((double)r.timeUniversal / maxTime * chartH);

        p.setBrush(QColor(70, 130, 220));
        p.setPen(Qt::NoPen);
        p.drawRect(x0, marginT + chartH - hMod, barW, hMod);

        p.setBrush(QColor(220, 100, 70));
        p.drawRect(x0 + barW + 2, marginT + chartH - hUni, barW, hUni);

        p.setPen(QColor(200, 200, 200));
        p.setFont(QFont("Courier New", 8));
        QString label = QString("N=%1").arg(r.tableSize);
        p.drawText(x0, marginT + chartH + 14, barW * 2, 20, Qt::AlignHCenter, label);
    }

    p.setPen(QColor(200, 200, 200));
    p.setFont(QFont("Courier New", 8));
    int steps = 5;
    for (int i = 0; i <= steps; i++) {
        long long val = maxTime * i / steps;
        int y = marginT + chartH - (int)((double)val / maxTime * chartH);
        p.drawLine(marginL - 4, y, marginL, y);
        p.drawText(4, y - 8, marginL - 8, 16, Qt::AlignRight | Qt::AlignVCenter,
                   QString::number(val) + " ns");
    }

    p.setFont(QFont("Courier New", 10, QFont::Bold));
    p.setPen(QColor(70, 130, 220));
    p.drawText(marginL, 14, 120, 16, Qt::AlignLeft, "■ Modular");
    p.setPen(QColor(220, 100, 70));
    p.drawText(marginL + 130, 14, 120, 16, Qt::AlignLeft, "■ Universal");

    p.setPen(QColor(180, 180, 180));
    p.setFont(QFont("Courier New", 9));
    p.drawText(marginL, marginT + chartH + 30, chartW, 16, Qt::AlignHCenter,
               "Search time comparison (75% load, 100 queries)");

    p.end();
    ui->labelChart->setPixmap(pix);
}

void MainWindow::appendLog(const QString& msg) {
    ui->memoLog->appendPlainText(msg);
}
