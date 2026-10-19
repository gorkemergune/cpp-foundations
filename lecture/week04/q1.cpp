#include "iostream"
using namespace std;


const int MAX_STACK = 100;


class Stack {
public:
    Stack();

    bool isEmpty();
    bool push(char c);
    bool pop();
    bool getTop(char &c);

private:
    struct StackNode {
        char data;
        StackNode *next;
    };

    StackNode *top;

};


bool Stack::push(char c) {
    StackNode *newNode = new StackNode;
    if (!newNode) {
        return false; // memory allocation failed
    }
    newNode->data = c;
    newNode->next = top;
    top = newNode;
    return true;
}


bool Stack::pop() {
    if (isEmpty()) {
        return false; // stack is empty
    }
    StackNode *temp = top;
    top = top->next;
    delete temp;
    return true;
}


bool Stack::isEmpty() {
    return top == nullptr;
}

int main() {

}