#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Expression.h"
#include <QMessageBox>
#include <stdexcept>

// ---- Парсер выражений ----

Expression* MainWindow::Parser::parse() {
    return parseAddSub();
}

Expression* MainWindow::Parser::parseAddSub() {
    Expression* left = parseMulDiv();
    skipSpaces();
    while (pos < expr.size() && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos].toLatin1();
        pos++;
        Expression* right = parseMulDiv();
        left = new BinaryOperation(left, op, right);
        skipSpaces();
    }
    return left;
}

Expression* MainWindow::Parser::parseMulDiv() {
    Expression* left = parsePrimary();
    skipSpaces();
    while (pos < expr.size() && (expr[pos] == '*' || expr[pos] == '/')) {
        char op = expr[pos].toLatin1();
        pos++;
        Expression* right = parsePrimary();
        left = new BinaryOperation(left, op, right);
        skipSpaces();
    }
    return left;
}

Expression* MainWindow::Parser::parsePrimary() {
    skipSpaces();
    if (pos >= expr.size())
        throw std::invalid_argument("Неожиданный конец выражения");

    // Скобки
    if (expr[pos] == '(') {
        pos++; // skip '('
        Expression* e = parseAddSub();
        skipSpaces();
        if (pos >= expr.size() || expr[pos] != ')')
            throw std::invalid_argument("Ожидалась ')'");
        pos++; // skip ')'
        return e;
    }

    // Число (включая унарный минус)
    bool negative = false;
    if (expr[pos] == '-') { negative = true; pos++; }

    int start = pos;
    while (pos < expr.size() && (expr[pos].isDigit() || expr[pos] == '.')) pos++;
    if (pos == start)
        throw std::invalid_argument(
            QString("Неожиданный символ '%1' на позиции %2").arg(expr[pos]).arg(pos).toStdString());

    bool ok;
    double val = expr.mid(start, pos - start).toDouble(&ok);
    if (!ok) throw std::invalid_argument("Некорректное число");
    if (negative) val = -val;
    return new Number(val);
}

// ---- MainWindow ----

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Задание 3 — Иерархия Expression");

    // Покажем начальный пример из условия: 3 + 4.5 * 5 = 25.5
    ui->textLog->append("Пример из условия задания:");
    ui->textLog->append("  Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));");
    ui->textLog->append("  Expression* expr = new BinaryOperation(new Number(3), '+', sube);");
    ui->textLog->append("  expr->evaluate() = 25.5");
    ui->textLog->append("");
    ui->textLog->append("Демонстрация иерархии классов:");
    ui->textLog->append("  Number::evaluate()           → возвращает хранимое число");
    ui->textLog->append("  BinaryOperation::evaluate()  → рекурсивно вычисляет л+п/л-п/л*п/л/п");
    ui->textLog->append("  ~BinaryOperation()           → удаляет левый и правый операнды");
    ui->textLog->append("");
    ui->textLog->append("Введите выражение и нажмите «Вычислить».");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btnEvaluate_clicked() {
    QString exprStr = ui->lineEditExpr->text().trimmed();
    if (exprStr.isEmpty()) {
        QMessageBox::warning(this, "Ввод", "Введите выражение.");
        return;
    }
    try {
        Parser p(exprStr);
        Expression* root = p.parse();

        // Вычисляем
        double result = root->evaluate();

        // Логируем шаги для числовых узлов
        ui->textLog->append(QString("─────────────────────────"));
        ui->textLog->append(QString("Выражение : %1").arg(exprStr));
        ui->textLog->append(QString("Результат : %1").arg(result));

        // Явная демонстрация: вывод дерева
        ui->labelResult->setText(QString("Результат: %1").arg(result));

        // Освобождаем память через виртуальный деструктор (удалятся все узлы)
        delete root;
        ui->textLog->append("(дерево объектов удалено через виртуальный деструктор)");

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка вычисления", e.what());
    }
}

void MainWindow::on_btnExample_clicked() {
    // Пример из условия: 3 + 4.5 * 5
    ui->lineEditExpr->setText("3 + 4.5 * 5");

    // Явное построение дерева как в условии
    Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression* expr = new BinaryOperation(new Number(3), '+', sube);
    double res = expr->evaluate();
    ui->textLog->append("─────────────────────────");
    ui->textLog->append("Пример из условия: 3 + 4.5 * 5");
    ui->textLog->append(QString("  new BinaryOperation(new Number(4.5),'*',new Number(5)) = %1").arg(sube->evaluate()));
    ui->textLog->append(QString("  Итог: %1").arg(res));
    ui->labelResult->setText(QString("Результат: %1").arg(res));
    delete expr; // удаляет sube, Number(4.5), Number(5), Number(3)
    ui->textLog->append("(delete expr — удалены все узлы дерева)");
}

void MainWindow::on_btnClear_clicked() {
    ui->textLog->clear();
    ui->lineEditExpr->clear();
    ui->labelResult->setText("Результат: —");
}
