#include "mainwindow.h"
#include "mystring.h"
#include <QApplication>
#include <QFont>
#include <QPalette>
#include <QScrollBar>
#include <cstring>
#include <cerrno>
#include <QString>
#include <QChar>
#include <QLibrary>

typedef size_t (*StrlenFunc)(const char*);

static const char* STYLE = R"(
QMainWindow {
    background: #1a1d23;
}
QTabWidget::pane {
    border: 1px solid #2e3240;
    background: #1e2130;
    border-radius: 4px;
}
QTabBar::tab {
    background: #252836;
    color: #8892a4;
    padding: 8px 18px;
    border: 1px solid #2e3240;
    border-bottom: none;
    border-radius: 4px 4px 0 0;
    font-weight: 600;
    font-size: 12px;
}
QTabBar::tab:selected {
    background: #2d6a9f;
    color: #ffffff;
}
QTabBar::tab:hover:!selected {
    background: #2e3240;
    color: #c0cad8;
}
QGroupBox {
    border: 1px solid #2e3240;
    border-radius: 6px;
    margin-top: 14px;
    padding: 8px;
    background: #252836;
    color: #c0cad8;
    font-weight: 700;
    font-size: 12px;
}
QGroupBox::title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 6px;
    color: #58a6ff;
}
QLineEdit {
    background: #1a1d23;
    border: 1px solid #3a3f52;
    border-radius: 4px;
    color: #e0e8f0;
    padding: 4px 8px;
    font-family: 'Consolas', 'Courier New', monospace;
    font-size: 13px;
    selection-background-color: #2d6a9f;
}
QLineEdit:focus {
    border-color: #58a6ff;
}
QSpinBox {
    background: #1a1d23;
    border: 1px solid #3a3f52;
    border-radius: 4px;
    color: #e0e8f0;
    padding: 4px 8px;
    font-size: 13px;
}
QSpinBox:focus { border-color: #58a6ff; }
QPushButton {
    background: #2d6a9f;
    color: #ffffff;
    border: none;
    border-radius: 5px;
    padding: 7px 18px;
    font-weight: 700;
    font-size: 12px;
}
QPushButton:hover   { background: #3a80bb; }
QPushButton:pressed { background: #1e5080; }
QPushButton#runAll {
    background: #2ea043;
    font-size: 13px;
    padding: 10px 28px;
}
QPushButton#runAll:hover { background: #3cb854; }
QTextEdit {
    background: #0d1117;
    color: #c9d1d9;
    border: 1px solid #2e3240;
    border-radius: 4px;
    font-family: 'Consolas', 'Courier New', monospace;
    font-size: 12px;
}
QLabel {
    color: #8892a4;
    font-size: 12px;
}
QScrollBar:vertical {
    background: #1a1d23;
    width: 8px;
}
QScrollBar::handle:vertical {
    background: #3a3f52;
    border-radius: 4px;
}
)";



QGroupBox* MainWindow::makeGroup(const QString& title, QLayout* layout)
{
    auto* g = new QGroupBox(title);
    g->setLayout(layout);
    return g;
}

QWidget* MainWindow::makeRow(const QString& labelText, QWidget* widget, int labelWidth)
{
    auto* row = new QWidget;
    auto* h   = new QHBoxLayout(row);
    h->setContentsMargins(0, 2, 0, 2);
    auto* lbl = new QLabel(labelText);
    lbl->setFixedWidth(labelWidth);
    h->addWidget(lbl);
    h->addWidget(widget, 1);
    return row;
}

void MainWindow::appendResult(QTextEdit* log, const QString& func,
                              const QString& input, const QString& result, bool ok)
{
    QString color = ok ? "#3fb950" : "#f85149";
    QString html  = QString(
        "<span style='color:#58a6ff;font-weight:bold;'>%1</span>"
        "(<span style='color:#ffa657;'>%2</span>) "
        "→ <span style='color:%3;'>%4</span>"
    ).arg(func, input, color, result);
    log->append(html);
    log->verticalScrollBar()->setValue(log->verticalScrollBar()->maximum());
}

// ═══════════════════════════════════════════════════════════════
//  Constructor
// ═══════════════════════════════════════════════════════════════
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("MyString Library — Демонстрационный стенд");
    setMinimumSize(900, 680);
    setStyleSheet(STYLE);

    auto* tabs = new QTabWidget;
    tabs->addTab(buildMemoryTab(),  "🗄  Память");
    tabs->addTab(buildCopyTab(),    "📋 Копирование");
    tabs->addTab(buildConcatTab(),  "➕ Конкатенация");
    tabs->addTab(buildCompareTab(), "⚖  Сравнение");
    tabs->addTab(buildMiscTab(),    "🔧 Разное");
    tabs->addTab(buildObjectTab(),  "🏗  Объект MyString");
    tabs->addTab(buildTestsTab(),   "✅ Тесты");

    setCentralWidget(tabs);
}

