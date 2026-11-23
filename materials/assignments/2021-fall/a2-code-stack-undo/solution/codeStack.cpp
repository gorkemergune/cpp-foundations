// Assignment 2 (2021) · reference solution for codeStack (header unchanged).
#include "codeStack.h"

#include <iostream>
#include <string>

using namespace std;

codeStack::~codeStack() {
    while (!isEmpty()) {
        stackNode* p = top->next;
        delete top;
        top = p;
    }
}

// The new node points to the old top and becomes the top: O(1).
void codeStack::pushToStack(const char* s) { top = new stackNode(s, top); }

// Removes the top line and returns it. On an empty stack it prints the error message
// of the given code and returns "" (the given code fell off the end without a return,
// which is undefined behaviour for a function that returns string).
string codeStack::popFromStack() {
    if (top != 0) {
        stackNode* old = top;
        string s = old->info;      // copy the text BEFORE deleting the node
        top = old->next;
        delete old;
        return s;
    }
    cout << "Error: Nothing to delete." << endl;
    return "";
}

// Newest line first (top to bottom). Reading the nodes does not change the stack.
void codeStack::printStack() {
    for (stackNode* p = top; p != 0; p = p->next) cout << p->info << endl;
}

// Oldest line first = document order. A second stack reverses the order once more.
void codeStack::printReverseStack() {
    codeStack tmp;
    for (stackNode* p = top; p != 0; p = p->next) tmp.pushToStack(p->info.c_str());
    tmp.printStack();
}
