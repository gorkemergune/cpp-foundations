// ============================================================================
//  Lab 08 · TIMED LAB (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a timer. Test:  .\run.ps1 L08      one part:  .\run.ps1 L08 L08-B
//  Allowed: indexing, loops, nums1[i] =, push_back in X. Not allowed: <algorithm> (sort, merge).
// ============================================================================
#include "lab08.h"

#include "todo.h"

using namespace std;

// Part A · Example: a = {1, 4, 9}, b = {2, 4}  =>  out = {1, 2, 4, 4, 9}, returns 5
// @begin mergeInto
int mergeInto(const int a[], int na, const int b[], int nb, int out[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] <= b[j]) out[k++] = a[i++];   // <= : on a tie, a goes first (stable)
        else out[k++] = b[j++];
    }
    while (i < na) out[k++] = a[i++];          // one of these two loops copies the rest
    while (j < nb) out[k++] = b[j++];
    return k;
}
// @end mergeInto

// Part B · Example: nums1 = {1, 2, 3, 0, 0, 0}, m = 3, nums2 = {2, 5, 6}, n = 3
//          =>  nums1 = {1, 2, 2, 3, 5, 6}
// @begin merge
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;   // fill from the BACK: no value is overwritten
    while (j >= 0) {                           // when nums2 is used up, nums1's rest is in place
        if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
        else nums1[k--] = nums2[j--];
    }
}
// @end merge

// Part C · Example: a = {1, 2, 2, 5, 7}, b = {2, 2, 3, 7}  =>  out = {2, 7}, returns 2
// @begin intersectSorted
int intersectSorted(const int a[], int na, const int b[], int nb, int out[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] < b[j]) i++;
        else if (a[i] > b[j]) j++;
        else {
            if (k == 0 || out[k - 1] != a[i]) out[k++] = a[i];   // each value once
            i++;
            j++;
        }
    }
    return k;
}
// @end intersectSorted

// L08-X · Example: {-4, -1, 0, 3, 10}  =>  {0, 1, 9, 16, 100}
// @begin sortedSquares
vector<int> sortedSquares(const vector<int>& nums) {
    int n = nums.size();
    vector<int> r(n);
    int lo = 0, hi = n - 1;
    for (int k = n - 1; k >= 0; k--) {         // the biggest square is at one of the ends
        int a = nums[lo] * nums[lo], b = nums[hi] * nums[hi];
        if (a > b) { r[k] = a; lo++; }
        else { r[k] = b; hi--; }
    }
    return r;
}
// @end sortedSquares

// L08-V · Example: {1, 1, 2, 3, 3}  =>  a starts {1, 2, 3}, returns 3
// @begin removeDuplicatesSorted
int removeDuplicatesSorted(int a[], int n) {
    if (n == 0) return 0;
    int k = 1;                                  // a[0..k-1] holds the distinct values
    for (int i = 1; i < n; i++)
        if (a[i] != a[k - 1]) a[k++] = a[i];
    return k;
}
// @end removeDuplicatesSorted
