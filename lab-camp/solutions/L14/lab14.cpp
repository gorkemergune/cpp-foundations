// ============================================================================
//  Lab 14 · pushBack and positions · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L14
//  Draw the boxes and arrows on paper before each function (Lab 13).
// ============================================================================
#include "lab14.h"

#include "todo.h"

// L14-A · Example: 2 -> 3, pushFront(head, 1)  =>  1 -> 2 -> 3
// @begin pushFront
void pushFront(Node*& head, int value) {
    head = new Node{value, head};      // new node points at the old head, then becomes head
}
// @end pushFront

// L14-B · Example: 1 -> 2, pushBack(head, 3)  =>  1 -> 2 -> 3;  empty  =>  3
// @begin pushBack
void pushBack(Node*& head, int value) {
    Node* n = new Node{value, nullptr};
    if (head == nullptr) {             // empty list: the caller's head must change
        head = n;
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr) cur = cur->next;   // stop ON the last node
    cur->next = n;
}
// @end pushBack

// L14-M1 · Example: 1 -> 3, insertAt(head, 1, 2)  =>  true, 1 -> 2 -> 3
// @begin insertAt
bool insertAt(Node*& head, int index, int value) {
    if (index < 0) return false;
    if (index == 0) {                  // the head changes: handled separately
        pushFront(head, value);
        return true;
    }
    Node* prev = head;                 // walk to the node BEFORE the position
    for (int i = 0; i < index - 1 && prev != nullptr; i++) prev = prev->next;
    if (prev == nullptr) return false; // index > length
    prev->next = new Node{value, prev->next};
    return true;
}
// @end insertAt

// L14-M2 · Example: 1 -> 2 -> 3, removeAt(head, 1)  =>  true, 1 -> 3 (the 2 is deleted)
// @begin removeAt
bool removeAt(Node*& head, int index) {
    if (index < 0 || head == nullptr) return false;
    if (index == 0) {
        Node* dead = head;
        head = head->next;
        delete dead;
        return true;
    }
    Node* prev = head;
    for (int i = 0; i < index - 1 && prev->next != nullptr; i++) prev = prev->next;
    if (prev->next == nullptr) return false;       // no node at that position
    Node* dead = prev->next;
    prev->next = dead->next;                       // unlink first ...
    delete dead;                                   // ... then delete
    return true;
}
// @end removeAt

// L14-X · Example: insertAtEnd(nullptr, 5) returns the new head 5
// @begin insertAtEnd
Node* insertAtEnd(Node* head, int x) {
    pushBack(head, x);     // head is a local copy here; pushBack may change the copy
    return head;           // ... so the caller gets it through the return value
}
// @end insertAtEnd

// L14-V · Example: head = tail = nullptr; pushToBack(head, tail, 1); pushToBack(head, tail, 2)
// @begin pushToBack
void pushToBack(Node*& head, Node*& tail, int value) {
    Node* n = new Node{value, nullptr};
    if (tail == nullptr) head = tail = n;
    else {
        tail->next = n;
        tail = n;
    }
}
// @end pushToBack
