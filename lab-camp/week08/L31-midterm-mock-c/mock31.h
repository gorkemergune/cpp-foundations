// ============================================================================
//  Lab 31 · MIDTERM MOCK C (50 min) · variants                       DO NOT EDIT
//  llstack.h and llqueue.h are the classes of Labs 22 and 26 (given here):
//  LLStack: pushToStack, popFromStack() returns T, isEmpty.  LLQueue: enqueue,
//  dequeue() returns T, isEmpty, size.
// ============================================================================
#pragma once

#include "llqueue.h"
#include "llstack.h"

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// Part A (30 pts) · circular singly linked list kept by `last` (Lab 19): delete the node
// BEFORE last. Fewer than 2 nodes -> false. With 2 nodes the first one goes and last
// points to itself.
bool deleteBeforeLast(Node*& last);

// Part B (35 pts) · Lab 27 with the camp classes: reverse the 1st, 3rd ... complete group of
// three in q, using ONE LLStack<int>.
void reverseAlternateTriplesLL(LLQueue<int>& q);

// Part C (35 pts) · delete the middle node (index n/2) of the list and enqueue the remaining
// values, in order, into `out`. Empty list: nothing happens.
void deleteMiddleToLLQueue(Node*& head, LLQueue<int>& out);
