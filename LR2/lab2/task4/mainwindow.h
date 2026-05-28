#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCheck_clicked();
    void on_btnRunAllTests_clicked();
    void on_cmbLeft_currentIndexChanged(int index);
    void on_cmbRight_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void logResult(const QString& left, const QString& right,
                   bool result, bool expected);
};

#endif // MAINWINDOW_H
