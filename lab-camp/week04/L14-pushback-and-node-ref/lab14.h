// ============================================================================
//  Lab 14 · pushBack(Node*& head, int value) and friends            DO NOT EDIT
//  The Node of Practice Lab 2 (field names data / next). The constructor only
//  adds a live-node counter for the tests; new Node{v, nullptr} works as before.
// ============================================================================
#pragma once

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// L14-A · Warm-up · insert at the front. O(1).
void pushFront(Node*& head, int value);

// L14-B · Warm-up · Practice Lab 2: append at the end (walk to the last node).
void pushBack(Node*& head, int value);

// L14-M1 · Main · insert so that value ends up at 0-based position index (0..length).
// Invalid index -> false, list unchanged.
bool insertAt(Node*& head, int index, int value);

// L14-M2 · Main · remove (and delete) the node at 0-based position index.
// Invalid index -> false, list unchanged.
bool removeAt(Node*& head, int index);

// L14-X · Optional · GeeksforGeeks "Linked List End Insertion": the same as pushBack,
// but the head is passed BY VALUE and the (possibly new) head is returned.
Node* insertAtEnd(Node* head, int x);

// L14-V · Optional · practice signature (not in the course archive): O(1) append
// using a tail pointer that the caller keeps. Both may change.
void pushToBack(Node*& head, Node*& tail, int value);
