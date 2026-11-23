// ============================================================================
//  Lab 26 · LLQueue<T>: a linked queue template · YOU WORK HERE (whole file)
//  Names as in the old midterm camp and 2021 Assignment 3: enqueue, dequeue()
//  RETURNS the value (runtime_error when empty), isEmpty, getFront, getRear.
//  Test:  .\run.ps1 L26
// ============================================================================
#ifndef LLQUEUE_H
#define LLQUEUE_H

#include <stdexcept>
#include <vector>

#include "todo.h"

template <typename T>
class queueNode {
public:
    queueNode(const T& el, queueNode<T>* ptr = nullptr) : info(el), next(ptr) { alive++; }
    ~queueNode() { alive--; }
    T info;
    queueNode<T>* next;
    static inline int alive = 0;             // lab camp: leak checks
};

template <typename T>
class LLQueue {
public:
    LLQueue() : front(nullptr), rear(nullptr), count(0) {}
    ~LLQueue() { clear(); }
    LLQueue(const LLQueue&) = delete;
    LLQueue& operator=(const LLQueue&) = delete;

    bool isEmpty() const;                    // L26-A
    void enqueue(const T& el);               // L26-A · at the rear, O(1)
    int size() const;                        // L26-A · O(1)
    T dequeue();                             // L26-B · remove + return the front
    T getFront() const;                      // L26-B · runtime_error if empty
    T getRear() const;                       // L26-B · runtime_error if empty
    void clear();                            // L26-M1 · the destructor calls it
    void reverse();                          // L26-V · relink, front and rear swap

    std::vector<T> toVector() const {        // test helper: front first
        std::vector<T> r;
        for (queueNode<T>* p = front; p != nullptr; p = p->next) r.push_back(p->info);
        return r;
    }
    bool endsOk() const {                    // test helper: rear is the last node
        if (front == nullptr) return rear == nullptr;
        queueNode<T>* p = front;
        while (p->next != nullptr) p = p->next;
        return p == rear;
    }

private:
    queueNode<T>* front;
    queueNode<T>* rear;
    int count;
};

template <typename T>
bool LLQueue<T>::isEmpty() const {
    TODO();
}

// L26-A · Example: enqueue 1, 2, 3  =>  front -> 1, 2, 3 <- rear
template <typename T>
void LLQueue<T>::enqueue(const T& el) {
    TODO();
}

template <typename T>
int LLQueue<T>::size() const {
    TODO();
}

// L26-B · Example: front -> 1, 2  =>  returns 1, front -> 2
template <typename T>
T LLQueue<T>::dequeue() {
    TODO();
}

template <typename T>
T LLQueue<T>::getFront() const {
    TODO();
}

template <typename T>
T LLQueue<T>::getRear() const {
    TODO();
}

template <typename T>
void LLQueue<T>::clear() {
    // TODO: write this (it must not throw)
}

// L26-V · Example: front -> 1, 2, 3  =>  front -> 3, 2, 1 (same nodes)
template <typename T>
void LLQueue<T>::reverse() {
    TODO();
}

#endif
