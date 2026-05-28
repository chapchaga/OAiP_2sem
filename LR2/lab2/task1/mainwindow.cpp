#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TestDate.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Задание 1 — Класс Date");

    // Run black-box tests at startup (results go to debug log only)
    TestDate::runAll();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::loadFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showError("Не удалось открыть файл: " + path);
        return;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    dates.clear();
    QStringList tokens = content.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    for (const QString& token : tokens) {
        Date d;
        if (d.fromString(token)) {
            dates.append(d);
        } else {
            showError("Некорректная дата: " + token);
        }
    }
    currentFilePath = path;
    updateTable();
}

void MainWindow::updateTable() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"Дата", "Следующий день",
                                                 "Предыдущий день",
                                                 "Разница с пред. (дней)"});
    for (int i = 0; i < dates.size(); i++) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(dates[i].toString()));
        try {
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(dates[i].nextDay().toString()));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(dates[i].previousDay().toString()));
        } catch (...) {
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem("N/A"));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem("N/A"));
        }
        if (i > 0) {
            int diff = dates[i].duration(dates[i-1]);
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(diff)));
        } else {
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem("—"));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_btnOpenFile_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл с датами",
                                                "", "Text Files (*.txt);;All Files (*)");
    if (!path.isEmpty()) loadFile(path);
}

void MainWindow::on_btnNextDay_clicked() {
    int row = selectedRow();
    if (row < 0) return;
    try {
        Date next = dates[row].nextDay();
        QMessageBox::information(this, "Следующий день",
            QString("Дата: %1\nСледующий день: %2")
                .arg(dates[row].toString(), next.toString()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void MainWindow::on_btnPrevDay_clicked() {
    int row = selectedRow();
    if (row < 0) return;
    try {
        Date prev = dates[row].previousDay();
        QMessageBox::information(this, "Предыдущий день",
            QString("Дата: %1\nПредыдущий день: %2")
                .arg(dates[row].toString(), prev.toString()));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void MainWindow::on_btnWeekNumber_clicked() {
    int row = selectedRow();
    if (row < 0) return;
    short wn = dates[row].weekNumber();
    QMessageBox::information(this, "Номер недели",
        QString("Дата: %1\nНомер недели: %2\nВисокосный год: %3")
            .arg(dates[row].toString())
            .arg(wn)
            .arg(dates[row].isLeap() ? "Да" : "Нет"));
}

void MainWindow::on_btnDuration_clicked() {
    int row = selectedRow();
    if (row < 0 || row >= dates.size() - 1) {
        showError("Выберите элемент (не последний) для расчёта разницы со следующим");
        return;
    }
    int dur = dates[row].duration(dates[row + 1]);
    QMessageBox::information(this, "Разница дат",
        QString("Между %1 и %2: %3 дн.")
            .arg(dates[row].toString(), dates[row+1].toString())
            .arg(dur));
}

void MainWindow::on_btnBirthday_clicked() {
    QString bdStr = ui->lineEditBirthday->text().trimmed();
    Date bday;
    if (!bday.fromString(bdStr)) {
        showError("Введите дату рождения в формате ДД.ММ.ГГГГ");
        return;
    }
    try {
        Date td = Date::today();
        int days = td.daysTillYourBirthday(bday);
        QMessageBox::information(this, "День рождения",
            QString("Сегодня: %1\nДата рождения: %2\nДней до дня рождения: %3")
                .arg(td.toString(), bdStr).arg(days));
    } catch (const std::exception& e) {
        showError(e.what());
    }
}

void MainWindow::on_btnAddDate_clicked() {
    QString dateStr = ui->lineEditNewDate->text().trimmed();
    Date d;
    if (!d.fromString(dateStr)) {
        showError("Некорректный формат даты. Используйте ДД.ММ.ГГГГ");
        return;
    }
    dates.append(d);
    updateTable();
    ui->lineEditNewDate->clear();
}

void MainWindow::on_btnSave_clicked() {
    if (currentFilePath.isEmpty()) {
        currentFilePath = QFileDialog::getSaveFileName(this, "Сохранить файл",
                                                        "", "Text Files (*.txt)");
        if (currentFilePath.isEmpty()) return;
    }
    QFile file(currentFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showError("Не удалось сохранить файл");
        return;
    }
    QTextStream out(&file);
    for (int i = 0; i < dates.size(); i++) {
        if (i > 0) out << " ";
        out << dates[i].toString();
    }
    file.close();
    QMessageBox::information(this, "Сохранено", "Файл успешно сохранён.");
}

void MainWindow::on_btnRunTests_clicked() {
    // Tests output goes to debug log (black-box / "чёрный ящик")
    TestDate::runAll();
    QMessageBox::information(this, "Тесты",
        "Тесты выполнены. Результаты смотрите в логе (консоль / Qt Creator Output).");
}

void MainWindow::showError(const QString& msg) {
    QMessageBox::critical(this, "Ошибка", msg);
}

int MainWindow::selectedRow() {
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        showError("Выберите строку в таблице");
    }
    return row;
}
