#include "MainWindow2.h"
#include "ui_MainWindow2.h"
#include "CandidateDialog.h"
#include "GlassBoxTest.h"
#include "XlsxWriter.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <algorithm>

MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow2) {
    ui->setupUi(this);
    refreshTable();

    // Live search
    connect(ui->editSearch, &QLineEdit::textChanged, this, [this](const QString& text) {
        for (int r = 0; r < ui->tableWidget->rowCount(); r++) {
            bool match = text.isEmpty();
            if (!match) {
                for (int c = 0; c < ui->tableWidget->columnCount(); c++) {
                    QTableWidgetItem* item = ui->tableWidget->item(r, c);
                    if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                        match = true; break;
                    }
                }
            }
            ui->tableWidget->setRowHidden(r, !match);
        }
    });
}

MainWindow2::~MainWindow2() { delete ui; }

void MainWindow2::showError(const QString& msg) {
    QMessageBox::warning(this, "Ошибка", msg);
}

void MainWindow2::loadFromFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        showError("Не удалось открыть файл: " + path); return;
    }
    candidates.clear();
    QTextStream in(&file);
    int lineNum = 0;
    while (!in.atEnd()) {
        lineNum++;
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        try {
            candidates.append(Candidate::fromFileLine(line));
        } catch (...) {
            showError(QString("Ошибка в строке %1: %2").arg(lineNum).arg(line));
        }
    }
    file.close();
    currentFilePath = path;
    refreshTable();
    ui->labelStatus->setText(QString("Загружено %1 кандидатов из: %2").arg(candidates.size()).arg(path));
}

void MainWindow2::saveToFile(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        showError("Не удалось сохранить файл: " + path); return;
    }
    QTextStream out(&file);
    for (const Candidate& c : candidates)
        out << c.toFileLine() << "\n";
    file.close();
    ui->labelStatus->setText("Сохранено: " + path);
}

void MainWindow2::refreshTable() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({
        "Округ", "ФИО", "Партия", "Возраст", "Профессия", "Доход (руб.)"
    });
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    for (int i = 0; i < candidates.size(); i++) {
        const Candidate& c = candidates[i];
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(c.getDistrict())));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(c.getFullName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(c.getParty()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(c.getAge())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(c.getProfession()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(c.getIncome(), 'f', 2)));
    }
    ui->labelStatus->setText(QString("Кандидатов в списке: %1").arg(candidates.size()));
}

// ---- Slots ----

void MainWindow2::on_btnOpen_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть файл",
        "", "Текстовые файлы (*.txt *.dat);;Все файлы (*)");
    if (!path.isEmpty()) loadFromFile(path);
}

void MainWindow2::on_btnSave_clicked() {
    if (currentFilePath.isEmpty()) { on_btnSaveAs_clicked(); return; }
    saveToFile(currentFilePath);
}

void MainWindow2::on_btnSaveAs_clicked() {
    QString path = QFileDialog::getSaveFileName(this, "Сохранить как",
        "", "Текстовые файлы (*.txt *.dat);;Все файлы (*)");
    if (!path.isEmpty()) { currentFilePath = path; saveToFile(path); }
}

void MainWindow2::on_btnAdd_clicked() {
    CandidateDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Candidate c = dlg.getCandidate();
        if (!c.isValid()) { showError("Введены некорректные данные."); return; }
        candidates.append(c);
        refreshTable();
    }
}

void MainWindow2::on_btnEdit_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= candidates.size()) { showError("Выберите строку."); return; }
    CandidateDialog dlg(this);
    dlg.setCandidate(candidates[row]);
    if (dlg.exec() == QDialog::Accepted) {
        Candidate c = dlg.getCandidate();
        if (!c.isValid()) { showError("Введены некорректные данные."); return; }
        candidates[row] = c;
        refreshTable();
    }
}

void MainWindow2::on_btnDelete_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row < 0 || row >= candidates.size()) { showError("Выберите строку."); return; }
    auto btn = QMessageBox::question(this, "Удаление",
        QString("Удалить кандидата '%1'?").arg(candidates[row].getFullName()));
    if (btn == QMessageBox::Yes) {
        candidates.removeAt(row);
        refreshTable();
    }
}

