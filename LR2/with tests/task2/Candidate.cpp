#include "Candidate.h"
#include <QStringList>
#include <stdexcept>

Candidate::Candidate()
    : districtNumber(0), age(0), income(0.0) {}

Candidate::Candidate(int district, const QString& fn, const QString& p,
                     int a, const QString& prof, double inc)
    : districtNumber(district), fullName(fn), party(p),
      age(a), profession(prof), income(inc) {}

int     Candidate::getDistrict()   const { return districtNumber; }
QString Candidate::getFullName()   const { return fullName; }
QString Candidate::getParty()      const { return party; }
int     Candidate::getAge()        const { return age; }
QString Candidate::getProfession() const { return profession; }
double  Candidate::getIncome()     const { return income; }

void Candidate::setDistrict(int v)           { districtNumber = v; }
void Candidate::setFullName(const QString& v){ fullName = v; }
void Candidate::setParty(const QString& v)   { party = v; }
void Candidate::setAge(int v)                { age = v; }
void Candidate::setProfession(const QString& v){ profession = v; }
void Candidate::setIncome(double v)          { income = v; }

bool Candidate::isValid() const {
    return districtNumber > 0 && !fullName.isEmpty() && !party.isEmpty()
           && age >= 18 && age <= 120 && income >= 0;
}

// CSV: district|fullName|party|age|profession|income
QString Candidate::toFileLine() const {
    return QString("%1|%2|%3|%4|%5|%6")
        .arg(districtNumber)
        .arg(fullName)
        .arg(party)
        .arg(age)
        .arg(profession)
        .arg(income, 0, 'f', 2);
}

Candidate Candidate::fromFileLine(const QString& line) {
    QStringList p = line.split('|');
    if (p.size() != 6) throw std::invalid_argument("Bad candidate line");
    return Candidate(p[0].toInt(), p[1], p[2], p[3].toInt(), p[4], p[5].toDouble());
}
