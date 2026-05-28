#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "Date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpen_clicked();
    void on_btnNextDay_clicked();
    void on_btnPrevDay_clicked();
    void on_btnWeekNum_clicked();
    void on_btnDuration_clicked();
    void on_btnBirthday_clicked();
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnRunTests_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Date> dates;
    QString currentFilePath;

    void loadDatesFromFile(const QString& path);
    void refreshTable();
    void saveDatesToFile();
    void appendDateToFile(const Date& d);
    void showError(const QString& msg);
};

#endif // MAINWINDOW_H
