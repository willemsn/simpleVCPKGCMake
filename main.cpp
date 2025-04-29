#include <iostream>
#include <symengine/expression.h>
#include <symengine/symbol.h>

using namespace SymEngine;

int main()
{
    // Correct way: Define Expression objects
    Expression x("x");
    Expression y("y");

    // Now you can safely do arithmetic
    Expression expr = x + y * 2;

    std::cout << "Expression: " << expr << std::endl;

    return 0;
}
