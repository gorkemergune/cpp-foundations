// ============================================================================
//  Lab 45 · Heapsort and priority_queue · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L45
// ============================================================================
#include "lab45.h"

#include <functional>
#include <queue>

#include "todo.h"

using namespace std;

// L45-A · Example: {3, 1, 2}  =>  {3, 2, 1}
// @begin drainMaxFirst
vector<int> drainMaxFirst(const vector<int>& v) {
    priority_queue<int> pq(v.begin(), v.end());   // a max-heap by default
    vector<int> out;
    while (!pq.empty()) {
        out.push_back(pq.top());            // top() reads, pop() removes (like std::stack)
        pq.pop();
    }
    return out;
}
// @end drainMaxFirst

// L45-B · Example: {3, 1, 2}  =>  {1, 2, 3}
// @begin drainMinFirst
vector<int> drainMinFirst(const vector<int>& v) {
    priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.end());
    vector<int> out;
    while (!pq.empty()) {
        out.push_back(pq.top());
        pq.pop();
    }
    return out;
}
// @end drainMinFirst

// L45-M1 · Example: {6, 3, 5, 9, 2, 10}  =>  {2, 3, 5, 6, 9, 10}
// @begin rebuild
// Lab 43's heapRebuild, written as a loop
void rebuild(vector<int>& a, int root, int n) {
    while (2 * root + 1 < n) {
        int child = 2 * root + 1;
        if (child + 1 < n && a[child + 1] > a[child]) child++;
        if (a[root] >= a[child]) return;
        swap(a[root], a[child]);
        root = child;
    }
}
// @end rebuild

// @begin heapSort
void heapSort(vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--) rebuild(a, i, n);   // slide 23: build a heap
    for (int last = n - 1; last > 0; last--) {
        swap(a[0], a[last]);                // the largest goes to the sorted region
        rebuild(a, 0, last);                // the heap is a[0 .. last-1] now
    }
}
// @end heapSort

// L45-M2 · Example: {3, 2, 1, 5, 6, 4}, k = 2  =>  5
// @begin findKthLargest
int findKthLargest(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> best;   // the k largest; top = smallest of them
    for (int x : nums) {
        best.push(x);
        if ((int)best.size() > k) best.pop();   // drop the smallest: it is not in the top k
    }
    return best.top();
}
// @end findKthLargest

// L45-M3 · Example: {6, 5, 3, 2, 8, 10, 9}, k = 3  =>  {2, 3, 5, 6, 8, 9, 10}
// @begin sortKSorted
vector<int> sortKSorted(const vector<int>& a, int k) {
    priority_queue<int, vector<int>, greater<int>> window;
    vector<int> out;
    for (int x : a) {
        window.push(x);
        if ((int)window.size() > k) {       // k+1 values: the smallest is surely next
            out.push_back(window.top());
            window.pop();
        }
    }
    while (!window.empty()) {
        out.push_back(window.top());
        window.pop();
    }
    return out;
}
// @end sortKSorted

// L45-X · Example: {(1,3), (-2,2)}, k = 1  =>  {(-2,2)}
// @begin kClosest
vector<pair<int, int>> kClosest(const vector<pair<int, int>>& points, int k) {
    priority_queue<pair<long long, int>> far;   // (distance², index): top = the farthest kept
    for (int i = 0; i < (int)points.size(); i++) {
        long long x = points[i].first, y = points[i].second;
        far.push({x * x + y * y, i});
        if ((int)far.size() > k) far.pop();
    }
    vector<pair<int, int>> out;
    while (!far.empty()) {
        out.push_back(points[far.top().second]);
        far.pop();
    }
    return out;
}
// @end kClosest

// L45-V · Example: {"ccc", "a", "bb", "aa"}  =>  {"a", "aa", "bb", "ccc"}
// @begin byLength
vector<string> byLength(const vector<string>& words) {
    struct ByLength {                       // a comparator: true when a comes out AFTER b
        bool operator()(const string& a, const string& b) const {
            if (a.size() != b.size()) return a.size() > b.size();
            return a > b;
        }
    };
    priority_queue<string, vector<string>, ByLength> pq(words.begin(), words.end());
    vector<string> out;
    while (!pq.empty()) {
        out.push_back(pq.top());
        pq.pop();
    }
    return out;
}
// @end byLength
