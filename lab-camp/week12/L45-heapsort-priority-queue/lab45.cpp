// ============================================================================
//  Lab 45 · Heapsort and priority_queue · YOU WORK HERE
//  Test everything:      .\run.ps1 L45
// ============================================================================
#include "lab45.h"

#include <functional>
#include <queue>

#include "todo.h"

using namespace std;

// L45-A · Example: {3, 1, 2}  =>  {3, 2, 1}
vector<int> drainMaxFirst(const vector<int>& v) {
    TODO();
}

// L45-B · Example: {3, 1, 2}  =>  {1, 2, 3}
vector<int> drainMinFirst(const vector<int>& v) {
    TODO();
}

// L45-M1 · Example: {6, 3, 5, 9, 2, 10}  =>  {2, 3, 5, 6, 9, 10}
// Lab 43's heapRebuild, written as a loop
void rebuild(vector<int>& a, int root, int n) {
    TODO();
}

void heapSort(vector<int>& a) {
    TODO();
}

// L45-M2 · Example: {3, 2, 1, 5, 6, 4}, k = 2  =>  5
int findKthLargest(const vector<int>& nums, int k) {
    TODO();
}

// L45-M3 · Example: {6, 5, 3, 2, 8, 10, 9}, k = 3  =>  {2, 3, 5, 6, 8, 9, 10}
vector<int> sortKSorted(const vector<int>& a, int k) {
    TODO();
}

// L45-X · Example: {(1,3), (-2,2)}, k = 1  =>  {(-2,2)}
vector<pair<int, int>> kClosest(const vector<pair<int, int>>& points, int k) {
    TODO();
}

// L45-V · Example: {"ccc", "a", "bb", "aa"}  =>  {"a", "aa", "bb", "ccc"}
vector<string> byLength(const vector<string>& words) {
    TODO();
}
