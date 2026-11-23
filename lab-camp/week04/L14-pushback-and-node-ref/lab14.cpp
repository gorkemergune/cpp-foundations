// ============================================================================
//  Lab 14 · pushBack and positions · YOU WORK HERE
//  Test everything:      .\run.ps1 L14
//  Draw the boxes and arrows on paper before each function (Lab 13).
// ============================================================================
#include "lab14.h"

#include "todo.h"

// L14-A · Example: 2 -> 3, pushFront(head, 1)  =>  1 -> 2 -> 3
void pushFront(Node*& head, int value) {
    TODO();
}

// L14-B · Example: 1 -> 2, pushBack(head, 3)  =>  1 -> 2 -> 3;  empty  =>  3
void pushBack(Node*& head, int value) {
    TODO();
}

// L14-M1 · Example: 1 -> 3, insertAt(head, 1, 2)  =>  true, 1 -> 2 -> 3
bool insertAt(Node*& head, int index, int value) {
    TODO();
}

// L14-M2 · Example: 1 -> 2 -> 3, removeAt(head, 1)  =>  true, 1 -> 3 (the 2 is deleted)
bool removeAt(Node*& head, int index) {
    TODO();
}

// L14-X · Example: insertAtEnd(nullptr, 5) returns the new head 5
Node* insertAtEnd(Node* head, int x) {
    TODO();
}

// L14-V · Example: head = tail = nullptr; pushToBack(head, tail, 1); pushToBack(head, tail, 2)
void pushToBack(Node*& head, Node*& tail, int value) {
    TODO();
}
