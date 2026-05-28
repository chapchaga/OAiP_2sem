#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <QVector>
#include "Candidate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow2; }
QT_END_NAMESPACE

class MainWindow2 : public QMainWindow {
    Q_OBJECT
public:
    MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

private slots:
    void on_btnOpen_clicked();
    void on_btnSave_clicked();
    void on_btnSaveAs_clicked();
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnEdit_clicked();
    void on_btnSort_clicked();
    void on_btnSearch_clicked();
    void on_btnBulletin_clicked();
    void on_btnRunTests_clicked();

private:
    Ui::MainWindow2 *ui;
    QVector<Candidate> candidates;
    QString currentFilePath;

    void loadFromFile(const QString& path);
    void saveToFile(const QString& path);
    void refreshTable();
    void showError(const QString& msg);
    void populateDialog(class CandidateDialog* dlg, const Candidate& c);
};

#endif // MAINWINDOW2_H
