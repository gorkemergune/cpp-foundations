#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

void printOddPosElements(Node* head) {
    int position = 1;
    Node* current = head;
    while (current != nullptr) {
        if (position % 2 == 1) {
            cout << current->data << " ";
        }
        current = current->next;
        position++;
    }
    cout << endl;
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
    for (int i = 10; i <= 70; i += 10) {
        pushBack(head, i);
    }

    // List: 10 20 30 40 50 60 70
    cout << "Odd positions: ";
    printOddPosElements(head);   // 10 30 50 70

    freeList(head);
    return 0;
}
