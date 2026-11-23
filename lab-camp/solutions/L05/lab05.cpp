// ============================================================================
//  Lab 05 · C-style arrays · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L05
//  Test one question:    .\run.ps1 L05 L05-M
//  Allowed: indexing a[i], loops, int& output parameters. Not allowed: <algorithm>.
// ============================================================================
#include "lab05.h"

#include "todo.h"

using namespace std;

// L05-A · Sum of a[0..n-1].   Example: {4, -1, 7}, n = 3  =>  10
// @begin sumArray
int sumArray(const int a[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) total += a[i];
    return total;
}
// @end sumArray

// L05-B · a[i] = i * i.   Example: n = 4  =>  the caller's array starts {0, 1, 4, 9}
// @begin fillSquares
void fillSquares(int a[], int n) {
    for (int i = 0; i < n; i++) a[i] = i * i;   // a points at the caller's memory
}
// @end fillSquares

// L05-M · First index of the minimum and of the maximum.
// Example: {3, 9, 2, 9, 2}  =>  true, minIdx = 2, maxIdx = 1
// @begin minMaxIndex
bool minMaxIndex(const int a[], int n, int& minIdx, int& maxIdx) {
    if (n <= 0) return false;              // nothing to report, outputs untouched
    int lo = 0, hi = 0;                    // work in locals, write the outputs once
    for (int i = 1; i < n; i++) {
        if (a[i] < a[lo]) lo = i;          // strict <: the FIRST minimum stays
        if (a[i] > a[hi]) hi = i;
    }
    minIdx = lo;
    maxIdx = hi;
    return true;
}
// @end minMaxIndex

// L05-X · {min, max}.   Example: {3, 2, 1, 56, 10000, 167}  =>  {1, 10000}
// @begin getMinMax
pair<int, int> getMinMax(const int a[], int n) {
    int lo, hi;
    minMaxIndex(a, n, lo, hi);             // reuse M: indexes -> values
    return {a[lo], a[hi]};
}
// @end getMinMax

// L05-V · Second largest distinct value, -1 if none.   Example: {12, 35, 1, 10, 34, 1}  =>  34
// @begin secondLargest
int secondLargest(const int a[], int n) {
    int first = -1, second = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] > first) {
            second = first;                // the old maximum becomes second
            first = a[i];
        } else if (a[i] < first && a[i] > second) {
            second = a[i];                 // equal to first does not count
        }
    }
    return second;
}
// @end secondLargest
