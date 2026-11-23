// ============================================================================
//  Lab 16 · TIMED LAB (50 min) · Reverse, remove, middle            DO NOT EDIT
// ============================================================================
#pragma once

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// Part A · L16-A · LeetCode 206: reverse the list IN PLACE (no new nodes); return the new head.
Node* reverseList(Node* head);

// Part B · L16-B · remove and delete the FIRST node holding v; true if one was removed.
bool removeFirst(Node*& head, int v);

// Part C · L16-C · LeetCode 876: the middle node; for an even length the SECOND middle.
// nullptr for an empty list. One pass.
Node* middleNode(Node* head);

// L16-X · Optional · LeetCode 234: does the list read the same both ways?
bool isPalindrome(Node* head);

// L16-V · Optional · memory variant: how many nodes hold v.
int countValue(const Node* head, int v);
