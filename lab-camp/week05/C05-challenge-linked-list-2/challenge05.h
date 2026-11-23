// ============================================================================
//  Challenge Set 05 · linked lists II (medium / hard)               DO NOT EDIT
// ============================================================================
#pragma once

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x, ListNode* n = nullptr) : val(x), next(n) { alive++; }
    ~ListNode() { alive--; }
    static inline int alive = 0;
};

// A node with an extra pointer to ANY node of the same list (or nullptr).
struct RNode {
    int val;
    RNode* next;
    RNode* random;
    RNode(int x) : val(x), next(nullptr), random(nullptr) { alive++; }
    ~RNode() { alive--; }
    static inline int alive = 0;
};

// C05-A · LeetCode 142 (medium): the node where the cycle begins, or nullptr. O(1) memory.
ListNode* detectCycle(ListNode* head);

// C05-B · LeetCode 25 (hard): reverse every group of k nodes; a shorter last group stays.
// Relink nodes, O(1) extra memory. Return the new head.
ListNode* reverseKGroup(ListNode* head, int k);

// C05-C · LeetCode 138 (medium): a deep copy; the copy's random pointers point into the COPY.
RNode* copyRandomList(RNode* head);
