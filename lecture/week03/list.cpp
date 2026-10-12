// elimde sıralı bir link list var, biz bi değer veriyoruz eğer verdiğimiz değer varsa onu siliyoruz yoksa listeye sırasına göre ekliyoruz.

// find function yazılcak, returns a pointer to the index-th node in the linked list

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

    

}