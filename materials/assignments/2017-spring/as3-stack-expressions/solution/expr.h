// Assignment 3 (2017) · stack algorithms with a printed trace of the stack after every step.
#pragma once
#include <string>
#include <vector>

// Q1 · brackets ()[]{}; every other character is ignored.
// trace gets one line per bracket: "read ( -> stack: ( [".
bool balanced(const std::string& s, std::vector<std::string>* trace = nullptr);

// Q2 · infix -> postfix (shunting-yard). Operands: letters or (multi-digit) numbers.
// Operators + - * / with the usual precedence, left associative. Tokens separated by one space.
std::string toPostfix(const std::string& infix, std::vector<std::string>* trace = nullptr);

// Q3 · evaluates a postfix string made by toPostfix (integer arithmetic, / truncates).
long long evalPostfix(const std::string& postfix, std::vector<std::string>* trace = nullptr);
