// ============================================================================
//  Lab 05 · C-style arrays: passing an array and its length      DO NOT EDIT
//  An array parameter `const int a[]` is really a pointer `const int* a`:
//  the function cannot know the length, so it is passed separately as n.
// ============================================================================
#pragma once

#include <utility>

// L05-A · Warm-up · sum of a[0..n-1]. n == 0 -> 0.
int sumArray(const int a[], int n);

// L05-B · Warm-up · a[i] = i * i for every i in 0..n-1 (writes into the caller's array).
void fillSquares(int a[], int n);

// L05-M · Main · indexes of the smallest and the largest element (first occurrence).
// n <= 0: return false and leave minIdx / maxIdx unchanged.
bool minMaxIndex(const int a[], int n, int& minIdx, int& maxIdx);

// L05-X · Optional · GeeksforGeeks "Min and Max in Array": {min, max}. Precondition n >= 1.
std::pair<int, int> getMinMax(const int a[], int n);

// L05-V · Optional · memory variant: the largest value that is strictly smaller than the
// maximum (values are >= 0). -1 if there is no such value.
int secondLargest(const int a[], int n);