// ═══════════════════════════════════════════════════════════════
//  TAB: Memory functions
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildMemoryTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(10);

    // memcpy / memmove inputs
    memSrc_ = new QLineEdit("Hello, World!");
    memDst_ = new QLineEdit("XXXXXXXXXXXXX");
    memN_   = new QSpinBox;
    memN_->setRange(0, 256); memN_->setValue(5);

    auto* cpyGrid = new QVBoxLayout;
    cpyGrid->addWidget(makeRow("Источник (s2):", memSrc_));
    cpyGrid->addWidget(makeRow("Приёмник (s1):", memDst_));
    cpyGrid->addWidget(makeRow("n байт:",        memN_));

    auto* btnRow1 = new QHBoxLayout;
    auto* btnMcpy  = new QPushButton("Выполнить memcpy");
    auto* btnMmove = new QPushButton("Выполнить memmove");
    auto* btnMcmp  = new QPushButton("Выполнить memcmp");
    btnRow1->addWidget(btnMcpy);
    btnRow1->addWidget(btnMmove);
    btnRow1->addWidget(btnMcmp);
    cpyGrid->addLayout(btnRow1);

    vbox->addWidget(makeGroup("memcpy / memmove / memcmp", cpyGrid));

    // memset
    memSetChar_ = new QLineEdit("*");
    memSetChar_->setMaxLength(1);
    memSetN_ = new QSpinBox;
    memSetN_->setRange(0, 64); memSetN_->setValue(10);

    auto* setGrid = new QVBoxLayout;
    setGrid->addWidget(makeRow("Символ:",   memSetChar_));
    setGrid->addWidget(makeRow("Размер n:", memSetN_));
    auto* btnMset = new QPushButton("Выполнить memset");
    setGrid->addWidget(btnMset);

    vbox->addWidget(makeGroup("memset", setGrid));

    memLog_ = new QTextEdit;
    memLog_->setReadOnly(true);
    memLog_->setMinimumHeight(220);
    vbox->addWidget(new QLabel("📜 Журнал выполнения:"));
    vbox->addWidget(memLog_, 1);

    connect(btnMcpy,  &QPushButton::clicked, this, &MainWindow::doMemcpy);
    connect(btnMmove, &QPushButton::clicked, this, &MainWindow::doMemmove);
    connect(btnMcmp,  &QPushButton::clicked, this, &MainWindow::doMemcmp);
    connect(btnMset,  &QPushButton::clicked, this, &MainWindow::doMemset);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  TAB: Copy functions
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildCopyTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(10);

    cpySrc_ = new QLineEdit("OpenSource");
    cpyDst_ = new QLineEdit("XXXXXXXXXX");
    cpyN_   = new QSpinBox;
    cpyN_->setRange(0, 64); cpyN_->setValue(4);

    auto* grid = new QVBoxLayout;
    grid->addWidget(makeRow("Источник (s2):", cpySrc_));
    grid->addWidget(makeRow("Приёмник (s1):", cpyDst_));
    grid->addWidget(makeRow("n для strncpy:", cpyN_));

    auto* btnRow = new QHBoxLayout;
    auto* btnCpy  = new QPushButton("strcpy");
    auto* btnNcpy = new QPushButton("strncpy(n)");
    btnRow->addWidget(btnCpy);
    btnRow->addWidget(btnNcpy);
    grid->addLayout(btnRow);

    vbox->addWidget(makeGroup("Функции копирования строк", grid));

    copyLog_ = new QTextEdit;
    copyLog_->setReadOnly(true);
    vbox->addWidget(new QLabel("📜 Журнал:"));
    vbox->addWidget(copyLog_, 1);

    connect(btnCpy,  &QPushButton::clicked, this, &MainWindow::doStrcpy);
    connect(btnNcpy, &QPushButton::clicked, this, &MainWindow::doStrncpy);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  TAB: Concat
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildConcatTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(10);

    catDst_ = new QLineEdit("Hello, ");
    catSrc_ = new QLineEdit("World!");
    catN_   = new QSpinBox;
    catN_->setRange(0, 64); catN_->setValue(3);

    auto* grid = new QVBoxLayout;
    grid->addWidget(makeRow("База (s1):",     catDst_));
    grid->addWidget(makeRow("Добавление (s2):", catSrc_));
    grid->addWidget(makeRow("n для strncat:", catN_));

    auto* btnRow = new QHBoxLayout;
    auto* btnCat  = new QPushButton("strcat");
    auto* btnNcat = new QPushButton("strncat(n)");
    btnRow->addWidget(btnCat);
    btnRow->addWidget(btnNcat);
    grid->addLayout(btnRow);

    vbox->addWidget(makeGroup("Конкатенация строк", grid));

    catLog_ = new QTextEdit;
    catLog_->setReadOnly(true);
    vbox->addWidget(new QLabel("📜 Журнал:"));
    vbox->addWidget(catLog_, 1);

    connect(btnCat,  &QPushButton::clicked, this, &MainWindow::doStrcat);
    connect(btnNcat, &QPushButton::clicked, this, &MainWindow::doStrncat);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  TAB: Compare
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildCompareTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(10);

    cmpS1_ = new QLineEdit("apple");
    cmpS2_ = new QLineEdit("application");
    cmpN_  = new QSpinBox;
    cmpN_->setRange(0, 64); cmpN_->setValue(5);

    auto* grid = new QVBoxLayout;
    grid->addWidget(makeRow("Строка s1:", cmpS1_));
    grid->addWidget(makeRow("Строка s2:", cmpS2_));
    grid->addWidget(makeRow("n для *ncmp:", cmpN_));

    auto* btnRow = new QHBoxLayout;
    auto* b1 = new QPushButton("strcmp");
    auto* b2 = new QPushButton("strcoll");
    auto* b3 = new QPushButton("strncmp(n)");
    auto* b4 = new QPushButton("strxfrm");
    btnRow->addWidget(b1); btnRow->addWidget(b2);
    btnRow->addWidget(b3); btnRow->addWidget(b4);
    grid->addLayout(btnRow);

    vbox->addWidget(makeGroup("Функции сравнения", grid));

    cmpLog_ = new QTextEdit;
    cmpLog_->setReadOnly(true);
    vbox->addWidget(new QLabel("📜 Журнал (возврат: <0 = s1<s2, 0 = равны, >0 = s1>s2):"));
    vbox->addWidget(cmpLog_, 1);

    connect(b1, &QPushButton::clicked, this, &MainWindow::doStrcmp);
    connect(b2, &QPushButton::clicked, this, &MainWindow::doStrcoll);
    connect(b3, &QPushButton::clicked, this, &MainWindow::doStrncmp);
    connect(b4, &QPushButton::clicked, this, &MainWindow::doStrxfrm);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  TAB: Misc
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildMiscTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(10);

    // strtok
    tokStr_   = new QLineEdit("one,two,,three,four");
    tokDelim_ = new QLineEdit(",");

    auto* tokGrid = new QVBoxLayout;
    tokGrid->addWidget(makeRow("Строка:", tokStr_));
    tokGrid->addWidget(makeRow("Разделители:", tokDelim_));
    auto* btnTok = new QPushButton("strtok — разбить на токены");
    tokGrid->addWidget(btnTok);
    vbox->addWidget(makeGroup("strtok", tokGrid));

    // strerror + strlen
    errNum_ = new QSpinBox;
    errNum_->setRange(0, 150); errNum_->setValue(22);

    auto* miscGrid = new QVBoxLayout;
    miscGrid->addWidget(makeRow("Код ошибки (errno):", errNum_));
    auto* btnRow2 = new QHBoxLayout;
    auto* btnErr = new QPushButton("strerror");
    auto* btnLen = new QPushButton("strlen(tokStr)");
    btnRow2->addWidget(btnErr);
    btnRow2->addWidget(btnLen);
    miscGrid->addLayout(btnRow2);
    vbox->addWidget(makeGroup("strerror / strlen", miscGrid));

    miscLog_ = new QTextEdit;
    miscLog_->setReadOnly(true);
    vbox->addWidget(new QLabel("📜 Журнал:"));
    vbox->addWidget(miscLog_, 1);

    connect(btnTok, &QPushButton::clicked, this, &MainWindow::doStrtok);
    connect(btnErr, &QPushButton::clicked, this, &MainWindow::doStrerror);
    connect(btnLen, &QPushButton::clicked, this, &MainWindow::doStrlen);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  TAB: MyString object demo
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildObjectTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(10);

    objS1_ = new QLineEdit("Hello");
    objS2_ = new QLineEdit("World");

    auto* grid = new QVBoxLayout;
    grid->addWidget(makeRow("MyString s1:", objS1_));
    grid->addWidget(makeRow("MyString s2:", objS2_));

    auto* btnRun = new QPushButton("Запустить демо (конструкторы, оператор=, +, итератор)");
    grid->addWidget(btnRun);
    vbox->addWidget(makeGroup("Демонстрация объекта MyString (Правило трёх)", grid));

    objLog_ = new QTextEdit;
    objLog_->setReadOnly(true);
    vbox->addWidget(new QLabel("📜 Журнал:"));
    vbox->addWidget(objLog_, 1);

    connect(btnRun, &QPushButton::clicked, this, &MainWindow::doObjDemo);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  TAB: Tests
