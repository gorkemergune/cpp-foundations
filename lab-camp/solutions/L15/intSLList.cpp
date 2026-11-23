//************************  intSLList.cpp  **************************
//  Lab 15 · the course class IntSLList · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L15
//  Keep head AND tail correct after every operation (the tests check tail too).
#include "intSLList.h"

#include "todo.h"

// L15-M2 · the destructor deletes every node (it must not throw)
// @begin ~IntSLList empty
IntSLList::~IntSLList() {
    while (head != 0) {
        IntSLLNode* p = head->next;
        delete head;
        head = p;
    }
}
// @end ~IntSLList

// L15-A · Example: addToHead(1) on 2 -> 3  =>  1 -> 2 -> 3
// @begin addToHead
void IntSLList::addToHead(int el) {
    head = new IntSLLNode(el, head);
    if (tail == 0) tail = head;          // the list was empty: one node is head and tail
}
// @end addToHead

// L15-A · Example: addToTail(4) on 1 -> 2  =>  1 -> 2 -> 4   (O(1) thanks to tail)
// @begin addToTail
void IntSLList::addToTail(int el) {
    if (tail != 0) {
        tail->next = new IntSLLNode(el);
        tail = tail->next;
    } else {
        head = tail = new IntSLLNode(el);
    }
}
// @end addToTail

// L15-B · precondition: not empty. Example: 1 -> 2  =>  returns 1, list 2
// @begin deleteFromHead
int IntSLList::deleteFromHead() {
    int el = head->info;
    IntSLLNode* tmp = head;
    if (head == tail) head = tail = 0;   // it was the only node
    else head = head->next;
    delete tmp;
    return el;
}
// @end deleteFromHead

// L15-B · precondition: not empty. Example: 1 -> 2 -> 3  =>  returns 3, list 1 -> 2
// @begin deleteFromTail
int IntSLList::deleteFromTail() {
    int el = tail->info;
    if (head == tail) {
        delete head;
        head = tail = 0;
    } else {
        IntSLLNode* tmp = head;          // a singly list has no prev: walk to the node before tail
        while (tmp->next != tail) tmp = tmp->next;
        delete tail;
        tail = tmp;
        tail->next = 0;
    }
    return el;
}
// @end deleteFromTail

// L15-M1 · Example: deleteNode(2) on 1 -> 2 -> 3 -> 2  =>  1 -> 3 -> 2
// @begin deleteNode
void IntSLList::deleteNode(int el) {
    if (head == 0) return;
    if (head->info == el) {              // the head is the one
        deleteFromHead();
        return;
    }
    IntSLLNode* pred = head;
    IntSLLNode* tmp = head->next;
    while (tmp != 0 && tmp->info != el) {
        pred = tmp;
        tmp = tmp->next;
    }
    if (tmp == 0) return;                // not found
    pred->next = tmp->next;
    if (tmp == tail) tail = pred;        // deleting the last node moves tail back
    delete tmp;
}
// @end deleteNode

// L15-M1 · Example: isInList(3) on 1 -> 3  =>  true
// @begin isInList
bool IntSLList::isInList(int el) const {
    IntSLLNode* tmp = head;
    while (tmp != 0 && tmp->info != el) tmp = tmp->next;
    return tmp != 0;
}
// @end isInList

// L15-X · Example: removeAll(2) on 2 -> 1 -> 2 -> 2  =>  returns 3, list 1
// @begin removeAll
int IntSLList::removeAll(int el) {
    int removed = 0;
    IntSLLNode* pred = 0;
    IntSLLNode* cur = head;
    while (cur != 0) {
        IntSLLNode* next = cur->next;
        if (cur->info == el) {
            if (pred == 0) head = next;
            else pred->next = next;
            if (cur == tail) tail = pred;
            delete cur;
            removed++;
        } else {
            pred = cur;
        }
        cur = next;
    }
    return removed;
}
// @end removeAll

// L15-V · Example: insertSorted(4) on 1 -> 3 -> 5  =>  1 -> 3 -> 4 -> 5
// @begin insertSorted
void IntSLList::insertSorted(int el) {
    if (head == 0 || el <= head->info) {
        addToHead(el);
        return;
    }
    IntSLLNode* pred = head;
    while (pred->next != 0 && pred->next->info < el) pred = pred->next;
    if (pred == tail) addToTail(el);
    else pred->next = new IntSLLNode(el, pred->next);
}
// @end insertSorted
