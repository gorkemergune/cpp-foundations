// ============================================================================
//  Challenge Set 12 · heaps (medium / hard)                          DO NOT EDIT
// ============================================================================
#pragma once

#include <queue>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

// C12-A · LeetCode 23 (hard): merge k sorted linked lists into one sorted list by relinking
// the existing nodes (no new nodes). O(N log k).
ListNode* mergeKLists(std::vector<ListNode*>& lists);

// C12-B · LeetCode 295 (hard): numbers arrive one by one; the median of all so far at any
// time (the mean of the two middle values for an even count). O(log n) per number.
class MedianFinder {
public:
    void addNum(int num);
    double findMedian() const;   // precondition: at least one number
private:
    std::priority_queue<int> low;                                       // the smaller half
    std::priority_queue<int, std::vector<int>, std::greater<int>> high; // the larger half
};

// C12-C · LeetCode 347 (medium): the k most frequent values (the answer is unique);
// any order.
std::vector<int> topKFrequent(const std::vector<int>& nums, int k);
