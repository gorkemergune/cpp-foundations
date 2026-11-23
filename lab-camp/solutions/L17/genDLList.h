//************************  genDLList.h  **************************
//  Lab 17 · the course's DoublyLinkedList<T> (Labwork 2, 3, 5) · YOU WORK HERE
//  Reference solution. @solution-note
//  A class template: EVERYTHING stays in this header.   Test:  .\run.ps1 L17
//  Keep head, tail, every next AND every prev correct (the tests walk both ways).
#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <vector>

#include "todo.h"

// @show classes
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
// @endshow classes

// L17-A · Example: addToDLLHead(1) on 2 <-> 3  =>  1 <-> 2 <-> 3
// @begin addToDLLHead
template <class T>
void DoublyLinkedList<T>::addToDLLHead(const T& el) {
    if (head != 0) {
        head = new DLLNode<T>(el, head, 0);   // next = old head, prev = none
        head->next->prev = head;              // the old head points back
    } else {
        head = tail = new DLLNode<T>(el);
    }
}
// @end addToDLLHead

// @begin addToDLLTail
template <class T>
void DoublyLinkedList<T>::addToDLLTail(const T& el) {
    if (tail != 0) {
        tail = new DLLNode<T>(el, 0, tail);   // next = none, prev = old tail
        tail->prev->next = tail;
    } else {
        head = tail = new DLLNode<T>(el);
    }
}
// @end addToDLLTail

// L17-B · Example: 1 <-> 2  =>  returns 1, list 2
// @begin deleteFromDLLHead
template <class T>
T DoublyLinkedList<T>::deleteFromDLLHead() {
    T el = head->info;
    if (head == tail) {
        delete head;
        head = tail = 0;
    } else {
        head = head->next;
        delete head->prev;
        head->prev = 0;
    }
    return el;
}
// @end deleteFromDLLHead

// @begin deleteFromDLLTail
template <class T>
T DoublyLinkedList<T>::deleteFromDLLTail() {
    T el = tail->info;
    if (head == tail) {
        delete head;
        head = tail = 0;
    } else {
        tail = tail->prev;                    // no walk needed: prev gives the new tail
        delete tail->next;
        tail->next = 0;
    }
    return el;
}
// @end deleteFromDLLTail

// @begin clear empty
template <class T>
void DoublyLinkedList<T>::clear() {
    while (head != 0) {
        DLLNode<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = 0;
}
// @end clear

// L17-M1 · Example: removeValue(2) on 1 <-> 2 <-> 3 <-> 2  =>  true, 1 <-> 3 <-> 2
// @begin removeValue
template <class T>
bool DoublyLinkedList<T>::removeValue(const T& el) {
    DLLNode<T>* p = head;
    while (p != 0 && !(p->info == el)) p = p->next;
    if (p == 0) return false;
    if (p->prev != 0) p->prev->next = p->next;   // left neighbour skips p
    else head = p->next;                         // p was the head
    if (p->next != 0) p->next->prev = p->prev;   // right neighbour points back past p
    else tail = p->prev;                         // p was the tail
    delete p;
    return true;
}
// @end removeValue

// L17-M2 · Example: 1 <-> 2 <-> 3  =>  3 <-> 2 <-> 1 (same nodes)
// @begin reverse
template <class T>
void DoublyLinkedList<T>::reverse() {
    for (DLLNode<T>* p = head; p != 0; p = p->prev) {   // after the swap, prev is the old next
        DLLNode<T>* t = p->next;
        p->next = p->prev;
        p->prev = t;
    }
    DLLNode<T>* t = head;
    head = tail;
    tail = t;
}
// @end reverse

// L17-X · Labwork 2 Q1. Example: A = 5 8, B = 6 7  =>  A = 5 8 6 7, B unchanged
// @begin append
template <class T>
void DoublyLinkedList<T>::append(const DoublyLinkedList<T>& other) {
    int n = 0;                                  // count first: a.append(a) must stop
    for (DLLNode<T>* p = other.head; p != 0; p = p->next) n++;
    DLLNode<T>* src = other.head;
    for (int i = 0; i < n; i++, src = src->next) addToDLLTail(src->info);
}
// @end append

// L17-V · Example: find(3) on 1 <-> 3  =>  pointer to the 3; find(9)  =>  0
// @begin find
template <class T>
T* DoublyLinkedList<T>::find(const T& el) const {
    for (DLLNode<T>* p = head; p != 0; p = p->next)
        if (p->info == el) return &p->info;
    return 0;
}
// @end find

#endif
