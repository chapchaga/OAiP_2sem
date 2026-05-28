#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include "filemanager.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    Candidate c(
        ui->editDistrict->text().toInt(),
        ui->editName->text(),
        ui->editParty->text(),
        ui->editAge->text().toInt(),
        ui->editProfession->text(),
        ui->editIncome->text().toDouble()
        );

    list.push_back(c);
}


void MainWindow::on_btnShow_clicked()
{
    ui->memo->clear();

    for (auto c : list)
    {
        ui->memo->append(
            QString("Округ: %1 | ФИО: %2 | Партия: %3 | Возраст: %4 | Профессия: %5 | Доход: %6")
                .arg(c.district)
                .arg(c.name)
                .arg(c.party)
                .arg(c.age)
                .arg(c.profession)
                .arg(c.income)
            );
    }
}


void MainWindow::on_btnSave_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,"Сохранить файл");

    if(filename.isEmpty())
        return;

    FileManager::saveToFile(filename,list);
}


void MainWindow::on_btnOpen_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Открыть файл");

    if(filename.isEmpty())
        return;

    FileManager::loadFromFile(filename,list);
}

void MainWindow::on_btnStats_clicked()
{
    ui->memo->clear();

    QMap<QString,int> count;
    QMap<QString,int> ageSum;
    QMap<QString,double> incomeSum;
    QMap<QString,QMap<QString,int>> professions;

    for(auto c : list)
    {
        count[c.party]++;
        ageSum[c.party] += c.age;
        incomeSum[c.party] += c.income;
        professions[c.party][c.profession]++;
    }

    for(auto party : count.keys())
    {
        int n = count[party];

        double avgAge = (double)ageSum[party] / n;
        double avgIncome = incomeSum[party] / n;

        QString mostProf;
        int max = 0;

        for(auto prof : professions[party].keys())
        {
            if(professions[party][prof] > max)
            {
                max = professions[party][prof];
                mostProf = prof;
            }
        }

        ui->memo->append("Партия: " + party);
        ui->memo->append("Число кандидатов: " + QString::number(n));
        ui->memo->append("Средний возраст: " + QString::number(avgAge));
        ui->memo->append("Самая частая профессия: " + mostProf);
        ui->memo->append("Средний доход: " + QString::number(avgIncome));
        ui->memo->append("----------------------");
    }
}

void MainWindow::on_btnDelete_clicked()
{
    QString name = ui->editName->text();

    for(int i = 0; i < list.size(); i++)
    {
        if(list[i].name == name)
        {
            list.remove(i);
            break;
        }
    }

    ui->memo->clear();

    for(auto c : list)
    {
        ui->memo->append(
            QString("Округ: %1 | ФИО: %2 | Партия: %3 | Возраст: %4 | Профессия: %5 | Доход: %6")
                .arg(c.district)
                .arg(c.name)
                .arg(c.party)
                .arg(c.age)
                .arg(c.profession)
                .arg(c.income)
            );
    }
}


