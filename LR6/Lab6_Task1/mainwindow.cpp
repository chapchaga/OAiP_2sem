#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QCoreApplication>
#include <QStringList>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filePathLabel->setText("Файлы: " + filesDir());
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::filesDir()
{
    return QCoreApplication::applicationDirPath() + "/";
}

void MainWindow::appendOutput(const QString &text)
{
    ui->outputEdit->append(text);
}

void MainWindow::onMenuChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

QString MainWindow::formatOdezhda(const Odezhda &o, const QString &sep)
{
    QString articles;
    for (int i = 0; i < 5; i++) {
        if (i > 0) articles += ",";
        articles += QString::number(o.articleNumbers[i]);
    }
    return QString("%1%2%3%4%5%6%7%8%9%10[%11]")
        .arg(o.size).arg(sep)
        .arg(o.price).arg(sep)
        .arg(QChar(o.gender)).arg(sep)
        .arg(o.inStock ? "true" : "false").arg(sep)
        .arg(o.brand).arg(sep)
        .arg(articles);
}

static Odezhda odezhdaFromFields(int sz, double pr, char gnd, bool stk,
                                  const QString &brand, const QString &arts)
{
    Odezhda o;
    o.size = sz;
    o.price = pr;
    o.gender = gnd;
    o.inStock = stk;
    strncpy(o.brand, brand.toUtf8().constData(), sizeof(o.brand) - 1);
    o.brand[sizeof(o.brand) - 1] = '\0';
    QStringList parts = arts.split(' ', Qt::SkipEmptyParts);
    for (int i = 0; i < 5; i++)
        o.articleNumbers[i] = (i < parts.size()) ? parts[i].toInt() : 0;
    return o;
}

// ──────────────── TASK 1 ────────────────

void MainWindow::onTask1_1Clicked()
{
    appendOutput("\n[1.1] Явная инициализация через инициализирующую строку:");
    Odezhda o1 = {44, 2499.99, 'M', true, "Adidas", {2001, 2002, 2003, 2004, 2005}};
    Odezhda o2;
    o2.size = 38;
    o2.price = 999.50;
    o2.gender = 'F';
    o2.inStock = false;
    strncpy(o2.brand, "Zara", sizeof(o2.brand));
    o2.articleNumbers[0] = 3001; o2.articleNumbers[1] = 3002;
    o2.articleNumbers[2] = 3003; o2.articleNumbers[3] = 3004;
    o2.articleNumbers[4] = 3005;
    appendOutput("o1 (init string): " + formatOdezhda(o1));
    appendOutput("o2 (field-by-field): " + formatOdezhda(o2));
}

void MainWindow::onTask1_2Clicked()
{
    appendOutput("\n[1.2] Присвоение полей по одному:");
    Odezhda o;
    o.size = 46; o.price = 3750.00; o.gender = 'U'; o.inStock = true;
    strncpy(o.brand, "H&M", sizeof(o.brand));
    o.articleNumbers[0]=5001; o.articleNumbers[1]=5002; o.articleNumbers[2]=5003;
    o.articleNumbers[3]=5004; o.articleNumbers[4]=5005;
    appendOutput(formatOdezhda(o));
}

void MainWindow::onTask1_3Clicked()
{
    appendOutput("\n[1.3] Инициализация из пользовательского ввода:");
    bool ok1, ok2;
    int sz = ui->t1_size->text().toInt(&ok1);
    double pr = ui->t1_price->text().toDouble(&ok2);
    QString gStr = ui->t1_gender->text().trimmed();
    if (!ok1 || !ok2 || gStr.isEmpty() || ui->t1_brand->text().trimmed().isEmpty()) {
        appendOutput("Ошибка: заполните все поля формы.");
        return;
    }
    Odezhda o = odezhdaFromFields(sz, pr, gStr[0].toLatin1(),
                                   ui->t1_stock->isChecked(),
                                   ui->t1_brand->text().trimmed(),
                                   ui->t1_articles->text().trimmed());
    appendOutput(formatOdezhda(o));
}

void MainWindow::onTask1_4Clicked()
{
    appendOutput("\n[1.4] Работа через указатель (ptr->поле):");
    Odezhda o;
    Odezhda *ptr = &o;
    ptr->size = 50; ptr->price = 5100.75; ptr->gender = 'M'; ptr->inStock = true;
    strncpy(ptr->brand, "Gucci", sizeof(ptr->brand));
    ptr->articleNumbers[0]=7001; ptr->articleNumbers[1]=7002; ptr->articleNumbers[2]=7003;
    ptr->articleNumbers[3]=7004; ptr->articleNumbers[4]=7005;
    QString arts;
    for (int i = 0; i < 5; i++) { if (i>0) arts+=","; arts+=QString::number(ptr->articleNumbers[i]); }
    appendOutput(QString("%1 | %2 | %3 | %4 | %5 | [%6]")
        .arg(ptr->size).arg(ptr->price).arg(QChar(ptr->gender))
        .arg(ptr->inStock?"true":"false").arg(ptr->brand).arg(arts));
}

