// ============================================================================
//  Lab 05 · C-style arrays · YOU WORK HERE
//  Test everything:      .\run.ps1 L05
//  Test one question:    .\run.ps1 L05 L05-M
//  Allowed: indexing a[i], loops, int& output parameters. Not allowed: <algorithm>.
// ============================================================================
#include "lab05.h"

#include "todo.h"

using namespace std;

// L05-A · Sum of a[0..n-1].   Example: {4, -1, 7}, n = 3  =>  10
int sumArray(const int a[], int n) {
    TODO();
}

// L05-B · a[i] = i * i.   Example: n = 4  =>  the caller's array starts {0, 1, 4, 9}
void fillSquares(int a[], int n) {
    TODO();
}

// L05-M · First index of the minimum and of the maximum.
// Example: {3, 9, 2, 9, 2}  =>  true, minIdx = 2, maxIdx = 1
bool minMaxIndex(const int a[], int n, int& minIdx, int& maxIdx) {
    TODO();
}

// L05-X · {min, max}.   Example: {3, 2, 1, 56, 10000, 167}  =>  {1, 10000}
pair<int, int> getMinMax(const int a[], int n) {
    TODO();
}

// L05-V · Second largest distinct value, -1 if none.   Example: {12, 35, 1, 10, 34, 1}  =>  34
int secondLargest(const int a[], int n) {
    TODO();
}
