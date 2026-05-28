#ifndef EXPRESSION_H
#define EXPRESSION_H

class Expression
{
public:
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

class Number : public Expression
{
private:
    double value;

public:
    Number(double value);
    double evaluate() const override;
};

class BinaryOperation : public Expression
{
private:
    Expression* left;
    Expression* right;
    char op;

public:
    BinaryOperation(Expression* left, char op, Expression* right);

    double evaluate() const override;

    ~BinaryOperation();
};

#endif