void MainWindow::onTask1_5Clicked()
{
    appendOutput("\n[1.5] Работа через ссылку (ref.поле):");
    Odezhda o;
    Odezhda &ref = o;
    ref.size = 36; ref.price = 899.00; ref.gender = 'F'; ref.inStock = false;
    strncpy(ref.brand, "Mango", sizeof(ref.brand));
    ref.articleNumbers[0]=9001; ref.articleNumbers[1]=9002; ref.articleNumbers[2]=9003;
    ref.articleNumbers[3]=9004; ref.articleNumbers[4]=9005;
    QString arts;
    for (int i = 0; i < 5; i++) { if (i>0) arts+=","; arts+=QString::number(ref.articleNumbers[i]); }
    appendOutput(QString("%1 | %2 | %3 | %4 | %5 | [%6]")
        .arg(ref.size).arg(ref.price).arg(QChar(ref.gender))
        .arg(ref.inStock?"true":"false").arg(ref.brand).arg(arts));
}

// ──────────────── TASK 2.1 ────────────────

void MainWindow::onTask2_TextSaveClicked()
{
    QString text = ui->t21_input->toPlainText();
    if (text.isEmpty()) { appendOutput("Введите текст."); return; }
    std::string path = (filesDir() + "FamiliyaLab20.txt").toStdString();
    std::wofstream file(path);
    if (!file.is_open()) { appendOutput("Ошибка открытия файла."); return; }
    std::wstring ws = text.toStdWString();
    for (wchar_t ch : ws) file.put(ch);
    file.close();
    appendOutput("[2.1] Текст записан посимвольно в FamiliyaLab20.txt (" +
                 QString::number(ws.size()) + " символов)");
}

void MainWindow::onTask2_TextLoadClicked()
{
    std::string path = (filesDir() + "FamiliyaLab20.txt").toStdString();
    std::wifstream file(path);
    if (!file.is_open()) { appendOutput("Файл не найден. Сначала запишите."); return; }
    std::wstring result, ws;
    wchar_t ch;
    while (file.get(ch)) result += ch;
    file.close();
    appendOutput("[2.1] Считано из файла: " + QString::fromStdWString(result));
}

// ──────────────── TASK 2.2 ────────────────

void MainWindow::onTask2_ArraySaveClicked()
{
    QString input = ui->t22_input->text().trimmed();
    if (input.isEmpty()) { appendOutput("Введите элементы массива."); return; }
    QStringList parts = input.split(' ', Qt::SkipEmptyParts);
    std::string path = (filesDir() + "FamiliyaLab20_0.txt").toStdString();
    std::ofstream file(path);
    if (!file.is_open()) { appendOutput("Ошибка открытия файла."); return; }
    for (int i = 0; i < parts.size(); i++) {
        int val = parts[i].toInt();
        file << val;
        if (i < parts.size() - 1) file << '\'';
    }
    file.close();
    appendOutput("[2.2] Массив записан в FamiliyaLab20_0.txt (разделитель: ')");
}

void MainWindow::onTask2_ArrayLoadClicked()
{
    std::string path = (filesDir() + "FamiliyaLab20_0.txt").toStdString();
    std::ifstream file(path);
    if (!file.is_open()) { appendOutput("Файл не найден. Сначала запишите."); return; }
    QString result = "[2.2] Считан массив: ";
    std::string token;
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    std::istringstream ss(content);
    std::string part;
    bool first = true;
    while (std::getline(ss, part, '\'')) {
        std::istringstream valStream(part);
        int val;
        if (valStream >> val) {
            if (!first) result += " ";
            result += QString::number(val);
            first = false;
        }
    }
    appendOutput(result);
}

// ──────────────── TASK 2.3 struct text ────────────────

static Odezhda odezhdaFromPage23(Ui::MainWindow *ui)
{
    bool ok1, ok2;
    int sz = ui->t23_size->text().toInt(&ok1);
    double pr = ui->t23_price->text().toDouble(&ok2);
    QString gStr = ui->t23_gender->text().trimmed();
    char g = gStr.isEmpty() ? 'U' : gStr[0].toLatin1();
    return odezhdaFromFields(sz, pr, g, ui->t23_stock->isChecked(),
                             ui->t23_brand->text().trimmed(),
                             ui->t23_articles->text().trimmed());
}

