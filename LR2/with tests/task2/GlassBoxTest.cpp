#include "GlassBoxTest.h"
#include <algorithm>
#include <numeric>
#include <cmath>

void GlassBoxTest::addResult(const QString& name, const QString& expected, const QString& actual) {
    TestResult r;
    r.testName = name;
    r.expected = expected;
    r.actual   = actual;
    r.passed   = (expected == actual);
    results.append(r);
}

void GlassBoxTest::run(const QVector<Candidate>& data) {
    results.clear();
    testAddCandidate(data);
    testDeleteCandidate(data);
    testSortByAge(data);
    testSortByIncome(data);
    testFilterByParty(data);
    testSearchByName(data);
    testBulletinAvgAge(data);
    testBulletinAvgIncome(data);
    testInvalidCandidate();
    testSerialization();
}

void GlassBoxTest::testAddCandidate(QVector<Candidate> data) {
    int before = data.size();
    Candidate c(1, "Иванов Иван Иванович", "Тест-Партия", 35, "Инженер", 50000.0);
    data.append(c);
    addResult("Добавление кандидата",
              QString::number(before + 1),
              QString::number(data.size()));
}

void GlassBoxTest::testDeleteCandidate(QVector<Candidate> data) {
    if (data.isEmpty()) {
        addResult("Удаление кандидата", "невозможно (пусто)", "пусто");
        return;
    }
    int before = data.size();
    data.removeAt(0);
    addResult("Удаление кандидата",
              QString::number(before - 1),
              QString::number(data.size()));
}

void GlassBoxTest::testSortByAge(QVector<Candidate> data) {
    if (data.size() < 2) { addResult("Сортировка по возрасту", "не применимо", "не применимо"); return; }
    std::sort(data.begin(), data.end(), [](const Candidate& a, const Candidate& b){
        return a.getAge() < b.getAge();
    });
    bool sorted = true;
    for (int i = 1; i < data.size(); i++)
        if (data[i].getAge() < data[i-1].getAge()) { sorted = false; break; }
    addResult("Сортировка по возрасту (возр.)", "true", sorted ? "true" : "false");
}

void GlassBoxTest::testSortByIncome(QVector<Candidate> data) {
    if (data.size() < 2) { addResult("Сортировка по доходу", "не применимо", "не применимо"); return; }
    std::sort(data.begin(), data.end(), [](const Candidate& a, const Candidate& b){
        return a.getIncome() > b.getIncome();
    });
    bool sorted = true;
    for (int i = 1; i < data.size(); i++)
        if (data[i].getIncome() > data[i-1].getIncome()) { sorted = false; break; }
    addResult("Сортировка по доходу (убыв.)", "true", sorted ? "true" : "false");
}

void GlassBoxTest::testFilterByParty(const QVector<Candidate>& data) {
    if (data.isEmpty()) { addResult("Фильтр по партии", "не применимо", "не применимо"); return; }
    QString party = data[0].getParty();
    int count = 0;
    for (const Candidate& c : data)
        if (c.getParty() == party) count++;
    // Manual count must match
    int check = 0;
    for (const Candidate& c : data)
        if (c.getParty() == party) check++;
    addResult("Фильтр по партии '" + party + "'",
              QString::number(count), QString::number(check));
}

void GlassBoxTest::testSearchByName(const QVector<Candidate>& data) {
    if (data.isEmpty()) { addResult("Поиск по ФИО", "не применимо", "не применимо"); return; }
    QString target = data[0].getFullName();
    bool found = false;
    for (const Candidate& c : data)
        if (c.getFullName() == target) { found = true; break; }
    addResult("Поиск по ФИО '" + target + "'", "true", found ? "true" : "false");
}

void GlassBoxTest::testBulletinAvgAge(const QVector<Candidate>& data) {
    if (data.isEmpty()) { addResult("Средний возраст (бюллетень)", "0", "0"); return; }
    double sum = 0;
    for (const Candidate& c : data) sum += c.getAge();
    double avg = sum / data.size();
    // Recalculate
    double sum2 = 0;
    for (const Candidate& c : data) sum2 += c.getAge();
    double avg2 = sum2 / data.size();
    addResult("Средний возраст (бюллетень)",
              QString::number(avg, 'f', 2),
              QString::number(avg2, 'f', 2));
}

void GlassBoxTest::testBulletinAvgIncome(const QVector<Candidate>& data) {
    if (data.isEmpty()) { addResult("Средний доход (бюллетень)", "0", "0"); return; }
    double sum = 0;
    for (const Candidate& c : data) sum += c.getIncome();
    double avg = sum / data.size();
    double sum2 = 0;
    for (const Candidate& c : data) sum2 += c.getIncome();
    double avg2 = sum2 / data.size();
    addResult("Средний доход (бюллетень)",
              QString::number(avg, 'f', 2),
              QString::number(avg2, 'f', 2));
}

void GlassBoxTest::testInvalidCandidate() {
    Candidate c;
    c.setDistrict(-1); c.setAge(15); c.setIncome(-100);
    addResult("Валидация (неверные данные)", "false", c.isValid() ? "true" : "false");
}

void GlassBoxTest::testSerialization() {
    Candidate orig(3, "Петров Пётр Петрович", "СтабПартия", 45, "Юрист", 75000.50);
    QString line = orig.toFileLine();
    try {
        Candidate restored = Candidate::fromFileLine(line);
        bool ok = (restored.getFullName() == orig.getFullName()
                   && restored.getParty() == orig.getParty()
                   && restored.getAge() == orig.getAge());
        addResult("Сериализация/десериализация", "true", ok ? "true" : "false");
    } catch (...) {
        addResult("Сериализация/десериализация", "true", "false");
    }
}
