// Lab 05 · Alternative solutions shown in the PDF. Standalone program.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// @begin stl
#include <algorithm>   // not allowed in this lab
bool minMaxIndexSTL(const int a[], int n, int& minIdx, int& maxIdx) {
    if (n <= 0) return false;
    minIdx = min_element(a, a + n) - a;   // a + n: one past the last element
    maxIdx = max_element(a, a + n) - a;
    return true;
}
// @end stl

// @begin template
// The length is part of the TYPE int (&)[N]: no separate n needed.
template <size_t N>
int sumFixed(const int (&a)[N]) {
    int total = 0;
    for (int x : a) total += x;           // range-for works: N is known
    return total;
}
// @end template

int main() {
    int a[] = {3, 9, 2, 9, 2};
    int lo = -1, hi = -1;
    assert(minMaxIndexSTL(a, 5, lo, hi) && lo == 2 && hi == 1);
    assert(!minMaxIndexSTL(a, 0, lo, hi));
    assert(sumFixed(a) == 25);
    cout << "alternatives OK\n";
    return 0;
}
