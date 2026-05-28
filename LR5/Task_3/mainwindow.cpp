#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QFont>
#include <QSplitter>
#include <QScrollArea>
#include <QString>
#include <QMessageBox>
#include <stdexcept>

// ──────────────────────────────────────────────
// Constructor / UI setup
// ──────────────────────────────────────────────
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("BitSet Visualizer");
    setMinimumSize(860, 640);

    // ── Central widget & top-level layout ──
    auto* central = new QWidget(this);
    setCentralWidget(central);
    auto* root = new QVBoxLayout(central);
    root->setSpacing(10);
    root->setContentsMargins(12, 12, 12, 12);

    // ── Create BitSet group ──
    auto* grpCreate = new QGroupBox("1. Создать BitSet");
    auto* layCreate = new QHBoxLayout(grpCreate);
    layCreate->addWidget(new QLabel("Размер (биты):"));
    spinSize_ = new QSpinBox; spinSize_->setRange(1, 256); spinSize_->setValue(8);
    layCreate->addWidget(spinSize_);
    layCreate->addWidget(new QLabel("Начальное значение (ULL):"));
    editInitVal_ = new QLineEdit("0"); editInitVal_->setMaximumWidth(100);
    layCreate->addWidget(editInitVal_);
    btnCreate_ = new QPushButton("Создать"); btnCreate_->setFixedWidth(100);
    layCreate->addWidget(btnCreate_);
    layCreate->addStretch();
    root->addWidget(grpCreate);

    // ── Bit display ──
    auto* grpDisplay = new QGroupBox("Текущий BitSet (MSB → LSB)");
    auto* layDisplay = new QVBoxLayout(grpDisplay);
    lblBits_ = new QLabel("--------");
    lblBits_->setFont(QFont("Courier New", 14, QFont::Bold));
    lblBits_->setAlignment(Qt::AlignCenter);
    lblBits_->setWordWrap(true);
    layDisplay->addWidget(lblBits_);
    lblInfo_ = new QLabel("size=8  count=0  all=false  any=false  none=true");
    lblInfo_->setAlignment(Qt::AlignCenter);
    layDisplay->addWidget(lblInfo_);
    root->addWidget(grpDisplay);

    // ── Bit operations (by position) ──
    auto* grpPos = new QGroupBox("2. Операции с отдельным битом");
    auto* layPos = new QHBoxLayout(grpPos);
    layPos->addWidget(new QLabel("Позиция:"));
    spinPos_ = new QSpinBox; spinPos_->setRange(0, 255); spinPos_->setValue(0);
    layPos->addWidget(spinPos_);
    btnSet_   = new QPushButton("set(pos)");
    btnReset_ = new QPushButton("reset(pos)");
    btnFlip_  = new QPushButton("flip(pos)");
    btnTest_  = new QPushButton("test(pos)");
    for (auto* b : {btnSet_, btnReset_, btnFlip_, btnTest_}) layPos->addWidget(b);
    layPos->addStretch();
    root->addWidget(grpPos);

    // ── Global operations ──
    auto* grpGlobal = new QGroupBox("3. Глобальные операции");
    auto* layGlobal = new QHBoxLayout(grpGlobal);
    btnSetAll_   = new QPushButton("set()  — все в 1");
    btnResetAll_ = new QPushButton("reset() — все в 0");
    btnFlipAll_  = new QPushButton("flip()  — инверсия");
    for (auto* b : {btnSetAll_, btnResetAll_, btnFlipAll_}) layGlobal->addWidget(b);
    layGlobal->addStretch();
    root->addWidget(grpGlobal);

    // ── Query ──
    auto* grpQuery = new QGroupBox("4. Запросы");
    auto* layQuery = new QHBoxLayout(grpQuery);
    btnAll_     = new QPushButton("all()");
    btnAny_     = new QPushButton("any()");
    btnNone_    = new QPushButton("none()");
    btnCount_   = new QPushButton("count()");
    btnToStr_   = new QPushButton("to_string()");
    btnToUlong_ = new QPushButton("to_ulong()");
    btnToUllong_= new QPushButton("to_ullong()");
    for (auto* b : {btnAll_,btnAny_,btnNone_,btnCount_,btnToStr_,btnToUlong_,btnToUllong_})
        layQuery->addWidget(b);
    layQuery->addStretch();
    root->addWidget(grpQuery);

    // ── Bitwise ops ──
    auto* grpBit = new QGroupBox("5. Побитовые операции (O(N/64)) — второй операнд (строка 0/1)");
    auto* layBit = new QHBoxLayout(grpBit);
    editSecond_ = new QLineEdit("00000000");
    layBit->addWidget(editSecond_);
    cmbOp_ = new QComboBox;
    cmbOp_->addItems({"& (AND)", "| (OR)", "^ (XOR)", "~ (NOT первого)"});
    layBit->addWidget(cmbOp_);
    btnBitOp_ = new QPushButton("Применить");
    layBit->addWidget(btnBitOp_);
    layBit->addStretch();
    root->addWidget(grpBit);

    // ── Tests ──
    btnRunTests_ = new QPushButton("▶  Запустить функциональные тесты");
    btnRunTests_->setFixedHeight(36);
    root->addWidget(btnRunTests_);

    // ── Log ──
    logEdit_ = new QTextEdit;
    logEdit_->setReadOnly(true);
    logEdit_->setFont(QFont("Courier New", 10));
    logEdit_->setMaximumHeight(200);
    root->addWidget(logEdit_);

    // ── Connections ──
    connect(btnCreate_,   &QPushButton::clicked, this, &MainWindow::onCreateBitSet);
    connect(btnSet_,      &QPushButton::clicked, this, &MainWindow::onSetBit);
    connect(btnReset_,    &QPushButton::clicked, this, &MainWindow::onResetBit);
    connect(btnFlip_,     &QPushButton::clicked, this, &MainWindow::onFlipBit);
    connect(btnTest_,     &QPushButton::clicked, this, &MainWindow::onTestBit);
    connect(btnSetAll_,   &QPushButton::clicked, this, &MainWindow::onSetAll);
    connect(btnResetAll_, &QPushButton::clicked, this, &MainWindow::onResetAll);
    connect(btnFlipAll_,  &QPushButton::clicked, this, &MainWindow::onFlipAll);
    connect(btnAll_,      &QPushButton::clicked, this, &MainWindow::onQueryAll);
    connect(btnAny_,      &QPushButton::clicked, this, &MainWindow::onQueryAny);
    connect(btnNone_,     &QPushButton::clicked, this, &MainWindow::onQueryNone);
    connect(btnCount_,    &QPushButton::clicked, this, &MainWindow::onQueryCount);
    connect(btnToStr_,    &QPushButton::clicked, this, &MainWindow::onToString);
    connect(btnToUlong_,  &QPushButton::clicked, this, &MainWindow::onToUlong);
    connect(btnToUllong_, &QPushButton::clicked, this, &MainWindow::onToUllong);
    connect(btnBitOp_,    &QPushButton::clicked, this, &MainWindow::onBitwiseOp);
    connect(btnRunTests_, &QPushButton::clicked, this, &MainWindow::onRunTests);

    updateDisplay();
}

