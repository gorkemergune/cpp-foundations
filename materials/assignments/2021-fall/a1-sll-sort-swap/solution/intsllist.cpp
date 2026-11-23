//************************  intSLList.cpp  **************************
// Assignment 1 (2021) · reference solution. Base functions as in the course (cleaned up).
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

// ---- rule of three ---------------------------------------------------------
IntSLList::IntSLList(const IntSLList& other) {
    head = tail = 0;
    for (IntSLLNode* p = other.head; p != 0; p = p->next) addToTail(p->info);   // deep copy
}

IntSLList& IntSLList::operator=(const IntSLList& other) {
    if (this == &other) return *this;            // list = list must not delete itself
    while (!isEmpty()) deleteFromHead();
    for (IntSLLNode* p = other.head; p != 0; p = p->next) addToTail(p->info);
    return *this;
}

// ---- Q1 ----------------------------------------------------------------------
// precondition: the list is not empty
int IntSLList::find_min() {
    int best = head->info;
    for (IntSLLNode* p = head->next; p != 0; p = p->next)
        if (p->info < best) best = p->info;
    return best;
}

// Selection sort on a COPY: the minimum is brought to the head with swap_nodes and
// moved to the result. The original list is not changed. O(n^2).
IntSLList IntSLList::sort_list() {
    IntSLList work(*this);
    IntSLList result;
    while (!work.isEmpty()) {
        work.swap_nodes(work.find_min());
        result.addToTail(work.deleteFromHead());
    }
    return result;
}

// ---- Q2 ----------------------------------------------------------------------
// Swap the first node holding val with the head node by changing links (not values).
void IntSLList::swap_nodes(int val) {
    if (head == 0 || head->info == val) return;          // empty, or already at the head
    IntSLLNode* prev = head;                             // node before the target
    while (prev->next != 0 && prev->next->info != val) prev = prev->next;
    if (prev->next == 0) return;                         // val is not in the list
    IntSLLNode* target = prev->next;
    IntSLLNode* oldHead = head;
    IntSLLNode* afterTarget = target->next;
    if (prev == oldHead) {                               // target is the second node
        target->next = oldHead;
        oldHead->next = afterTarget;
    } else {
        target->next = oldHead->next;
        prev->next = oldHead;
        oldHead->next = afterTarget;
    }
    head = target;
    if (tail == target) tail = oldHead;                  // the old head took the last place
}
