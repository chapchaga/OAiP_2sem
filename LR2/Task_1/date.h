#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d,int m,int y);

    Date nextDay() const;
    Date previousDay() const;

    bool isLeap() const;
    int weekNumber() const;

    int duration(const Date& other) const;
    int daysTillBirthday(const Date& birthday) const;

    int getDay() const;
    int getMonth() const;
    int getYear() const;
};

#endif
