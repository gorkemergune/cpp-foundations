// ============================================================================
//  Challenge Set 05 · linked lists II · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C05        one problem:  .\run.ps1 C05 C05-B
// ============================================================================
#include "challenge05.h"

#include "todo.h"

// C05-A · Example: 3 -> 2 -> 0 -> -4 -> (2)  =>  the node 2
// @begin detectCycle
ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                 // inside the cycle (Lab 20, Part C)
            ListNode* p = head;             // distance head -> start == meeting -> start
            while (p != slow) {             //   (modulo the cycle length)
                p = p->next;
                slow = slow->next;
            }
            return p;
        }
    }
    return nullptr;
}
// @end detectCycle

// C05-B · Example: 1 2 3 4 5, k = 2  =>  2 1 4 3 5
// @begin reverseKGroup
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode dummy(0, head);
    ListNode* groupPrev = &dummy;           // the node before the current group
    while (true) {
        ListNode* kth = groupPrev;          // is there a full group of k?
        for (int i = 0; i < k && kth != nullptr; i++) kth = kth->next;
        if (kth == nullptr) break;
        ListNode* groupNext = kth->next;
        ListNode* prev = groupNext;         // reverse the group; its first node will point on
        ListNode* cur = groupPrev->next;
        while (cur != groupNext) {
            ListNode* nx = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nx;
        }
        ListNode* oldFirst = groupPrev->next;   // becomes the last node of the group
        groupPrev->next = kth;                  // kth is the new first node
        groupPrev = oldFirst;
    }
    head = dummy.next;
    dummy.next = nullptr;
    return head;
}
// @end reverseKGroup

// C05-C · copies interleaved: A -> A' -> B -> B' ..., then random fixed, then split
// @begin copyRandomList
RNode* copyRandomList(RNode* head) {
    for (RNode* p = head; p != nullptr; p = p->next->next) {   // 1) A -> A' -> B
        RNode* c = new RNode(p->val);
        c->next = p->next;
        p->next = c;
    }
    for (RNode* p = head; p != nullptr; p = p->next->next)     // 2) A'.random = A.random'
        p->next->random = (p->random != nullptr) ? p->random->next : nullptr;
    RNode* copyHead = head ? head->next : nullptr;             // 3) split the two lists
    for (RNode* p = head; p != nullptr; p = p->next) {
        RNode* c = p->next;
        p->next = c->next;                                     // restore the original
        c->next = c->next ? c->next->next : nullptr;
    }
    return copyHead;
}
// @end copyRandomList
