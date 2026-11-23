// ============================================================================
//  Lab 19 · Circular list with last · YOU WORK HERE
//  Test everything:      .\run.ps1 L19
//  A circle has no nullptr at the end: stop when you come back to where you started.
// ============================================================================
#include "lab19.h"

#include "todo.h"

using namespace std;

// L19-A · Example: last = 3 (circle 1 2 3), insertAtEnd(last, 4)  =>  circle 1 2 3 4, last = 4
void insertAtEnd(Node*& last, int v) {
    TODO();
}

// L19-B · Example: circle 1 2 3 with last = 3  =>  {1, 2, 3}
vector<int> toVector(const Node* last) {
    TODO();
}

// L19-M1 · Example: circle 1 2 3 4 (last = 4)  =>  true, circle 1 2 3, last = 3
bool deleteLast(Node*& last) {
    TODO();
}

// L19-M2 · Example: circle 1 2 3 (last = 3)  =>  true, circle 2 3, last still 3
bool deleteFirst(Node*& last) {
    TODO();
}

// L19-X · Example: circle 1 2 3, deleteValue(last, 3)  =>  true, circle 1 2, last = 2
bool deleteValue(Node*& last, int v) {
    TODO();
}

// L19-V · Example: circle 1 2 3  =>  3
int countNodes(const Node* last) {
    TODO();
}
