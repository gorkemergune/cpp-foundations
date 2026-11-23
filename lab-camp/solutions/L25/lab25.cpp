// ============================================================================
//  Lab 25 · std::queue and the slides' Queue · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L25
//  std::queue: push (back), front, back, pop (void!), empty, size.
// ============================================================================
#include "lab25.h"

#include "todo.h"

using namespace std;

// L25-A · Example: front -> 1, 2, 3  =>  {1, 2, 3}, queue empty
// @begin drainStd
vector<int> drainStd(queue<int>& q) {
    vector<int> out;
    while (!q.empty()) {
        out.push_back(q.front());     // read ...
        q.pop();                      // ... then remove
    }
    return out;
}
// @end drainStd

// L25-B · Example: the same values in the slides' Queue  =>  {1, 2, 3}
// @begin drainSlides
vector<int> drainSlides(Queue& q) {
    vector<int> out;
    QueueItemType x;
    while (q.dequeue(x)) out.push_back(x);   // false when empty ends the loop
    return out;
}
// @end drainSlides

// L25-M1 · Example: ping(1) 1, ping(100) 2, ping(3001) 3, ping(3002) 3
// @begin ping
int RecentCounter::ping(int t) {
    times.enqueue(t);
    QueueItemType oldest;
    while (times.getFront(oldest) && oldest < t - 3000)
        times.dequeue();              // too old: just remove, the value is not needed
    int n = 0;                        // the slides' Queue has no size(): count on a copy
    Queue copy(times);
    QueueItemType x;
    while (copy.dequeue(x)) n++;
    return n;
}
// @end ping

// L25-M2 · Example: a = 1 2 3, b = 1 2 3  =>  true;  a = 1 2, b = 1 2 3  =>  false
// @begin sameQueue
bool sameQueue(const Queue& a, const Queue& b) {
    Queue ca(a), cb(b);               // copies: the originals stay untouched
    QueueItemType x, y;
    while (true) {
        bool gotA = ca.dequeue(x);
        bool gotB = cb.dequeue(y);
        if (gotA != gotB) return false;       // one ended earlier: different lengths
        if (!gotA) return true;               // both ended together
        if (x != y) return false;
    }
}
// @end sameQueue

// L25-X · Example: students {1,1,0,0}, sandwiches {0,1,0,1}  =>  0
// @begin countStudents
int countStudents(const vector<int>& students, const vector<int>& sandwiches) {
    queue<int> q;
    for (int s : students) q.push(s);
    size_t top = 0;
    int refusals = 0;                 // students in a row who did not take the top sandwich
    while (!q.empty() && refusals < (int)q.size()) {
        if (q.front() == sandwiches[top]) {
            q.pop();
            top++;
            refusals = 0;
        } else {
            q.push(q.front());        // to the back of the line
            q.pop();
            refusals++;
        }
    }
    return (int)q.size();
}
// @end countStudents

// L25-V · Example: front -> 1, 2, 3, 4, 5, k = 7  =>  front -> 3, 4, 5, 1, 2
// @begin rotateK
void rotateK(queue<int>& q, int k) {
    if (q.empty()) return;
    k %= (int)q.size();
    for (int i = 0; i < k; i++) {
        q.push(q.front());
        q.pop();
    }
}
// @end rotateK
