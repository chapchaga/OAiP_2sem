#ifndef TESTDATE_H
#define TESTDATE_H

#include <QString>
#include <QDebug>
#include "Date.h"

// ============================================================
//  "Чёрный ящик" — функциональные тесты класса Date
//  Результаты пишутся в лог (qDebug), НЕ в интерфейс
// ============================================================

class TestDate {
public:
    static void runAll() {
        qDebug() << "===== TestDate: начало тестирования =====";
        Test1_NextDay();
        Test2_PreviousDay();
        Test3_IsLeap();
        Test4_WeekNumber();
        Test5_Duration();
        Test6_DaysTillBirthday();
        Test7_LeapYearFeb29();
        Test8_EndOfYearRollover();
        qDebug() << "===== TestDate: тестирование завершено =====";
    }

private:
    static void ASSERT(bool condition, const QString& testName,
                       const QString& result, const QString& expected) {
        if (condition)
            qDebug() << "[PASS]" << testName
                     << "| result:" << result
                     << "| expected:" << expected;
        else
            qDebug() << "[FAIL]" << testName
                     << "| result:" << result
                     << "| expected:" << expected;
    }

    // Test1: nextDay — обычный день
    static void Test1_NextDay() {
        Date d(15, 6, 2023);
        Date next = d.nextDay();
        QString result   = next.toString();
        QString etalon   = "16.06.2023";
        ASSERT(result == etalon, "Test1_NextDay", result, etalon);
    }

    // Test2: previousDay — переход через месяц
    static void Test2_PreviousDay() {
        Date d(1, 3, 2023);
        Date prev = d.previousDay();
        QString result = prev.toString();
        QString etalon = "28.02.2023";
        ASSERT(result == etalon, "Test2_PreviousDay", result, etalon);
    }

    // Test3: isLeap — 2000 и 1900
    static void Test3_IsLeap() {
        Date d2000(1, 1, 2000);
        ASSERT(d2000.isLeap(), "Test3_IsLeap_2000", "true", "true");

        Date d1900(1, 1, 1900);
        ASSERT(!d1900.isLeap(), "Test3_IsLeap_1900", "false", "false");

        Date d2024(1, 1, 2024);
        ASSERT(d2024.isLeap(), "Test3_IsLeap_2024", "true", "true");
    }

    // Test4: weekNumber — 1 января 2024 (пон.) → неделя 1
    static void Test4_WeekNumber() {
        Date d(1, 1, 2024);
        short w = d.weekNumber();
        ASSERT(w == 1, "Test4_WeekNumber_01Jan2024",
               QString::number(w), "1");
    }

    // Test5: duration между двумя датами
    static void Test5_Duration() {
        Date d1(1, 1, 2023);
        Date d2(1, 1, 2024);
        int dur = d1.duration(d2);
        ASSERT(dur == 365, "Test5_Duration_2023_2024",
               QString::number(dur), "365");
    }

    // Test6: daysTillBirthday — если ДР уже прошёл
    static void Test6_DaysTillBirthday() {
        Date today_d(10, 6, 2023);
        Date birthday(5, 6, 1990); // 5 июня — уже прошёл
        int days = today_d.daysTillYourBirthday(birthday);
        // следующий ДР — 05.06.2024, от 10.06.2023 = 360 дней
        ASSERT(days == 360, "Test6_DaysTillBirthday_Passed",
               QString::number(days), "360");
    }

    // Test7: nextDay для 29 февраля в високосный год
    static void Test7_LeapYearFeb29() {
        Date d(29, 2, 2024);
        Date next = d.nextDay();
        QString result = next.toString();
        QString etalon = "01.03.2024";
        ASSERT(result == etalon, "Test7_LeapFeb29_NextDay", result, etalon);
    }

    // Test8: nextDay 31.12.2023 → 01.01.2024
    static void Test8_EndOfYearRollover() {
        Date d(31, 12, 2023);
        Date next = d.nextDay();
        QString result = next.toString();
        QString etalon = "01.01.2024";
        ASSERT(result == etalon, "Test8_EndOfYear_Rollover", result, etalon);
    }
};

#endif // TESTDATE_H
