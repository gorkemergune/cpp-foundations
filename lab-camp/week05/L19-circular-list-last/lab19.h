// ============================================================================
//  Lab 19 · Circular singly linked list kept by `last` (midterm)    DO NOT EDIT
//  The list is reached through ONE pointer, last. last->next is the first node.
//  Empty list: last == nullptr. One node: last->next == last.
// ============================================================================
#pragma once

#include <vector>

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// L19-A · Warm-up · append v; the new node becomes last. O(1).
void insertAtEnd(Node*& last, int v);

// L19-B · Warm-up · the values from the first node (last->next) to last. {} if empty.
std::vector<int> toVector(const Node* last);

// L19-M1 · Main (midterm) · delete the node that `last` points to and close the circle
// again; the node before it becomes last. One node -> last = nullptr. Empty -> false.
bool deleteLast(Node*& last);

// L19-M2 · Main · delete the first node (last->next). One node -> last = nullptr.
bool deleteFirst(Node*& last);

// L19-X · Optional · delete the first node (from the front) holding v; false if none.
bool deleteValue(Node*& last, int v);

// L19-V · Optional · memory variant: number of nodes (0 if empty).
int countNodes(const Node* last);
