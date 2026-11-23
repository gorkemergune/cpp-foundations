// ============================================================================
//  Lab 28 · Delete the middle node, build a new queue (midterm)     DO NOT EDIT
//  A string is stored as a linked list of chars; the queue is the slides' Queue
//  (it stores the char codes as int).
// ============================================================================
#pragma once

#include <queue>
#include <string>

#include "SlidesQueue.h"

struct CNode {
    char ch;
    CNode* next;
    CNode(char c, CNode* n = nullptr) : ch(c), next(n) { alive++; }
    ~CNode() { alive--; }
    static inline int alive = 0;
};

// L28-A · Warm-up · one node per character, in order. "" -> nullptr.
CNode* buildList(const std::string& s);

// L28-B · Warm-up · dequeue everything (dequeue(item&)) and return the characters in order.
std::string drainToString(Queue& q);

// L28-M1 · Main · delete (and free) the middle node, index n/2, then enqueue the remaining
// characters, in order, into `out`. The list itself keeps the remaining nodes.
// Empty list: false and nothing changes.
bool deleteMiddleToQueue(CNode*& head, Queue& out);

// L28-M2 · Main · the whole midterm task: build the list from s, delete the middle node,
// copy into a NEW queue, print it into the returned string, free every node.
std::string midtermTask(const std::string& s);

// L28-X · Optional · GeeksforGeeks "Queue using Linked List": push at the back,
// pop returns the front or -1 if empty.
class LinkedQueue {
public:
    ~LinkedQueue();
    void push(int x);
    int pop();
private:
    struct QNode {
        int data;
        QNode* next;
    };
    QNode* front = nullptr;
    QNode* rear = nullptr;
};

// L28-V · Optional · memory variant (old camp QU-9): even size; merge the halves one by one,
// 1 2 3 4 5 6 -> 1 4 2 5 3 6. Use one helper queue.
void interleaveHalves(std::queue<int>& q);
