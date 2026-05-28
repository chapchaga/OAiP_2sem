#ifndef TESTDATE_H
#define TESTDATE_H

#include "Date.h"
#include <QDebug>
#include <QString>
#include <functional>

// ============================================================
//  "Black Box" functional test class for Date
//  Results are written to qDebug() log only, NOT to the UI.
// ============================================================
class TestDate {
private:
    int passed = 0;
    int failed = 0;

    void ASSERT(const QString& label, bool condition) {
        if (condition) {
            qDebug() << "[PASS]" << label;
            passed++;
        } else {
            qDebug() << "[FAIL]" << label;
            failed++;
        }
    }

    void ASSERT_EQ(const QString& label, const QString& result, const QString& expected) {
        bool ok = (result == expected);
        if (ok) {
            qDebug() << "[PASS]" << label << "| result:" << result << "expected:" << expected;
            passed++;
        } else {
            qDebug() << "[FAIL]" << label << "| result:" << result << "expected:" << expected;
            failed++;
        }
    }

    void ASSERT_INT(const QString& label, int result, int expected) {
        bool ok = (result == expected);
        if (ok) {
            qDebug() << "[PASS]" << label << "| result:" << result << "expected:" << expected;
            passed++;
        } else {
            qDebug() << "[FAIL]" << label << "| result:" << result << "expected:" << expected;
            failed++;
        }
    }

public:
    // ----------------------------------------------------------
    // Test 1: isLeap()
    // ----------------------------------------------------------
    void Test1_IsLeap() {
        qDebug() << "=== Test1_IsLeap ===";
        Date d[4];
        d[0].setDate(1, 1, 2000); // leap (div 400)
        d[1].setDate(1, 1, 1900); // not leap (div 100 but not 400)
        d[2].setDate(1, 1, 2024); // leap (div 4, not 100)
        d[3].setDate(1, 1, 2023); // not leap

        ASSERT("Year 2000 is leap",  d[0].isLeap() == true);
        ASSERT("Year 1900 not leap", d[1].isLeap() == false);
        ASSERT("Year 2024 is leap",  d[2].isLeap() == true);
        ASSERT("Year 2023 not leap", d[3].isLeap() == false);
    }

    // ----------------------------------------------------------
    // Test 2: nextDay()
    // ----------------------------------------------------------
    void Test2_NextDay() {
        qDebug() << "=== Test2_NextDay ===";
        Date d[3];
        d[0].setDate(31, 12, 2023); // year boundary
        d[1].setDate(28, 2, 2024);  // leap feb
        d[2].setDate(28, 2, 2023);  // normal feb

        ASSERT_EQ("31.12.2023 -> 01.01.2024", d[0].nextDay().toString(), "01.01.2024");
        ASSERT_EQ("28.02.2024 -> 29.02.2024", d[1].nextDay().toString(), "29.02.2024");
        ASSERT_EQ("28.02.2023 -> 01.03.2023", d[2].nextDay().toString(), "01.03.2023");
    }

    // ----------------------------------------------------------
    // Test 3: previousDay()
    // ----------------------------------------------------------
    void Test3_PreviousDay() {
        qDebug() << "=== Test3_PreviousDay ===";
        Date d[3];
        d[0].setDate(1, 1, 2024);  // year boundary
        d[1].setDate(1, 3, 2024);  // leap march -> feb 29
        d[2].setDate(1, 3, 2023);  // normal march -> feb 28

        ASSERT_EQ("01.01.2024 -> 31.12.2023", d[0].previousDay().toString(), "31.12.2023");
        ASSERT_EQ("01.03.2024 -> 29.02.2024", d[1].previousDay().toString(), "29.02.2024");
        ASSERT_EQ("01.03.2023 -> 28.02.2023", d[2].previousDay().toString(), "28.02.2023");
    }

    // ----------------------------------------------------------
    // Test 4: weekNumber()
    // ----------------------------------------------------------
    void Test4_WeekNumber() {
        qDebug() << "=== Test4_WeekNumber ===";
        Date d[2];
        d[0].setDate(1, 1, 2024);  // ISO week 1
        d[1].setDate(31, 12, 2023);// ISO week 52

        ASSERT_INT("01.01.2024 week", d[0].weekNumber(), 1);
        ASSERT_INT("31.12.2023 week", d[1].weekNumber(), 52);
    }

    // ----------------------------------------------------------
    // Test 5: duration()
    // ----------------------------------------------------------
    void Test5_Duration() {
        qDebug() << "=== Test5_Duration ===";
        Date d[2];
        d[0].setDate(1, 1, 2024);
        d[1].setDate(10, 1, 2024);

        ASSERT_INT("Duration 01.01.2024 -> 10.01.2024 = 9", d[0].duration(d[1]), 9);
        ASSERT_INT("Duration symmetric", d[1].duration(d[0]), 9);
    }

    // ----------------------------------------------------------
    // Test 6: invalid date throws
    // ----------------------------------------------------------
    void Test6_InvalidDate() {
        qDebug() << "=== Test6_InvalidDate ===";
        bool threw = false;
        try {
            Date d(31, 2, 2023); // invalid
        } catch (...) {
            threw = true;
        }
        ASSERT("31.02.2023 throws exception", threw);

        threw = false;
        try {
            Date d(29, 2, 2023); // not a leap year
        } catch (...) {
            threw = true;
        }
        ASSERT("29.02.2023 throws exception", threw);
    }

    // ----------------------------------------------------------
    // Run all tests
    // ----------------------------------------------------------
    void runAll() {
        qDebug() << "========== DATE BLACK-BOX TESTS ==========";
        Test1_IsLeap();
        Test2_NextDay();
        Test3_PreviousDay();
        Test4_WeekNumber();
        Test5_Duration();
        Test6_InvalidDate();
        qDebug() << "==========================================";
        qDebug() << "Results: PASSED=" << passed << " FAILED=" << failed;
        qDebug() << "==========================================";
    }
};

#endif // TESTDATE_H
