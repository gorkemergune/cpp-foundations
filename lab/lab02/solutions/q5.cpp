#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Walk through the list and turn each arrow around.
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;   // remember the rest of the list
        current->next = prev;             // reverse the arrow
        prev = current;                   // move prev one step forward
        current = nextNode;               // move current one step forward
    }
    return prev;                          // prev is the new head
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

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    for (int i = 1; i <= 5; i++) {
        pushBack(head, i);
    }

    cout << "Original: ";
    printList(head);          // 1 2 3 4 5

    head = reverseList(head);

    cout << "Reversed: ";
    printList(head);          // 5 4 3 2 1

    freeList(head);
    return 0;
}
