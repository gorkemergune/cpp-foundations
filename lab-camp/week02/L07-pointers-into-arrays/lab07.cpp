// ============================================================================
//  Lab 07 · Pointers into arrays and 2-D arrays · YOU WORK HERE
//  Test everything:      .\run.ps1 L07
//  A, B, V: walk with pointers (p++, *p). M1, M2: m[i][j] indexing.
// ============================================================================
#include "lab07.h"

#include "todo.h"

using namespace std;

// L07-A · Example: a = {4, 7, 2, 7}, findFirst(a, a + 4, 7) == a + 1; not found -> a + 4
const int* findFirst(const int* begin, const int* end, int x) {
    TODO();
}

// L07-B · Example: a = 3, b = 8; swapViaPointers(&a, &b)  =>  a = 8, b = 3
void swapViaPointers(int* x, int* y) {
    TODO();
}

// L07-M1 · Example: {{1,2,3},{4,5,6},{7,8,9}}  =>  1+5+9 + 3+7 = 25 (the 5 counted once)
int diagonalSum(const int m[][MAXN], int n) {
    TODO();
}

// L07-M2 · Example: {{1,2},{3,4}}  =>  {{1,3},{2,4}}
void transposeSquare(int m[][MAXN], int n) {
    TODO();
}

// L07-X · Example: {{1,2,3},{4,5,6}}  =>  {{1,4},{2,5},{3,6}}
vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    TODO();
}

// L07-V · Example: {5, 1, 9, 3}, lo = 2, hi = 6  =>  2 (5 and 3)
int countInRange(const int* begin, const int* end, int lo, int hi) {
    TODO();
}
