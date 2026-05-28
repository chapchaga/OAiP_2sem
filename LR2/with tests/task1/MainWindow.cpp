#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "TestDate.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Задание 1 — Класс Date");

    // Run black-box tests on startup (results go to qDebug log only)
    TestDate tester;
    tester.runAll();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showError(const QString& msg) {
    QMessageBox::warning(this, "Ошибка", msg);
}

// ---- Load from file ----
void MainWindow::loadDatesFromFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showError("Не удалось открыть файл: " + path);
        return;
    }
    dates.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString token;
        in >> token;
        if (token.isEmpty()) continue;
        try {
            dates.append(Date::fromString(token));
        } catch (...) {
            showError("Неверная дата в файле: " + token + " — пропущена.");
        }
    }
    file.close();
    currentFilePath = path;
    refreshTable();
}

void MainWindow::refreshTable() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Дата", "Следующий день", "Разница с пред.", "Номер недели"});

    Date today = Date::today();
    for (int i = 0; i < dates.size(); i++) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(dates[i].toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(dates[i].nextDay().toString()));
        int diff = (i > 0) ? dates[i-1].duration(dates[i]) : 0;
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(i > 0 ? QString::number(diff) : "-"));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(dates[i].weekNumber())));
    }
}

void MainWindow::saveDatesToFile() {
    if (currentFilePath.isEmpty()) return;
    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showError("Не удалось сохранить файл.");
        return;
    }
    QTextStream out(&file);
    for (const Date& d : dates)
        out << d.toString() << " ";
    file.close();
}

void MainWindow::appendDateToFile(const Date& d) {
    if (currentFilePath.isEmpty()) return;
    QFile file(currentFilePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        showError("Не удалось дописать в файл.");
        return;
    }
    QTextStream out(&file);
    out << " " << d.toString();
    file.close();
}

// ---- Slots ----
void MainWindow::on_btnOpen_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл с датами", "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (!path.isEmpty())
        loadDatesFromFile(path);
}

void MainWindow::on_btnNextDay_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= dates.size()) { showError("Выберите строку."); return; }
    try {
        Date nd = dates[row].nextDay();
        QMessageBox::information(this, "Следующий день",
            QString("Дата: %1\nСледующий день: %2").arg(dates[row].toString()).arg(nd.toString()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void MainWindow::on_btnPrevDay_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= dates.size()) { showError("Выберите строку."); return; }
    try {
        Date pd = dates[row].previousDay();
        QMessageBox::information(this, "Предыдущий день",
            QString("Дата: %1\nПредыдущий день: %2").arg(dates[row].toString()).arg(pd.toString()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void MainWindow::on_btnWeekNum_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= dates.size()) { showError("Выберите строку."); return; }
    QMessageBox::information(this, "Номер недели",
        QString("Дата: %1\nНомер недели: %2").arg(dates[row].toString()).arg(dates[row].weekNumber()));
}

void MainWindow::on_btnDuration_clicked() {
    if (dates.size() < 2) { showError("Нужно минимум 2 даты."); return; }
    int row = ui->tableWidget->currentRow();
    if (row <= 0 || row >= dates.size()) { showError("Выберите строку (не первую)."); return; }
    int diff = dates[row-1].duration(dates[row]);
    QMessageBox::information(this, "Разница дат",
        QString("Между %1 и %2: %3 дн.").arg(dates[row-1].toString()).arg(dates[row].toString()).arg(diff));
}

void MainWindow::on_btnBirthday_clicked() {
    QString input = ui->editBirthday->text().trimmed();
    if (input.isEmpty()) { showError("Введите дату рождения в поле."); return; }
    try {
        Date birthday = Date::fromString(input);
        Date today = Date::today();
        int days = today.daysTillYourBirthday(birthday);
        QMessageBox::information(this, "До дня рождения",
            QString("Сегодня: %1\nДата рождения: %2\nДо ДР: %3 дн.").arg(today.toString()).arg(birthday.toString()).arg(days));
    } catch (const std::exception& e) {
        showError(QString("Ошибка: ") + e.what());
    }
}

void MainWindow::on_btnAdd_clicked() {
    bool ok;
    QString input = QInputDialog::getText(this, "Добавить дату", "Введите дату (дд.мм.гггг):", QLineEdit::Normal, "", &ok);
    if (!ok || input.isEmpty()) return;
    try {
        Date d = Date::fromString(input);
        dates.append(d);
        appendDateToFile(d);
        refreshTable();
    } catch (const std::exception& e) {
        showError(QString("Неверная дата: ") + e.what());
    }
}

void MainWindow::on_btnEdit_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= dates.size()) { showError("Выберите строку."); return; }
    bool ok;
    QString input = QInputDialog::getText(this, "Изменить дату",
        "Введите новую дату (дд.мм.гггг):", QLineEdit::Normal, dates[row].toString(), &ok);
    if (!ok || input.isEmpty()) return;
    try {
        dates[row] = Date::fromString(input);
        saveDatesToFile();
        refreshTable();
    } catch (const std::exception& e) {
        showError(QString("Неверная дата: ") + e.what());
    }
}

void MainWindow::on_btnRunTests_clicked() {
    // Tests output to qDebug() only — professor's "black box" requirement
    TestDate tester;
    tester.runAll();
    QMessageBox::information(this, "Тесты",
        "Тесты (чёрный ящик) запущены.\nРезультаты смотрите в консоли/логе Qt.");
}
