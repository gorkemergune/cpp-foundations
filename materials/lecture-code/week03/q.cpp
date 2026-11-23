#include "iostream"
using namespace std;

struct Node {
    int data;
    Node *next;
};


int count (Node *head, int key) {
    int count = 0;
    while (head != NULL) {
        if (head->data == key) {
            count++;
        }
        head = head->next;
    }
    return count;
}

int sum(Node *head) {
    int sum = 0;
    while (head != NULL) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

void printMiddle(Node *head) { // tek döngüyle çözülecek

    int temp = 0;
    Node *slow = head;
    Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        temp++;
    }

    cout << "Middle element is: " << slow->data << endl;

}

int main() {

    Node *head = new Node();
    head->data = 1;
    head->next = new Node();
    head->next->data = 2;
    head->next->next = new Node();
    head->next->next->data = 1;
    head->next->next->next = new Node();
    head->next->next->next->data = 3;
    head->next->next->next->next = NULL;

    int key = 1;
    cout << "Count of " << key << " is " << count(head, key) << endl;
    cout << "Sum of " << sum(head) << endl;
    
    printMiddle(head);

    return 0;

}