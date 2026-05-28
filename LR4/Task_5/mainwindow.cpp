#include "mainwindow.h"
#include <QHeaderView>
#include <QGroupBox>
#include <QFormLayout>
#include <cstdlib>
#include <ctime>

// ── вспомогательная функция ──────────────────────────────────────────
static QString vecStr(Vector<int>& v)
{
    if (v.empty()) return "[ ]";
    QString s = "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i) s += ", ";
        s += QString::number(v[i]);
    }
    return s + "]";
}

// ── конструктор ──────────────────────────────────────────────────────
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    setWindowTitle("Task 5 – Vector & Pair");
    resize(860, 700);

    tabs = new QTabWidget;
    buildMatrixTab();
    buildVectorTab();
    setCentralWidget(tabs);

    for (int i = 10; i <= 50; i += 10)
        swapVec.push_back(i);
}

// ════════════════════════════════════════════════════════════════════
//  ВКЛАДКА 1 — Pair / Матрицы
// ════════════════════════════════════════════════════════════════════
void MainWindow::buildMatrixTab()
{
    QWidget*     w   = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(w);
    lay->setSpacing(10);

    // Заголовок
    auto* title = new QLabel(
        "<b style='font-size:13px'>Объект: "
        "Pair&lt; Vector&lt;int&gt;, Vector&lt;Pair&lt;int,double&gt;&gt; &gt;</b>"
    );
    title->setAlignment(Qt::AlignCenter);
    lay->addWidget(title);

    // Nested pair
    auto* nestedBox = new QGroupBox("Демо: Pair< Pair<T,T>, Pair<T,T> >");
    auto* nestedLay = new QVBoxLayout(nestedBox);
    nestedPairLabel = new QLabel;
    nestedPairLabel->setAlignment(Qt::AlignCenter);
    nestedPairLabel->setStyleSheet(
        "font-family:monospace; font-size:12px; "
        "background:#eef6ff; padding:8px; border-radius:4px;"
    );
    nestedLay->addWidget(nestedPairLabel);
    lay->addWidget(nestedBox);

    // Кнопка
    generateMatrixBtn = new QPushButton("🔄  Сгенерировать новые данные");
    generateMatrixBtn->setFixedHeight(34);
    lay->addWidget(generateMatrixBtn);

    // Матрица 1
    auto* box1 = new QGroupBox(
        "Матрица 1 — первый аргумент pair:  Vector<int>"
    );
    auto* lay1 = new QVBoxLayout(box1);
    matrixTable1 = new QTableWidget;
    matrixTable1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    matrixTable1->setMinimumHeight(90);
    matrixTable1->setMaximumHeight(120);
    lay1->addWidget(matrixTable1);
    lay->addWidget(box1);

    // Матрица 2
    auto* box2 = new QGroupBox(
        "Матрица 2 — второй аргумент pair:  Vector< Pair<int,double> >"
    );
    auto* lay2 = new QVBoxLayout(box2);
    matrixTable2 = new QTableWidget;
    matrixTable2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    lay2->addWidget(matrixTable2);
    lay->addWidget(box2);

    tabs->addTab(w, "Pair / Матрицы");

    connect(generateMatrixBtn, &QPushButton::clicked, this, &MainWindow::generateMatrix);
    generateMatrix();
}

