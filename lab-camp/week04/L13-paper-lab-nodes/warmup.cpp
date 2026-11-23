// Lab 13 · THE PAPER TRACE. Draw boxes and arrows for every numbered line BEFORE
// you compile. Then compile and compare:  g++ -std=c++17 -Wall warmup.cpp -o warmup.exe
#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
    Node(int v, Node* n = nullptr) : value(v), next(n) {}
};

static void show(const char* step, const Node* head) {
    cout << step << " ";
    for (const Node* p = head; p != nullptr; p = p->next) cout << p->value << " -> ";
    cout << "null\n";
}

int main() {
    Node* head = nullptr;                    // 1
    show("1)", head);
    head = new Node(3);                      // 2
    show("2)", head);
    head = new Node(1, head);                // 3  the new node points at the old head
    show("3)", head);
    head->next = new Node(2, head->next);    // 4  insert after the first node
    show("4)", head);
    Node* p = head->next;                    // 5  p names the 2
    head->next = p->next;                    // 6  bypass the 2
    show("6)", head);
    cout << "   p->value is still " << p->value << " (the node exists, nobody links to it)\n";
    delete p;                                // 7  now it is gone; p must not be used
    p = nullptr;
    Node* q = head;                          // 8  walk to the last node
    while (q->next != nullptr) q = q->next;
    q->next = new Node(4);                   // 9  append
    show("9)", head);
    while (head != nullptr) {                // 10 free everything
        Node* next = head->next;
        delete head;
        head = next;
    }
    show("10)", head);
    return 0;
}