// ──────────────────────────────────────────────
// Display helpers
// ──────────────────────────────────────────────
void MainWindow::updateDisplay() {
    QString bits = QString::fromStdString(bs_.to_string());
    // Split into groups of 8 for readability
    QString spaced;
    for (int i = 0; i < bits.size(); ++i) {
        if (i > 0 && i % 8 == 0) spaced += ' ';
        spaced += bits[i];
    }
    lblBits_->setText(spaced);

    lblInfo_->setText(QString("size=%1  count=%2  all=%3  any=%4  none=%5")
        .arg(bs_.size()).arg(bs_.count())
        .arg(bs_.all()?"true":"false")
        .arg(bs_.any()?"true":"false")
        .arg(bs_.none()?"true":"false"));

    // Update spinPos max
    spinPos_->setMaximum((int)bs_.size() - 1);
    // Update editSecond placeholder
    editSecond_->setPlaceholderText(QString(bs_.size(), '0'));
}

void MainWindow::log(const QString& msg, bool ok) {
    QString color = ok ? "#2ecc71" : "#e74c3c";
    logEdit_->append(QString("<span style='color:%1'>%2</span>").arg(color, msg));
}

// ──────────────────────────────────────────────
// Slots
// ──────────────────────────────────────────────
void MainWindow::onCreateBitSet() {
    try {
        size_t n = spinSize_->value();
        bool ok;
        unsigned long long val = editInitVal_->text().toULongLong(&ok);
        if (!ok) val = 0;
        bs_ = BitSet(n, val);
        log(QString("Создан BitSet(size=%1, init=%2)").arg(n).arg(val));
        updateDisplay();
    } catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}

