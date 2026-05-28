#include "filemanager.h"
#include <QFile>
#include <QTextStream>

void FileManager::saveToFile(QString filename, QVector<Candidate> &list)
{
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for(auto c : list)
        {
            out << c.district << ";"
                << c.name << ";"
                << c.party << ";"
                << c.age << ";"
                << c.profession << ";"
                << c.income << "\n";
        }

        file.close();
    }
}

void FileManager::loadFromFile(QString filename, QVector<Candidate> &list)
{
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        list.clear();

        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(";");

            if(parts.size()==6)
            {
                Candidate c(
                    parts[0].toInt(),
                    parts[1],
                    parts[2],
                    parts[3].toInt(),
                    parts[4],
                    parts[5].toDouble()
                    );

                list.push_back(c);
            }
        }

        file.close();
    }
}