// ════════════════════════════════════════════════════════════════════
//  ВКЛАДКА 2 — Методы Vector
// ════════════════════════════════════════════════════════════════════
void MainWindow::buildVectorTab()
{
    QWidget*     w   = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(w);
    lay->setSpacing(8);

    // ── Текущий вектор ──────────────────────────────────────────────
    auto* vecBox = new QGroupBox("Текущий Vector<int>");
    auto* vecLay = new QVBoxLayout(vecBox);

    vectorTable = new QTableWidget(1, 0);
    vectorTable->setMaximumHeight(60);
    vectorTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    vectorTable->setVerticalHeaderLabels({"vec"});
    vecLay->addWidget(vectorTable);

    statsLabel = new QLabel;
    statsLabel->setStyleSheet(
        "font-family:monospace; color:#555; font-size:11px;"
    );
    vecLay->addWidget(statsLabel);
    lay->addWidget(vecBox);

    // ── Блок: Добавление / удаление ─────────────────────────────────
    auto* addBox = new QGroupBox("Добавление / удаление элементов");
    auto* addLay = new QHBoxLayout(addBox);

    // push_back
    auto* pbLay = new QVBoxLayout;
    auto* pbLabel = new QLabel("Значение:");
    pushValSpin = new QSpinBox; pushValSpin->setRange(-999, 999); pushValSpin->setValue(42);
    pushBackBtn = new QPushButton("push_back");
    pbLay->addWidget(pbLabel); pbLay->addWidget(pushValSpin); pbLay->addWidget(pushBackBtn);
    addLay->addLayout(pbLay);

    addLay->addSpacing(16);

    // pop_back
    popBackBtn = new QPushButton("pop_back\n(удалить последний)");
    popBackBtn->setFixedHeight(60);
    addLay->addWidget(popBackBtn);

    addLay->addSpacing(16);

    // insert
    auto* insLay = new QVBoxLayout;
    insLay->addWidget(new QLabel("Позиция:"));
    insertPosSpin = new QSpinBox; insertPosSpin->setRange(0, 999); insertPosSpin->setValue(0);
    insLay->addWidget(insertPosSpin);
    insLay->addWidget(new QLabel("Значение:"));
    insertValSpin = new QSpinBox; insertValSpin->setRange(-999, 999); insertValSpin->setValue(99);
    insLay->addWidget(insertValSpin);
    insertBtn = new QPushButton("insert");
    insLay->addWidget(insertBtn);
    addLay->addLayout(insLay);

    addLay->addSpacing(16);

    // erase
    auto* erLay = new QVBoxLayout;
    erLay->addWidget(new QLabel("Позиция:"));
    erasePosSpin = new QSpinBox; erasePosSpin->setRange(0, 999); erasePosSpin->setValue(0);
    erLay->addWidget(erasePosSpin);
    eraseBtn = new QPushButton("erase\n(удалить по индексу)");
    eraseBtn->setFixedHeight(44);
    erLay->addWidget(eraseBtn);
    addLay->addLayout(erLay);

    lay->addWidget(addBox);

    // ── Блок: Утилиты ───────────────────────────────────────────────
    auto* utilBox = new QGroupBox("Утилиты");
    auto* utilLay = new QHBoxLayout(utilBox);

    // resize
    auto* rzLay = new QVBoxLayout;
    rzLay->addWidget(new QLabel("Новый размер:"));
    resizeSpin = new QSpinBox; resizeSpin->setRange(0, 30); resizeSpin->setValue(10);
    rzLay->addWidget(resizeSpin);
    resizeBtn = new QPushButton("resize");
    rzLay->addWidget(resizeBtn);
    utilLay->addLayout(rzLay);

    utilLay->addSpacing(8);

    assignBtn  = new QPushButton("assign\n4 элемента = 99");
    shrinkBtn  = new QPushButton("shrink_to_fit\n(обрезать ёмкость)");
    swapBtn    = new QPushButton("swap\nс [10,20,30,40,50]");
    clearBtn   = new QPushButton("clear\n(очистить)");
    resetBtn   = new QPushButton("↺  Сбросить\n(начальный вектор)");

    for (auto* b : {assignBtn, shrinkBtn, swapBtn, clearBtn, resetBtn})
        b->setFixedHeight(50);

    utilLay->addWidget(assignBtn);
    utilLay->addWidget(shrinkBtn);
    utilLay->addWidget(swapBtn);
    utilLay->addWidget(clearBtn);
    utilLay->addWidget(resetBtn);
    lay->addWidget(utilBox);

    // ── Блок: Сортировка и поиск ────────────────────────────────────
    auto* sortBox = new QGroupBox("Сортировка и поиск");
    auto* sortLay = new QHBoxLayout(sortBox);

    sortBtn = new QPushButton("quickSort\n(отсортировать)");
    sortBtn->setFixedHeight(50);
    sortLay->addWidget(sortBtn);

    sortLay->addSpacing(8);

    auto* srLay = new QVBoxLayout;
    srLay->addWidget(new QLabel("Искать число:"));
    searchSpin = new QSpinBox; searchSpin->setRange(-999, 999); searchSpin->setValue(5);
    srLay->addWidget(searchSpin);
    searchBtn = new QPushButton("binarySearch\n(сортирует автоматически)");
    searchBtn->setFixedHeight(44);
    srLay->addWidget(searchBtn);
    sortLay->addLayout(srLay);

    lay->addWidget(sortBox);

    // ── Блок: Итераторы и обращение к элементам ─────────────────────
    auto* iterBox = new QGroupBox("Итераторы и обращение к элементам");
    auto* iterLay = new QHBoxLayout(iterBox);

    iteratorBtn    = new QPushButton("iterator\n(обход + сумма)");
    reverseIterBtn = new QPushButton("reverse_iterator\n(обратный обход)");
    frontBackBtn   = new QPushButton("front / back / at\n(первый, последний, по индексу)");

    for (auto* b : {iteratorBtn, reverseIterBtn, frontBackBtn})
        b->setFixedHeight(50);

    iterLay->addWidget(iteratorBtn);
    iterLay->addWidget(reverseIterBtn);
    iterLay->addWidget(frontBackBtn);
    lay->addWidget(iterBox);

    // ── Лог ─────────────────────────────────────────────────────────
    lay->addWidget(new QLabel("<b>Лог операций:</b>"));
    logEdit = new QTextEdit;
    logEdit->setReadOnly(true);
    logEdit->setFont(QFont("Monospace", 9));
    lay->addWidget(logEdit);

    tabs->addTab(w, "Методы Vector");

    // Подключения
    connect(pushBackBtn,    &QPushButton::clicked, this, &MainWindow::doPushBack);
    connect(popBackBtn,     &QPushButton::clicked, this, &MainWindow::doPopBack);
    connect(insertBtn,      &QPushButton::clicked, this, &MainWindow::doInsert);
    connect(eraseBtn,       &QPushButton::clicked, this, &MainWindow::doErase);
    connect(clearBtn,       &QPushButton::clicked, this, &MainWindow::doClear);
    connect(sortBtn,        &QPushButton::clicked, this, &MainWindow::doSort);
    connect(searchBtn,      &QPushButton::clicked, this, &MainWindow::doSearch);
    connect(resizeBtn,      &QPushButton::clicked, this, &MainWindow::doResize);
    connect(swapBtn,        &QPushButton::clicked, this, &MainWindow::doSwap);
    connect(assignBtn,      &QPushButton::clicked, this, &MainWindow::doAssign);
    connect(shrinkBtn,      &QPushButton::clicked, this, &MainWindow::doShrink);
    connect(iteratorBtn,    &QPushButton::clicked, this, &MainWindow::doIterator);
    connect(reverseIterBtn, &QPushButton::clicked, this, &MainWindow::doReverseIter);
    connect(frontBackBtn,   &QPushButton::clicked, this, &MainWindow::doFrontBack);
    connect(resetBtn,       &QPushButton::clicked, this, &MainWindow::doReset);

    doReset(); // начальные данные без лога
    log("Вектор инициализирован: нажимайте любые кнопки!");
}

