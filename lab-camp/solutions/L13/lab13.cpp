// ============================================================================
//  Lab 13 · Nodes and arrows · YOU WORK HERE (after the paper trace!)
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L13
//  The tests count live nodes: every new needs exactly one delete.
// ============================================================================
#include "lab13.h"

#include "todo.h"

using namespace std;

// L13-A · Example: {3, 1, 2}  =>  3 -> 1 -> 2 -> nullptr
// @begin makeList
Node* makeList(const vector<int>& values) {
    Node* head = nullptr;
    Node* tail = nullptr;                    // last node so far: appending is O(1)
    for (int v : values) {
        Node* n = new Node(v);
        if (head == nullptr) head = n;       // the first node is also the head
        else tail->next = n;                 // link the old last node to the new one
        tail = n;
    }
    return head;
}
// @end makeList

// L13-B · Example: 3 -> 1 -> 2  =>  {3, 1, 2}
// @begin toVector
vector<int> toVector(const Node* head) {
    vector<int> out;
    for (const Node* p = head; p != nullptr; p = p->next) out.push_back(p->value);
    return out;
}
// @end toVector

// L13-M1 · After the call head == nullptr and Node::alive went down by the list length.
// @begin freeList
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* next = head->next;    // read next BEFORE the node is deleted
        delete head;
        head = next;
    }                               // the loop ends with head == nullptr
}
// @end freeList

// L13-M2 · Example: 3 -> 1 -> 2  =>  3
// @begin countNodes
int countNodes(const Node* head) {
    int n = 0;
    while (head != nullptr) {       // head is our own copy of the pointer
        n++;
        head = head->next;
    }
    return n;
}
// @end countNodes

// L13-X · Example: 1 -> 0 -> 1  =>  5
// @begin getDecimalValue
int getDecimalValue(const Node* head) {
    int x = 0;
    for (const Node* p = head; p != nullptr; p = p->next) x = x * 2 + p->value;
    return x;
}
// @end getDecimalValue

// L13-V · Example: copy of 3 -> 1  =>  a new 3 -> 1 (different nodes)
// @begin copyList
Node* copyList(const Node* head) {
    Node* first = nullptr;
    Node* last = nullptr;
    for (const Node* p = head; p != nullptr; p = p->next) {
        Node* n = new Node(p->value);
        if (first == nullptr) first = n;
        else last->next = n;
        last = n;
    }
    return first;
}
// @end copyList
