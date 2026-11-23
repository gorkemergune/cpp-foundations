// ============================================================================
//  Lab 43 · Max-heap · YOU WORK HERE
//  Test everything:      .\run.ps1 L43
// ============================================================================
#include "lab43.h"

#include "todo.h"

using namespace std;

// L43-A · Example: {9, 8, 5, 1, 3, 2}  =>  true;  {1, 2}  =>  false
bool isMaxHeap(const vector<int>& items) {
    TODO();
}

// L43-B · Example: {9, 8, 5}, i = 0, n = 3  =>  1
int largerChild(const vector<int>& items, int i, int n) {
    TODO();
}

// L43-M1 · Example: insert 5 3 8 1 9 2 into {}  =>  {9, 8, 5, 1, 3, 2}
void heapInsert(vector<int>& items, int newItem) {
    TODO();
}

// L43-M2 · Example: {2, 8, 5, 1, 3}, root 0  =>  {8, 3, 5, 1, 2}
void heapRebuild(vector<int>& items, int root, int n) {
    TODO();
}

// L43-M3 · Example: {9, 8, 5, 1, 3, 2}  =>  rootItem 9, heap {8, 3, 5, 1, 2}
bool heapDelete(vector<int>& items, int& rootItem) {
    TODO();
}

// L43-M4 · Example: {6, 3, 5, 9, 2, 10}  =>  {10, 9, 6, 3, 2, 5}
void buildHeap(vector<int>& items) {
    TODO();
}

// L43-X · Example: {2, 7, 4, 1, 8, 1}  =>  1
int lastStoneWeight(const vector<int>& stones) {
    TODO();
}

// L43-V · Example: {9, 8, 5, 1, 3, 2}, k = 3  =>  {9, 8, 5}
vector<int> topK(vector<int> items, int k) {
    TODO();
}
