// ============================================================================
//  Lab 02 · References: editing a vector in place · YOU WORK HERE
//  Test everything:      .\run.ps1 L02
//  Test one question:    .\run.ps1 L02 L02-M1
//  Allowed in M1, M2, V: v.size(), v[i], v.push_back(x), v.pop_back(), v.back()
//  Not allowed in M1, M2, V: v.erase, v.insert, <algorithm>, a second vector
// ============================================================================
#include "lab02.h"

#include "todo.h"

using namespace std;

// L02-A · Add d to every element. The CALLER's vector must change.
// Example: v = {1, 2, 3}, d = 10  =>  v becomes {11, 12, 13}
void addToEach(vector<int>& v, int d) {
    TODO();
}

// L02-B · Index of the first x, or -1. v must not change (const&).
// Example: v = {4, 7, 2, 7}, x = 7  =>  1
int indexOf(const vector<int>& v, int x) {
    TODO();
}

// L02-M1 · Remove v[index], shifting the elements after it one step left.
// Example: v = {4, 7, 2, 9}, index = 1  =>  true, v becomes {4, 2, 9}
// Invalid index  =>  false, v unchanged.
bool removeAt(vector<int>& v, int index) {
    TODO();
}

// L02-M2 · Insert value at position index (0..size), shifting the rest right.
// Example: v = {4, 2, 9}, index = 1, value = 7  =>  true, v becomes {4, 7, 2, 9}
// index == size appends. Invalid index  =>  false, v unchanged.
bool insertAt(vector<int>& v, int index, int value) {
    TODO();
}

// L02-X · Optional · LeetCode 27. Move every element != val to the front,
// keeping their order, and return how many there are (k).
// Only nums[0..k-1] is checked. Example: {3, 2, 2, 3}, val = 3  =>  2, nums starts {2, 2}
int removeElement(vector<int>& nums, int val) {
    TODO();
}

// L02-V · Optional · Move v[index] to position 0; the elements before it shift right.
// Example: v = {4, 7, 2, 9}, index = 2  =>  true, v becomes {2, 4, 7, 9}
bool moveToFront(vector<int>& v, int index) {
    TODO();
}
