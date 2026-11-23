// ============================================================================
//  Lab 29 · MIDTERM MOCK A (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a 50-minute timer.   Test:  .\run.ps1 L29      one part:  .\run.ps1 L29 L29-C
// ============================================================================
#include "mock29.h"

#include "todo.h"

using namespace std;

// Part A · Example: from top -> 9, 4; to top -> 7  =>  true; from top -> 4; to top -> 9, 7
// @begin moveTopSlides
bool moveTopSlides(Stack& from, Stack& to) {
    StackItemType x;
    if (!from.getTop(x)) return false;   // empty source
    if (!to.push(x)) return false;       // target full: nothing was removed yet
    from.pop();                          // only now remove it from the source
    return true;
}
// @end moveTopSlides

// Part B · Example: top -> 5, 1, 8, 3, x = 4  =>  2
// @begin countAbove
int countAbove(stack<int> st, int x) {
    int n = 0;
    while (!st.empty()) {                // !empty: "while something is left"
        if (st.top() > x) n++;
        st.pop();
    }
    return n;                            // the caller's stack was never touched (copy)
}
// @end countAbove

// Part C · Example: 1 <-> 2 <-> 3 <-> 4  =>  true, 1 <-> 2 <-> 4
// @begin deleteMiddleDLL
bool deleteMiddleDLL(DNode*& head, DNode*& tail) {
    if (head == nullptr) return false;
    DNode* slow = head;                  // with prev links we can stop ON the middle
    DNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    DNode* mid = slow;                   // index n/2
    if (mid->prev) mid->prev->next = mid->next;
    else head = mid->next;               // n = 1: the head was the middle
    if (mid->next) mid->next->prev = mid->prev;
    else tail = mid->prev;               // the tail was the middle (n = 1 or 2)
    delete mid;
    return true;
}
// @end deleteMiddleDLL
