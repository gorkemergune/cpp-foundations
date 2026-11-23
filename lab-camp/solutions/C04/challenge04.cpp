// ============================================================================
//  Challenge Set 04 · linked lists · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C04        one problem:  .\run.ps1 C04 C04-C
// ============================================================================
#include "challenge04.h"

#include "todo.h"

// C04-A · Example: (2 -> 4 -> 3) + (5 -> 6 -> 4)  =>  7 -> 0 -> 8   (342 + 465 = 807)
// @begin addTwoNumbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);                 // a fake head on the stack: no "first node" special case
    ListNode* tail = &dummy;
    int carry = 0;
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }
        tail->next = new ListNode(sum % 10);
        tail = tail->next;
        carry = sum / 10;
    }
    ListNode* head = dummy.next;
    dummy.next = nullptr;
    return head;
}
// @end addTwoNumbers

// C04-B · Example: 1 -> 2 -> 3 -> 4 -> 5, n = 2  =>  1 -> 2 -> 3 -> 5
// @begin removeNthFromEnd
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0, head);           // the node before the head: removing the head is normal
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;
    for (int i = 0; i < n; i++) fast = fast->next;   // fast is n nodes ahead
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }                                  // slow is now just before the node to remove
    ListNode* dead = slow->next;
    slow->next = dead->next;
    delete dead;
    head = dummy.next;
    dummy.next = nullptr;
    return head;
}
// @end removeNthFromEnd

// C04-C · Example: 1 -> 2 -> 3 -> 4 -> 5  =>  1 -> 5 -> 2 -> 4 -> 3
// @begin reorderList
void reorderList(ListNode* head) {
    if (head == nullptr) return;
    ListNode* slow = head;             // 1) find the end of the first half
    ListNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* prev = nullptr;          // 2) reverse the second half
    ListNode* cur = slow->next;
    slow->next = nullptr;
    while (cur != nullptr) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    ListNode* a = head;                // 3) weave the two halves together
    ListNode* b = prev;
    while (b != nullptr) {
        ListNode* an = a->next;
        ListNode* bn = b->next;
        a->next = b;
        b->next = an;
        a = an;
        b = bn;
    }
}
// @end reorderList
