// Linked-list based queue (as assumed in the PDF: queueNode{info, next}, front,
// rear, enqueue, dequeue (throws when empty), isEmpty).
// The functions you write live in: problems/queue.cpp
#pragma once

#include "LLStack.h"  // for QU-5 and QU-8

template <typename T>
class queueNode {
public:
    queueNode(const T& el, queueNode<T>* ptr = 0) {
        info = el;
        next = ptr;
    }
    T info;
    queueNode<T>* next;
};

template <typename T>
class LLQueue {
public:
    LLQueue() {
        front = 0;
        rear = 0;
    }
    ~LLQueue() {
        while (!isEmpty()) dequeue();
    }
    LLQueue(const LLQueue&) = delete;
    LLQueue& operator=(const LLQueue&) = delete;

    bool isEmpty() const { return front == 0; }

    void enqueue(const T& el) {
        queueNode<T>* n = new queueNode<T>(el);
        if (isEmpty()) {
            front = rear = n;
        } else {
            rear->next = n;
            rear = n;
        }
    }

    T dequeue() {
        if (isEmpty()) throw runtime_error("dequeue: queue is empty");
        queueNode<T>* p = front;
        T el = p->info;
        front = front->next;
        if (front == 0) rear = 0;
        delete p;
        return el;
    }

    // For debugging: q.printQueue();  →  front -> 4 6 1 <- rear
    void printQueue() const {
        cout << "front ->";
        for (queueNode<T>* p = front; p != 0; p = p->next) cout << " " << p->info;
        cout << " <- rear" << endl;
    }

    // ---------------- problems (problems/queue.cpp) ----------------
    int size();                     // QU-1
    T getFront();                   // QU-2
    T getRear();                    // QU-2
    bool contains(const T& v);      // QU-3
    int countGreater(const T& v);   // QU-4
    void reverse();                 // QU-5
    int removeAll(const T& v);      // QU-6
    void rotate(int k);             // QU-7
    void reverseFirstK(int k);      // QU-8
    void interleave();              // QU-9

    // ---------------- test helpers ----------------
    void fill(const vector<T>& frontToRear) {
        for (const T& x : frontToRear) enqueue(x);
    }
    vector<T> toVector() const {  // front to rear
        vector<T> r;
        for (queueNode<T>* p = front; p != 0; p = p->next) r.push_back(p->info);
        return r;
    }

private:
    queueNode<T>* front;
    queueNode<T>* rear;
};
