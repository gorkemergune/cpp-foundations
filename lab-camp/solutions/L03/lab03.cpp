// Lab 03 · Reference solution. Look at it only after you tried yourself.
#include "lab03.h"

#include <utility>

using namespace std;

// @begin reverseRange
void reverseRange(vector<int>& v, int lo, int hi) {
    if (lo < 0 || hi >= (int)v.size() || lo >= hi) return;   // invalid: no change
    while (lo < hi) {
        swap(v[lo], v[hi]);     // exchange the two ends
        lo++;                   // lo and hi are copies (int parameters),
        hi--;                   // changing them does not affect the caller
    }
}
// @end reverseRange

// @begin isReverseOf
bool isReverseOf(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;     // different lengths: never
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (a[i] != b[n - 1 - i]) return false; // first mismatch decides
    }
    return true;                                // includes n == 0
}
// @end isReverseOf

// @begin reverseAlternateTriples
void reverseAlternateTriples(vector<int>& v) {
    int n = v.size();
    // group g starts at 3*g; we want g = 0, 2, 4, ... so start = 0, 6, 12, ...
    for (int start = 0; start + 2 < n; start += 6) {   // start+2 < n: group is complete
        swap(v[start], v[start + 2]);                  // reversing 3 = swapping the ends
    }
}
// @end reverseAlternateTriples

// @begin reverseInGroups
void reverseInGroups(vector<int>& arr, int k) {
    int n = arr.size();
    for (int start = 0; start < n; start += k) {
        int end = start + k - 1;
        if (end > n - 1) end = n - 1;       // the last group may be shorter
        reverseRange(arr, start, end);
    }
}
// @end reverseInGroups

// @begin reverseFirstK
void reverseFirstK(vector<int>& v, int k) {
    if (k <= 0 || k > (int)v.size()) return;
    reverseRange(v, 0, k - 1);
}
// @end reverseFirstK