// ════════════════════════════════════════════════════════════════════
//  Обновление UI
// ════════════════════════════════════════════════════════════════════
void MainWindow::updateMatrixTables()
{
    Vector<int>& v1 = complexData.first;
    const int cols = 5;
    int rows = (static_cast<int>(v1.size()) + cols - 1) / cols;
    matrixTable1->setRowCount(rows);
    matrixTable1->setColumnCount(cols);
    QStringList hh;
    for (int c = 0; c < cols; c++) hh << QString("[%1]").arg(c);
    matrixTable1->setHorizontalHeaderLabels(hh);
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
        {
            size_t idx = r * cols + c;
            matrixTable1->setItem(r, c, new QTableWidgetItem(
                idx < v1.size() ? QString::number(v1[idx]) : ""
            ));
        }

    Vector<Pair<int,double>>& v2 = complexData.second;
    matrixTable2->setRowCount(static_cast<int>(v2.size()));
    matrixTable2->setColumnCount(2);
    matrixTable2->setHorizontalHeaderLabels({"first (int)", "second (double)"});
    for (size_t i = 0; i < v2.size(); i++)
    {
        matrixTable2->setItem(static_cast<int>(i), 0,
            new QTableWidgetItem(QString::number(v2[i].first)));
        matrixTable2->setItem(static_cast<int>(i), 1,
            new QTableWidgetItem(QString::number(v2[i].second, 'f', 2)));
    }
}

