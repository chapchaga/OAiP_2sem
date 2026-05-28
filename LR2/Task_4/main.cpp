#include <iostream>
#include "expression.h"

int main()
{
    Expression* a = new Number();
    Expression* b = new Number();
    Expression* c = new BinaryOperation();

    std::cout << check_equals(a, b) << std::endl; // 1
    std::cout << check_equals(a, c) << std::endl; // 0

    delete a;
    delete b;
    delete c;

    return 0;
}
