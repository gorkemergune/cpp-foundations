// ============================================================================
//  Lab 26 · circular array queue · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 L26 L26-M2
// ============================================================================
#include "circularqueue.h"

#include <queue>

#include "todo.h"

// @begin MyCircularQueue
MyCircularQueue::MyCircularQueue(int k)
    : items(k), front(0), back(k - 1), count(0) {
    // back = k - 1 so that the first enQueue moves it to index 0
}
// @end MyCircularQueue

// L26-M2 · Example: k = 3: enQueue 1, 2, 3 true; enQueue 4 false; Rear 3; deQueue; enQueue 4 true
// @begin enQueue
bool MyCircularQueue::enQueue(int value) {
    if (isFull()) return false;
    back = (back + 1) % (int)items.size();     // wrap around to index 0 after the end
    items[back] = value;
    count++;
    return true;
}
// @end enQueue

// @begin deQueue
bool MyCircularQueue::deQueue() {
    if (isEmpty()) return false;
    front = (front + 1) % (int)items.size();   // the old front is simply forgotten
    count--;
    return true;
}
// @end deQueue

// @begin Front
int MyCircularQueue::Front() const {
    return isEmpty() ? -1 : items[front];
}
// @end Front

// @begin Rear
int MyCircularQueue::Rear() const {
    return isEmpty() ? -1 : items[back];
}
// @end Rear

// @begin isEmpty
bool MyCircularQueue::isEmpty() const {
    return count == 0;                         // count, not front == back: that is ambiguous
}
// @end isEmpty

// @begin isFull
bool MyCircularQueue::isFull() const {
    return count == (int)items.size();
}
// @end isFull

// L26-X · Example: tickets {2, 3, 2}, k = 2  =>  6
// @begin timeRequiredToBuy
int timeRequiredToBuy(const std::vector<int>& tickets, int k) {
    std::queue<int> line;                      // indexes of people, in line order
    std::vector<int> left = tickets;
    for (int i = 0; i < (int)tickets.size(); i++) line.push(i);
    int seconds = 0;
    while (true) {
        int p = line.front();
        line.pop();
        left[p]--;
        seconds++;
        if (left[p] == 0 && p == k) return seconds;
        if (left[p] > 0) line.push(p);         // back to the end of the line
    }
}
// @end timeRequiredToBuy
