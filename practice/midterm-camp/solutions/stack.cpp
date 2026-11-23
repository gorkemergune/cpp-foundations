// ============================================================================
//  STACK · ST-1 … ST-10 · reference solutions
//  Run the tests against this file:  .\run.ps1 -Solution st
// ============================================================================
#include "../ds/LLStack.h"

template <typename T>
int LLStack<T>::size() {
    int n = 0;
    for (stackNode<T>* p = top; p != 0; p = p->next) n++;
    return n;
}

template <typename T>
T LLStack<T>::peek() {
    if (isEmpty()) throw runtime_error("peek: stack is empty");
    return top->info;
}

template <typename T>
bool LLStack<T>::contains(const T& v) {
    for (stackNode<T>* p = top; p != 0; p = p->next)
        if (p->info == v) return true;
    return false;
}

string reverseString(const string& s) {
    LLStack<char> st;
    for (char c : s) st.pushToStack(c);
    string r;
    while (!st.isEmpty()) r += st.popFromStack();
    return r;
}

bool isBalanced(const string& s) {
    LLStack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.pushToStack(c);
        } else if (c == ')' || c == ']' || c == '}') {
            char open = c == ')' ? '(' : c == ']' ? '[' : '{';
            if (st.isEmpty() || st.popFromStack() != open) return false;
        }
    }
    return st.isEmpty();                     // "((" leaves something behind
}

// Two pours: this -> a reverses, a -> b restores, b -> this reverses once more.
template <typename T>
void LLStack<T>::reverseStack() {
    LLStack<T> a, b;
    while (!isEmpty()) a.pushToStack(popFromStack());
    while (!a.isEmpty()) b.pushToStack(a.popFromStack());
    while (!b.isEmpty()) pushToStack(b.popFromStack());
}

int evalPostfix(const string& s) {
    LLStack<int> st;
    for (char c : s) {
        if (c == ' ') continue;
        if (c >= '0' && c <= '9') {
            st.pushToStack(c - '0');
        } else {
            int right = st.popFromStack();    // popped first = right operand
            int left = st.popFromStack();
            st.pushToStack(c == '+' ? left + right : c == '-' ? left - right : c == '*' ? left * right : left / right);
        }
    }
    return st.popFromStack();
}

template <typename T>
int LLStack<T>::removeAll(const T& v) {
    LLStack<T> keep;
    int removed = 0;
    while (!isEmpty()) {
        T x = popFromStack();
        if (x == v) removed++;
        else keep.pushToStack(x);           // reversed order in keep
    }
    while (!keep.isEmpty()) pushToStack(keep.popFromStack());   // back in the original order
    return removed;
}

// Insertion sort with one helper stack. tmp keeps the LARGEST on top while we work;
// moving everything back at the end puts the smallest on top.
template <typename T>
void LLStack<T>::sortStack() {
    LLStack<T> tmp;
    while (!isEmpty()) {
        T x = popFromStack();
        while (!tmp.isEmpty() && tmp.peek() > x) pushToStack(tmp.popFromStack());
        tmp.pushToStack(x);
    }
    while (!tmp.isEmpty()) pushToStack(tmp.popFromStack());
}

// Right to left: the stack keeps candidates that are greater than everything after them.
vector<int> nextGreater(const vector<int>& a) {
    vector<int> r(a.size(), -1);
    LLStack<int> st;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        while (!st.isEmpty() && st.peek() <= a[i]) st.popFromStack();
        if (!st.isEmpty()) r[i] = st.peek();
        st.pushToStack(a[i]);
    }
    return r;
}
