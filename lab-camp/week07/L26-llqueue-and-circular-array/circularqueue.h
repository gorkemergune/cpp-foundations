// ============================================================================
//  Lab 26 · the slides' array-based circular queue (10-queues.ppt, slides 23-29)
//  in LeetCode 622's form.                                          DO NOT EDIT
//  items[front] is the front; items[back] is the back; count elements are stored.
//  Indexes wrap around with % capacity.
// ============================================================================
#pragma once

#include <vector>

class MyCircularQueue {
public:
    explicit MyCircularQueue(int k);   // capacity k >= 1
    bool enQueue(int value);           // false when full
    bool deQueue();                    // false when empty (removes only)
    int Front() const;                 // -1 when empty
    int Rear() const;                  // -1 when empty
    bool isEmpty() const;
    bool isFull() const;

private:
    std::vector<int> items;
    int front;   // index of the front element
    int back;    // index of the back element (starts at capacity - 1, as in the slides)
    int count;
};

// L26-X · Optional · LeetCode 2073: people buy one ticket per turn; how many seconds until
// person k has bought all of tickets[k]?
int timeRequiredToBuy(const std::vector<int>& tickets, int k);
