// ============================================================================
//  Lab 23 · Two stacks · YOU WORK HERE
//  Test everything:      .\run.ps1 L23
//  Allowed: push, top, pop, empty of std::stack. Not allowed: other containers.
// ============================================================================
#include "lab23.h"

#include "todo.h"

using namespace std;

// L23-A · Example: from top -> 9, 4; to top -> 7  =>  true; from top -> 4; to top -> 9, 7
bool moveTop(stack<int>& from, stack<int>& to) {
    TODO();
}

// L23-B · Example: from top -> 1, 2, 3; to empty  =>  to top -> 3, 2, 1
void moveAll(stack<int>& from, stack<int>& to) {
    TODO();
}

// L23-M1 · Example: "stack", "kcats"  =>  true
bool areReverses(const string& a, const string& b) {
    TODO();
}

// L23-M2 · Example: push 1, push 2, peek -> 1, pop -> 1, empty -> false
void MyQueue::push(int x) {
    TODO();
}

int MyQueue::pop() {
    TODO();
}

int MyQueue::peek() {
    TODO();
}

bool MyQueue::empty() const {
    TODO();
}

// L23-X · Example: pushed {1,2,3,4,5}, popped {4,5,3,2,1}  =>  true
bool validateStackSequences(const vector<int>& pushed, const vector<int>& popped) {
    TODO();
}

// L23-V · Example: top -> 3, 1, 4, 2  =>  top -> 1, 2, 3, 4
void sortStack(stack<int>& s) {
    TODO();
}
