// ============================================================================
//  Lab 08 · TIMED LAB (50 min) · Merging sorted arrays              DO NOT EDIT
//  All input arrays are sorted in non-decreasing order.
// ============================================================================
#pragma once

#include <vector>

// Part A · L08-A · write a[0..na-1] and b[0..nb-1] merged (sorted) into out; return na + nb.
// out has room for na + nb ints. Equal values: the ones from a come first.
int mergeInto(const int a[], int na, const int b[], int nb, int out[]);

// Part B · L08-B · LeetCode 88: nums1 has m values followed by n zeros (size m + n);
// merge nums2 (n values) into nums1 in place.
void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

// Part C · L08-C · values that appear in BOTH arrays, each value once, ascending; return the count.
int intersectSorted(const int a[], int na, const int b[], int nb, int out[]);

// L08-X · Optional · LeetCode 977: squares of a sorted array, sorted.
std::vector<int> sortedSquares(const std::vector<int>& nums);

// L08-V · Optional · memory variant: remove repeated values in place, return the new length.
int removeDuplicatesSorted(int a[], int n);
