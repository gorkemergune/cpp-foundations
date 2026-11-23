// ============================================================================
//  Challenge Set 12 · heaps · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C12        one problem:  .\run.ps1 C12 C12-B
// ============================================================================
#include "challenge12.h"

#include <unordered_map>
#include <utility>

#include "todo.h"

using namespace std;

// C12-A · Example: {1->4->5, 1->3->4, 2->6}  =>  1->1->2->3->4->4->5->6
// @begin mergeKLists
ListNode* mergeKLists(vector<ListNode*>& lists) {
    using Item = pair<int, ListNode*>;      // (value, node): the heads of the lists
    priority_queue<Item, vector<Item>, greater<Item>> heads;
    for (ListNode* l : lists)
        if (l != nullptr) heads.push({l->val, l});
    ListNode dummy(0);                      // a fake first node: no special case for the head
    ListNode* tail = &dummy;
    while (!heads.empty()) {
        ListNode* n = heads.top().second;
        heads.pop();
        tail->next = n;                     // relink the smallest head
        tail = n;
        if (n->next != nullptr) heads.push({n->next->val, n->next});
    }
    tail->next = nullptr;
    return dummy.next;
}
// @end mergeKLists

// C12-B · Example: add 1, add 2  =>  1.5;  add 3  =>  2
// @begin addNum
void MedianFinder::addNum(int num) {
    if (low.empty() || num <= low.top()) low.push(num);
    else high.push(num);
    if (low.size() > high.size() + 1) {     // keep |low| == |high| or |high| + 1
        high.push(low.top());
        low.pop();
    } else if (high.size() > low.size()) {
        low.push(high.top());
        high.pop();
    }
}
// @end addNum

// @begin findMedian
double MedianFinder::findMedian() const {
    if (low.size() > high.size()) return low.top();
    return (low.top() + (double)high.top()) / 2;
}
// @end findMedian

// C12-C · Example: {1,1,1,2,2,3}, k = 2  =>  {1, 2}
// @begin topKFrequent
vector<int> topKFrequent(const vector<int>& nums, int k) {
    unordered_map<int, int> count;
    for (int x : nums) count[x]++;
    using Item = pair<int, int>;            // (frequency, value)
    priority_queue<Item, vector<Item>, greater<Item>> best;   // the k most frequent so far
    for (auto [value, freq] : count) {
        best.push({freq, value});
        if ((int)best.size() > k) best.pop();
    }
    vector<int> out;
    while (!best.empty()) {
        out.push_back(best.top().second);
        best.pop();
    }
    return out;
}
// @end topKFrequent
