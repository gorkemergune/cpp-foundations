// ============================================================================
//  Lab 03 · Two indexes: reversing parts of a vector · YOU WORK HERE
//  Test everything:      .\run.ps1 L03
//  Test one question:    .\run.ps1 L03 L03-M
//  Allowed: v.size(), v[i], std::swap(a, b) (from <utility>), your own functions.
//  Not allowed: std::reverse, <algorithm>, a second vector (except in L03-B, which only reads).
// ============================================================================
#include "lab03.h"

#include <utility>  // std::swap

#include "todo.h"

using namespace std;

// L03-A · Reverse v[lo..hi] in place (both ends included).
// Example: v = {1, 2, 3, 4, 5}, lo = 1, hi = 3  =>  {1, 4, 3, 2, 5}
// Invalid range (lo < 0, hi >= size, lo >= hi)  =>  v unchanged.
void reverseRange(vector<int>& v, int lo, int hi) {
    TODO();
}

// L03-B · true if b is a backwards. Two empty vectors are reverses of each other.
// Example: a = {1, 2, 3}, b = {3, 2, 1}  =>  true
bool isReverseOf(const vector<int>& a, const vector<int>& b) {
    TODO();
}

// L03-M · Reverse groups 0, 2, 4, ... of three consecutive elements.
// Example: {1, 2, 3, 4, 5, 6, 7, 8, 9}  =>  {3, 2, 1, 4, 5, 6, 9, 8, 7}
// An incomplete last group is never changed.
void reverseAlternateTriples(vector<int>& v) {
    TODO();
}

// L03-X · Optional · GfG: reverse every group of k; a shorter last group too. k >= 1.
// Example: {1, 2, 3, 4, 5}, k = 3  =>  {3, 2, 1, 5, 4}
void reverseInGroups(vector<int>& arr, int k) {
    TODO();
}

// L03-V · Optional · Reverse the first k elements. k <= 0 or k > size: nothing.
// Example: {1, 2, 3, 4, 5}, k = 3  =>  {3, 2, 1, 4, 5}
void reverseFirstK(vector<int>& v, int k) {
    TODO();
}
