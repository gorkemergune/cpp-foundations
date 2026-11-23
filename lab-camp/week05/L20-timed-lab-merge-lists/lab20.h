// ============================================================================
//  Lab 20 · TIMED LAB (50 min) · Merging and cleaning lists         DO NOT EDIT
//  LeetCode's ListNode (val / next) with a live counter for the tests.
// ============================================================================
#pragma once

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x, ListNode* n = nullptr) : val(x), next(n) { alive++; }
    ~ListNode() { alive--; }
    static inline int alive = 0;
};

// Part A · L20-A · LeetCode 83: sorted list, delete the repeated nodes (keep one of each).
ListNode* deleteDuplicates(ListNode* head);

// Part B · L20-B · LeetCode 21: merge two sorted lists by RELINKING their nodes.
ListNode* mergeTwoLists(ListNode* a, ListNode* b);

// Part C · L20-C · LeetCode 141: does the list contain a cycle? O(1) extra memory.
bool hasCycle(ListNode* head);

// L20-X · Optional · LeetCode 160: the first node shared by two lists, or nullptr.
ListNode* getIntersectionNode(ListNode* a, ListNode* b);

// L20-V · Optional · LeetCode 203: delete every node holding val; return the head.
ListNode* removeElements(ListNode* head, int val);
