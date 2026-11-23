// ============================================================================
//  Lab 28 · Delete the middle, build a queue · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L28
//  Queue API (slides): enqueue, dequeue(), dequeue(item&), getFront(item&), isEmpty.
// ============================================================================
#include "lab28.h"

#include "todo.h"

using namespace std;

// L28-A · Example: "abc"  =>  a -> b -> c
// @begin buildList
CNode* buildList(const string& s) {
    CNode* head = nullptr;
    CNode* tail = nullptr;
    for (char c : s) {
        CNode* n = new CNode(c);
        if (head == nullptr) head = n;
        else tail->next = n;
        tail = n;
    }
    return head;
}
// @end buildList

// L28-B · Example: queue holding 'x', 'y'  =>  "xy", queue empty
// @begin drainToString
string drainToString(Queue& q) {
    string out;
    QueueItemType x;
    while (q.dequeue(x)) out += (char)x;      // char codes back to characters
    return out;
}
// @end drainToString

// L28-M1 · Example: A -> B -> C -> D -> E  =>  true, list A B D E, out gets A B D E
// @begin deleteMiddleToQueue
bool deleteMiddleToQueue(CNode*& head, Queue& out) {
    if (head == nullptr) return false;
    if (head->next == nullptr) {               // one node: it is the middle
        delete head;
        head = nullptr;
        return true;                           // nothing remains to enqueue
    }
    CNode* slow = head;                        // Lab 18: stop one before index n/2
    CNode* fast = head->next->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    CNode* mid = slow->next;
    slow->next = mid->next;
    delete mid;
    for (CNode* p = head; p != nullptr; p = p->next) out.enqueue(p->ch);
    return true;
}
// @end deleteMiddleToQueue

// L28-M2 · Example: "ABCDE"  =>  "ABDE";  "ABCD"  =>  "ABD";  ""  =>  ""
// @begin midtermTask
string midtermTask(const string& s) {
    CNode* head = buildList(s);
    Queue q;                                   // the NEW queue
    deleteMiddleToQueue(head, q);
    string printed = drainToString(q);
    while (head != nullptr) {                  // free the remaining nodes
        CNode* n = head->next;
        delete head;
        head = n;
    }
    return printed;
}
// @end midtermTask

// L28-X · Example: push 2, push 3, pop -> 2, push 4, pop -> 3
// @begin LinkedQueueDtor empty
LinkedQueue::~LinkedQueue() {
    while (front != nullptr) {
        QNode* n = front->next;
        delete front;
        front = n;
    }
}
// @end LinkedQueueDtor

// @begin push
void LinkedQueue::push(int x) {
    QNode* n = new QNode{x, nullptr};
    if (rear == nullptr) front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
}
// @end push

// @begin pop
int LinkedQueue::pop() {
    if (front == nullptr) return -1;
    QNode* old = front;
    int x = old->data;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete old;
    return x;
}
// @end pop

// L28-V · Example: 1 2 3 4 5 6  =>  1 4 2 5 3 6
// @begin interleaveHalves
void interleaveHalves(queue<int>& q) {
    int half = q.size() / 2;
    queue<int> first;
    for (int i = 0; i < half; i++) { first.push(q.front()); q.pop(); }
    while (!first.empty()) {
        q.push(first.front()); first.pop();    // one from the first half
        q.push(q.front()); q.pop();            // one from the second half
    }
}
// @end interleaveHalves
