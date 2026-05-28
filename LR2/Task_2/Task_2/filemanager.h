#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "candidate.h"
#include <QVector>
#include <QString>

class FileManager
{
public:
    static void saveToFile(QString filename, QVector<Candidate> &list);
    static void loadFromFile(QString filename, QVector<Candidate> &list);
};

#endif
