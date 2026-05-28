#ifndef EXPRESSION_H
#define EXPRESSION_H

// ============================================================
//  Задание 3: Иерархия классов для арифметических выражений
// ============================================================

// Базовый абстрактный класс
class Expression {
public:
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

// Класс числа
class Number : public Expression {
private:
    double value;
public:
    explicit Number(double val) : value(val) {}
    double evaluate() const override { return value; }
    ~Number() override {}
};

// Класс бинарной операции
class BinaryOperation : public Expression {
private:
    Expression* left;
    Expression* right;
    char        op;   // '+', '-', '*', '/'

public:
    BinaryOperation(Expression* l, char operation, Expression* r)
        : left(l), op(operation), right(r) {}

    double evaluate() const override {
        double l = left->evaluate();
        double r = right->evaluate();
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/':
                if (r == 0.0)
                    throw std::runtime_error("Деление на ноль");
                return l / r;
            default:
                throw std::invalid_argument("Неизвестная операция");
        }
    }

    // BinaryOperation отвечает за уничтожение операндов
    ~BinaryOperation() override {
        delete left;
        delete right;
    }
};

#endif // EXPRESSION_H
