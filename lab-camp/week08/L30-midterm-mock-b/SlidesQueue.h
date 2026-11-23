// ============================================================================
//  The pointer-based Queue of the course slides (10-queues.ppt, slides 15-22) and
//  of the lecture code (materials/lecture-code/week05/queue.cpp).   DO NOT EDIT
//  QueueItemType is int here. Every operation returns bool: false = "could not".
// ============================================================================
#pragma once

#include <cstddef>

typedef int QueueItemType;

class Queue {
public:
    Queue() : backPtr(NULL), frontPtr(NULL) {}
    Queue(const Queue& Q) : backPtr(NULL), frontPtr(NULL) {   // deep copy, same order
        for (QueueNode* cur = Q.frontPtr; cur != NULL; cur = cur->next) enqueue(cur->item);
    }
    Queue& operator=(const Queue&) = delete;
    ~Queue() {
        while (!isEmpty()) dequeue();
    }

    bool isEmpty() const { return backPtr == NULL; }

    bool enqueue(QueueItemType newItem) {             // insert at the back
        QueueNode* newPtr = new QueueNode;
        newPtr->item = newItem;
        newPtr->next = NULL;
        if (isEmpty()) frontPtr = newPtr;
        else backPtr->next = newPtr;
        backPtr = newPtr;
        return true;
    }
    bool dequeue() {                                  // remove the front; false when empty
        if (isEmpty()) return false;
        QueueNode* tempPtr = frontPtr;
        if (frontPtr == backPtr) frontPtr = backPtr = NULL;
        else frontPtr = frontPtr->next;
        delete tempPtr;
        return true;
    }
    bool dequeue(QueueItemType& queueFront) {         // copy the front out, then remove it
        if (isEmpty()) return false;
        queueFront = frontPtr->item;
        return dequeue();
    }
    bool getFront(QueueItemType& queueFront) const {  // copy the front, do not remove it
        if (isEmpty()) return false;
        queueFront = frontPtr->item;
        return true;
    }

private:
    struct QueueNode {
        QueueItemType item;
        QueueNode* next;
    };
    QueueNode* backPtr;
    QueueNode* frontPtr;
};
