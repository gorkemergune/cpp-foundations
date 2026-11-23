//************************  intSLList.cpp  **************************
// Labwork 1 · reference solution (base functions from the course + Q1, Q2)
#include "intSLList.h"

#include <iostream>
using namespace std;

IntSLList::~IntSLList() {
    while (!isEmpty()) {
        IntSLLNode* p = head->next;
        delete head;
        head = p;
    }
}

void IntSLList::addToHead(int el) {
    head = new IntSLLNode(el, head);
    if (tail == 0) tail = head;
}

void IntSLList::addToTail(int el) {
    if (tail != 0) {
        tail->next = new IntSLLNode(el);
        tail = tail->next;
    } else {
        head = tail = new IntSLLNode(el);
    }
}

int IntSLList::deleteFromHead() {  // precondition: list is not empty
    int el = head->info;
    IntSLLNode* tmp = head;
    if (head == tail) head = tail = 0;
    else head = head->next;
    delete tmp;
    return el;
}

int IntSLList::deleteFromTail() {  // precondition: list is not empty
    int el = tail->info;
    if (head == tail) {
        delete head;
        head = tail = 0;
    } else {
        IntSLLNode* tmp = head;
        while (tmp->next != tail) tmp = tmp->next;
        delete tail;
        tail = tmp;
        tail->next = 0;
    }
    return el;
}

void IntSLList::deleteNode(int el) {
    if (head == 0) return;
    if (head->info == el) {
        IntSLLNode* tmp = head;
        head = head->next;
        if (head == 0) tail = 0;
        delete tmp;
        return;
    }
    IntSLLNode* pred = head;
    IntSLLNode* tmp = head->next;
    while (tmp != 0 && tmp->info != el) {
        pred = tmp;
        tmp = tmp->next;
    }
    if (tmp != 0) {
        pred->next = tmp->next;
        if (tmp == tail) tail = pred;
        delete tmp;
    }
}

bool IntSLList::isInList(int el) const {
    IntSLLNode* tmp = head;
    while (tmp != 0 && tmp->info != el) tmp = tmp->next;
    return tmp != 0;
}

void IntSLList::printAll() const {
    for (IntSLLNode* tmp = head; tmp != 0; tmp = tmp->next) cout << tmp->info << " ";
    cout << endl;
}

// Q1 · remove every node that stores an even number, in one pass.
// pred is the last node we KEEP; head and tail are fixed when they are removed.
void IntSLList::remove_even() {
    IntSLLNode* pred = 0;
    IntSLLNode* cur = head;
    while (cur != 0) {
        IntSLLNode* next = cur->next;
        if (cur->info % 2 == 0) {          // also true for negative evens
            if (pred == 0) head = next;    // removing the current head
            else pred->next = next;
            if (cur == tail) tail = pred;  // removing the tail: pred is the new tail (0 if empty)
            delete cur;
        } else {
            pred = cur;
        }
        cur = next;
    }
}

// Q2 · after every node holding 5, insert a new node holding 5.
// Only when the duplicated node was the tail does the new node become the tail.
void IntSLList::duplicate_fives() {
    IntSLLNode* cur = head;
    while (cur != 0) {
        if (cur->info == 5) {
            IntSLLNode* copy = new IntSLLNode(5, cur->next);
            cur->next = copy;
            if (cur == tail) tail = copy;
            cur = copy->next;              // skip the copy, or we would loop forever
        } else {
            cur = cur->next;
        }
    }
}
