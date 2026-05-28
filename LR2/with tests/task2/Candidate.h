#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

// Variant 22: Election candidate registration
class Candidate {
private:
    int     districtNumber;   // Номер округа
    QString fullName;         // ФИО
    QString party;            // Наименование партии
    int     age;              // Возраст
    QString profession;       // Профессия
    double  income;           // Доход за прошедший год

public:
    Candidate();
    Candidate(int district, const QString& fullName, const QString& party,
              int age, const QString& profession, double income);

    // Getters
    int     getDistrict()   const;
    QString getFullName()   const;
    QString getParty()      const;
    int     getAge()        const;
    QString getProfession() const;
    double  getIncome()     const;

    // Setters
    void setDistrict(int v);
    void setFullName(const QString& v);
    void setParty(const QString& v);
    void setAge(int v);
    void setProfession(const QString& v);
    void setIncome(double v);

    // Serialisation
    QString toFileLine() const;
    static Candidate fromFileLine(const QString& line);

    bool isValid() const;
};

#endif // CANDIDATE_H