// ═══════════════════════════════════════════════════════════════
QWidget* MainWindow::buildTestsTab()
{
    auto* w    = new QWidget;
    auto* vbox = new QVBoxLayout(w);
    vbox->setSpacing(12);

    auto* info = new QLabel(
        "Нажмите кнопку ниже — автоматически выполнятся все функциональные тесты.\n"
        "✅ зелёный = тест пройден,  ❌ красный = тест провален."
    );
    info->setWordWrap(true);
    vbox->addWidget(info);

    auto* btnAll = new QPushButton("▶  Запустить все тесты");
    btnAll->setObjectName("runAll");
    vbox->addWidget(btnAll);

    testLog_ = new QTextEdit;
    testLog_->setReadOnly(true);
    vbox->addWidget(testLog_, 1);

    connect(btnAll, &QPushButton::clicked, this, &MainWindow::runAllTests);

    return w;
}

// ═══════════════════════════════════════════════════════════════
//  SLOTS — Memory
// ═══════════════════════════════════════════════════════════════
void MainWindow::doMemcpy()
{
    QByteArray src = memSrc_->text().toUtf8();
    QByteArray dst = memDst_->text().toUtf8();
    int n = memN_->value();

    // Make dst large enough
    while (dst.size() < (int)src.size() + 1) dst.append('\0');

    MyString::Memcpy(dst.data(), src.data(), qMin(n, (int)src.size()));
    dst.append('\0');

    QString info = QString("src=\"%1\", dst=\"%2\", n=%3")
        .arg(memSrc_->text(), memDst_->text()).arg(n);
    appendResult(memLog_, "memcpy", info,
                 QString("dst → \"%1\"").arg(QString::fromUtf8(dst)));
}

