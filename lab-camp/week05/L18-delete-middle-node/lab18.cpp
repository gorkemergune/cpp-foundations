// ============================================================================
//  Lab 18 · Delete the middle node · YOU WORK HERE
//  Test everything:      .\run.ps1 L18
//  B, M, X, V: one pass with slow/fast pointers; no length() inside them.
// ============================================================================
#include "lab18.h"

#include "todo.h"

// L18-A · Example: 1 -> 2 -> 3  =>  3
int length(const Node* head) {
    TODO();
}

// L18-B · Example: 1 -> 2 -> 3 -> 4 -> 5 (middle = 3)  =>  the node holding 2
Node* beforeMiddle(Node* head) {
    TODO();
}

// L18-M · Example: 1 -> 3 -> 4 -> 7 -> 1 -> 2 -> 6  =>  true, 1 -> 3 -> 4 -> 1 -> 2 -> 6
bool deleteMiddle(Node*& head) {
    TODO();
}

// L18-X · Example: deleteMiddleLC(1 -> 2) returns 1 (the 2 was deleted)
Node* deleteMiddleLC(Node* head) {
    TODO();
}

// L18-V · Example: 1 -> 2 -> 3 -> 4  =>  true, 1 -> 3 -> 4   (the 2 is the first middle)
bool deleteLeftMiddle(Node*& head) {
    TODO();
}
