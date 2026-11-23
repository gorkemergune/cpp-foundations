// ============================================================================
//  Lab 44 · Min-heap archive questions · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L44
// ============================================================================
#include "lab44.h"

#include "todo.h"

using namespace std;

// L44-A · Example: {0, 1, 3, 2}  =>  true;  {0, 3, 1}  =>  false
// @begin isMinHeap
bool isMinHeap(const vector<int>& h) {
    for (int i = 2; i < (int)h.size(); i++)
        if (h[i] < h[i / 2]) return false;
    return true;
}
// @end isMinHeap

// L44-M1 · Example: {0, 9, 2, 3, 4, 5}, i = 1  =>  {0, 2, 4, 3, 9, 5}
// @begin percolateDown
void percolateDown(vector<int>& h, int i) {
    int n = h.size() - 1;
    while (2 * i <= n) {                    // i has at least a left child
        int child = 2 * i;
        if (child + 1 <= n && h[child + 1] < h[child]) child++;   // the smaller child
        if (h[child] >= h[i]) return;       // heap order holds: done
        int t = h[i];
        h[i] = h[child];
        h[child] = t;
        i = child;
    }
}
// @end percolateDown

// L44-M2 · Example: AS5 Q4-a  =>  4 10 7 12 11 19 14 25 41 28 18 67 37 52 22
// @begin buildMinHeap
void buildMinHeap(vector<int>& h) {
    int n = h.size() - 1;
    for (int i = n / 2; i >= 1; i--) percolateDown(h, i);
}
// @end buildMinHeap

// L44-M3 · Example: AS5 Q4-b  =>  4, heap 7 10 14 12 11 19 22 25 41 28 18 67 37 52
// @begin deleteMin
int deleteMin(vector<int>& h) {
    if (h.size() <= 1) return -1;           // only the unused h[0]: empty
    int min = h[1];
    h[1] = h.back();                        // the last leaf moves to the root
    h.pop_back();
    if (h.size() > 1) percolateDown(h, 1);
    return min;
}
// @end deleteMin

// L44-M4 · Example: AS5 Q4-c, insert 19  =>  7 10 14 12 11 19 19 25 41 28 18 67 37 52 22
// @begin insertMin
void insertMin(vector<int>& h, int x) {
    h.push_back(x);
    int i = h.size() - 1;
    while (i > 1 && h[i / 2] > h[i]) {      // strictly larger parent: swap
        int t = h[i];
        h[i] = h[i / 2];
        h[i / 2] = t;
        i /= 2;
    }
}
// @end insertMin

// L44-X · Example: pre 21 19 24 18 62 10 46 25 18  =>  21 19 46 24 10 25 18 18 62
// @begin fillPreorder
void fillPreorder(vector<int>& arr, int i, const vector<int>& pre, int& next) {
    if (i >= (int)arr.size()) return;       // position i does not exist in this shape
    arr[i] = pre[next++];
    fillPreorder(arr, 2 * i, pre, next);
    fillPreorder(arr, 2 * i + 1, pre, next);
}
// @end fillPreorder

// @begin arrayFromPreorder
vector<int> arrayFromPreorder(const vector<int>& pre) {
    vector<int> arr(pre.size() + 1, 0);
    int next = 0;
    fillPreorder(arr, 1, pre, next);
    return arr;
}
// @end arrayFromPreorder

// L44-V · Example: {0, 1, 2, 3, 4}  =>  {4, 2, 1, 3}
// @begin inorderFrom
void inorderFrom(const vector<int>& h, int i, vector<int>& out) {
    if (i >= (int)h.size()) return;
    inorderFrom(h, 2 * i, out);
    out.push_back(h[i]);
    inorderFrom(h, 2 * i + 1, out);
}
// @end inorderFrom

// @begin heapInorder
vector<int> heapInorder(const vector<int>& h) {
    vector<int> out;
    inorderFrom(h, 1, out);
    return out;
}
// @end heapInorder
