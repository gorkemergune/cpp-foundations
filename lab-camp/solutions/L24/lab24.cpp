// ============================================================================
//  Lab 24 · TIMED LAB (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a timer. Test:  .\run.ps1 L24      one part:  .\run.ps1 L24 L24-C
//  Allowed: std::stack, std::stoi. Remember: std::stack::pop returns nothing.
// ============================================================================
#include "lab24.h"

#include "todo.h"

using namespace std;

// Part A · Example: {"2","1","+","3","*"}  =>  9
// @begin evalRPN
int evalRPN(const vector<string>& tokens) {
    stack<int> st;
    for (const string& t : tokens) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            int right = st.top(); st.pop();       // the FIRST pop is the RIGHT operand
            int left = st.top(); st.pop();
            if (t == "+") st.push(left + right);
            else if (t == "-") st.push(left - right);
            else if (t == "*") st.push(left * right);
            else st.push(left / right);           // C++ already truncates toward zero
        } else {
            st.push(stoi(t));                     // "-11" is a number, not an operator
        }
    }
    return st.top();
}
// @end evalRPN

// Part B · Example: push -2, push 0, push -3, getMin -3, pop, top 0, getMin -2
// @begin push
void MinStack::push(int val) {
    values.push(val);
    mins.push(mins.empty() || val < mins.top() ? val : mins.top());   // min so far, per level
}
// @end push

// @begin pop
void MinStack::pop() {
    values.pop();
    mins.pop();                                   // both stacks always have the same size
}
// @end pop

// @begin top
int MinStack::top() const {
    return values.top();
}
// @end top

// @begin getMin
int MinStack::getMin() const {
    return mins.top();
}
// @end getMin

// Part C · Example: "a*(b-c)/d+e"  =>  "abc-*d/e+"
// @begin toPostfix
string toPostfix(const string& infix) {
    auto prec = [](char op) { return (op == '*' || op == '/') ? 2 : 1; };
    stack<char> ops;
    string out;
    for (char c : infix) {
        if (c == '(') {
            ops.push(c);
        } else if (c == ')') {
            while (ops.top() != '(') { out += ops.top(); ops.pop(); }
            ops.pop();                            // drop the '('
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!ops.empty() && ops.top() != '(' && prec(ops.top()) >= prec(c)) {
                out += ops.top();                 // >= : equal precedence leaves first
                ops.pop();
            }
            ops.push(c);
        } else {
            out += c;                             // operand
        }
    }
    while (!ops.empty()) { out += ops.top(); ops.pop(); }
    return out;
}
// @end toPostfix

// L24-X · Example: {"5","2","C","D","+"}  =>  30
// @begin calPoints
int calPoints(const vector<string>& operations) {
    stack<int> st;
    for (const string& op : operations) {
        if (op == "C") {
            st.pop();
        } else if (op == "D") {
            st.push(2 * st.top());
        } else if (op == "+") {
            int a = st.top(); st.pop();
            int b = st.top();
            st.push(a);
            st.push(a + b);
        } else {
            st.push(stoi(op));
        }
    }
    int sum = 0;
    while (!st.empty()) { sum += st.top(); st.pop(); }
    return sum;
}
// @end calPoints

// L24-V · Example: "93-"  =>  6;  "234*+"  =>  14
// @begin evalPostfixDigits
int evalPostfixDigits(const string& s) {
    stack<int> st;
    for (char c : s) {
        if (c >= '0' && c <= '9') { st.push(c - '0'); continue; }
        int right = st.top(); st.pop();
        int left = st.top(); st.pop();
        st.push(c == '+' ? left + right : c == '-' ? left - right : c == '*' ? left * right : left / right);
    }
    return st.top();
}
// @end evalPostfixDigits
