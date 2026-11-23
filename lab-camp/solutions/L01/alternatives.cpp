// Lab 01 · Alternative solutions shown in the PDF. Standalone program:
//   g++ -std=c++17 -Wall alternatives.cpp -o alt.exe && .\alt.exe
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// @begin inPlace
vector<int> runningTotalsInPlace(vector<int> changes) {
    for (size_t i = 1; i < changes.size(); i++) {
        changes[i] += changes[i - 1];   // previous slot already holds its total
    }
    return changes;                     // our own copy, now transformed
}
// @end inPlace

// @begin stl
#include <numeric>   // not allowed in this lab
vector<int> runningTotalsSTL(const vector<int>& changes) {
    vector<int> r(changes.size());
    partial_sum(changes.begin(), changes.end(), r.begin());
    return r;
}
// @end stl

int main() {
    vector<int> in = {3, -1, 4, 0}, expected = {3, 2, 6, 6};
    assert(runningTotalsInPlace(in) == expected);
    assert(runningTotalsSTL(in) == expected);
    assert(runningTotalsInPlace({}).empty());
    assert(runningTotalsSTL({}).empty());
    assert((in == vector<int>{3, -1, 4, 0}));  // caller unchanged
    cout << "alternatives OK\n";
    return 0;
}
