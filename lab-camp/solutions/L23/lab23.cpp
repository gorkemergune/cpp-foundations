// ============================================================================
//  Lab 23 · Two stacks · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L23
//  Allowed: push, top, pop, empty of std::stack. Not allowed: other containers.
// ============================================================================
#include "lab23.h"

#include "todo.h"

using namespace std;

// L23-A · Example: from top -> 9, 4; to top -> 7  =>  true; from top -> 4; to top -> 9, 7
// @begin moveTop
bool moveTop(stack<int>& from, stack<int>& to) {
    if (from.empty()) return false;   // the guard the midterm asked about
    to.push(from.top());
    from.pop();
    return true;
}
// @end moveTop

// L23-B · Example: from top -> 1, 2, 3; to empty  =>  to top -> 3, 2, 1
// @begin moveAll
void moveAll(stack<int>& from, stack<int>& to) {
    while (!from.empty()) moveTop(from, to);
}
// @end moveAll

// L23-M1 · Example: "stack", "kcats"  =>  true
// @begin areReverses
bool areReverses(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    stack<char> sa, sb;
    for (char c : a) sa.push(c);                              // pops give a BACKWARDS
    for (int i = (int)b.size() - 1; i >= 0; i--) sb.push(b[i]);   // pops give b FORWARDS
    while (!sa.empty()) {                                     // same size: sb is not empty either
        if (sa.top() != sb.top()) return false;
        sa.pop();
        sb.pop();
    }
    return true;
}
// @end areReverses

// L23-M2 · Example: push 1, push 2, peek -> 1, pop -> 1, empty -> false
// @begin push
void MyQueue::push(int x) {
    in.push(x);                         // new elements always go to `in`
}
// @end push

// @begin pop
int MyQueue::pop() {
    int x = peek();                     // peek makes sure the front is on top of `out`
    out.pop();
    return x;
}
// @end pop

// @begin peek
int MyQueue::peek() {
    if (out.empty())                    // refill ONLY when out is empty: keeps FIFO order
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    return out.top();
}
// @end peek

// @begin queueEmpty
bool MyQueue::empty() const {
    return in.empty() && out.empty();
}
// @end queueEmpty

// L23-X · Example: pushed {1,2,3,4,5}, popped {4,5,3,2,1}  =>  true
// @begin validateStackSequences
bool validateStackSequences(const vector<int>& pushed, const vector<int>& popped) {
    stack<int> st;
    size_t j = 0;
    for (int x : pushed) {
        st.push(x);
        while (!st.empty() && j < popped.size() && st.top() == popped[j]) {
            st.pop();                   // pop greedily whenever the next wanted value is on top
            j++;
        }
    }
    return st.empty();
}
// @end validateStackSequences

// L23-V · Example: top -> 3, 1, 4, 2  =>  top -> 1, 2, 3, 4
// @begin sortStack
void sortStack(stack<int>& s) {
    stack<int> tmp;                     // kept with the LARGEST on top
    while (!s.empty()) {
        int x = s.top();
        s.pop();
        while (!tmp.empty() && tmp.top() > x) {
            s.push(tmp.top());          // bigger ones go back to s for a moment
            tmp.pop();
        }
        tmp.push(x);
    }
    while (!tmp.empty()) {              // pour back: the smallest ends on top
        s.push(tmp.top());
        tmp.pop();
    }
}
// @end sortStack