void MainWindow::updateVectorTable()
{
    int n = static_cast<int>(vec.size());
    vectorTable->setRowCount(1);
    vectorTable->setColumnCount(n);
    QStringList hh;
    for (int i = 0; i < n; i++) hh << QString("[%1]").arg(i);
    vectorTable->setHorizontalHeaderLabels(hh);
    for (int i = 0; i < n; i++)
        vectorTable->setItem(0, i, new QTableWidgetItem(QString::number(vec[i])));
}

void MainWindow::updateStats()
{
    statsLabel->setText(
        QString("  size = %1   |   capacity = %2   |   empty = %3   |   max_size = %4")
        .arg(vec.size()).arg(vec.capacity())
        .arg(vec.empty() ? "true" : "false")
        .arg(vec.max_size())
    );
    // Обновляем максимальные значения спиннеров позиций
    int sz = static_cast<int>(vec.size());
    insertPosSpin->setMaximum(qMax(0, sz));
    erasePosSpin->setMaximum(qMax(0, sz - 1));
}

void MainWindow::log(const QString& msg)
{
    logEdit->append(msg);
}

// ════════════════════════════════════════════════════════════════════
//  Слоты — вкладка 1
// ════════════════════════════════════════════════════════════════════
void MainWindow::generateMatrix()
{
    complexData.first.clear();
    for (int i = 0; i < 10; i++)
        complexData.first.push_back(std::rand() % 100);

    complexData.second.clear();
    for (int i = 0; i < 8; i++)
        complexData.second.push_back(Pair<int,double>(i * 2, i * 1.5));

    Pair<Pair<int,int>, Pair<int,int>> nested(
        Pair<int,int>(std::rand() % 10, std::rand() % 10),
        Pair<int,int>(std::rand() % 10, std::rand() % 10)
    );
    nestedPairLabel->setText(
        QString("first = (%1, %2)     second = (%3, %4)")
        .arg(nested.first.first).arg(nested.first.second)
        .arg(nested.second.first).arg(nested.second.second)
    );

    updateMatrixTables();
}

// ════════════════════════════════════════════════════════════════════
//  Слоты — вкладка 2
// ════════════════════════════════════════════════════════════════════
void MainWindow::doReset()
{
    vec.clear();
    for (int i : {5, 3, 8, 1, 9, 2, 7}) vec.push_back(i);
    updateVectorTable(); updateStats();
    log("↺  Сброс → " + vecStr(vec));
}

void MainWindow::doPushBack()
{
    int val = pushValSpin->value();
    vec.push_back(val);
    updateVectorTable(); updateStats();
    log(QString("push_back(%1)  →  %2").arg(val).arg(vecStr(vec)));
}

void MainWindow::doPopBack()
{
    if (vec.empty()) { log("pop_back: вектор пуст!"); return; }
    int removed = vec.back();
    vec.pop_back();
    updateVectorTable(); updateStats();
    log(QString("pop_back  удалено: %1  →  %2").arg(removed).arg(vecStr(vec)));
}

void MainWindow::doInsert()
{
    size_t pos = static_cast<size_t>(insertPosSpin->value());
    int    val = insertValSpin->value();
    if (pos > vec.size()) pos = vec.size();
    vec.insert(pos, val);
    updateVectorTable(); updateStats();
    log(QString("insert(%1, %2)  →  %3").arg(pos).arg(val).arg(vecStr(vec)));
}

