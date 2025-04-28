#include <iostream>

#include <symengine/expression.h>
#include <symengine/add.h>
#include <symengine/symbol.h>

using namespace SymEngine;

int main(int argc, char* argv[]) 
{
    // Create symbolic variables
    Symbol x("x");
    Symbol y("y");

    // Create a symbolic expression
    Expression expr = x + 2 * y;

    // Print the expression
    std::cout << expr << std::endl; // Output: x + 2*y

    return 0;
}
