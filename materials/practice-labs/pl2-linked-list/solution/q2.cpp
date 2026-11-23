#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int lengthIterative(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

int lengthRecursive(Node* head) {
    if (head == nullptr) {
        return 0;
    }
    return 1 + lengthRecursive(head->next);
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
    Node* head = nullptr;
    cout << "Empty list -> iterative: " << lengthIterative(head)
         << ", recursive: " << lengthRecursive(head) << endl;   // 0, 0

    for (int i = 1; i <= 5; i++) {
        pushBack(head, i);
    }
    cout << "5 nodes    -> iterative: " << lengthIterative(head)
         << ", recursive: " << lengthRecursive(head) << endl;   // 5, 5

    freeList(head);
    return 0;
}
