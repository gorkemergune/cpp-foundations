// ============================================================================
//  Lab 44 · Min-heap questions from the archive (1-based array)       DO NOT EDIT
//  2017 Assignment 5 Q4 and Labwork 8. h[0] is UNUSED; the heap is h[1..n] with
//  n = h.size() - 1; the children of i are 2i and 2i+1, its parent i/2.
// ============================================================================
#pragma once

#include <vector>

// L44-A · Warm-up · is h[1..n] a min-heap (every item <= its children)?
bool isMinHeap(const std::vector<int>& h);

// L44-M1 · Main (Labwork 8, percolate_down) · move h[i] down: swap with the SMALLER child
// (the right one only if strictly smaller) while that child is smaller. Use a loop.
void percolateDown(std::vector<int>& h, int i);

// L44-M2 · Main (AS5 Q4-a, Labwork 8 heapify) · bottom-up construction: i = n/2 down to 1.
void buildMinHeap(std::vector<int>& h);

// L44-M3 · Main (AS5 Q4-b, Labwork 8 delete_min) · remove and return the minimum.
// Empty heap: return -1 and change nothing.
int deleteMin(std::vector<int>& h);

// L44-M4 · Main (AS5 Q4-c) · insert x: percolate UP while smaller than the parent.
void insertMin(std::vector<int>& h, int x);

// L44-X · Optional (AS5 Q4-d) · a heap of n items is drawn as a complete tree and only its
// PREORDER is given. Return its array layout (h[0] = 0): the shape is fixed, so walk the
// positions 1, 2, 4 ... in preorder and fill them.
std::vector<int> arrayFromPreorder(const std::vector<int>& pre);

// L44-V · Optional (Labwork 8, inorder) · the inorder traversal of the heap's tree.
std::vector<int> heapInorder(const std::vector<int>& h);
