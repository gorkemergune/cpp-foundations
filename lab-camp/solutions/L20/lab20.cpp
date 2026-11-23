// ============================================================================
//  Lab 20 · TIMED LAB (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a timer. Test:  .\run.ps1 L20      one part:  .\run.ps1 L20 L20-B
// ============================================================================
#include "lab20.h"

#include "todo.h"

// Part A · Example: 1 -> 1 -> 2 -> 3 -> 3  =>  1 -> 2 -> 3 (two nodes deleted)
// @begin deleteDuplicates
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while (cur != nullptr && cur->next != nullptr) {
        if (cur->next->val == cur->val) {
            ListNode* dup = cur->next;
            cur->next = dup->next;     // skip the duplicate; do NOT move cur yet
            delete dup;
        } else {
            cur = cur->next;
        }
    }
    return head;
}
// @end deleteDuplicates

// Part B · Example: 1 -> 2 -> 4 and 1 -> 3 -> 4  =>  1 -> 1 -> 2 -> 3 -> 4 -> 4
// @begin mergeTwoLists
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (a != nullptr && b != nullptr) {
        if (a->val <= b->val) { tail->next = a; a = a->next; }
        else { tail->next = b; b = b->next; }
        tail = tail->next;
    }
    tail->next = (a != nullptr) ? a : b;   // the rest is already sorted and linked
    ListNode* head = dummy.next;
    dummy.next = nullptr;
    return head;
}
// @end mergeTwoLists

// Part C · Example: 3 -> 2 -> 0 -> -4 -> (back to 2)  =>  true
// @begin hasCycle
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;     // fast caught up from behind: there is a loop
    }
    return false;                          // fast fell off the end
}
// @end hasCycle

// L20-X · Example: a = 4 1 [8 4 5], b = 5 6 1 [8 4 5]  =>  the shared node 8
// @begin getIntersectionNode
ListNode* getIntersectionNode(ListNode* a, ListNode* b) {
    ListNode* p = a;
    ListNode* q = b;
    while (p != q) {                       // both walk a+b steps in total
        p = (p == nullptr) ? b : p->next;
        q = (q == nullptr) ? a : q->next;
    }
    return p;                              // the meeting node or nullptr
}
// @end getIntersectionNode

// L20-V · Example: 1 -> 2 -> 6 -> 3 -> 6, val = 6  =>  1 -> 2 -> 3
// @begin removeElements
ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(0, head);
    ListNode* prev = &dummy;
    while (prev->next != nullptr) {
        if (prev->next->val == val) {
            ListNode* dead = prev->next;
            prev->next = dead->next;
            delete dead;
        } else {
            prev = prev->next;
        }
    }
    head = dummy.next;
    dummy.next = nullptr;
    return head;
}
// @end removeElements
