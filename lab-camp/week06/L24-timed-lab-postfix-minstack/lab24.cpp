// ============================================================================
//  Lab 24 · TIMED LAB (50 min) · YOU WORK HERE
//  Start a timer. Test:  .\run.ps1 L24      one part:  .\run.ps1 L24 L24-C
//  Allowed: std::stack, std::stoi. Remember: std::stack::pop returns nothing.
// ============================================================================
#include "lab24.h"

#include "todo.h"

using namespace std;

// Part A · Example: {"2","1","+","3","*"}  =>  9
int evalRPN(const vector<string>& tokens) {
    TODO();
}

// Part B · Example: push -2, push 0, push -3, getMin -3, pop, top 0, getMin -2
void MinStack::push(int val) {
    TODO();
}

void MinStack::pop() {
    TODO();
}

int MinStack::top() const {
    TODO();
}

int MinStack::getMin() const {
    TODO();
}

// Part C · Example: "a*(b-c)/d+e"  =>  "abc-*d/e+"
string toPostfix(const string& infix) {
    TODO();
}

// L24-X · Example: {"5","2","C","D","+"}  =>  30
int calPoints(const vector<string>& operations) {
    TODO();
}

// L24-V · Example: "93-"  =>  6;  "234*+"  =>  14
int evalPostfixDigits(const string& s) {
    TODO();
}
