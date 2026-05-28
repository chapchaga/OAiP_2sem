#ifndef DATE_H
#define DATE_H

#include <QString>

class Date {
private:
    int day;
    int month;
    int year;

    static const int daysInMonth[13];

public:
    Date();
    Date(int d, int m, int y);

    void setDate(int d, int m, int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool isValid() const;
    bool isLeap() const;
    int daysInCurrentMonth() const;

    Date nextDay() const;
    Date previousDay() const;
    short weekNumber() const;
    int daysTillYourBirthday(const Date& birthday) const;
    int duration(const Date& other) const;

    long long toDays() const;
    static Date fromDays(long long days);
    static Date today();

    QString toString() const;
    bool fromString(const QString& str);

    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;
};

#endif // DATE_H
