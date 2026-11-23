// ============================================================================
//  Challenge Set 04 · singly linked lists (medium)                  DO NOT EDIT
//  ListNode is LeetCode's node type (val / next); a live counter is added for tests.
// ============================================================================
#pragma once

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x, ListNode* n = nullptr) : val(x), next(n) { alive++; }
    ~ListNode() { alive--; }
    static inline int alive = 0;
};

// C04-A · LeetCode 2: digits stored in reverse order; return a NEW list with the sum.
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

// C04-B · LeetCode 19: remove (and delete) the n-th node from the end; return the head.
// 1 <= n <= length. One pass.
ListNode* removeNthFromEnd(ListNode* head, int n);

// C04-C · LeetCode 143: L0 L1 ... Ln  ->  L0 Ln L1 Ln-1 L2 ...  in place, no new nodes.
void reorderList(ListNode* head);
