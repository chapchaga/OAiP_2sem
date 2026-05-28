#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFolder();

private:
    void recursiveCount(QString path, int &files, int &folders);

    QPushButton *openButton;
    QLabel *resultLabel;
};

#endif
