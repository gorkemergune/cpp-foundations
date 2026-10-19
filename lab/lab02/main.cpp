#include "iostream"


struct Node {
    int val;
    Node* next;
};


void printOddPodElements(Node* head) {

    while (head != NULL && head->next != NULL) {
        std::cout << head->val << " ";
        head = head->next->next;
    }
}


int lengIterative(Node* head) {
    int len = 0;
    while (head != NULL)  {
        len++;
        head = head->next;
    }
    return len;
}


int lenRecursive(Node* head) {
    if (head == NULL) {
        return 0;
    }
    return 1 + lenRecursive(head->next);
}


Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}


void insertSorted(Node* &head, int value) {

    Node* newNode = new Node();
    newNode->val = value;
    newNode->next = NULL;

    // Liste boşsa veya yeni değer en küçükse
    if (head == NULL || value <= head->val) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
        if (temp->val <= value && value <= temp->next->val) {
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }

        temp = temp->next;
    }

    // En sona ekleme
    temp->next = newNode;
}


Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next; // Sonraki düğümü sakla
        current->next = prev; // Bağlantıyı tersine çevir
        prev = current;       // Prev'i ilerlet
        current = next;       // Current'i ilerlet
    }

    return prev; // Yeni baş düğüm
}


Node* RecursiveReverseList(Node* head) {
    if (head == NULL ) return NULL;
    
    Node* newHead = head;
    if (head->next != NULL) {
        newHead = RecursiveReverseList(head->next);
        head->next->next = head;
    }
    head->next = NULL;

    return newHead;
}


bool isCircular(Node* head) {

    if (head == NULL)  return false;


    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {

        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) return true;
    }
}


int main() {

    // 1 2 1 3

    Node *head = new Node();
    head->val = 1;
    head->next = new Node();
    head->next->val = 2;
    head->next->next = new Node();
    head->next->next->val = 1;
    head->next->next->next = new Node();
    head->next->next->next->val = 3;
    head->next->next->next->next = NULL;




    return 0;
}