void MainWindow::doErase()
{
    if (vec.empty()) { log("erase: вектор пуст!"); return; }
    size_t pos = static_cast<size_t>(erasePosSpin->value());
    if (pos >= vec.size()) pos = vec.size() - 1;
    int removed = vec[pos];
    vec.erase(pos);
    updateVectorTable(); updateStats();
    log(QString("erase(%1)  удалено: %2  →  %3").arg(pos).arg(removed).arg(vecStr(vec)));
}

void MainWindow::doClear()
{
    vec.clear();
    updateVectorTable(); updateStats();
    log("clear()  →  [ ]   size=0, capacity=" + QString::number(vec.capacity()));
}

void MainWindow::doSort()
{
    if (vec.empty()) { log("quickSort: вектор пуст!"); return; }
    quickSort(vec, 0, static_cast<int>(vec.size()) - 1, [](const Vector<int>&){});
    updateVectorTable(); updateStats();
    log("quickSort  →  " + vecStr(vec));
}

void MainWindow::doSearch()
{
    // Сортируем автоматически если нужно
    if (!vec.empty())
    {
        bool sorted = true;
        for (size_t i = 1; i < vec.size(); i++)
            if (vec[i] < vec[i-1]) { sorted = false; break; }
        if (!sorted)
        {
            quickSort(vec, 0, static_cast<int>(vec.size()) - 1, [](const Vector<int>&){});
            updateVectorTable(); updateStats();
            log("(автоматически отсортировано перед поиском)  →  " + vecStr(vec));
        }
    }
    int x   = searchSpin->value();
    int idx = binarySearch(vec, x);
    if (idx == -1)
        log(QString("binarySearch(%1)  →  не найден").arg(x));
    else
        log(QString("binarySearch(%1)  →  найден на индексе [%2]").arg(x).arg(idx));
}

void MainWindow::doResize()
{
    int n = resizeSpin->value();
    log(QString("resize(%1)  size: %2 → %3").arg(n).arg(vec.size()).arg(n));
    vec.resize(static_cast<size_t>(n), 0);
    updateVectorTable(); updateStats();
    log("  " + vecStr(vec));
}

void MainWindow::doSwap()
{
    log("swap:");
    log("  до:    vec     = " + vecStr(vec));
    log("  до:    swapVec = " + vecStr(swapVec));
    vec.swap(swapVec);
    updateVectorTable(); updateStats();
    log("  после: vec     = " + vecStr(vec));
    log("  после: swapVec = " + vecStr(swapVec));
}

void MainWindow::doAssign()
{
    vec.assign(4, 99);
    updateVectorTable(); updateStats();
    log("assign(4, 99)  →  " + vecStr(vec));
}

void MainWindow::doShrink()
{
    size_t before = vec.capacity();
    vec.shrink_to_fit();
    updateStats();
    log(QString("shrink_to_fit  capacity: %1 → %2").arg(before).arg(vec.capacity()));
}

void MainWindow::doIterator()
{
    if (vec.empty()) { log("iterator: вектор пуст!"); return; }
    int sum = 0;
    QString items;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        sum += *it;
        if (!items.isEmpty()) items += ", ";
        items += QString::number(*it);
    }
    log(QString("iterator (begin→end): [%1]  сумма = %2").arg(items).arg(sum));
    // показываем emplace_back
    vec.emplace_back(sum % 10);
    updateVectorTable(); updateStats();
    log(QString("  emplace_back(%1)  →  %2").arg(sum % 10).arg(vecStr(vec)));
}

void MainWindow::doReverseIter()
{
    if (vec.empty()) { log("reverse_iterator: вектор пуст!"); return; }
    QString items;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        if (!items.isEmpty()) items += ", ";
        items += QString::number(*it);
    }
    log("reverse_iterator (rbegin→rend): [" + items + "]");
}

void MainWindow::doFrontBack()
{
    if (vec.empty()) { log("front/back: вектор пуст!"); return; }
    log(QString("front() = %1   back() = %2   at(0) = %3")
        .arg(vec.front()).arg(vec.back()).arg(vec.at(0)));
}
