// ============================================================================
//  Lab 07 · Pointers into arrays and 2-D arrays · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L07
//  A, B, V: walk with pointers (p++, *p). M1, M2: m[i][j] indexing.
// ============================================================================
#include "lab07.h"

#include "todo.h"

using namespace std;

// L07-A · Example: a = {4, 7, 2, 7}, findFirst(a, a + 4, 7) == a + 1; not found -> a + 4
// @begin findFirst
const int* findFirst(const int* begin, const int* end, int x) {
    for (const int* p = begin; p != end; p++) {   // p walks; end is never read
        if (*p == x) return p;
    }
    return end;                                   // "not found" is the end pointer
}
// @end findFirst

// L07-B · Example: a = 3, b = 8; swapViaPointers(&a, &b)  =>  a = 8, b = 3
// @begin swapViaPointers
void swapViaPointers(int* x, int* y) {
    if (x == nullptr || y == nullptr) return;
    int tmp = *x;          // *x is the int that x points to
    *x = *y;
    *y = tmp;
}
// @end swapViaPointers

// L07-M1 · Example: {{1,2,3},{4,5,6},{7,8,9}}  =>  1+5+9 + 3+7 = 25 (the 5 counted once)
// @begin diagonalSum
int diagonalSum(const int m[][MAXN], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += m[i][i];                    // primary diagonal
        if (i != n - 1 - i) sum += m[i][n - 1 - i];   // secondary, skip the shared centre
    }
    return sum;
}
// @end diagonalSum

// L07-M2 · Example: {{1,2},{3,4}}  =>  {{1,3},{2,4}}
// @begin transposeSquare
void transposeSquare(int m[][MAXN], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {  // only above the diagonal: each pair swapped once
            int tmp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = tmp;
        }
    }
}
// @end transposeSquare

// L07-X · Example: {{1,2,3},{4,5,6}}  =>  {{1,4},{2,5},{3,6}}
// @begin transpose
vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> t(cols, vector<int>(rows));   // cols rows, each of length rows
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) t[j][i] = matrix[i][j];
    return t;
}
// @end transpose

// L07-V · Example: {5, 1, 9, 3}, lo = 2, hi = 6  =>  2 (5 and 3)
// @begin countInRange
int countInRange(const int* begin, const int* end, int lo, int hi) {
    int count = 0;
    while (begin != end) {
        if (*begin >= lo && *begin <= hi) count++;
        begin++;                           // begin is our own copy of the pointer
    }
    return count;
}
// @end countInRange