void MainWindow::doMemmove()
{
    QByteArray buf = memSrc_->text().toUtf8();
    buf.append(QByteArray(16, '\0'));
    int n = qMin(memN_->value(), (int)memSrc_->text().size());

    // Overlap demo: copy first n bytes forward by 2
    MyString::Memmove(buf.data() + 2, buf.data(), n);

    QString info = QString("src=\"%1\", overlap shift=2, n=%2")
        .arg(memSrc_->text()).arg(n);
    appendResult(memLog_, "memmove", info,
                 QString("buf → \"%1\"").arg(QString::fromUtf8(buf.data())));
}

void MainWindow::doMemcmp()
{
    QByteArray a = memSrc_->text().toUtf8();
    QByteArray b = memDst_->text().toUtf8();
    int n = memN_->value();
    int r = MyString::Memcmp(a.data(), b.data(),
                             qMin(n, qMin((int)a.size(), (int)b.size())));

    QString info = QString("s1=\"%1\", s2=\"%2\", n=%3")
        .arg(memSrc_->text(), memDst_->text()).arg(n);
    QString res  = QString("ret=%1 (%2)").arg(r)
        .arg(r < 0 ? "s1 < s2" : r > 0 ? "s1 > s2" : "равны");
    appendResult(memLog_, "memcmp", info, res);
}

void MainWindow::doMemset()
{
    int n = memSetN_->value();
    QByteArray buf(n, '\0');
    char ch = memSetChar_->text().isEmpty() ? '*'
                                            : memSetChar_->text().at(0).toLatin1();
    MyString::Memset(buf.data(), ch, n);
    buf.append('\0');

    appendResult(memLog_, "memset",
                 QString("c='%1', n=%2").arg(ch).arg(n),
                 QString("\"%1\"").arg(QString::fromLatin1(buf.data())));
}

