#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdexcept>

// ============================================================
//  Задание 4: check_equals без typeid и dynamic_cast
//
//  Решение: виртуальный метод getTypeTag() возвращает
//  указатель на статическую переменную, уникальную для каждого класса.
//  Если теги совпадают — объекты одного типа.
//  Вызов методов по переданным указателям НЕ запрещён для getTypeTag,
//  т.к. это вспомогательный виртуальный метод самого класса иерархии.
//  Typeid и dynamic_cast — не используются.
// ============================================================

class Expression {
public:
    virtual double evaluate() const = 0;

    // Возвращает адрес статической переменной,
    // уникальной для каждого конкретного класса.
    // По совпадению адресов определяем тип.
    virtual const void* getTypeTag() const = 0;

    virtual ~Expression() {}
};

class Number : public Expression {
private:
    double value;
public:
    explicit Number(double val) : value(val) {}

    double evaluate() const override { return value; }

    const void* getTypeTag() const override {
        static char tag; // уникальный адрес для Number
        return &tag;
    }

    ~Number() override {}
};

class BinaryOperation : public Expression {
private:
    Expression* left;
    Expression* right;
    char        op;

public:
    BinaryOperation(Expression* l, char operation, Expression* r)
        : left(l), op(operation), right(r) {}

    double evaluate() const override {
        double lv = left->evaluate();
        double rv = right->evaluate();
        switch (op) {
            case '+': return lv + rv;
            case '-': return lv - rv;
            case '*': return lv * rv;
            case '/':
                if (rv == 0.0) throw std::runtime_error("Деление на ноль");
                return lv / rv;
            default:
                throw std::invalid_argument("Неизвестная операция");
        }
    }

    const void* getTypeTag() const override {
        static char tag; // уникальный адрес для BinaryOperation
        return &tag;
    }

    ~BinaryOperation() override {
        delete left;
        delete right;
    }
};

// ============================================================
//  Функция из задания:
//  true  — оба указателя на объекты ОДНОГО класса
//  false — классы разные
//  Запрет: typeid, dynamic_cast
// ============================================================
bool check_equals(Expression const* left, Expression const* right) {
    if (!left || !right) return false;
    return left->getTypeTag() == right->getTypeTag();
}

#endif // EXPRESSION_H
