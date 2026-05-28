#ifndef EXPRESSION_H
#define EXPRESSION_H

class Expression
{
public:
    virtual ~Expression() {}
};

class Number : public Expression
{
};

class BinaryOperation : public Expression
{
};

bool check_equals(Expression const* left, Expression const* right);

#endif
