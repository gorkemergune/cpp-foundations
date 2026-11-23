#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void insertSorted(Node*& head, int value) {
    Node* newNode = new Node{value, nullptr};

    // Case 1: empty list, or the new value goes before the head
    if (head == nullptr || value <= head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Case 2: find the last node whose value is smaller than the new value
    Node* current = head;
    while (current->next != nullptr && current->next->data < value) {
        current = current->next;
    }
    newNode->next = current->next;
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

    insertSorted(head, 30);   // into an empty list
    insertSorted(head, 10);   // at the beginning
    insertSorted(head, 50);   // at the end
    insertSorted(head, 20);   // in the middle
    insertSorted(head, 40);   // in the middle

    cout << "Sorted list: ";
    printList(head);          // 10 20 30 40 50

    freeList(head);
    return 0;
}
