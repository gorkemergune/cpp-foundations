// Lab 04 · Alternative solutions shown in the PDF. Standalone program.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// @begin byOne
// Rotate left by one, k times: correct, but O(n * k) moves.
void rotateLeftSlow(vector<int>& v, int k) {
    int n = v.size();
    if (n == 0) return;
    for (int step = 0; step < k % n; step++) {
        int first = v[0];
        for (int i = 0; i < n - 1; i++) v[i] = v[i + 1];
        v[n - 1] = first;
    }
}
// @end byOne

// @begin stl
// std::rotate is not allowed in this lab.
void rotateLeftSTL(vector<int>& v, int k) {
    if (v.empty()) return;
    rotate(v.begin(), v.begin() + k % v.size(), v.end());
}
// @end stl

// @begin copyBack
// Uses a second vector: O(n) extra memory, breaks the Part C rule.
void rotateLeftWithCopy(vector<int>& v, int k) {
    int n = v.size();
    if (n == 0) return;
    vector<int> tmp(n);
    for (int i = 0; i < n; i++) tmp[i] = v[(i + k) % n];
    v = tmp;                      // copy assignment: v gets tmp's elements
}
// @end copyBack

int main() {
    for (int k = 0; k < 15; k++) {
        vector<int> a = {1, 2, 3, 4, 5, 6}, b = a, c = a, want = a;
        rotate(want.begin(), want.begin() + k % 6, want.end());
        rotateLeftSlow(a, k);
        rotateLeftSTL(b, k);
        rotateLeftWithCopy(c, k);
        assert(a == want && b == want && c == want);
    }
    vector<int> e;
    rotateLeftSlow(e, 3);
    rotateLeftSTL(e, 3);
    rotateLeftWithCopy(e, 3);
    assert(e.empty());
    cout << "alternatives OK\n";
    return 0;
}
