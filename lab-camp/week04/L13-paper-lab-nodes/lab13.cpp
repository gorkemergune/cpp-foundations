// ============================================================================
//  Lab 13 · Nodes and arrows · YOU WORK HERE (after the paper trace!)
//  Test everything:      .\run.ps1 L13
//  The tests count live nodes: every new needs exactly one delete.
// ============================================================================
#include "lab13.h"

#include "todo.h"

using namespace std;

// L13-A · Example: {3, 1, 2}  =>  3 -> 1 -> 2 -> nullptr
Node* makeList(const vector<int>& values) {
    TODO();
}

// L13-B · Example: 3 -> 1 -> 2  =>  {3, 1, 2}
vector<int> toVector(const Node* head) {
    TODO();
}

// L13-M1 · After the call head == nullptr and Node::alive went down by the list length.
void freeList(Node*& head) {
    TODO();
}

// L13-M2 · Example: 3 -> 1 -> 2  =>  3
int countNodes(const Node* head) {
    TODO();
}

// L13-X · Example: 1 -> 0 -> 1  =>  5
int getDecimalValue(const Node* head) {
    TODO();
}

// L13-V · Example: copy of 3 -> 1  =>  a new 3 -> 1 (different nodes)
Node* copyList(const Node* head) {
    TODO();
}
