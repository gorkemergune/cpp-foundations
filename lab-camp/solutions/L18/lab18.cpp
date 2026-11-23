// ============================================================================
//  Lab 18 · Delete the middle node · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L18
//  B, M, X, V: one pass with slow/fast pointers; no length() inside them.
// ============================================================================
#include "lab18.h"

#include "todo.h"

// L18-A · Example: 1 -> 2 -> 3  =>  3
// @begin length
int length(const Node* head) {
    int n = 0;
    for (; head != nullptr; head = head->next) n++;
    return n;
}
// @end length

// L18-B · Example: 1 -> 2 -> 3 -> 4 -> 5 (middle = 3)  =>  the node holding 2
// @begin beforeMiddle
Node* beforeMiddle(Node* head) {
    if (head == nullptr || head->next == nullptr) return nullptr;
    Node* slow = head;                 // will stop one node before the middle
    Node* fast = head->next->next;     // fast starts two ahead: slow lags by one step
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
// @end beforeMiddle

// L18-M · Example: 1 -> 3 -> 4 -> 7 -> 1 -> 2 -> 6  =>  true, 1 -> 3 -> 4 -> 1 -> 2 -> 6
// @begin deleteMiddle
bool deleteMiddle(Node*& head) {
    if (head == nullptr) return false;
    if (head->next == nullptr) {       // one node: it IS the middle
        delete head;
        head = nullptr;
        return true;
    }
    Node* prev = beforeMiddle(head);
    Node* mid = prev->next;
    prev->next = mid->next;            // unlink
    delete mid;                        // then free
    return true;
}
// @end deleteMiddle

// L18-X · Example: deleteMiddleLC(1 -> 2) returns 1 (the 2 was deleted)
// @begin deleteMiddleLC
Node* deleteMiddleLC(Node* head) {
    deleteMiddle(head);                // head is a copy; deleteMiddle may change the copy
    return head;
}
// @end deleteMiddleLC

// L18-V · Example: 1 -> 2 -> 3 -> 4  =>  true, 1 -> 3 -> 4   (the 2 is the first middle)
// @begin deleteLeftMiddle
bool deleteLeftMiddle(Node*& head) {
    if (head == nullptr) return false;
    if (head->next == nullptr || head->next->next == nullptr) {   // n = 1 or 2: the head
        Node* dead = head;
        head = head->next;
        delete dead;
        return true;
    }
    Node* slow = head;
    Node* fast = head->next->next->next;   // one step further than in beforeMiddle
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* mid = slow->next;
    slow->next = mid->next;
    delete mid;
    return true;
}
// @end deleteLeftMiddle
