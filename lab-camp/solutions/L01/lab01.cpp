// Lab 01 · Reference solution. Look at it only after you tried yourself.
#include "lab01.h"

using namespace std;

// @begin sumAll
int sumAll(vector<int> v) {
    int total = 0;
    for (int x : v) {        // x takes each value in turn
        total += x;
    }
    return total;            // empty vector: the loop never runs -> 0
}
// @end sumAll

// @begin evensOnly
vector<int> evensOnly(vector<int> v) {
    vector<int> result;      // starts empty: size 0
    for (int x : v) {
        if (x % 2 == 0) {    // -4 % 2 == 0, -3 % 2 == -1
            result.push_back(x);
        }
    }
    return result;
}
// @end evensOnly

// @begin runningTotals
vector<int> runningTotals(vector<int> changes) {
    vector<int> result;
    int total = 0;
    for (size_t i = 0; i < changes.size(); i++) {
        total += changes[i];        // balance after day i
        result.push_back(total);    // result grows by one each step
    }
    return result;                  // same length as changes
}
// @end runningTotals

// @begin getConcatenation
vector<int> getConcatenation(vector<int> nums) {
    int n = nums.size();            // remember the ORIGINAL size once
    for (int i = 0; i < n; i++) {
        nums.push_back(nums[i]);    // nums is our own copy, we may grow it
    }
    return nums;
}
// @end getConcatenation

// @begin runningMax
vector<int> runningMax(vector<int> v) {
    vector<int> result;
    for (size_t i = 0; i < v.size(); i++) {
        if (result.empty() || v[i] > result.back()) result.push_back(v[i]);
        else result.push_back(result.back());
    }
    return result;
}
// @end runningMax
