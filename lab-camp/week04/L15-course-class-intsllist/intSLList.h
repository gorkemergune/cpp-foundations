//************************  intSLList.h  **************************
//  The course's singly-linked list of ints (Labwork 1 / Assignments 1, 5).
//  DO NOT EDIT. Two additions for the tests are marked "lab camp".
#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

#include <iostream>
#include <vector>

class IntSLLNode {
public:
    IntSLLNode() { next = 0; alive++; }
    IntSLLNode(int el, IntSLLNode* ptr = 0) { info = el; next = ptr; alive++; }
    ~IntSLLNode() { alive--; }
    int info;
    IntSLLNode* next;
    static inline int alive = 0;   // lab camp: live nodes, for leak checks
};

class IntSLList {
public:
    IntSLList() { head = tail = 0; }
    ~IntSLList();                       // L15-M2 · delete every node
    int isEmpty() { return head == 0; } // note: int, not bool, in the course file
    void addToHead(int);                // L15-A
    void addToTail(int);                // L15-A
    int deleteFromHead();               // L15-B · delete the head and return its info
    int deleteFromTail();               // L15-B · delete the tail and return its info
    void deleteNode(int);               // L15-M1 · delete the first node holding el
    bool isInList(int) const;           // L15-M1
    void printAll() const {             // given
        for (IntSLLNode* p = head; p != 0; p = p->next) std::cout << p->info << " ";
        std::cout << std::endl;
    }
    int removeAll(int);                 // L15-X · delete every node holding el, return count
    void insertSorted(int);             // L15-V · keep an ascending list ascending

    // lab camp: test helpers (read only)
    std::vector<int> toVector() const {
        std::vector<int> r;
        for (IntSLLNode* p = head; p != 0 && r.size() < 100000; p = p->next) r.push_back(p->info);
        return r;
    }
    bool tailOk() const {               // tail is the last node, or both are 0
        if (head == 0) return tail == 0;
        IntSLLNode* p = head;
        while (p->next != 0) p = p->next;
        return p == tail;
    }

private:
    IntSLLNode *head, *tail;
};

#endif
