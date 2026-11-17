// ============================================================================
//  QUEUE · QU-1 … QU-10
//  Delete the TODO(); line in a function and write your own code.
//  Test:  .\run.ps1 qu        single problem:  .\run.ps1 QU-8
//  Available: front, rear, enqueue(x), dequeue(), isEmpty(), printQueue()
//  LLStack<T> can be used too (QU-5, QU-8).
// ============================================================================
#include "../ds/LLQueue.h"

// QU-1 · Easy · Queue size
// Return the number of elements in the queue.
// Example: front → 4, 6, 1 ← rear  ⇒  3
template <typename T>
int LLQueue<T>::size() {
    TODO();
}

// QU-2 · Easy · Front and rear elements
// Return without removing. Throw runtime_error if the queue is empty.
// Example: front → 4, 6, 1 ← rear  ⇒  getFront = 4, getRear = 1
template <typename T>
T LLQueue<T>::getFront() {
    TODO();
}

template <typename T>
T LLQueue<T>::getRear() {
    TODO();
}

// QU-3 · Easy · Contains
// Return true if v is in the queue.
// Example: front → 4, 6, 1, v = 6  ⇒  true
template <typename T>
bool LLQueue<T>::contains(const T& v) {
    TODO();
}

// QU-4 · Easy · Count greater
// Return the number of elements greater than v.
// Example: front → 5, 2, 8, 7, v = 5  ⇒  2
template <typename T>
int LLQueue<T>::countGreater(const T& v) {
    TODO();
}

// QU-5 · Medium · Reverse the queue
// Reverse the queue using an LLStack<T>.
// Example: front → 1, 2, 3  ⇒  front → 3, 2, 1
template <typename T>
void LLQueue<T>::reverse() {
    TODO();
}

// QU-6 · Medium · Remove all occurrences (rotation pattern)
// Without any extra data structure, remove every element equal to v. Keep the
// order, return how many were removed.
// Example: front → 3, 7, 3, 1, v = 3  ⇒  front → 7, 1  (returns 2)
template <typename T>
int LLQueue<T>::removeAll(const T& v) {
    TODO();
}

// QU-7 · Medium · Rotate k steps
// Move the front element to the back, k times. k may be larger than the size.
// Example: front → 1, 2, 3, 4, 5, k = 7  ⇒  front → 3, 4, 5, 1, 2
template <typename T>
void LLQueue<T>::rotate(int k) {
    TODO();
}

// QU-8 · Medium · Reverse the first k elements
// Reverse the first k elements, leave the rest in place.
// If k is invalid (≤ 0 or > size), do nothing.
// Example: front → 1, 2, 3, 4, 5, k = 3  ⇒  front → 3, 2, 1, 4, 5
template <typename T>
void LLQueue<T>::reverseFirstK(int k) {
    TODO();
}

// QU-9 · Hard · Interleave the two halves
// The queue has an even number of elements. Merge the first half and the second
// half one by one. You may use only one temporary queue.
// Example: front → 1, 2, 3, 4, 5, 6  ⇒  front → 1, 4, 2, 5, 3, 6
template <typename T>
void LLQueue<T>::interleave() {
    TODO();
}

// QU-10 · Hard · Josephus problem
// People numbered 1..n stand in a circle. Counting around, every k-th person is
// eliminated. Find the survivor's number using an LLQueue<int>.
// Example: n = 5, k = 2  ⇒  elimination order 2, 4, 1, 5 → survivor 3
int josephus(int n, int k) {
    TODO();
}