void MainWindow::onSetBit() {
    try {
        int pos = spinPos_->value();
        bs_.set(pos);
        log(QString("set(%1) → бит %1 = 1").arg(pos));
        updateDisplay();
    } catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}

void MainWindow::onResetBit() {
    try {
        int pos = spinPos_->value();
        bs_.reset(pos);
        log(QString("reset(%1) → бит %1 = 0").arg(pos));
        updateDisplay();
    } catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}

void MainWindow::onFlipBit() {
    try {
        int pos = spinPos_->value();
        bs_.flip(pos);
        log(QString("flip(%1) → бит %1 инвертирован").arg(pos));
        updateDisplay();
    } catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}

void MainWindow::onTestBit() {
    try {
        int pos = spinPos_->value();
        bool v = bs_.test(pos);
        log(QString("test(%1) = %2").arg(pos).arg(v ? "true (1)" : "false (0)"));
    } catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}

void MainWindow::onSetAll() {
    bs_.set();
    log("set() — все биты = 1");
    updateDisplay();
}

void MainWindow::onResetAll() {
    bs_.reset();
    log("reset() — все биты = 0");
    updateDisplay();
}

void MainWindow::onFlipAll() {
    bs_.flip();
    log("flip() — все биты инвертированы");
    updateDisplay();
}

void MainWindow::onQueryAll()   { log(QString("all()   = %1").arg(bs_.all()  ?"true":"false")); }
void MainWindow::onQueryAny()   { log(QString("any()   = %1").arg(bs_.any()  ?"true":"false")); }
void MainWindow::onQueryNone()  { log(QString("none()  = %1").arg(bs_.none() ?"true":"false")); }
void MainWindow::onQueryCount() { log(QString("count() = %1").arg(bs_.count())); }
void MainWindow::onToString()   { log(QString("to_string() = \"%1\"").arg(QString::fromStdString(bs_.to_string()))); }
void MainWindow::onToUlong()  {
    try { log(QString("to_ulong()  = %1").arg(bs_.to_ulong())); }
    catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}
void MainWindow::onToUllong() {
    log(QString("to_ullong() = %1").arg(bs_.to_ullong()));
}

void MainWindow::onBitwiseOp() {
    try {
        QString str = editSecond_->text();
        int op = cmbOp_->currentIndex();

        if (op == 3) { // NOT — only first operand
            bs_.flip();
            log("~bs → все биты инвертированы");
            updateDisplay();
            return;
        }

        // Pad/trim to same size
        size_t n = bs_.size();
        while ((size_t)str.size() < n) str = "0" + str;
        str = str.right(n);

        BitSet rhs(n, str.toStdString());
        QString opName;
        if (op == 0) { bs_ &= rhs; opName = "& (AND)"; }
        else if (op == 1) { bs_ |= rhs; opName = "| (OR)"; }
        else { bs_ ^= rhs; opName = "^ (XOR)"; }

        log(QString("bs %1 rhs → %2").arg(opName, QString::fromStdString(bs_.to_string())));
        updateDisplay();
    } catch (std::exception& e) { log(QString("Ошибка: ") + e.what(), false); }
}