// ═══════════════════════════════════════════════════════════════
//  SLOTS — Copy
// ═══════════════════════════════════════════════════════════════
void MainWindow::doStrcpy()
{
    QByteArray src = cpySrc_->text().toUtf8();
    QByteArray dst(src.size() + 1, '\0');
    MyString::Strcpy(dst.data(), src.data());

    appendResult(copyLog_, "strcpy",
                 QString("s2=\"%1\"").arg(cpySrc_->text()),
                 QString("s1 → \"%1\"").arg(QString::fromUtf8(dst)));
}

void MainWindow::doStrncpy()
{
    QByteArray src = cpySrc_->text().toUtf8();
    int n = cpyN_->value();
    QByteArray dst(n + 1, '\0');
    MyString::Strncpy(dst.data(), src.data(), n);

    appendResult(copyLog_, "strncpy",
                 QString("s2=\"%1\", n=%2").arg(cpySrc_->text()).arg(n),
                 QString("s1 → \"%1\"").arg(QString::fromUtf8(dst)));
}

// ═══════════════════════════════════════════════════════════════
//  SLOTS — Concat
// ═══════════════════════════════════════════════════════════════
void MainWindow::doStrcat()
{
    QByteArray base = catDst_->text().toUtf8();
    QByteArray add  = catSrc_->text().toUtf8();
    base.resize(base.size() + add.size() + 1, '\0');

    MyString::Strcat(base.data(), add.data());

    appendResult(catLog_, "strcat",
                 QString("s1=\"%1\", s2=\"%2\"").arg(catDst_->text(), catSrc_->text()),
                 QString("s1 → \"%1\"").arg(QString::fromUtf8(base.data())));
}

void MainWindow::doStrncat()
{
    QByteArray base = catDst_->text().toUtf8();
    QByteArray add  = catSrc_->text().toUtf8();
    int n = catN_->value();
    base.resize(base.size() + n + 2, '\0');

    MyString::Strncat(base.data(), add.data(), n);

    appendResult(catLog_, "strncat",
                 QString("s1=\"%1\", s2=\"%2\", n=%3")
                 .arg(catDst_->text(), catSrc_->text()).arg(n),
                 QString("s1 → \"%1\"").arg(QString::fromUtf8(base.data())));
}

// ═══════════════════════════════════════════════════════════════
//  SLOTS — Compare
// ═══════════════════════════════════════════════════════════════
static QString cmpResult(int r)
{
    return QString("ret=%1 (%2)").arg(r)
        .arg(r < 0 ? "s1 < s2" : r > 0 ? "s1 > s2" : "равны");
}

void MainWindow::doStrcmp()
{
    QByteArray a = cmpS1_->text().toUtf8();
    QByteArray b = cmpS2_->text().toUtf8();
    int r = MyString::Strcmp(a.data(), b.data());
    appendResult(cmpLog_, "strcmp",
                 QString("\"%1\" vs \"%2\"").arg(cmpS1_->text(), cmpS2_->text()),
                 cmpResult(r));
}

void MainWindow::doStrcoll()
{
    QByteArray a = cmpS1_->text().toUtf8();
    QByteArray b = cmpS2_->text().toUtf8();
    int r = MyString::Strcoll(a.data(), b.data());
    appendResult(cmpLog_, "strcoll",
                 QString("\"%1\" vs \"%2\"").arg(cmpS1_->text(), cmpS2_->text()),
                 cmpResult(r));
}

void MainWindow::doStrncmp()
{
    QByteArray a = cmpS1_->text().toUtf8();
    QByteArray b = cmpS2_->text().toUtf8();
    int n = cmpN_->value();
    int r = MyString::Strncmp(a.data(), b.data(), n);
    appendResult(cmpLog_, "strncmp",
                 QString("\"%1\" vs \"%2\", n=%3").arg(cmpS1_->text(), cmpS2_->text()).arg(n),
                 cmpResult(r));
}

void MainWindow::doStrxfrm()
{
    QByteArray src = cmpS1_->text().toUtf8();
    size_t n = cmpN_->value();
    QByteArray dst(n + 1, '\0');
    size_t needed = MyString::Strxfrm(dst.data(), src.data(), n);
    appendResult(cmpLog_, "strxfrm",
                 QString("s2=\"%1\", n=%2").arg(cmpS1_->text()).arg((int)n),
                 QString("needed=%1, s1 → \"%2\"").arg((int)needed).arg(QString::fromUtf8(dst)));
}

