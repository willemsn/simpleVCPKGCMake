#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <symengine/basic.h>
#include <symengine/add.h>
#include <symengine/symbol.h>
#include <symengine/mul.h>
#include <symengine/integer.h> 

using SymEngine::Basic;
using SymEngine::symbol;
using SymEngine::add;
using SymEngine::mul;
using SymEngine::RCP;

TEST_CASE("SymEngine working")
{
    // Create symbol x
    RCP<const Basic> x = symbol("x");

    // Expression: x + x
    RCP<const Basic> expr = add(x, x);

    // Expected: 2 * x
    RCP<const Basic> expected = mul(SymEngine::integer(2), x);

    // Check symbolic equality
    REQUIRE(eq(*expr, *expected));
}