// ──────────────────────────────────────────────
// Functional tests
// ──────────────────────────────────────────────
void MainWindow::onRunTests() {
    logEdit_->append("<br><b>=== ФУНКЦИОНАЛЬНЫЕ ТЕСТЫ ===</b>");
    int passed = 0, failed = 0;

    auto check = [&](const QString& name, bool cond) {
        if (cond) { log("  ✓ " + name); ++passed; }
        else       { log("  ✗ " + name, false); ++failed; }
    };

    // 1. Constructor & size
    {
        BitSet b(8, 0b10110100ULL);
        check("size()==8",       b.size() == 8);
        check("to_string==10110100", b.to_string() == "10110100");
        check("count()==4",      b.count() == 4);
        check("any()==true",     b.any());
        check("all()==false",    !b.all());
        check("none()==false",   !b.none());
    }

    // 2. set / reset / flip (single bit)
    {
        BitSet b(8, 0ULL);
        b.set(3);
        check("set(3): test(3)==true",  b.test(3));
        check("set(3): count==1",       b.count() == 1);
        b.reset(3);
        check("reset(3): test(3)==false", !b.test(3));
        check("reset(3): none()==true",   b.none());
        b.flip(5);
        check("flip(5): test(5)==true",   b.test(5));
        b.flip(5);
        check("flip(5) twice: test(5)==false", !b.test(5));
    }

    // 3. set() / reset() / flip() — all bits
    {
        BitSet b(8, 0ULL);
        b.set();
        check("set(): all()==true",   b.all());
        check("set(): count==8",      b.count() == 8);
        b.reset();
        check("reset(): none()==true", b.none());
        b.set();
        b.flip();
        check("flip after set: none()==true", b.none());
    }

    // 4. all() / any() / none()
    {
        BitSet b(4, 0b1111ULL);
        check("all() on 1111 == true",  b.all());
        b.reset(0);
        check("all() on 1110 == false", !b.all());
        BitSet c(4, 0ULL);
        check("none() on 0000 == true", c.none());
        check("any()  on 0000 == false",!c.any());
    }

    // 5. Bitwise & O(N/64)
    {
        BitSet a(8, 0b11001100ULL);
        BitSet b(8, 0b10101010ULL);
        BitSet r = a & b;
        check("& (AND): 11001100 & 10101010 == 10001000",
              r.to_string() == "10001000");
        BitSet r2 = a | b;
        check("| (OR): 11001100 | 10101010 == 11101110",
              r2.to_string() == "11101110");
        BitSet r3 = a ^ b;
        check("^ (XOR): 11001100 ^ 10101010 == 01100110",
              r3.to_string() == "01100110");
    }

    // 6. ~ operator
    {
        BitSet a(8, 0b11110000ULL);
        BitSet b = ~a;
        check("~11110000 == 00001111", b.to_string() == "00001111");
    }

    // 7. to_ulong / to_ullong
    {
        BitSet b(8, 42ULL);
        check("to_ullong()==42", b.to_ullong() == 42);
        check("to_ulong()==42",  b.to_ulong()  == 42);
    }

    // 8. operator[]
    {
        BitSet b(8, 0ULL);
        b[4] = true;
        check("operator[](4)=true: test(4)==true", b.test(4));
        b[4] = false;
        check("operator[](4)=false: test(4)==false", !b.test(4));
    }

    // 9. String constructor
    {
        BitSet b(8, std::string("10101010"));
        check("string ctor: to_string==10101010", b.to_string() == "10101010");
        check("string ctor: count==4", b.count() == 4);
    }

    // 10. Equality
    {
        BitSet a(8, 0b11001100ULL);
        BitSet b(8, 0b11001100ULL);
        BitSet c(8, 0b00110011ULL);
        check("a==b (same)", a == b);
        check("a!=c (diff)", a != c);
    }

    // 11. Large BitSet (>64 bits)
    {
        BitSet big(128, 0ULL);
        big.set(65); big.set(127);
        check("large: test(65)==true",  big.test(65));
        check("large: test(127)==true", big.test(127));
        check("large: test(0)==false",  !big.test(0));
        check("large: count==2",        big.count() == 2);
        big.flip();
        check("large: flip: count==126", big.count() == 126);
    }

    // 12. Out-of-range exception
    {
        BitSet b(8, 0ULL);
        bool threw = false;
        try { b.test(100); } catch (std::out_of_range&) { threw = true; }
        check("out_of_range exception on test(100)", threw);
    }

    logEdit_->append(QString("<br><b>Итог: %1 прошло, %2 не прошло</b><br>")
                         .arg(passed).arg(failed));
}
