// ============================================================================
//  Lab 30 · MIDTERM MOCK B (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a 50-minute timer.   Test:  .\run.ps1 L30      one part:  .\run.ps1 L30 L30-B
// ============================================================================
#include "mock30.h"

#include "todo.h"

using namespace std;

// Part A · Example: "a12b-3c5"  =>  true, out = -3
// @begin minNumberInText
bool minNumberInText(const string& s, int& out) {
    bool found = false;
    int best = 0;
    int n = s.size();
    for (int i = 0; i < n;) {
        if (s[i] < '0' || s[i] > '9') { i++; continue; }
        bool negative = i > 0 && s[i - 1] == '-';
        int value = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') value = value * 10 + (s[i++] - '0');
        if (negative) value = -value;
        if (!found || value < best) best = value;   // the first number becomes the temp
        found = true;
    }
    if (found) out = best;
    return found;
}
// @end minNumberInText

// Part B · Example: "stack", "kcats"  =>  true
// @begin areReversesSlides
bool areReversesSlides(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    Stack sa, sb;
    for (char c : a) sa.push(c);                                  // pops: a backwards
    for (int i = (int)b.size() - 1; i >= 0; i--) sb.push(b[i]);   // pops: b forwards
    StackItemType x, y;
    while (sa.pop(x) && sb.pop(y))
        if (x != y) return false;
    return true;
}
// @end areReversesSlides

// Part C · Example: 1..9, n = 9, g = 3  =>  3 2 1 4 5 6 9 8 7
// @begin reverseAlternateGroupsSlides
void reverseAlternateGroupsSlides(Queue& q, int n, int g) {
    Stack st;
    QueueItemType x;
    for (int start = 0, group = 0; start < n; start += g, group++) {
        int len = (n - start < g) ? n - start : g;
        if (group % 2 == 0 && len == g) {
            for (int i = 0; i < g; i++) { q.dequeue(x); st.push(x); }
            while (st.pop(x)) q.enqueue(x);
        } else {
            for (int i = 0; i < len; i++) { q.dequeue(x); q.enqueue(x); }
        }
    }
}
// @end reverseAlternateGroupsSlides
