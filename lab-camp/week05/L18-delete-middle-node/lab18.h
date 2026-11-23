// ============================================================================
//  Lab 18 · Delete the middle node (midterm topic)                  DO NOT EDIT
//  "Middle" of a list of n nodes = the node at 0-based index n / 2
//  (for an even n that is the SECOND of the two middle nodes, as in LeetCode 2095).
// ============================================================================
#pragma once

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// L18-A · Warm-up · number of nodes.
int length(const Node* head);

// L18-B · Warm-up · the node just BEFORE the middle (index n/2 - 1), in ONE pass
// without length(). nullptr when n < 2 (the middle is the head or there is none).
Node* beforeMiddle(Node* head);

// L18-M · Main · unlink and delete the middle node; false for an empty list.
// A single node: it is deleted and head becomes nullptr.
bool deleteMiddle(Node*& head);

// L18-X · Optional · LeetCode 2095 signature: head by value, the new head returned.
Node* deleteMiddleLC(Node* head);

// L18-V · Optional · memory variant: for an EVEN n delete the FIRST middle
// (index n/2 - 1); for an odd n the same node as deleteMiddle. false if empty.
bool deleteLeftMiddle(Node*& head);
