// Lab 03 · Alternative solutions shown in the PDF. Standalone program.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

static void reverseRange(vector<int>& v, int lo, int hi) {
    if (lo < 0 || hi >= (int)v.size() || lo >= hi) return;
    for (; lo < hi; lo++, hi--) swap(v[lo], v[hi]);
}

// @begin general
// Works for any group size g (here g = 3), reusing L03-A.
void reverseAlternateGroups(vector<int>& v, int g) {
    int n = v.size();
    for (int start = 0; start + g - 1 < n; start += 2 * g) {
        reverseRange(v, start, start + g - 1);
    }
}
// @end general

// @begin stl
#include <algorithm>   // std::reverse is not allowed in this lab
void reverseAlternateTriplesSTL(vector<int>& v) {
    for (size_t start = 0; start + 3 <= v.size(); start += 6) {
        reverse(v.begin() + start, v.begin() + start + 3);
    }
}
// @end stl

// @begin sizeTrap
// WRONG for an empty vector: v.size() - 1 is a huge unsigned number.
bool isPalindromeWrong(const vector<int>& v) {
    for (size_t i = 0; i < v.size() - 1 - i; i++) {
        if (v[i] != v[v.size() - 1 - i]) return false;
    }
    return true;
}
// @end sizeTrap

int main() {
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9}, b = a;
    vector<int> want = {3, 2, 1, 4, 5, 6, 9, 8, 7};
    reverseAlternateGroups(a, 3);
    reverseAlternateTriplesSTL(b);
    assert(a == want && b == want);
    vector<int> e;
    reverseAlternateGroups(e, 3);
    reverseAlternateTriplesSTL(e);
    assert(e.empty());
    assert(isPalindromeWrong({1, 2, 1}) && !isPalindromeWrong({1, 2}));
    cout << "alternatives OK\n";   // isPalindromeWrong({}) is not called: it would read out of range
    return 0;
}
