// ============================================================================
//  Lab 24 · TIMED LAB (50 min) · Postfix and Min Stack              DO NOT EDIT
// ============================================================================
#pragma once

#include <stack>
#include <string>
#include <vector>

// Part A · L24-A · LeetCode 150: evaluate tokens in postfix (Reverse Polish) notation.
// Operators + - * /, division truncates toward zero. The expression is valid.
int evalRPN(const std::vector<std::string>& tokens);

// Part B · L24-B · LeetCode 155: a stack that also returns its minimum in O(1).
class MinStack {
public:
    void push(int val);
    void pop();          // precondition: not empty
    int top() const;     // precondition: not empty
    int getMin() const;  // precondition: not empty
private:
    std::stack<int> values;
    std::stack<int> mins;   // mins.top() is the minimum of everything in values
};

// Part C · L24-C · infix -> postfix. Operands are single letters or digits; operators
// + - * / (usual precedence, left associative) and parentheses. Output: no spaces.
// Example: "a+b*c" -> "abc*+". The input is valid.
std::string toPostfix(const std::string& infix);

// L24-X · Optional · LeetCode 682 Baseball Game.
int calPoints(const std::vector<std::string>& operations);

// L24-V · Optional · memory variant: evaluate a postfix string of single digits, e.g. "93-".
int evalPostfixDigits(const std::string& s);
