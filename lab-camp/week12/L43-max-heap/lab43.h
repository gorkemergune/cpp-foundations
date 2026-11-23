// ============================================================================
//  Lab 43 · The slides' max-heap in an array                          DO NOT EDIT
//  items[0] is the root; the children of i are 2i+1 and 2i+2, its parent (i-1)/2.
//  The heap is a std::vector<int>: size() plays the role of the slides' `size`.
// ============================================================================
#pragma once

#include <vector>

// L43-A · Warm-up · is every item >= its children?
bool isMaxHeap(const std::vector<int>& items);

// L43-B · Warm-up · the index of the LARGER child of i among items[0..n-1] (the right child
// only if it is strictly larger), or -1 if i has no child.
int largerChild(const std::vector<int>& items, int i, int n);

// L43-M1 · Main · slide 13 heapInsert: add at the end, trickle up while larger than the parent.
void heapInsert(std::vector<int>& items, int newItem);

// L43-M2 · Main · slide 15 heapRebuild: items[0..n-1]; the subtree at root is a semiheap
// (both child subtrees are heaps). Trickle items[root] down: swap with the larger child
// while it is smaller.
void heapRebuild(std::vector<int>& items, int root, int n);

// L43-M3 · Main · slide 14 heapDelete: copy the root into rootItem, move the last item to
// the root, shrink, rebuild. Empty heap: false.
bool heapDelete(std::vector<int>& items, int& rootItem);

// L43-M4 · Main · slide 23: turn any array into a heap bottom-up, index n/2 - 1 down to 0.
void buildHeap(std::vector<int>& items);

// L43-X · Optional · LeetCode 1046: smash the two heaviest stones; |x - y| goes back if
// non-zero. The weight of the last stone, or 0. Use your heap functions.
int lastStoneWeight(const std::vector<int>& stones);

// L43-V · Optional · memory variant: items is a max-heap; its k largest values, largest first
// (k <= size), without changing `items` (work on a copy).
std::vector<int> topK(std::vector<int> items, int k);
