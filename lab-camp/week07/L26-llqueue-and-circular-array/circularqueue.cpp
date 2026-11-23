// ============================================================================
//  Lab 26 · circular array queue · YOU WORK HERE
//  Test:  .\run.ps1 L26 L26-M2
// ============================================================================
#include "circularqueue.h"

#include <queue>

#include "todo.h"

MyCircularQueue::MyCircularQueue(int k) {
    TODO();
}

// L26-M2 · Example: k = 3: enQueue 1, 2, 3 true; enQueue 4 false; Rear 3; deQueue; enQueue 4 true
bool MyCircularQueue::enQueue(int value) {
    TODO();
}

bool MyCircularQueue::deQueue() {
    TODO();
}

int MyCircularQueue::Front() const {
    TODO();
}

int MyCircularQueue::Rear() const {
    TODO();
}

bool MyCircularQueue::isEmpty() const {
    TODO();
}

bool MyCircularQueue::isFull() const {
    TODO();
}

// L26-X · Example: tickets {2, 3, 2}, k = 2  =>  6
int timeRequiredToBuy(const std::vector<int>& tickets, int k) {
    TODO();
}
