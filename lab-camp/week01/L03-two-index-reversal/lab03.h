// ============================================================================
//  Lab 03 · Two indexes: reversing parts of a vector             DO NOT EDIT
// ============================================================================
#pragma once

#include <vector>

// L03-A · Warm-up · reverse v[lo..hi] (both ends included) in place.
// If lo < 0, hi >= size or lo >= hi, do nothing.
void reverseRange(std::vector<int>& v, int lo, int hi);

// L03-B · Warm-up · true if b is a read backwards (same length, b[i] == a[n-1-i]).
bool isReverseOf(const std::vector<int>& a, const std::vector<int>& b);

// L03-M · Main · reverse the 1st, 3rd, 5th, ... COMPLETE group of three.
// The other groups and an incomplete last group stay as they are.
void reverseAlternateTriples(std::vector<int>& v);

// L03-X · Optional · GeeksforGeeks "Reverse Array in Groups":
// reverse every group of k (the last group may be shorter and is reversed too).
void reverseInGroups(std::vector<int>& arr, int k);

// L03-V · Optional · memory variant: reverse the first k elements.
// If k <= 0 or k > size, do nothing.
void reverseFirstK(std::vector<int>& v, int k);
