#include "date.h"
#include <QDate>

Date::Date()
{
    day = 1;
    month = 1;
    year = 2000;
}

Date::Date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

Date Date::nextDay() const
{
    QDate d(year, month, day);
    d = d.addDays(1);
    return Date(d.day(), d.month(), d.year());
}

Date Date::previousDay() const
{
    QDate d(year, month, day);
    d = d.addDays(-1);
    return Date(d.day(), d.month(), d.year());
}

bool Date::isLeap() const
{
    return QDate::isLeapYear(year);
}

int Date::weekNumber() const
{
    QDate d(year, month, day);
    return d.weekNumber();
}

int Date::duration(const Date& other) const
{
    QDate d1(year, month, day);
    QDate d2(other.getYear(), other.getMonth(), other.getDay());
    return d1.daysTo(d2);
}

int Date::daysTillBirthday(const Date& birthday) const
{
    QDate today(year, month, day);

    QDate nextBirthday(today.year(),
                       birthday.getMonth(),
                       birthday.getDay());

    if (nextBirthday < today)
        nextBirthday = nextBirthday.addYears(1);

    return today.daysTo(nextBirthday);
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}
