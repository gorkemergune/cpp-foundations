// Lab 14 · Alternative shown in the PDF. Standalone program.
#include <cassert>
#include <iostream>

#include "lab14.h"

// @begin pp
bool removeAt2(Node*& head, int index) {
    Node** link = &head;                 // the arrow we may change
    for (int i = 0; i < index && *link; i++) link = &(*link)->next;
    if (index < 0 || *link == nullptr) return false;
    Node* dead = *link;
    *link = dead->next;                  // works for the head and for any other node
    delete dead;
    return true;
}
// @end pp

int main() {
    Node* h = new Node(1, new Node(2, new Node(3)));
    assert(removeAt2(h, 1) && h->data == 1 && h->next->data == 3);
    assert(removeAt2(h, 0) && h->data == 3);
    assert(!removeAt2(h, 1) && !removeAt2(h, -1));
    assert(removeAt2(h, 0) && h == nullptr && Node::alive == 0);
    std::cout << "alternatives OK\n";
    return 0;
}
