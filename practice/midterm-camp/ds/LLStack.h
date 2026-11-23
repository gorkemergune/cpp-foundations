// Linked-list based stack (same names as the lab: stackNode, top,
// pushToStack, popFromStack, isEmpty).
// The functions you write live in: problems/stack.cpp
#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../framework/test.h"

using namespace std;

template <typename T>
class stackNode {
public:
    stackNode(const T& el, stackNode<T>* ptr = 0) {
        info = el;
        next = ptr;
    }
    T info;
    stackNode<T>* next;
};

template <typename T>
class LLStack {
public:
    LLStack() { top = 0; }
    ~LLStack() {
        while (!isEmpty()) popFromStack();
    }
    LLStack(const LLStack&) = delete;
    LLStack& operator=(const LLStack&) = delete;

    bool isEmpty() const { return top == 0; }

    void pushToStack(const T& el) { top = new stackNode<T>(el, top); }

    T popFromStack() {
        if (isEmpty()) throw runtime_error("popFromStack: stack is empty");
        stackNode<T>* p = top;
        T el = p->info;
        top = top->next;
        delete p;
        return el;
    }

    // For debugging: s.printStack();  →  top -> 5 2 9
    void printStack() const {
        cout << "top ->";
        for (stackNode<T>* p = top; p != 0; p = p->next) cout << " " << p->info;
        cout << endl;
    }

    // ---------------- problems (problems/stack.cpp) ----------------
    int size();                    // ST-1
    T peek();                      // ST-2
    bool contains(const T& v);     // ST-3
    void reverseStack();           // ST-6
    int removeAll(const T& v);     // ST-8
    void sortStack();              // ST-9

    // ---------------- test helpers ----------------
    // fill({5, 2, 9}) → 5 is on top
    void fill(const vector<T>& topToBottom) {
        for (int i = (int)topToBottom.size() - 1; i >= 0; i--) pushToStack(topToBottom[i]);
    }
    vector<T> toVector() const {  // top to bottom
        vector<T> r;
        for (stackNode<T>* p = top; p != 0; p = p->next) r.push_back(p->info);
        return r;
    }

private:
    stackNode<T>* top;
};
