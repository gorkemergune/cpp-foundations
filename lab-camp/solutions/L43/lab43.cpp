// ============================================================================
//  Lab 43 · Max-heap · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L43
// ============================================================================
#include "lab43.h"

#include "todo.h"

using namespace std;

// L43-A · Example: {9, 8, 5, 1, 3, 2}  =>  true;  {1, 2}  =>  false
// @begin isMaxHeap
bool isMaxHeap(const vector<int>& items) {
    for (int i = 1; i < (int)items.size(); i++)
        if (items[i] > items[(i - 1) / 2]) return false;   // every child vs. its parent
    return true;
}
// @end isMaxHeap

// L43-B · Example: {9, 8, 5}, i = 0, n = 3  =>  1
// @begin largerChild
int largerChild(const vector<int>& items, int i, int n) {
    int child = 2 * i + 1;
    if (child >= n) return -1;              // a leaf
    if (child + 1 < n && items[child + 1] > items[child]) child++;
    return child;
}
// @end largerChild

// L43-M1 · Example: insert 5 3 8 1 9 2 into {}  =>  {9, 8, 5, 1, 3, 2}
// @begin heapInsert
void heapInsert(vector<int>& items, int newItem) {
    items.push_back(newItem);               // place it at the end ...
    int place = items.size() - 1;
    int parent = (place - 1) / 2;
    while (place > 0 && items[place] > items[parent]) {   // ... and trickle it up
        int temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;
        place = parent;
        parent = (place - 1) / 2;
    }
}
// @end heapInsert

// L43-M2 · Example: {2, 8, 5, 1, 3}, root 0  =>  {8, 3, 5, 1, 2}
// @begin heapRebuild
void heapRebuild(vector<int>& items, int root, int n) {
    int child = largerChild(items, root, n);
    if (child != -1 && items[root] < items[child]) {
        int temp = items[root];
        items[root] = items[child];
        items[child] = temp;
        heapRebuild(items, child, n);       // the swapped subtree may be a semiheap now
    }
}
// @end heapRebuild

// L43-M3 · Example: {9, 8, 5, 1, 3, 2}  =>  rootItem 9, heap {8, 3, 5, 1, 2}
// @begin heapDelete
bool heapDelete(vector<int>& items, int& rootItem) {
    if (items.empty()) return false;
    rootItem = items[0];
    items[0] = items.back();                // the last item becomes the root
    items.pop_back();
    heapRebuild(items, 0, items.size());
    return true;
}
// @end heapDelete

// L43-M4 · Example: {6, 3, 5, 9, 2, 10}  =>  {10, 9, 6, 3, 2, 5}
// @begin buildHeap
void buildHeap(vector<int>& items) {
    int n = items.size();
    for (int index = n / 2 - 1; index >= 0; index--)   // leaves are already heaps
        heapRebuild(items, index, n);
}
// @end buildHeap

// L43-X · Example: {2, 7, 4, 1, 8, 1}  =>  1
// @begin lastStoneWeight
int lastStoneWeight(const vector<int>& stones) {
    vector<int> h = stones;
    buildHeap(h);
    while (h.size() > 1) {
        int y, x;
        heapDelete(h, y);                   // the heaviest
        heapDelete(h, x);                   // the second heaviest
        if (y != x) heapInsert(h, y - x);
    }
    return h.empty() ? 0 : h[0];
}
// @end lastStoneWeight

// L43-V · Example: {9, 8, 5, 1, 3, 2}, k = 3  =>  {9, 8, 5}
// @begin topK
vector<int> topK(vector<int> items, int k) {
    vector<int> out;
    int x;
    for (int i = 0; i < k && heapDelete(items, x); i++) out.push_back(x);
    return out;
}
// @end topK
