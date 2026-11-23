// ============================================================================
//  Lab 01 · First steps with std::vector · YOU WORK HERE
//  Delete the TODO(); line inside a function and write your code.
//  Test everything:      .\run.ps1 L01
//  Test one question:    .\run.ps1 L01 L01-M
//  Allowed: v.size(), v[i], v.push_back(x), v.back(), range-for.
//  Not allowed in L01-M: <numeric> (accumulate, partial_sum).
// ============================================================================
#include "lab01.h"

#include "todo.h"

using namespace std;

// L01-A · Sum of all elements. Empty vector -> 0.
// Example: {4, -1, 7}  =>  10
int sumAll(vector<int> v) {
    TODO();
}

// L01-B · The even elements in their original order. 0 and negative evens count.
// Example: {5, 2, -4, 7, 0}  =>  {2, -4, 0}
vector<int> evensOnly(vector<int> v) {
    TODO();
}

// L01-M · Running totals (balance after each day).
// result[i] = changes[0] + changes[1] + ... + changes[i]. Same length as the input.
// Example: {3, -1, 4, 0}  =>  {3, 2, 6, 6}
vector<int> runningTotals(vector<int> changes) {
    TODO();
}

// L01-X · Optional · LeetCode 1929 Concatenation of Array.
// Return a vector of length 2n: nums, then nums again.
// Example: {1, 2, 1}  =>  {1, 2, 1, 1, 2, 1}
vector<int> getConcatenation(vector<int> nums) {
    TODO();
}

// L01-V · Optional · Memory variant: running maximum.
// result[i] = the largest of v[0..i].
// Example: {2, 5, 1, 7, 3}  =>  {2, 5, 5, 7, 7}
vector<int> runningMax(vector<int> v) {
    TODO();
}
