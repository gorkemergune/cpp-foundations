// Linked list structure (same as the lab: Node{item, next} and head).
// The functions you write live in: problems/linkedlist.cpp
#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "../framework/test.h"

struct Node {
    int item;
    Node* next;

    // Use it as new Node{v, nullptr} or new Node(v).
    Node(int item = 0, Node* next = nullptr) : item(item), next(next) {
        if (++alive > 1000000)
            throw std::runtime_error("more than 1 million nodes allocated: you may be calling new inside an infinite loop");
    }
    ~Node() { --alive; }

    // For tests: how many nodes are alive right now. Tests catch a forgotten delete.
    static inline int alive = 0;
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}
    LinkedList(std::initializer_list<int> vals) : LinkedList(std::vector<int>(vals)) {}
    explicit LinkedList(const std::vector<int>& vals) : head(nullptr) {
        Node* tail = nullptr;
        for (int v : vals) {
            Node* n = new Node(v);
            if (tail == nullptr) head = n;
            else tail->next = n;
            tail = n;
        }
    }
    ~LinkedList() {
        if (hasCycle()) return;  // don't crash trying to free a broken list
        while (head != nullptr) {
            Node* d = head;
            head = head->next;
            delete d;
        }
    }
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // For debugging: l.print();  →  3 -> 8 -> 1 -> null
    void print() const {
        int guard = 0;
        for (Node* p = head; p != nullptr && guard < 50; p = p->next, guard++)
            std::cout << p->item << " -> ";
        std::cout << (guard == 50 ? "..." : "null") << std::endl;
    }

    // ---------------- problems (problems/linkedlist.cpp) ----------------
    int count() const;                               // LL-1
    int countValue(int v) const;                     // LL-2
    int indexOfMax() const;                          // LL-3
    void insertAtEnd(int v);                         // LL-4
    bool removeFirst(int v);                         // LL-5
    void reverse();                                  // LL-6
    void insertSorted(int v);                        // LL-7
    int insertAfterEach(int target, int value);      // LL-8
    int removeDuplicates();                          // LL-9
    void swapPairs();                                // LL-10

    // ---------------- test helpers ----------------
    std::vector<Node*> nodes() const {
        std::vector<Node*> r;
        for (Node* p = head; p != nullptr; p = p->next) {
            r.push_back(p);
            if (r.size() > 100000)
                throw std::runtime_error("list never ends: the next pointers form a cycle (a link was set up wrong)");
        }
        return r;
    }
    std::vector<int> toVector() const {
        std::vector<int> r;
        for (Node* p : nodes()) r.push_back(p->item);
        return r;
    }

private:
    bool hasCycle() const {
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