void MainWindow2::on_btnSort_clicked() {
    QStringList options = {"По округу", "По ФИО", "По партии", "По возрасту (возр.)",
                           "По возрасту (убыв.)", "По доходу (возр.)", "По доходу (убыв.)"};
    bool ok;
    QString choice = QInputDialog::getItem(this, "Сортировка", "Критерий:", options, 0, false, &ok);
    if (!ok) return;

    int idx = options.indexOf(choice);
    switch (idx) {
    case 0: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getDistrict() < b.getDistrict(); }); break;
    case 1: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getFullName() < b.getFullName(); }); break;
    case 2: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getParty() < b.getParty(); }); break;
    case 3: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getAge() < b.getAge(); }); break;
    case 4: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getAge() > b.getAge(); }); break;
    case 5: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getIncome() < b.getIncome(); }); break;
    case 6: std::sort(candidates.begin(), candidates.end(),
        [](const Candidate& a, const Candidate& b){ return a.getIncome() > b.getIncome(); }); break;
    }
    refreshTable();
}

void MainWindow2::on_btnSearch_clicked() {
    bool ok;
    QString query = QInputDialog::getText(this, "Поиск", "ФИО или партия:", QLineEdit::Normal, "", &ok);
    if (!ok || query.isEmpty()) return;
    ui->editSearch->setText(query);
}

void MainWindow2::on_btnBulletin_clicked() {
    if (candidates.isEmpty()) { showError("Нет кандидатов."); return; }

    // Group by party
    QMap<QString, QVector<Candidate>> byParty;
    for (const Candidate& c : candidates)
        byParty[c.getParty()].append(c);

    QString report;
    report += "=== ИНФОРМАЦИОННЫЙ БЮЛЛЕТЕНЬ ===\n\n";

    for (auto it = byParty.begin(); it != byParty.end(); ++it) {
        const QString& party = it.key();
        const QVector<Candidate>& group = it.value();

        // Count applications
        int count = group.size();

        // Average age
        double sumAge = 0;
        for (const Candidate& c : group) sumAge += c.getAge();
        double avgAge = sumAge / count;

        // Most common profession
        QMap<QString, int> profCount;
        for (const Candidate& c : group) profCount[c.getProfession()]++;
        QString topProf;
        int topCount = 0;
        for (auto pit = profCount.begin(); pit != profCount.end(); ++pit) {
            if (pit.value() > topCount) { topCount = pit.value(); topProf = pit.key(); }
        }

        // Average income
        double sumIncome = 0;
        for (const Candidate& c : group) sumIncome += c.getIncome();
        double avgIncome = sumIncome / count;

        report += QString("Партия: %1\n").arg(party);
        report += QString("  Заявлений на регистрацию: %1\n").arg(count);
        report += QString("  Средний возраст: %1\n").arg(avgAge, 0, 'f', 1);
        report += QString("  Наиболее частая профессия: %1\n").arg(topProf);
        report += QString("  Средний доход: %1 руб.\n").arg(avgIncome, 0, 'f', 2);
        report += "\n";
    }

    QMessageBox box(this);
    box.setWindowTitle("Информационный бюллетень");
    box.setText(report);
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();
}

void MainWindow2::on_btnRunTests_clicked() {
    QString path = QFileDialog::getSaveFileName(this, "Сохранить результаты тестов",
        "glass_box_results.xlsx", "Excel файлы (*.xlsx)");
    if (path.isEmpty()) return;

    GlassBoxTest tester;
    tester.run(candidates);

    bool ok = XlsxWriter::writeResults(tester.results, path);
    if (ok) {
        int passed = 0, failed = 0;
        for (const TestResult& r : tester.results)
            r.passed ? passed++ : failed++;
        QMessageBox::information(this, "Тесты завершены",
            QString("Результаты сохранены в:\n%1\n\nПройдено: %2 | Провалено: %3")
                .arg(path).arg(passed).arg(failed));
    } else {
        QMessageBox::warning(this, "Ошибка",
            "Не удалось создать .xlsx файл.\n"
            "Убедитесь, что Python 3 и openpyxl установлены:\n"
            "pip install openpyxl");
    }
}
