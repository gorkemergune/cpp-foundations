// ============================================================================
//  Lab 27 · queue + one stack · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L27
//  Rotation pattern: read the size n ONCE, then handle exactly n elements.
// ============================================================================
#include "lab27.h"

#include "todo.h"

using namespace std;

// L27-A · Example: front -> 1, 2, 3  =>  front -> 3, 2, 1
// @begin reverseQueue
void reverseQueue(queue<int>& q) {
    stack<int> st;
    while (!q.empty()) { st.push(q.front()); q.pop(); }   // queue order goes in ...
    while (!st.empty()) { q.push(st.top()); st.pop(); }   // ... and comes out reversed
}
// @end reverseQueue

// L27-B · Example: front -> 1, 2, 3, 4, 5, k = 3  =>  front -> 3, 2, 1, 4, 5
// @begin reverseFirstK
void reverseFirstK(queue<int>& q, int k) {
    int n = q.size();
    if (k <= 0 || k > n) return;
    stack<int> st;
    for (int i = 0; i < k; i++) { st.push(q.front()); q.pop(); }
    while (!st.empty()) { q.push(st.top()); st.pop(); }  // reversed k are now at the back
    for (int i = 0; i < n - k; i++) { q.push(q.front()); q.pop(); }   // move the rest behind
}
// @end reverseFirstK

// L27-M · Example: front -> 1 .. 9  =>  front -> 3, 2, 1, 4, 5, 6, 9, 8, 7
// @begin reverseAlternateTriples
void reverseAlternateTriples(queue<int>& q) {
    int n = q.size();                       // every element is moved to the back exactly once
    stack<int> st;
    for (int start = 0, group = 0; start < n; start += 3, group++) {
        int len = (n - start < 3) ? n - start : 3;     // the last group may be shorter
        if (group % 2 == 0 && len == 3) {              // 1st, 3rd, 5th ... complete group
            for (int i = 0; i < 3; i++) { st.push(q.front()); q.pop(); }
            while (!st.empty()) { q.push(st.top()); st.pop(); }
        } else {                                       // keep the order: rotate
            for (int i = 0; i < len; i++) { q.push(q.front()); q.pop(); }
        }
    }
}
// @end reverseAlternateTriples

// L27-X · Example: reverseFirstKGfG({1, 2, 3, 4, 5}, 3) returns {3, 2, 1, 4, 5}
// @begin reverseFirstKGfG
queue<int> reverseFirstKGfG(queue<int> q, int k) {
    reverseFirstK(q, k);                    // q is our own copy
    return q;
}
// @end reverseFirstKGfG

// L27-V · Example: front -> 1 .. 7, g = 3  =>  front -> 3, 2, 1, 6, 5, 4, 7
// @begin reverseGroups
void reverseGroups(queue<int>& q, int g) {
    int n = q.size();
    stack<int> st;
    for (int start = 0; start < n; start += g) {
        int len = (n - start < g) ? n - start : g;
        if (len == g) {
            for (int i = 0; i < g; i++) { st.push(q.front()); q.pop(); }
            while (!st.empty()) { q.push(st.top()); st.pop(); }
        } else {
            for (int i = 0; i < len; i++) { q.push(q.front()); q.pop(); }
        }
    }
}
// @end reverseGroups
