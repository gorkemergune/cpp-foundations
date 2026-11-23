//************************  intSLList.cpp  **************************
// Assignment 3 (2021) · IntSLList from the assignment files, cleaned up; size is tracked.
#include "IntSLList.h"

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
    size++;
    if (tail == 0) tail = head;
}

void IntSLList::addToTail(int el) {
    size++;
    if (tail != 0) {
        tail->next = new IntSLLNode(el);
        tail = tail->next;
    } else {
        head = tail = new IntSLLNode(el);
    }
}

int IntSLList::deleteFromHead() {  // precondition: list is not empty
    size--;
    int el = head->info;
    IntSLLNode* tmp = head;
    if (head == tail) head = tail = 0;
    else head = head->next;
    delete tmp;
    return el;
}

int IntSLList::deleteFromTail() {  // precondition: list is not empty
    size--;
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
        size--;
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
        size--;
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


// 1-based position, as in the assignment files: GetAt(1) is the head.
int IntSLList::GetAt(int x) {
    IntSLLNode* tmp = head;
    for (int i = 1; i < x && tmp != 0; i++) tmp = tmp->next;
    return tmp->info;            // precondition: 1 <= x <= size
}

int IntSLList::GetSize() { return size; }
