// Assignment 3 (2017) · prints every step that the assignment asks you to draw.
// g++ -std=c++17 main.cpp expr.cpp
#include <iostream>

#include "expr.h"

static void show(const std::vector<std::string>& t) {
    for (const auto& line : t) std::cout << "   " << line << "\n";
}

int main() {
    for (const char* s : {"( ( [ { ( ) } ( ) ] ) )", "( [ ( ) () }"}) {
        std::vector<std::string> t;
        bool ok = balanced(s, &t);
        std::cout << "Q1  " << s << "  ->  " << (ok ? "balanced" : "NOT balanced") << "\n";
        show(t);
    }
    for (const char* s : {"A * (B - C) / D + E", "A - B * C - (D + F) * E"}) {
        std::vector<std::string> t;
        std::cout << "Q2  " << s << "  ->  " << toPostfix(s, &t) << "\n";
        show(t);
    }
    for (const char* s : {"10-4*2/2+5*9+1", "6 * ((5-2) * (2+1)) -9/3"}) {
        std::vector<std::string> t1, t2;
        std::string p = toPostfix(s, &t1);
        long long v = evalPostfix(p, &t2);
        std::cout << "Q3  " << s << "  ->  postfix " << p << "  =  " << v << "\n   conversion:\n";
        show(t1);
        std::cout << "   evaluation:\n";
        show(t2);
    }
}
