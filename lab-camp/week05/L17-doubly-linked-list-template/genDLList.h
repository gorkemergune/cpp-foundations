//************************  genDLList.h  **************************
//  Lab 17 · the course's DoublyLinkedList<T> (Labwork 2, 3, 5) · YOU WORK HERE
//  A class template: EVERYTHING stays in this header.   Test:  .\run.ps1 L17
//  Keep head, tail, every next AND every prev correct (the tests walk both ways).
#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <vector>

#include "todo.h"

template <class T>
class DLLNode {
public:
    DLLNode() { next = prev = 0; alive++; }
    DLLNode(const T& el, DLLNode<T>* n = 0, DLLNode<T>* p = 0) {
        info = el; next = n; prev = p; alive++;
    }
    ~DLLNode() { alive--; }
    T info;
    DLLNode<T> *next, *prev;
    static inline int alive = 0;     // lab camp: live nodes, for leak checks
};

template <class T>
class DoublyLinkedList {
public:
    DoublyLinkedList() { head = tail = 0; }
    ~DoublyLinkedList() { clear(); }
    DoublyLinkedList(const DoublyLinkedList&) = delete;            // lab camp: no copies
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    bool isEmpty() const { return head == 0; }

    void addToDLLHead(const T&);     // L17-A
    void addToDLLTail(const T&);     // L17-A
    T deleteFromDLLHead();           // L17-B · precondition: not empty
    T deleteFromDLLTail();           // L17-B · precondition: not empty, O(1) thanks to prev
    void clear();                    // L17-B · delete every node
    bool removeValue(const T&);      // L17-M1 · first node holding el; false if none
    void reverse();                  // L17-M2 · in place: swap next/prev, swap head/tail
    void append(const DoublyLinkedList<T>&);   // L17-X · Labwork 2 Q1: copy other to the end
    T* find(const T&) const;         // L17-V · pointer to the first match's info, or 0
    T& firstEl() { return head->info; }        // given

    // lab camp: test helpers (read only)
    std::vector<T> forward() const {
        std::vector<T> r;
        for (DLLNode<T>* p = head; p != 0 && r.size() < 100000; p = p->next) r.push_back(p->info);
        return r;
    }
    std::vector<T> backward() const {
        std::vector<T> r;
        for (DLLNode<T>* p = tail; p != 0 && r.size() < 100000; p = p->prev) r.push_back(p->info);
        return r;
    }
    bool endsOk() const {
        return head == 0 ? tail == 0 : (head->prev == 0 && tail != 0 && tail->next == 0);
    }

private:
    DLLNode<T> *head, *tail;
};

// L17-A · Example: addToDLLHead(1) on 2 <-> 3  =>  1 <-> 2 <-> 3
template <class T>
void DoublyLinkedList<T>::addToDLLHead(const T& el) {
    TODO();
}

template <class T>
void DoublyLinkedList<T>::addToDLLTail(const T& el) {
    TODO();
}

// L17-B · Example: 1 <-> 2  =>  returns 1, list 2
template <class T>
T DoublyLinkedList<T>::deleteFromDLLHead() {
    TODO();
}

template <class T>
T DoublyLinkedList<T>::deleteFromDLLTail() {
    TODO();
}

template <class T>
void DoublyLinkedList<T>::clear() {
    // TODO: write this (it must not throw)
}

// L17-M1 · Example: removeValue(2) on 1 <-> 2 <-> 3 <-> 2  =>  true, 1 <-> 3 <-> 2
template <class T>
bool DoublyLinkedList<T>::removeValue(const T& el) {
    TODO();
}

// L17-M2 · Example: 1 <-> 2 <-> 3  =>  3 <-> 2 <-> 1 (same nodes)
template <class T>
void DoublyLinkedList<T>::reverse() {
    TODO();
}

// L17-X · Labwork 2 Q1. Example: A = 5 8, B = 6 7  =>  A = 5 8 6 7, B unchanged
template <class T>
void DoublyLinkedList<T>::append(const DoublyLinkedList<T>& other) {
    TODO();
}

// L17-V · Example: find(3) on 1 <-> 3  =>  pointer to the 3; find(9)  =>  0
template <class T>
T* DoublyLinkedList<T>::find(const T& el) const {
    TODO();
}

#endif
