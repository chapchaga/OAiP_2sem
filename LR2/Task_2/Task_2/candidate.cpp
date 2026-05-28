#include "candidate.h"

Candidate::Candidate()
{
    district = 0;
    age = 0;
    income = 0;
}

Candidate::Candidate(int d, QString n, QString p, int a, QString prof, double inc)
{
    district = d;
    name = n;
    party = p;
    age = a;
    profession = prof;
    income = inc;
}
