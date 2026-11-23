// ============================================================================
//  Lab 21 · std::stack and the slides' Stack · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L21
//  std::stack: push, top, pop (void!), empty.   Slides Stack: see SlidesStack.h.
// ============================================================================
#include "lab21.h"

#include "todo.h"

using namespace std;

// L21-A · Example: top -> 3, 2, 1  =>  6, stack empty
// @begin popAllSum
int popAllSum(stack<int>& st) {
    int sum = 0;
    while (!st.empty()) {        // "while there is something": !empty()
        sum += st.top();         // read first ...
        st.pop();                // ... then remove (pop() returns nothing)
    }
    return sum;
}
// @end popAllSum

// L21-B · Example: the same values in the slides' Stack  =>  6
// @begin popAllSumSlides
int popAllSumSlides(Stack& st) {
    int sum = 0;
    StackItemType x;
    while (st.pop(x)) sum += x;  // pop(item&) reads AND removes, false when empty
    return sum;
}
// @end popAllSumSlides

// L21-M1 · Example: "{[()]}"  =>  true;  "([)]"  =>  false;  "(("  =>  false
// @begin isValid
bool isValid(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;              // a closer with nothing open
            char open = st.top();
            st.pop();
            if ((c == ')' && open != '(') || (c == ']' && open != '[') || (c == '}' && open != '{'))
                return false;
        }
    }
    return st.empty();                                 // something still open -> false
}
// @end isValid

// L21-M2 · Same examples as M1.
// @begin isValidSlides
bool isValidSlides(const string& s) {
    Stack st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            if (!st.push(c)) return false;             // deeper than MAX_STACK
        } else {
            StackItemType open;
            if (!st.pop(open)) return false;           // empty: pop(item&) says false
            char want = c == ')' ? '(' : c == ']' ? '[' : '{';
            if (open != want) return false;
        }
    }
    return st.isEmpty();
}
// @end isValidSlides

// L21-X · Example: "abbaca"  =>  "ca"
// @begin removeDuplicates
string removeDuplicates(const string& s) {
    string st;                                         // a string used as a stack
    for (char c : s) {
        if (!st.empty() && st.back() == c) st.pop_back();
        else st.push_back(c);
    }
    return st;
}
// @end removeDuplicates

// L21-V · Example: top -> 3, 9, 1  =>  9, stack still top -> 3, 9, 1
// @begin maxKeep
int maxKeep(Stack& st) {
    Stack tmp;
    StackItemType x, best;
    st.getTop(best);
    while (st.pop(x)) {                                // pour into tmp ...
        if (x > best) best = x;
        tmp.push(x);
    }
    while (tmp.pop(x)) st.push(x);                     // ... and back: original order again
    return best;
}
// @end maxKeep
