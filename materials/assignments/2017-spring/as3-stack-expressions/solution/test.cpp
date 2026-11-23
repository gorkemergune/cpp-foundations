#include <stdexcept>

#include "check.h"
#include "expr.h"

int main() {
    CHECK(balanced("( ( [ { ( ) } ( ) ] ) )"));
    CHECK(!balanced("( [ ( ) () }"));
    CHECK(balanced(""));
    CHECK(!balanced("(("));
    CHECK(!balanced("]"));
    CHECK_EQ(toPostfix("A * (B \xE2\x80\x93 C) / D  + E"), std::string("A B C - * D / E +"));
    CHECK_EQ(toPostfix("A \xE2\x80\x93 B * C \xE2\x80\x93 (D + F) * E"), std::string("A B C * - D F + E * -"));
    CHECK_EQ(toPostfix("10-4*2/2+5*9+1"), std::string("10 4 2 * 2 / - 5 9 * + 1 +"));
    CHECK_EQ(evalPostfix(toPostfix("10-4*2/2+5*9+1")), 52LL);
    CHECK_EQ(evalPostfix(toPostfix("6 * ((5-2) * (2+1)) -9/3")), 51LL);
    CHECK_EQ(evalPostfix("9 3 -"), 6LL);  // operand order: 9 - 3, not 3 - 9
    CHECK_EQ(evalPostfix("9 3 /"), 3LL);
    bool threw = false;
    try {
        evalPostfix("1 0 /");
    } catch (const std::domain_error&) {
        threw = true;
    }
    CHECK(threw);
    return check_summary("2017 as3 stack expressions");
}
