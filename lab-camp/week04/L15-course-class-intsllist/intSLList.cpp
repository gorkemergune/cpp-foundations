//************************  intSLList.cpp  **************************
//  Lab 15 · the course class IntSLList · YOU WORK HERE
//  Test everything:      .\run.ps1 L15
//  Keep head AND tail correct after every operation (the tests check tail too).
#include "intSLList.h"

#include "todo.h"

// L15-M2 · the destructor deletes every node (it must not throw)
IntSLList::~IntSLList() {
    // TODO: write this (it must not throw)
}

// L15-A · Example: addToHead(1) on 2 -> 3  =>  1 -> 2 -> 3
void IntSLList::addToHead(int el) {
    TODO();
}

// L15-A · Example: addToTail(4) on 1 -> 2  =>  1 -> 2 -> 4   (O(1) thanks to tail)
void IntSLList::addToTail(int el) {
    TODO();
}

// L15-B · precondition: not empty. Example: 1 -> 2  =>  returns 1, list 2
int IntSLList::deleteFromHead() {
    TODO();
}

// L15-B · precondition: not empty. Example: 1 -> 2 -> 3  =>  returns 3, list 1 -> 2
int IntSLList::deleteFromTail() {
    TODO();
}

// L15-M1 · Example: deleteNode(2) on 1 -> 2 -> 3 -> 2  =>  1 -> 3 -> 2
void IntSLList::deleteNode(int el) {
    TODO();
}

// L15-M1 · Example: isInList(3) on 1 -> 3  =>  true
bool IntSLList::isInList(int el) const {
    TODO();
}

// L15-X · Example: removeAll(2) on 2 -> 1 -> 2 -> 2  =>  returns 3, list 1
int IntSLList::removeAll(int el) {
    TODO();
}

// L15-V · Example: insertSorted(4) on 1 -> 3 -> 5  =>  1 -> 3 -> 4 -> 5
void IntSLList::insertSorted(int el) {
    TODO();
}
