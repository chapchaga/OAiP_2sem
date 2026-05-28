#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget->setColumnCount(4);

    QStringList headers;

    headers<<"Дата"
            <<"Следующий день"
            <<"Разница"
            <<"Номер недели";

    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,"Открыть файл","","Text (*.txt)");

    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);

        dates.clear();

        while(!in.atEnd())
        {
            QString line=in.readLine();

            QStringList parts=line.split(".");

            if(parts.size()==3)
            {
                int d=parts[0].toInt();
                int m=parts[1].toInt();
                int y=parts[2].toInt();

                dates.append(Date(d,m,y));
            }
        }
    }

    updateTable();
}

void MainWindow::on_addButton_clicked()
{
    QDate d=ui->dateEdit->date();

    dates.append(Date(d.day(),d.month(),d.year()));

    updateTable();
}

void MainWindow::on_calcButton_clicked()
{
    updateTable();
}

void MainWindow::updateTable()
{
    ui->tableWidget->setRowCount(dates.size());
    std::sort(dates.begin(), dates.end(), [](const Date& a, const Date& b) {
        if (a.getYear() != b.getYear()) return a.getYear() < b.getYear();
        if (a.getMonth() != b.getMonth()) return a.getMonth() < b.getMonth();
        return a.getDay() < b.getDay();
    });

    for(int i=0;i<dates.size();i++)
    {
        Date d=dates[i];

        QString dateStr=QString::number(d.getDay())+"."
                          +QString::number(d.getMonth())+"."
                          +QString::number(d.getYear());

        Date next=d.nextDay();

        QString nextStr=QString::number(next.getDay())+"."
                          +QString::number(next.getMonth())+"."
                          +QString::number(next.getYear());

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(dateStr));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(nextStr));

        if(i+1<dates.size())
        {
            int diff=d.duration(dates[i+1]);

            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(diff)));
        }
        ui->tableWidget->setItem(i,3,
                                 new QTableWidgetItem(QString::number(d.weekNumber())));
    }
}
