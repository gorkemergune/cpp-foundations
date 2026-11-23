// ============================================================================
//  Lab 23 · Two stacks (midterm topics)                             DO NOT EDIT
//  Only std::stack's push, top, pop and empty are allowed in this lab.
// ============================================================================
#pragma once

#include <stack>
#include <string>
#include <vector>

// L23-A · Warm-up · move the top of `from` onto `to`. Empty `from`: false, nothing changes.
bool moveTop(std::stack<int>& from, std::stack<int>& to);

// L23-B · Warm-up · move every element of `from` onto `to` (their order flips).
void moveAll(std::stack<int>& from, std::stack<int>& to);

// L23-M1 · Main (midterm) · is b the reverse of a? Use exactly two stacks of char.
bool areReverses(const std::string& a, const std::string& b);

// L23-M2 · Main · LeetCode 232: a FIFO queue built from two stacks.
class MyQueue {
public:
    void push(int x);    // to the back
    int pop();           // remove and return the front (precondition: not empty)
    int peek();          // the front (precondition: not empty)
    bool empty() const;
private:
    std::stack<int> in, out;
};

// L23-X · Optional · LeetCode 946: can `popped` be produced by pushing `pushed` in order?
bool validateStackSequences(const std::vector<int>& pushed, const std::vector<int>& popped);

// L23-V · Optional · memory variant: sort so that the SMALLEST is on top, using one extra stack.
void sortStack(std::stack<int>& s);
