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
    void on_btnOpenFile_clicked();
    void on_btnNextDay_clicked();
    void on_btnPrevDay_clicked();
    void on_btnWeekNumber_clicked();
    void on_btnDuration_clicked();
    void on_btnBirthday_clicked();
    void on_btnAddDate_clicked();
    void on_btnSave_clicked();
    void on_btnRunTests_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Date> dates;
    QString currentFilePath;

    void loadFile(const QString& path);
    void updateTable();
    void showError(const QString& msg);
    int selectedRow();
};

#endif // MAINWINDOW_H
