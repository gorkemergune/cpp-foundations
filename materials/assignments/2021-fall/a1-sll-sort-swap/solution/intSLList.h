// Assignment 1 (2021) · reference solution header
//************************  intSLList.h  **************************
//           singly-linked list class to store integers

#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class IntSLLNode {
public:
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(int el, IntSLLNode *ptr = 0) {
        info = el; next = ptr;
    }
    int info;
    IntSLLNode *next;
};

class IntSLList {
public:
    IntSLList() {
        head = tail = 0;
    }
    ~IntSLList();
    // Added by the solution (rule of three): sort_list() returns a list BY VALUE and
    // main does `list2 = list.sort_list();`. Without these two, both objects would share
    // the same nodes and the destructor would delete them twice.
    IntSLList(const IntSLList& other);
    IntSLList& operator=(const IntSLList& other);
    int isEmpty() {
        return head == 0;
    }
    void addToHead(int);
    void addToTail(int);
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    void printAll() const;
    IntSLList  sort_list();
    void swap_nodes(int);
    int find_min();
private:
    IntSLLNode *head, *tail;
};

#endif
