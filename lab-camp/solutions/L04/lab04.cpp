// Lab 04 · Reference solution. Look at it only after the timer ended.
#include "lab04.h"

#include <utility>

using namespace std;

// @begin reverseRange
void reverseRange(vector<int>& v, int lo, int hi) {
    while (lo < hi) {
        swap(v[lo], v[hi]);
        lo++;
        hi--;
    }
}
// @end reverseRange

// @begin moveZeroes
void moveZeroes(vector<int>& nums) {
    int k = 0;                               // next slot for a non-zero
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != 0) {
            nums[k] = nums[i];               // compact the non-zeros (Lab 02, L02-X)
            k++;
        }
    }
    for (int i = k; i < (int)nums.size(); i++) {
        nums[i] = 0;                         // fill the tail with zeros
    }
}
// @end moveZeroes

// @begin rotatedCopy
vector<int> rotatedCopy(const vector<int>& v, int k) {
    int n = v.size();
    vector<int> result;
    if (n == 0) return result;               // avoid k % 0
    k = k % n;                               // k = n, 2n, ... is "no rotation"
    for (int i = 0; i < n; i++) {
        result.push_back(v[(i + k) % n]);    // element i comes from i + k (wrapping)
    }
    return result;
}
// @end rotatedCopy

// @begin rotateLeft
void rotateLeft(vector<int>& v, int k) {
    int n = v.size();
    if (n == 0) return;
    k = k % n;
    if (k == 0) return;
    reverseRange(v, 0, k - 1);               // reverse the first k
    reverseRange(v, k, n - 1);               // reverse the rest
    reverseRange(v, 0, n - 1);               // reverse everything
}
// @end rotateLeft

// @begin rotateRight
void rotateRight(vector<int>& nums, int k) {
    int n = nums.size();
    if (n == 0) return;
    k = k % n;
    rotateLeft(nums, (n - k) % n);           // right by k == left by n - k
}
// @end rotateRight

// @begin isRotation
bool isRotation(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;
    if (a.empty()) return true;
    for (int k = 0; k < (int)a.size(); k++) {
        if (rotatedCopy(a, k) == b) return true;   // vector == compares all elements
    }
    return false;
}
// @end isRotation
