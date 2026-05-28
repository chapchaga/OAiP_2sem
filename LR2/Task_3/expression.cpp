#include "expression.h"

Number::Number(double value)
{
    this->value = value;
}

double Number::evaluate() const
{
    return value;
}

BinaryOperation::BinaryOperation(Expression* left, char op, Expression* right)
{
    this->left = left;
    this->right = right;
    this->op = op;
}

double BinaryOperation::evaluate() const
{
    double l = left->evaluate();
    double r = right->evaluate();

    if (op == '+')
        return l + r;
    if (op == '-')
        return l - r;
    if (op == '*')
        return l * r;
    if (op == '/')
        return l / r;

    return 0;
}

BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
}
