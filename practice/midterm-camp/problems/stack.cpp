// ============================================================================
//  STACK · ST-1 … ST-10
//  Delete the TODO(); line in a function and write your own code.
//  Test:  .\run.ps1 st        single problem:  .\run.ps1 ST-5
//  Available: top, pushToStack(x), popFromStack(), isEmpty(), printStack()
// ============================================================================
#include "../ds/LLStack.h"

// ST-1 · Easy · Stack size
// Return the number of elements. The stack must stay unchanged.
// Example: top → 5, 2, 9  ⇒  3
template <typename T>
int LLStack<T>::size() {
    stackNode<T>* p = top;
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// ST-2 · Easy · Peek at the top
// Return the top element without removing it. Throw runtime_error if empty.
// Example: top → 5, 2  ⇒  5 (stack unchanged)
template <typename T>
T LLStack<T>::peek() {
    if (isEmpty()) {
        throw runtime_error("peek: stack is empty");
    }
    return top->info;
}

// ST-3 · Easy · Contains
// Return true if v is in the stack. The stack must stay unchanged.
// Example: top → 4, 7, 1, v = 7  ⇒  true
template <typename T>
bool LLStack<T>::contains(const T& v) {
    stackNode<T>* p = top;
    while (p != NULL) {
        if (p->info == v) return true;  
        p = p->next;
    } return false;
}

// ST-4 · Easy · Reverse a string with a stack
// Reverse s using an LLStack<char>.
// Example: "abc"  ⇒  "cba"
string reverseString(const string& s) {
    LLStack<char> st;
    for (size_t i = 0; i < s.length(); i++) {
        st.pushToStack(s[i]);
    }
    string res = "";
    while (!st.isEmpty()) {
        res += st.popFromStack();
    }
    return res;

}

// ST-5 · Medium · Balanced brackets
// Is a string containing ( ) [ ] { } balanced? Ignore all other characters.
// Example: "{[()]}" ⇒ true | "([)]" ⇒ false | "((" ⇒ false
bool isBalanced(const string& s) {
    LLStack<char> br;
    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            br.pushToStack(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (br.isEmpty()) {
                return false;
            }
            char t = br.popFromStack();
            if ((c == ')' && t != '(') || (c == ']' && t != '[') || (c == '}' && t != '{' )) {
                return false;
            }
        }
    }
    return br.isEmpty();
}

// ST-6 · Medium · Reverse the stack
// Reverse it using only push/pop and temporary stacks (no pointer manipulation).
// Example: top → 1, 2, 3  ⇒  top → 3, 2, 1
template <typename T>
void LLStack<T>::reverseStack() {
    TODO();
}

// ST-7 · Medium · Evaluate a postfix expression
// Evaluate a postfix expression with single-digit numbers and + - * /. Ignore spaces.
// Example: "2 3 4 * +" ⇒ 14 | "9 3 / 2 -" ⇒ 1
int evalPostfix(const string& s) {
    TODO();
}

// ST-8 · Medium · Remove all occurrences
// Remove every element equal to v. Keep the order of the rest. Return how many were removed.
// Example: top → 3, 7, 3, 1, v = 3  ⇒  top → 7, 1  (returns 2)
template <typename T>
int LLStack<T>::removeAll(const T& v) {
    TODO();
}

// ST-9 · Hard · Sort the stack
// Using only ONE temporary stack, sort so that the smallest element is on top.
// Example: top → 3, 1, 4, 2  ⇒  top → 1, 2, 3, 4
template <typename T>
void LLStack<T>::sortStack() {
    TODO();
}

// ST-10 · Hard · Next greater element
// For each a[i], find the first greater element to its right, or -1. Use an LLStack<int>.
// Example: {4, 5, 2, 10, 8}  ⇒  {5, 10, 10, -1, -1}
vector<int> nextGreater(const vector<int>& a) {
    TODO();
}
