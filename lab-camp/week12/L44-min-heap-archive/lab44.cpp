// ============================================================================
//  Lab 44 · Min-heap archive questions · YOU WORK HERE
//  Test everything:      .\run.ps1 L44
// ============================================================================
#include "lab44.h"

#include "todo.h"

using namespace std;

// L44-A · Example: {0, 1, 3, 2}  =>  true;  {0, 3, 1}  =>  false
bool isMinHeap(const vector<int>& h) {
    TODO();
}

// L44-M1 · Example: {0, 9, 2, 3, 4, 5}, i = 1  =>  {0, 2, 4, 3, 9, 5}
void percolateDown(vector<int>& h, int i) {
    TODO();
}

// L44-M2 · Example: AS5 Q4-a  =>  4 10 7 12 11 19 14 25 41 28 18 67 37 52 22
void buildMinHeap(vector<int>& h) {
    TODO();
}

// L44-M3 · Example: AS5 Q4-b  =>  4, heap 7 10 14 12 11 19 22 25 41 28 18 67 37 52
int deleteMin(vector<int>& h) {
    TODO();
}

// L44-M4 · Example: AS5 Q4-c, insert 19  =>  7 10 14 12 11 19 19 25 41 28 18 67 37 52 22
void insertMin(vector<int>& h, int x) {
    TODO();
}

// L44-X · Example: pre 21 19 24 18 62 10 46 25 18  =>  21 19 46 24 10 25 18 18 62
void fillPreorder(vector<int>& arr, int i, const vector<int>& pre, int& next) {
    TODO();
}

vector<int> arrayFromPreorder(const vector<int>& pre) {
    TODO();
}

// L44-V · Example: {0, 1, 2, 3, 4}  =>  {4, 2, 1, 3}
void inorderFrom(const vector<int>& h, int i, vector<int>& out) {
    TODO();
}

vector<int> heapInorder(const vector<int>& h) {
    TODO();
}
