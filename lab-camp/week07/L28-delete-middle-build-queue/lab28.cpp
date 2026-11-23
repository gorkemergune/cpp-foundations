// ============================================================================
//  Lab 28 · Delete the middle, build a queue · YOU WORK HERE
//  Test everything:      .\run.ps1 L28
//  Queue API (slides): enqueue, dequeue(), dequeue(item&), getFront(item&), isEmpty.
// ============================================================================
#include "lab28.h"

#include "todo.h"

using namespace std;

// L28-A · Example: "abc"  =>  a -> b -> c
CNode* buildList(const string& s) {
    TODO();
}

// L28-B · Example: queue holding 'x', 'y'  =>  "xy", queue empty
string drainToString(Queue& q) {
    TODO();
}

// L28-M1 · Example: A -> B -> C -> D -> E  =>  true, list A B D E, out gets A B D E
bool deleteMiddleToQueue(CNode*& head, Queue& out) {
    TODO();
}

// L28-M2 · Example: "ABCDE"  =>  "ABDE";  "ABCD"  =>  "ABD";  ""  =>  ""
string midtermTask(const string& s) {
    TODO();
}

// L28-X · Example: push 2, push 3, pop -> 2, push 4, pop -> 3
LinkedQueue::~LinkedQueue() {
    // TODO: write this (it must not throw)
}

void LinkedQueue::push(int x) {
    TODO();
}

int LinkedQueue::pop() {
    TODO();
}

// L28-V · Example: 1 2 3 4 5 6  =>  1 4 2 5 3 6
void interleaveHalves(queue<int>& q) {
    TODO();
}
