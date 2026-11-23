// ============================================================================
//  Challenge Set 07 · queues and deques · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C07        one problem:  .\run.ps1 C07 C07-C
// ============================================================================
#include "challenge07.h"

#include <deque>
#include <queue>

#include "todo.h"

using namespace std;

// C07-A · Example: "RDD"  =>  "Dire"
// @begin predictPartyVictory
string predictPartyVictory(const string& senate) {
    int n = senate.size();
    queue<int> r, d;                         // indexes = turn order of each party
    for (int i = 0; i < n; i++) (senate[i] == 'R' ? r : d).push(i);
    while (!r.empty() && !d.empty()) {
        int a = r.front(), b = d.front();
        r.pop();
        d.pop();
        if (a < b) r.push(a + n);            // the earlier one bans the other and votes again
        else d.push(b + n);                  // next round (index + n keeps the order)
    }
    return r.empty() ? "Dire" : "Radiant";
}
// @end predictPartyVictory

// C07-B · Example: k = 3: insertLast 1, insertLast 2, insertFront 3, insertFront 4 (false), getRear 2
// @begin MyCircularDeque
MyCircularDeque::MyCircularDeque(int k)
    : a(k), head(0), count(0) {
}
// @end MyCircularDeque

// @begin insertFront
bool MyCircularDeque::insertFront(int value) {
    if (isFull()) return false;
    int k = a.size();
    head = (head - 1 + k) % k;               // step back, wrapping to the end
    a[head] = value;
    count++;
    return true;
}
// @end insertFront

// @begin insertLast
bool MyCircularDeque::insertLast(int value) {
    if (isFull()) return false;
    a[(head + count) % (int)a.size()] = value;   // the slot after the last element
    count++;
    return true;
}
// @end insertLast

// @begin deleteFront
bool MyCircularDeque::deleteFront() {
    if (isEmpty()) return false;
    head = (head + 1) % (int)a.size();
    count--;
    return true;
}
// @end deleteFront

// @begin deleteLast
bool MyCircularDeque::deleteLast() {
    if (isEmpty()) return false;
    count--;                                 // the last slot is simply forgotten
    return true;
}
// @end deleteLast

// @begin getFront
int MyCircularDeque::getFront() const {
    return isEmpty() ? -1 : a[head];
}
// @end getFront

// @begin getRear
int MyCircularDeque::getRear() const {
    return isEmpty() ? -1 : a[(head + count - 1) % (int)a.size()];
}
// @end getRear

// @begin isEmptyD
bool MyCircularDeque::isEmpty() const {
    return count == 0;
}
// @end isEmptyD

// @begin isFullD
bool MyCircularDeque::isFull() const {
    return count == (int)a.size();
}
// @end isFullD

// C07-C · Example: {1,3,-1,-3,5,3,6,7}, k = 3  =>  {3,3,5,5,6,7}
// @begin maxSlidingWindow
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    deque<int> dq;                           // indexes; their values DEcrease front to back
    vector<int> out;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();          // left the window
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back(); // can never be max
        dq.push_back(i);
        if (i >= k - 1) out.push_back(nums[dq.front()]);
    }
    return out;
}
// @end maxSlidingWindow
