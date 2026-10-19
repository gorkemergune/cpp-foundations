#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// A circular list's last node points back to the head.
// Start after the head and walk forward:
//   - if we reach nullptr, the list has an end -> not circular
//   - if we come back to head, the list is circular
bool isCircular(Node* head) {
    if (head == nullptr) {
        return false;
    }
    Node* current = head->next;
    while (current != nullptr && current != head) {
        current = current->next;
    }
    return current == head;
}

int main() {
    // Build 1 -> 2 -> 3 -> 4
    Node* n1 = new Node{1, nullptr};
    Node* n2 = new Node{2, nullptr};
    Node* n3 = new Node{3, nullptr};
    Node* n4 = new Node{4, nullptr};
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;

    cout << boolalpha;
    cout << "1 -> 2 -> 3 -> 4 -> null : circular? " << isCircular(n1) << endl;  // false

    n4->next = n1;   // make the last node point back to the head
    cout << "1 -> 2 -> 3 -> 4 -> 1    : circular? " << isCircular(n1) << endl;  // true

    delete n1;
    delete n2;
    delete n3;
    delete n4;
    return 0;
}
