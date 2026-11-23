// ============================================================================
//  Lab 45 · Heapsort and std::priority_queue                          DO NOT EDIT
// ============================================================================
#pragma once

#include <string>
#include <utility>
#include <vector>

// L45-A · Warm-up · push every value into a std::priority_queue<int> and pop them all:
// the values from the largest to the smallest.
std::vector<int> drainMaxFirst(const std::vector<int>& v);

// L45-B · Warm-up · the same with a MIN-heap: std::priority_queue<int, std::vector<int>,
// std::greater<int>>.
std::vector<int> drainMinFirst(const std::vector<int>& v);

// L45-M1 · Main · slides 21-28 heapsort, in place, ascending: build a max-heap bottom-up,
// then n-1 times swap the root with the last item of the heap part and rebuild the smaller
// heap. No std::sort, no priority_queue.
void heapSort(std::vector<int>& a);

// L45-M2 · Main · LeetCode 215: the k-th largest value (1 <= k <= size).
// Keep a MIN-heap of the k largest values seen so far: O(n log k).
int findKthLargest(const std::vector<int>& nums, int k);

// L45-M3 · Main · every value is at most k places away from its place in sorted order.
// Sort it in O(n log k) with a min-heap of k+1 values.
std::vector<int> sortKSorted(const std::vector<int>& a, int k);

// L45-X · Optional · LeetCode 973: the k points closest to (0, 0); any order.
std::vector<std::pair<int, int>> kClosest(const std::vector<std::pair<int, int>>& points, int k);

// L45-V · Optional · memory variant: a priority_queue with your own comparator struct:
// words from the SHORTEST to the longest, equal lengths alphabetically.
std::vector<std::string> byLength(const std::vector<std::string>& words);