// ═══════════════════════════════════════════════════════════════
//  SLOTS — Misc
// ═══════════════════════════════════════════════════════════════
void MainWindow::doStrtok()
{
    // Copy because strtok modifies in place
    QByteArray str   = tokStr_->text().toUtf8();
    QByteArray delim = tokDelim_->text().toUtf8();

    QStringList tokens;
    char* tok = MyString::Strtok(str.data(), delim.data());
    while (tok) {
        tokens << QString::fromUtf8(tok);
        tok = MyString::Strtok(nullptr, delim.data());
    }

    appendResult(miscLog_, "strtok",
                 QString("\"%1\", delim=\"%2\"").arg(tokStr_->text(), tokDelim_->text()),
                 QString("[%1]").arg(tokens.join(", ")));
}

void MainWindow::doStrerror()
{
    int code = errNum_->value();
    char* msg = MyString::Strerror(code);
    appendResult(miscLog_, "strerror",
                 QString("errnum=%1").arg(code),
                 QString::fromLocal8Bit(msg));
}

void MainWindow::doStrlen()
{
    QLibrary library("StringLib");

    if (!library.load())
    {
        appendResult(
            miscLog_,
            "DLL",
            "",
            "StringLib.dll not loaded",
            false
            );

        return;
    }

    auto strlenFunc =
        (StrlenFunc)library.resolve("ExportedStrlen");

    if (!strlenFunc)
    {
        appendResult(
            miscLog_,
            "resolve",
            "",
            "Function not found",
            false
            );

        library.unload();

        return;
    }

    QByteArray str = tokStr_->text().toUtf8();

    size_t len = strlenFunc(str.data());

    appendResult(
        miscLog_,
        "ExportedStrlen",
        QString("\"%1\"").arg(tokStr_->text()),
        QString("%1").arg((int)len)
        );

    library.unload();

    appendResult(
        miscLog_,
        "DLL",
        "",
        "StringLib.dll unloaded"
        );
}

// ═══════════════════════════════════════════════════════════════
//  SLOT — Object demo
// ═══════════════════════════════════════════════════════════════
void MainWindow::doObjDemo()
{
    objLog_->clear();
    auto log = [this](const QString& msg) {
        objLog_->append(msg);
    };

    QByteArray a = objS1_->text().toUtf8();
    QByteArray b = objS2_->text().toUtf8();

    log("<span style='color:#58a6ff;font-weight:bold;'>── Конструктор из C-строки ──</span>");
    MyString s1(a.data());
    MyString s2(b.data());
    log(QString("  s1(\"%1\") → size=%2, cap=%3")
        .arg(a.data()).arg((int)s1.size()).arg((int)s1.capacity()));
    log(QString("  s2(\"%1\") → size=%2, cap=%3")
        .arg(b.data()).arg((int)s2.size()).arg((int)s2.capacity()));

    log("<span style='color:#58a6ff;font-weight:bold;'>── Конструктор копирования [Правило 3] ──</span>");
    MyString s3(s1);
    log(QString("  s3(s1) → \"%1\"").arg(s3.c_str()));

    log("<span style='color:#58a6ff;font-weight:bold;'>── Оператор присваивания [Правило 3] ──</span>");
    MyString s4;
    s4 = s2;
    log(QString("  s4 = s2 → \"%1\"").arg(s4.c_str()));
    log("  Изменяем s2[0]='X' — s4 не должна измениться (глубокая копия):");
    s2[0] = 'X';
    log(QString("    s2 = \"%1\",  s4 = \"%2\"  %3")
        .arg(s2.c_str(), s4.c_str(),
             (s4[0] != 'X') ? "<span style='color:#3fb950;'>✅ глубокая копия</span>"
                            : "<span style='color:#f85149;'>❌ мелкая копия!</span>"));

    log("<span style='color:#58a6ff;font-weight:bold;'>── Оператор + (конкатенация) ──</span>");
    MyString s5 = s3 + MyString(" ") + s4;
    log(QString("  s3 + \" \" + s4 → \"%1\"").arg(s5.c_str()));

    log("<span style='color:#58a6ff;font-weight:bold;'>── Итератор (перебор символов) ──</span>");
    QString chars;
    for (auto it = s5.begin(); it != s5.end(); ++it)
        chars += QString("'%1' ").arg(*it);
    log("  " + chars);

    log("<span style='color:#58a6ff;font-weight:bold;'>── Range-based for через итератор ──</span>");
    QString upper;
    for (char c : s5)
        upper += QChar(c).toUpper();
    log(QString("  upper → \"%1\"").arg(upper));

    log("<span style='color:#58a6ff;font-weight:bold;'>── Операторы сравнения ──</span>");
    MyString aa("abc"), bb("abd");
    log(QString("  \"abc\" < \"abd\" → %1").arg((aa < bb) ? "true ✅" : "false ❌"));
    log(QString("  \"abc\" == \"abc\" → %1").arg((aa == MyString("abc")) ? "true ✅" : "false ❌"));
    log(QString("  \"abc\" != \"abd\" → %1").arg((aa != bb) ? "true ✅" : "false ❌"));

    log("<span style='color:#58a6ff;font-weight:bold;'>── reserve / resize ──</span>");
    MyString sr("Hi");
    sr.reserve(100);
    log(QString("  reserve(100) → cap=%1").arg((int)sr.capacity()));
    sr.resize(6, '!');
    log(QString("  resize(6,'!') → \"%1\"").arg(sr.c_str()));

    log("<br><span style='color:#3fb950;font-weight:bold;'>Демо завершено ✅</span>");
}

