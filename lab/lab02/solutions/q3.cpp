#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// slow moves 1 step, fast moves 2 steps.
// When fast reaches the end, slow is in the middle.
// For an even number of nodes, this returns the second middle node.
Node* findMiddle(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void pushBack(Node*& head, int value) {
    Node* newNode = new Node{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* odd = nullptr;
    for (int i = 1; i <= 5; i++) {
        pushBack(odd, i);
    }
    cout << "Middle of 1 2 3 4 5: " << findMiddle(odd)->data << endl;     // 3

    Node* even = nullptr;
    for (int i = 1; i <= 6; i++) {
        pushBack(even, i);
    }
    cout << "Middle of 1 2 3 4 5 6: " << findMiddle(even)->data << endl;  // 4

    freeList(odd);
    freeList(even);
    return 0;
}
