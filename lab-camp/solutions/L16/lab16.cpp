// ============================================================================
//  Lab 16 · TIMED LAB (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a timer. Test:  .\run.ps1 L16      one part:  .\run.ps1 L16 L16-A
//  Draw before you code. No new nodes in A and C; B deletes exactly one node.
// ============================================================================
#include "lab16.h"

#include "todo.h"

// Part A · Example: 1 -> 2 -> 3  =>  returns the old 3, list 3 -> 2 -> 1
// @begin reverseList
Node* reverseList(Node* head) {
    Node* prev = nullptr;          // the already reversed part
    Node* cur = head;              // the part still to reverse
    while (cur != nullptr) {
        Node* next = cur->next;    // 1) save the rest of the list
        cur->next = prev;          // 2) turn this arrow around
        prev = cur;                // 3) move both pointers one step
        cur = next;
    }
    return prev;                   // the old last node
}
// @end reverseList

// Part B · Example: 1 -> 4 -> 3 -> 4, v = 4  =>  true, 1 -> 3 -> 4
// @begin removeFirst
bool removeFirst(Node*& head, int v) {
    if (head == nullptr) return false;
    if (head->data == v) {
        Node* dead = head;
        head = head->next;
        delete dead;
        return true;
    }
    Node* prev = head;
    while (prev->next != nullptr && prev->next->data != v) prev = prev->next;
    if (prev->next == nullptr) return false;
    Node* dead = prev->next;
    prev->next = dead->next;
    delete dead;
    return true;
}
// @end removeFirst

// Part C · Example: 1 -> 2 -> 3 -> 4  =>  the node holding 3
// @begin middleNode
Node* middleNode(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;         // one step
        fast = fast->next->next;   // two steps
    }
    return slow;                   // fast reached the end: slow is half-way
}
// @end middleNode

// L16-X · Example: 1 -> 2 -> 2 -> 1  =>  true
// @begin isPalindrome
bool isPalindrome(Node* head) {
    Node* second = reverseList(middleNode(head));   // reverse the second half
    bool ok = true;
    for (Node *a = head, *b = second; b != nullptr; a = a->next, b = b->next)
        if (a->data != b->data) { ok = false; break; }
    reverseList(second);           // restore: the caller's list must look unchanged
    return ok;
}
// @end isPalindrome

// L16-V · Example: 4 -> 1 -> 4, v = 4  =>  2
// @begin countValue
int countValue(const Node* head, int v) {
    int n = 0;
    for (; head != nullptr; head = head->next)
        if (head->data == v) n++;
    return n;
}
// @end countValue
