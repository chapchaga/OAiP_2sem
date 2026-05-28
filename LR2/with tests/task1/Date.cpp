#include "Date.h"
#include <QDate>
#include <stdexcept>

const int Date::daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

Date::Date() : day(1), month(1), year(1) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (!isValid())
        throw std::invalid_argument("Invalid date");
}

int Date::daysInCurrentMonth() const {
    if (month == 2 && isLeap()) return 29;
    return daysInMonth[month];
}

void Date::setDate(int d, int m, int y) {
    day = d; month = m; year = y;
    if (!isValid())
        throw std::invalid_argument("Invalid date");
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

bool Date::isValid() const {
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;
    int maxDay = (month == 2 && isLeap()) ? 29 : daysInMonth[month];
    return day <= maxDay;
}

bool Date::isLeap() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Date Date::nextDay() const {
    int d = day + 1, m = month, y = year;
    int maxDay = (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) ? 29 : daysInMonth[m];
    if (d > maxDay) { d = 1; m++; }
    if (m > 12) { m = 1; y++; }
    return Date(d, m, y);
}

Date Date::previousDay() const {
    int d = day - 1, m = month, y = year;
    if (d < 1) {
        m--;
        if (m < 1) { m = 12; y--; }
        if (y < 1) throw std::runtime_error("Date out of range");
        d = (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) ? 29 : daysInMonth[m];
    }
    return Date(d, m, y);
}

// Zeller-based week number (ISO 8601)
short Date::weekNumber() const {
    QDate qd(year, month, day);
    return (short)qd.weekNumber();
}

long long Date::toDays() const {
    // Rata Die algorithm
    int y = year, m = month, d = day;
    if (m <= 2) { y--; m += 12; }
    long long A = y / 100;
    long long B = 2 - A + A / 4;
    return (long long)(365.25 * (y + 4716)) + (long long)(30.6001 * (m + 1)) + d + B - 1524;
}

Date Date::fromDays(long long jd) {
    long long z = jd + 1 - 1721119;
    long long a = (4 * z - 1) / 146097;
    z = 4 * z - 1 - 146097 * a;
    long long d = z / 4;
    z = (4 * d + 3) / 1461;
    d = 4 * d + 3 - 1461 * z;
    d = (d + 4) / 4;
    long long m = (5 * d - 3) / 153;
    d = 5 * d - 3 - 153 * m;
    d = (d + 5) / 5;
    long long y = 100 * a + z;
    if (m < 10) m += 3; else { m -= 9; y++; }
    return Date((int)d, (int)m, (int)y);
}

int Date::daysTillYourBirthday(Date birthdayDate) const {
    // Next birthday from today
    Date bday(birthdayDate.day, birthdayDate.month, year);
    // If the birthday already passed this year
    if (bday.toDays() < toDays()) {
        bday = Date(birthdayDate.day, birthdayDate.month, year + 1);
    }
    // Handle leap year birthday on Feb 29
    if (birthdayDate.month == 2 && birthdayDate.day == 29 && !Date(1,1,bday.year).isLeap()) {
        bday = Date(1, 3, bday.year);
    }
    long long diff = bday.toDays() - toDays();
    return (int)(diff < 0 ? 0 : diff);
}

int Date::duration(Date date) const {
    long long diff = date.toDays() - toDays();
    return (int)(diff < 0 ? -diff : diff);
}

QString Date::toString() const {
    return QString("%1.%2.%3")
        .arg(day, 2, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0'))
        .arg(year, 4, 10, QChar('0'));
}

Date Date::fromString(const QString& s) {
    QStringList parts = s.trimmed().split('.');
    if (parts.size() != 3) throw std::invalid_argument("Bad format");
    return Date(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
}

Date Date::today() {
    QDate qd = QDate::currentDate();
    return Date(qd.day(), qd.month(), qd.year());
}