// ═══════════════════════════════════════════════════════════════
//  SLOT — All tests
// ═══════════════════════════════════════════════════════════════
void MainWindow::runAllTests()
{
    testLog_->clear();
    int pass = 0, fail = 0;

    auto check = [&](const QString& name, bool ok, const QString& detail = "") {
        QString icon  = ok ? "✅" : "❌";
        QString color = ok ? "#3fb950" : "#f85149";
        testLog_->append(QString(
            "<span style='color:%1;'>%2 %3</span>%4"
        ).arg(color, icon, name,
              detail.isEmpty() ? "" : QString(" — <span style='color:#8892a4;'>%1</span>").arg(detail)));
        if (ok) ++pass; else ++fail;
    };

    testLog_->append("<b style='color:#58a6ff;'>══ Тесты статических функций ══</b>");

    // ── strlen ──────────────────────────────────────────────────
    check("strlen(\"hello\")==5",   MyString::Strlen("hello") == 5);
    check("strlen(\"\")==0",        MyString::Strlen("") == 0);
    check("strlen(\"abc\")==3",     MyString::Strlen("abc") == 3);

    // ── memcpy ──────────────────────────────────────────────────
    {
        char dst[10] = {};
        MyString::Memcpy(dst, "abcde", 5);
        check("memcpy copies 5 bytes", std::string(dst,5) == "abcde");
    }

    // ── memmove (overlapping) ───────────────────────────────────
    {
        char buf[] = "ABCDE";
        MyString::Memmove(buf + 1, buf, 4); // shift right by 1
        check("memmove overlap shift-right", std::string(buf) == "AABCD", buf);
    }

    // ── memset ──────────────────────────────────────────────────
    {
        char buf[6] = {};
        MyString::Memset(buf, 'Z', 5);
        check("memset fills with 'Z'", std::string(buf,5) == "ZZZZZ");
    }

    // ── memcmp ──────────────────────────────────────────────────
    check("memcmp equal",    MyString::Memcmp("abc","abc",3) == 0);
    check("memcmp less",     MyString::Memcmp("abc","abd",3)  < 0);
    check("memcmp greater",  MyString::Memcmp("abd","abc",3)  > 0);
    check("memcmp n=0",      MyString::Memcmp("abc","xyz",0) == 0);

    // ── strcpy ──────────────────────────────────────────────────
    {
        char dst[32] = {};
        MyString::Strcpy(dst, "Hello");
        check("strcpy basic", std::string(dst) == "Hello");
    }

    // ── strncpy ─────────────────────────────────────────────────
    {
        char dst[8] = {'X','X','X','X','X','X','X','X'};
        MyString::Strncpy(dst, "Hello", 3);
        check("strncpy copies 3 chars", dst[0]=='H' && dst[1]=='e' && dst[2]=='l');
        check("strncpy pads with \\0 when src shorter", [](){
            char d[8]={};
            MyString::Strncpy(d, "Hi", 6);
            return d[2]=='\0' && d[3]=='\0' && d[4]=='\0' && d[5]=='\0';
        }());
    }

    // ── strcat ──────────────────────────────────────────────────
    {
        char buf[32] = "Hello, ";
        MyString::Strcat(buf, "World!");
        check("strcat basic", std::string(buf) == "Hello, World!");
    }

    // ── strncat ─────────────────────────────────────────────────
    {
        char buf[32] = "Hi ";
        MyString::Strncat(buf, "There!!!", 5);
        check("strncat n=5", std::string(buf) == "Hi There");
    }

    // ── strcmp ───────────────────────────────────────────────────
    check("strcmp equal",          MyString::Strcmp("abc","abc") == 0);
    check("strcmp less",           MyString::Strcmp("abc","abd")  < 0);
    check("strcmp greater",        MyString::Strcmp("abd","abc")  > 0);
    check("strcmp prefix shorter", MyString::Strcmp("ab","abc")   < 0);

    // ── strncmp ──────────────────────────────────────────────────
    check("strncmp equal prefix",  MyString::Strncmp("abcXX","abcYY",3) == 0);
    check("strncmp differ at n",   MyString::Strncmp("abcX","abcY",4)    < 0);

    // ── strtok ───────────────────────────────────────────────────
    {
        char buf[] = "one,two,,three";
        std::vector<std::string> toks;
        char* t = MyString::Strtok(buf, ",");
        while (t) { toks.push_back(t); t = MyString::Strtok(nullptr, ","); }
        check("strtok 3 tokens", toks.size() == 3 &&
              toks[0]=="one" && toks[1]=="two" && toks[2]=="three",
              QString("got %1 tokens").arg((int)toks.size()));
    }

    // ── strerror ─────────────────────────────────────────────────
    {
        char* msg = MyString::Strerror(EINVAL);
        check("strerror non-empty", msg && MyString::Strlen(msg) > 0, msg ? msg : "null");
    }

    testLog_->append("<br><b style='color:#58a6ff;'>══ Тесты объекта MyString ══</b>");

    // ── Constructors ─────────────────────────────────────────────
    {
        MyString s;
        check("default ctor — empty, size=0", s.size()==0 && std::string(s.c_str())=="");

        MyString s2("hello");
        check("ctor from C-str", std::string(s2.c_str())=="hello" && s2.size()==5);

        MyString s3(4,'*');
        check("ctor(n,c)", std::string(s3.c_str())=="****" && s3.size()==4);
    }

    // ── Rule of Three ────────────────────────────────────────────
    {
        MyString orig("deep");
        MyString copy(orig);                          // copy ctor
        copy[0] = 'D';
        check("copy ctor deep copy", orig[0]=='d', "orig unchanged after copy[0]='D'");

        MyString assigned;
        assigned = orig;                              // operator=
        orig[0] = 'X';
        check("operator= deep copy", std::string(assigned.c_str())=="deep",
              QString("assigned=\"%1\"").arg(assigned.c_str()));

        // self-assignment
        MyString sa("self");
        sa = sa;
        check("self-assignment guard", std::string(sa.c_str())=="self");
    }

    // ── Operators ────────────────────────────────────────────────
    {
        MyString a("Hello"), b(" World");
        MyString c = a + b;
        check("operator+ concat", std::string(c.c_str())=="Hello World");

        MyString x("abc"), y("abd");
        check("operator<",  x < y);
        check("operator>",  y > x);
        check("operator==", x == MyString("abc"));
        check("operator!=", x != y);
        check("operator<=", x <= y);
        check("operator>=", y >= x);
    }

    // ── Iterator ─────────────────────────────────────────────────
    {
        MyString s("test");
        std::string collected;
        for (auto it = s.begin(); it != s.end(); ++it)
            collected += *it;
        check("iterator forward traversal", collected == "test", collected.c_str());

        // range-based for
        std::string rb;
        for (char c : s) rb += c;
        check("range-based for via iterator", rb == "test");

        // iterator distance
        check("iterator distance", s.end()-s.begin() == 4);
    }

    // ── reserve / resize ────────────────────────────────────────
    {
        MyString s("Hi");
        s.reserve(50);
        check("reserve increases capacity", s.capacity() >= 50);
        check("reserve preserves content", std::string(s.c_str())=="Hi");

        s.resize(5, '!');
        check("resize extends with fill char", std::string(s.c_str())=="Hi!!!");
    }

    // ── at() bounds check ───────────────────────────────────────
    {
        MyString s("abc");
        bool threw = false;
        try { s.at(99); } catch (const std::out_of_range&) { threw = true; }
        check("at() throws out_of_range", threw);
    }

    // ── Summary ──────────────────────────────────────────────────
    testLog_->append("");
    testLog_->append(QString(
        "<b>Итого: <span style='color:#3fb950;'>%1 пройдено</span>  "
        "<span style='color:%2;'>%3 провалено</span></b>"
    ).arg(pass).arg(fail ? "#f85149" : "#3fb950").arg(fail));

    if (fail == 0)
        testLog_->append("<span style='color:#3fb950;font-size:14px;'>🎉 Все тесты пройдены!</span>");
    else
        testLog_->append("<span style='color:#f85149;'>⚠ Есть провалившиеся тесты.</span>");
}
