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
    void on_btnEvaluate_clicked();
    void on_btnExample_clicked();
    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;

    // Простой рекурсивный парсер выражений
    // Поддерживает: числа, +, -, *, /, скобки
    // Используется для демонстрации иерархии классов
    struct Parser {
        QString expr;
        int pos;

        Parser(const QString& e) : expr(e), pos(0) {}

        class Expression* parse();
        class Expression* parseAddSub();
        class Expression* parseMulDiv();
        class Expression* parsePrimary();

        void skipSpaces() {
            while (pos < expr.size() && expr[pos] == ' ') pos++;
        }
    };
};

#endif // MAINWINDOW_H
