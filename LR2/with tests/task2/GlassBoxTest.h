#ifndef GLASSBOXTEST_H
#define GLASSBOXTEST_H

// ============================================================
//  "Glass Box" (white-box) tests for Task 2.
//  Results are written to an .xlsx file via xlsxwriter / QAxObject.
//  Columns: Test name | Expected | ok/fail
// ============================================================

#include "Candidate.h"
#include <QVector>
#include <QString>

struct TestResult {
    QString testName;
    QString expected;
    QString actual;
    bool    passed;
};

class GlassBoxTest {
public:
    QVector<TestResult> results;

    void run(const QVector<Candidate>& data);

    // Individual test methods
    void testAddCandidate(QVector<Candidate> data);
    void testDeleteCandidate(QVector<Candidate> data);
    void testSortByAge(QVector<Candidate> data);
    void testSortByIncome(QVector<Candidate> data);
    void testFilterByParty(const QVector<Candidate>& data);
    void testSearchByName(const QVector<Candidate>& data);
    void testBulletinAvgAge(const QVector<Candidate>& data);
    void testBulletinAvgIncome(const QVector<Candidate>& data);
    void testInvalidCandidate();
    void testSerialization();

private:
    void addResult(const QString& name, const QString& expected, const QString& actual);
};

#endif // GLASSBOXTEST_H
