// ============================================================================
//  Lab 31 · MIDTERM MOCK C (50 min) · YOU WORK HERE
//  Reference solution. @solution-note
//  Start a 50-minute timer.   Test:  .\run.ps1 L31      one part:  .\run.ps1 L31 L31-A
// ============================================================================
#include "mock31.h"

#include "todo.h"

// Part A · Example: circle 1 2 3 4 (last = 4)  =>  true, circle 1 2 4
// @begin deleteBeforeLast
bool deleteBeforeLast(Node*& last) {
    if (last == nullptr || last->next == last) return false;
    Node* prev = last;                         // the node before the victim
    while (prev->next->next != last) prev = prev->next;
    Node* victim = prev->next;                 // victim->next == last
    prev->next = last;                         // with 2 nodes prev == last: last->next = last
    delete victim;
    return true;
}
// @end deleteBeforeLast

// Part B · Example: front -> 1 .. 9  =>  front -> 3 2 1 4 5 6 9 8 7
// @begin reverseAlternateTriplesLL
void reverseAlternateTriplesLL(LLQueue<int>& q) {
    int n = q.size();
    LLStack<int> st;
    for (int start = 0, group = 0; start < n; start += 3, group++) {
        int len = (n - start < 3) ? n - start : 3;
        if (group % 2 == 0 && len == 3) {
            for (int i = 0; i < 3; i++) st.pushToStack(q.dequeue());
            while (!st.isEmpty()) q.enqueue(st.popFromStack());
        } else {
            for (int i = 0; i < len; i++) q.enqueue(q.dequeue());
        }
    }
}
// @end reverseAlternateTriplesLL

// Part C · Example: 1 -> 2 -> 3 -> 4  =>  list 1 -> 2 -> 4, out gets 1 2 4
// @begin deleteMiddleToLLQueue
void deleteMiddleToLLQueue(Node*& head, LLQueue<int>& out) {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    Node* slow = head;
    Node* fast = head->next->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* mid = slow->next;
    slow->next = mid->next;
    delete mid;
    for (Node* p = head; p != nullptr; p = p->next) out.enqueue(p->data);
}
// @end deleteMiddleToLLQueue
