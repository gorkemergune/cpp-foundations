#include "iostream"

struct Node {
    int data;
    Node* next;
};


int main() {

    Node* head = NULL;
    Node* tail = NULL;

    // Create a linked list with 5 nodes
    for (int i = 1; i <= 5; ++i) {
        Node* newNode = new Node();
        newNode->data = i;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Print the linked list
    Node* current = head;
    while (current != NULL) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;

    // Free the allocated memory
    current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }



    for (Node *cur = head; cur != NULL; cur = cur->next) {
        std::cout << cur->data << " ";
    }

    // deleting an interior node
    prev -> next = cur -> next;

    // deleting the first node
    head = head -> next;

    // return deleted note to system
    cur -> next = NULL;
    delete cur;
    cur = NULL;
    

    // to insert a node between two nodes
    newPrev -> next = cur;
    prev -> next = newPrev;

    return 0;




} 