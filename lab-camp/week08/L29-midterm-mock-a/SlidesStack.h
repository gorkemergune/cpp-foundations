// ============================================================================
//  The array-based Stack of the course slides (09-stacks.ppt, slides 15-22).
//  DO NOT EDIT. StackItemType is int here; MAX_STACK is the fixed capacity.
//  Every operation returns bool: false means "could not do it".
// ============================================================================
#pragma once

typedef int StackItemType;
const int MAX_STACK = 50;

class Stack {
public:
    Stack() : top(-1) {}
    bool isEmpty() const { return top < 0; }
    bool push(StackItemType newItem) {           // false when full
        if (top >= MAX_STACK - 1) return false;
        items[++top] = newItem;
        return true;
    }
    bool pop() {                                 // removes the top; false when empty
        if (isEmpty()) return false;
        --top;
        return true;
    }
    bool pop(StackItemType& stackTop) {          // copies the top into stackTop, then removes it
        if (isEmpty()) return false;
        stackTop = items[top--];
        return true;
    }
    bool getTop(StackItemType& stackTop) const { // copies the top, does not remove it
        if (isEmpty()) return false;
        stackTop = items[top];
        return true;
    }

private:
    StackItemType items[MAX_STACK];
    int top;                                     // index of the top item, -1 when empty
};
