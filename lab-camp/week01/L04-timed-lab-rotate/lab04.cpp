// ============================================================================
//  Lab 04 · TIMED LAB (50 min) · YOU WORK HERE
//  Start a timer. Do not open the Turkish pages of the PDF before it ends.
//  Test everything:      .\run.ps1 L04
//  Test one part:        .\run.ps1 L04 L04-C
//  Allowed: v.size(), v[i], v.push_back(x), std::swap, your own helper below.
//  Not allowed: <algorithm> (std::rotate, std::reverse, std::stable_partition), erase, insert.
// ============================================================================
#include "lab04.h"

#include <utility>  // std::swap

#include "todo.h"

using namespace std;

// Helper for Part C (and X), not declared in lab04.h: reverse v[lo..hi], both ends included.
// Write it again from memory (Lab 03, L03-A). It is not tested on its own.
void reverseRange(vector<int>& v, int lo, int hi) {
    TODO();
}

// Part A · L04-A · LeetCode 283 Move Zeroes. In place, keep the order of non-zeros.
// Example: {0, 1, 0, 3, 12}  =>  {1, 3, 12, 0, 0}
void moveZeroes(vector<int>& nums) {
    TODO();
}

// Part B · L04-B · New vector rotated LEFT by k. Input unchanged. k may be larger than n.
// Example: v = {1, 2, 3, 4, 5, 6}, k = 2  =>  {3, 4, 5, 6, 1, 2}
vector<int> rotatedCopy(const vector<int>& v, int k) {
    TODO();
}

// Part C · L04-C · Rotate LEFT by k in place, without a second vector.
// Example: v = {1, 2, 3, 4, 5, 6}, k = 2  =>  v becomes {3, 4, 5, 6, 1, 2}
void rotateLeft(vector<int>& v, int k) {
    TODO();
}

// L04-X · Optional · LeetCode 189 Rotate Array: rotate RIGHT by k, in place.
// Example: {1, 2, 3, 4, 5, 6, 7}, k = 3  =>  {5, 6, 7, 1, 2, 3, 4}
void rotateRight(vector<int>& nums, int k) {
    TODO();
}

// L04-V · Optional · true if b equals a rotated left by some k (0 <= k < n).
// Example: a = {1, 2, 3, 4}, b = {3, 4, 1, 2}  =>  true
bool isRotation(const vector<int>& a, const vector<int>& b) {
    TODO();
}
