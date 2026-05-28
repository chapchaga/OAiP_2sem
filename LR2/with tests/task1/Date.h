#ifndef DATE_H
#define DATE_H

#include <QString>

class Date {
private:
    int day;
    int month;
    int year;

    static const int daysInMonth[13];
    int daysInCurrentMonth() const;

public:
    Date();
    Date(int d, int m, int y);

    void setDate(int d, int m, int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool isValid() const;
    bool isLeap() const;

    Date nextDay() const;
    Date previousDay() const;
    short weekNumber() const;
    int daysTillYourBirthday(Date birthdayDate) const;
    int duration(Date date) const;

    long long toDays() const;
    static Date fromDays(long long days);

    QString toString() const;
    static Date fromString(const QString& s);
    static Date today();
};

#endif // DATE_H
