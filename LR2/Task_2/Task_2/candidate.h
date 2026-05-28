#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

class Candidate
{
public:
    int district;
    QString name;
    QString party;
    int age;
    QString profession;
    double income;

    Candidate();
    Candidate(int d, QString n, QString p, int a, QString prof, double inc);
};

#endif
