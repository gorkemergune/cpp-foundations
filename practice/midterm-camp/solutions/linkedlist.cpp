// ============================================================================
//  LINKED LIST · LL-1 … LL-10 · reference solutions
//  Run the tests against this file:  .\run.ps1 -Solution ll
// ============================================================================
#include "../ds/LinkedList.h"

int LinkedList::count() const {
    int n = 0;
    for (Node* p = head; p != nullptr; p = p->next) n++;
    return n;
}

int LinkedList::countValue(int v) const {
    int n = 0;
    for (Node* p = head; p != nullptr; p = p->next)
        if (p->item == v) n++;
    return n;
}

int LinkedList::indexOfMax() const {
    if (head == nullptr) return -1;
    int best = 0, i = 0;
    int bestValue = head->item;
    for (Node* p = head; p != nullptr; p = p->next, i++)
        if (p->item > bestValue) {          // strict >: keeps the FIRST maximum
            bestValue = p->item;
            best = i;
        }
    return best;
}

void LinkedList::insertAtEnd(int v) {
    Node* n = new Node(v);
    if (head == nullptr) {
        head = n;
        return;
    }
    Node* p = head;
    while (p->next != nullptr) p = p->next;
    p->next = n;
}

bool LinkedList::removeFirst(int v) {
    Node** link = &head;                    // the pointer that points to the current node
    while (*link != nullptr && (*link)->item != v) link = &(*link)->next;
    if (*link == nullptr) return false;
    Node* dead = *link;
    *link = dead->next;                     // works for the head too
    delete dead;
    return true;
}

void LinkedList::reverse() {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur != nullptr) {
        Node* next = cur->next;             // save before overwriting
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}

void LinkedList::insertSorted(int v) {
    Node** link = &head;
    while (*link != nullptr && (*link)->item < v) link = &(*link)->next;
    *link = new Node(v, *link);
}

int LinkedList::insertAfterEach(int target, int value) {
    int added = 0;
    for (Node* p = head; p != nullptr; p = p->next) {
        if (p->item == target) {
            p->next = new Node(value, p->next);
            p = p->next;                    // skip the new node (target == value trap)
            added++;
        }
    }
    return added;
}

int LinkedList::removeDuplicates() {
    int removed = 0;
    for (Node* p = head; p != nullptr; p = p->next) {
        Node* q = p;                        // q->next is the candidate
        while (q->next != nullptr) {
            if (q->next->item == p->item) {
                Node* dead = q->next;
                q->next = dead->next;
                delete dead;
                removed++;
            } else {
                q = q->next;
            }
        }
    }
    return removed;
}

void LinkedList::swapPairs() {
    Node** link = &head;
    while (*link != nullptr && (*link)->next != nullptr) {
        Node* a = *link;
        Node* b = a->next;
        a->next = b->next;                  // a -> rest
        b->next = a;                        // b -> a
        *link = b;                          // previous -> b
        link = &a->next;                    // next pair starts after a
    }
}
