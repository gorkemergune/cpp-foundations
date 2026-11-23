// Lab 13 · Alternative shown in the PDF. Standalone program.
#include <cassert>
#include <iostream>

#include "lab13.h"

// @begin rec
int countNodesRec(const Node* head) {
    return head == nullptr ? 0 : 1 + countNodesRec(head->next);
}
// @end rec

int main() {
    Node* h = new Node(1, new Node(2, new Node(3)));
    assert(countNodesRec(h) == 3 && countNodesRec(nullptr) == 0);
    while (h) {
        Node* n = h->next;
        delete h;
        h = n;
    }
    assert(Node::alive == 0);
    std::cout << "alternatives OK\n";
    return 0;
}
