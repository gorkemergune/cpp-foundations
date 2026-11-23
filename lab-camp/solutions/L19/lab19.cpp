// ============================================================================
//  Lab 19 · Circular list with last · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L19
//  A circle has no nullptr at the end: stop when you come back to where you started.
// ============================================================================
#include "lab19.h"

#include "todo.h"

using namespace std;

// L19-A · Example: last = 3 (circle 1 2 3), insertAtEnd(last, 4)  =>  circle 1 2 3 4, last = 4
// @begin insertAtEnd
void insertAtEnd(Node*& last, int v) {
    Node* n = new Node(v);
    if (last == nullptr) {
        n->next = n;                   // a circle of one node points to itself
    } else {
        n->next = last->next;          // the new node points to the first
        last->next = n;                // the old last points to the new node
    }
    last = n;
}
// @end insertAtEnd

// L19-B · Example: circle 1 2 3 with last = 3  =>  {1, 2, 3}
// @begin toVector
vector<int> toVector(const Node* last) {
    vector<int> out;
    if (last == nullptr) return out;
    const Node* p = last->next;        // the first node
    do {
        out.push_back(p->data);
        p = p->next;
    } while (p != last->next);         // back at the first node: one full round
    return out;
}
// @end toVector

// L19-M1 · Example: circle 1 2 3 4 (last = 4)  =>  true, circle 1 2 3, last = 3
// @begin deleteLast
bool deleteLast(Node*& last) {
    if (last == nullptr) return false;
    if (last->next == last) {          // only one node
        delete last;
        last = nullptr;
        return true;
    }
    Node* prev = last->next;           // walk to the node BEFORE last
    while (prev->next != last) prev = prev->next;
    prev->next = last->next;           // close the circle around last
    delete last;
    last = prev;                       // the caller's last moves back
    return true;
}
// @end deleteLast

// L19-M2 · Example: circle 1 2 3 (last = 3)  =>  true, circle 2 3, last still 3
// @begin deleteFirst
bool deleteFirst(Node*& last) {
    if (last == nullptr) return false;
    Node* first = last->next;
    if (first == last) last = nullptr; // only one node
    else last->next = first->next;     // O(1): last already is the predecessor of first
    delete first;
    return true;
}
// @end deleteFirst

// L19-X · Example: circle 1 2 3, deleteValue(last, 3)  =>  true, circle 1 2, last = 2
// @begin deleteValue
bool deleteValue(Node*& last, int v) {
    if (last == nullptr) return false;
    Node* prev = last;                 // the predecessor of the first node is last
    do {
        Node* cur = prev->next;
        if (cur->data == v) {
            if (cur == prev) last = nullptr;          // it was the only node
            else {
                prev->next = cur->next;
                if (cur == last) last = prev;         // deleting last moves last back
            }
            delete cur;
            return true;
        }
        prev = cur;
    } while (prev != last);
    return false;
}
// @end deleteValue

// L19-V · Example: circle 1 2 3  =>  3
// @begin countNodes
int countNodes(const Node* last) {
    if (last == nullptr) return 0;
    int n = 1;
    for (const Node* p = last->next; p != last; p = p->next) n++;
    return n;
}
// @end countNodes
