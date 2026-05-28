#include "Date.h"
#include <QDate>
#include <stdexcept>

const int Date::daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

Date::Date() : day(1), month(1), year(2000) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValid())
        throw std::invalid_argument("Invalid date");
}

void Date::setDate(int d, int m, int y) {
    day = d; month = m; year = y;
    if (!isValid())
        throw std::invalid_argument("Invalid date");
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

bool Date::isLeap() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInCurrentMonth() const {
    if (month == 2 && isLeap()) return 29;
    return daysInMonth[month];
}

bool Date::isValid() const {
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;
    if (month == 2 && isLeap()) return day <= 29;
    return day <= daysInMonth[month];
}

Date Date::nextDay() const {
    Date d = *this;
    d.day++;
    if (d.day > d.daysInCurrentMonth()) {
        d.day = 1;
        d.month++;
        if (d.month > 12) {
            d.month = 1;
            d.year++;
        }
    }
    return d;
}

Date Date::previousDay() const {
    Date d = *this;
    d.day--;
    if (d.day < 1) {
        d.month--;
        if (d.month < 1) {
            d.month = 12;
            d.year--;
            if (d.year < 1)
                throw std::out_of_range("Date before 01.01.0001");
        }
        d.day = d.daysInCurrentMonth();
    }
    return d;
}

long long Date::toDays() const {
    long long y = year - 1;
    long long days = y * 365 + y / 4 - y / 100 + y / 400;
    for (int m = 1; m < month; m++) {
        days += daysInMonth[m];
        if (m == 2 && isLeap()) days++;
    }
    days += day;
    return days;
}

Date Date::fromDays(long long days) {
    int y = (int)(days / 365.2425);
    if (y < 1) y = 1;
    Date tmp; tmp.year = y; tmp.month = 1; tmp.day = 1;
    while (tmp.toDays() > days) { tmp.year--; }
    while (true) {
        Date next; next.year = tmp.year + 1; next.month = 1; next.day = 1;
        if (next.toDays() <= days) tmp.year++;
        else break;
    }
    tmp.month = 1; tmp.day = 1;
    for (int m = 1; m <= 12; m++) {
        int dim = (m == 2 && tmp.isLeap()) ? 29 : daysInMonth[m];
        if (tmp.toDays() + dim - 1 >= days) {
            tmp.month = m;
            break;
        }
        tmp.day += dim;
    }
    long long base; Date base_d; base_d.year = tmp.year; base_d.month = tmp.month; base_d.day = 1;
    base = base_d.toDays();
    tmp.day = (int)(days - base + 1);
    return tmp;
}

short Date::weekNumber() const {
    // ISO 8601: week starts on Monday
    Date jan1(1, 1, year);
    long long d = toDays() - jan1.toDays();
    // day of week for jan1 (0=Mon...6=Sun)
    // Tomohiko Sakamoto-like: use QDate
    QDate qjan1(year, 1, 1);
    int dow = qjan1.dayOfWeek() - 1; // 0=Mon
    int week = (int)((d + dow) / 7) + 1;
    if (week == 0) week = 53;
    return (short)week;
}

int Date::daysTillYourBirthday(const Date& birthday) const {
    Date todayDate = *this;
    Date nextBday(birthday.day, birthday.month, todayDate.year);
    if (!nextBday.isValid()) {
        // Feb 29 on non-leap - use Mar 1
        nextBday = Date(1, 3, todayDate.year);
    }
    if (nextBday.toDays() <= todayDate.toDays()) {
        nextBday = Date(birthday.day, birthday.month, todayDate.year + 1);
        if (!nextBday.isValid())
            nextBday = Date(1, 3, todayDate.year + 1);
    }
    return (int)(nextBday.toDays() - todayDate.toDays());
}

int Date::duration(const Date& other) const {
    return (int)std::abs(toDays() - other.toDays());
}

Date Date::today() {
    QDate q = QDate::currentDate();
    return Date(q.day(), q.month(), q.year());
}

QString Date::toString() const {
    return QString("%1.%2.%3")
        .arg(day, 2, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0'))
        .arg(year, 4, 10, QChar('0'));
}

bool Date::fromString(const QString& str) {
    QStringList parts = str.split('.');
    if (parts.size() != 3) return false;
    bool ok1, ok2, ok3;
    int d = parts[0].toInt(&ok1);
    int m = parts[1].toInt(&ok2);
    int y = parts[2].toInt(&ok3);
    if (!ok1 || !ok2 || !ok3) return false;
    day = d; month = m; year = y;
    return isValid();
}

bool Date::operator==(const Date& o) const { return toDays() == o.toDays(); }
bool Date::operator<(const Date& o) const { return toDays() < o.toDays(); }
bool Date::operator>(const Date& o) const { return toDays() > o.toDays(); }
