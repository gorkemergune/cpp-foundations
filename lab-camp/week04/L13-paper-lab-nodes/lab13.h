// ============================================================================
//  Lab 13 · Paper lab: nodes, arrows, new and delete               DO NOT EDIT
// ============================================================================
#pragma once

#include <vector>

struct Node {
    int value;
    Node* next;
    Node(int v, Node* n = nullptr) : value(v), next(n) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;   // test helper: how many nodes exist right now
};

// L13-A · Warm-up · a new list holding the values in the same order; return its head
// (nullptr for no values).
Node* makeList(const std::vector<int>& values);

// L13-B · Warm-up · the values from head to the end. The list is not changed.
std::vector<int> toVector(const Node* head);

// L13-M1 · Main · delete every node and set the caller's head to nullptr.
void freeList(Node*& head);

// L13-M2 · Main · number of nodes.
int countNodes(const Node* head);

// L13-X · Optional · LeetCode 1290: the list holds bits, most significant first;
// return the number they form.
int getDecimalValue(const Node* head);

// L13-V · Optional · memory variant: a deep copy (new nodes, same values, same order).
Node* copyList(const Node* head);
