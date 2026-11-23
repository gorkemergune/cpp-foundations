// ============================================================================
//  Lab 22 · Your own linked stack template LLStack<T> · YOU WORK HERE (whole file)
//  Names as in 2021 Assignment 2 (codeStack) and the old midterm camp:
//  pushToStack, popFromStack (RETURNS the value), isEmpty, peek.
//  Test:  .\run.ps1 L22
// ============================================================================
#ifndef LLSTACK_H
#define LLSTACK_H

#include <stdexcept>
#include <vector>

#include "todo.h"

template <typename T>
class stackNode {
public:
    stackNode(const T& el, stackNode<T>* ptr = nullptr) : info(el), next(ptr) { alive++; created++; }
    ~stackNode() { alive--; }
    T info;
    stackNode<T>* next;
    static inline int alive = 0;          // lab camp: leak checks
    static inline int created = 0;        // lab camp: nodes ever constructed
};

template <typename T>
class LLStack {
public:
    LLStack() : top(nullptr), count(0) {}
    ~LLStack() { clear(); }
    LLStack(const LLStack<T>& other);                 // L22-X · deep copy, same order
    LLStack<T>& operator=(const LLStack<T>&) = delete;

    bool isEmpty() const;                             // L22-A
    void pushToStack(const T& el);                    // L22-A
    int size() const;                                 // L22-A · O(1)
    T popFromStack();                                 // L22-B · runtime_error if empty
    T peek() const;                                   // L22-B · runtime_error if empty
    void clear();                                     // L22-M1 · delete every node
    bool pushFromStack(LLStack<T>& source);           // L22-M2 · practice signature
    void reverse();                                   // L22-V · relink, no new nodes

    std::vector<T> toVector() const {                 // test helper: top first
        std::vector<T> r;
        for (stackNode<T>* p = top; p != nullptr; p = p->next) r.push_back(p->info);
        return r;
    }

private:
    stackNode<T>* top;
    int count;
};

// L22-A
template <typename T>
bool LLStack<T>::isEmpty() const {
    TODO();
}

// L22-A · Example: push 1, 2, 3  =>  top -> 3, 2, 1
template <typename T>
void LLStack<T>::pushToStack(const T& el) {
    TODO();
}

template <typename T>
int LLStack<T>::size() const {
    TODO();
}

// L22-B · Example: top -> 3, 2, 1  =>  returns 3, top -> 2, 1
template <typename T>
T LLStack<T>::popFromStack() {
    TODO();
}

template <typename T>
T LLStack<T>::peek() const {
    TODO();
}

// L22-M1 · the destructor calls clear(); it must not throw
template <typename T>
void LLStack<T>::clear() {
    // TODO: write this (it must not throw)
}

// L22-M2 · move the top of source onto this stack (the NODE moves, nothing is copied).
// Example: this top -> 9, source top -> 4, 7  =>  true; this top -> 4, 9; source top -> 7
template <typename T>
bool LLStack<T>::pushFromStack(LLStack<T>& source) {
    TODO();
}

// L22-X · copy constructor: new nodes, same values, same order
template <typename T>
LLStack<T>::LLStack(const LLStack<T>& other) {
    TODO();
}

// L22-V · Example: top -> 1, 2, 3  =>  top -> 3, 2, 1 (same nodes)
template <typename T>
void LLStack<T>::reverse() {
    TODO();
}

#endif
