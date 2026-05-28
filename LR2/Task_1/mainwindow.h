#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_openButton_clicked();
    void on_addButton_clicked();
    void on_calcButton_clicked();

private:

    Ui::MainWindow *ui;

    QVector<Date> dates;

    void updateTable();
};

#endif