void MainWindow::onTask2_StructTxtSaveClicked()
{
    Odezhda o = odezhdaFromPage23(ui);
    std::string path = (filesDir() + "FamiliyaLab20_1.txt").toStdString();
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) { appendOutput("Ошибка открытия файла."); return; }
    file << o.size << "\n"
         << o.price << "\n"
         << o.gender << "\n"
         << (o.inStock ? 1 : 0) << "\n"
         << o.brand << "\n";
    for (int i = 0; i < 5; i++) file << o.articleNumbers[i] << (i<4?" ":"\n");
    file.close();
    appendOutput("[2.3] Структура дозаписана в FamiliyaLab20_1.txt");
}

void MainWindow::onTask2_StructTxtLoadClicked()
{
    std::string path = (filesDir() + "FamiliyaLab20_1.txt").toStdString();
    std::ifstream file(path);
    if (!file.is_open()) { appendOutput("Файл не найден."); return; }
    appendOutput("[2.3] Считаны структуры из файла:");
    int count = 0;
    while (file.peek() != EOF) {
        Odezhda o;
        int stockInt;
        std::string brandStr;
        if (!(file >> o.size >> o.price >> o.gender >> stockInt)) break;
        file.ignore();
        std::getline(file, brandStr);
        strncpy(o.brand, brandStr.c_str(), sizeof(o.brand)-1);
        o.brand[sizeof(o.brand)-1] = '\0';
        o.inStock = (stockInt != 0);
        for (int i = 0; i < 5; i++) file >> o.articleNumbers[i];
        file.ignore();
        appendOutput(QString("  #%1: ").arg(++count) + formatOdezhda(o));
    }
    file.close();
    if (count == 0) appendOutput("  Файл пуст.");
}

// ──────────────── TASK 2.4 struct binary ────────────────

static Odezhda odezhdaFromPage24(Ui::MainWindow *ui)
{
    bool ok1, ok2;
    int sz = ui->t24_size->text().toInt(&ok1);
    double pr = ui->t24_price->text().toDouble(&ok2);
    QString gStr = ui->t24_gender->text().trimmed();
    char g = gStr.isEmpty() ? 'U' : gStr[0].toLatin1();
    return odezhdaFromFields(sz, pr, g, ui->t24_stock->isChecked(),
                             ui->t24_brand->text().trimmed(),
                             ui->t24_articles->text().trimmed());
}

void MainWindow::onTask2_StructBinSaveClicked()
{
    Odezhda o = odezhdaFromPage24(ui);
    std::string path = (filesDir() + "FamiliyaLab20_2.bin").toStdString();
    std::ofstream file(path, std::ios::binary | std::ios::app);
    if (!file.is_open()) { appendOutput("Ошибка открытия файла."); return; }
    file.write(reinterpret_cast<char*>(&o), sizeof(Odezhda));
    file.close();
    appendOutput("[2.4] Структура дозаписана в FamiliyaLab20_2.bin");
}

void MainWindow::onTask2_StructBinLoadClicked()
{
    std::string path = (filesDir() + "FamiliyaLab20_2.bin").toStdString();
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) { appendOutput("Файл не найден."); return; }
    appendOutput("[2.4] Считаны структуры из бинарного файла:");
    int count = 0;
    Odezhda o;
    while (file.read(reinterpret_cast<char*>(&o), sizeof(Odezhda))) {
        appendOutput(QString("  #%1: ").arg(++count) + formatOdezhda(o, " ; "));
    }
    file.close();
    if (count == 0) appendOutput("  Файл пуст.");
}

// ──────────────── TASK 2.5 lines ────────────────

void MainWindow::onTask2_LineSaveClicked()
{
    QString line = ui->t25_input->text().trimmed();
    if (line.isEmpty()) { appendOutput("Введите предложение."); return; }
    std::string path = (filesDir() + "FamiliyaLab20_3.txt").toStdString();
    std::ofstream file(path, std::ios::app);
    if (!file.is_open()) { appendOutput("Ошибка открытия файла."); return; }
    file << line.toUtf8().constData() << "\n";
    file.close();
    appendOutput("[2.5] Строка дозаписана в FamiliyaLab20_3.txt");
}

void MainWindow::onTask2_LineLoadClicked()
{
    std::string path = (filesDir() + "FamiliyaLab20_3.txt").toStdString();
    std::ifstream file(path);
    if (!file.is_open()) { appendOutput("Файл не найден."); return; }
    appendOutput("[2.5] Строки из файла:");
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        appendOutput(QString("  %1: %2").arg(++count).arg(QString::fromUtf8(line.c_str())));
    }
    file.close();
    if (count == 0) appendOutput("  Файл пуст.");
}
