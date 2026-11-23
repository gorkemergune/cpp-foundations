// Labwork 8 · reference solution. Min-heap stored in an array, root at index 0:
// children of i are 2i+1 and 2i+2, parent of i is (i-1)/2.
#include "heap.h"

#include <iostream>

// The task asks for a COPY of the caller's array, so the caller's array is not reordered.
// heap.h has no destructor and may not be changed, so this copy is never freed: with a
// free hand you would add ~heap() { delete[] data; } (and a copy constructor).
heap::heap(int* a, int s) {
    size = s;
    data = new int[s > 0 ? s : 1];
    for (int i = 0; i < s; i++) data[i] = a[i];
    heapify(0);
}

void heap::swap(int a, int b) {
    int t = data[a];
    data[a] = data[b];
    data[b] = t;
}

int heap::min(int a, int b) { return a < b ? a : b; }

// Precondition: both subtrees of index are already min-heaps.
void heap::percolate_down(int index) {
    while (true) {
        int left = 2 * index + 1, right = left + 1, smallest = index;
        if (left < size && data[left] < data[smallest]) smallest = left;
        if (right < size && data[right] < data[smallest]) smallest = right;
        if (smallest == index) return;      // both children are >= parent: done
        swap(index, smallest);
        index = smallest;                   // continue in the subtree we disturbed
    }
}

// Bottom-up build: leaves are already heaps, so start at the last internal node.
// The parameter is part of the given header; the whole array is always heapified.
void heap::heapify(int) {
    for (int i = size / 2 - 1; i >= 0; i--) percolate_down(i);
}

void heap::delete_min() {
    if (size == 0) return;                  // nothing to delete
    data[0] = data[size - 1];               // last leaf moves to the root
    size--;
    percolate_down(0);
}

void heap::print() {
    for (int i = 0; i < size; i++) std::cout << data[i] << " ";
    std::cout << std::endl;
}

void heap::inorder(int index) {
    if (index >= size) return;
    inorder(2 * index + 1);
    std::cout << data[index] << " ";
    inorder(2 * index + 2);
}

void heap::inorder() {
    inorder(0);
    std::cout << std::endl;
}
