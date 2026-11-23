// ============================================================================
//  Challenge Set 07 · queues and deques · YOU WORK HERE
//  Test:  .\run.ps1 C07        one problem:  .\run.ps1 C07 C07-C
// ============================================================================
#include "challenge07.h"

#include <deque>
#include <queue>

#include "todo.h"

using namespace std;

// C07-A · Example: "RDD"  =>  "Dire"
string predictPartyVictory(const string& senate) {
    TODO();
}

// C07-B · Example: k = 3: insertLast 1, insertLast 2, insertFront 3, insertFront 4 (false), getRear 2
MyCircularDeque::MyCircularDeque(int k) {
    TODO();
}

bool MyCircularDeque::insertFront(int value) {
    TODO();
}

bool MyCircularDeque::insertLast(int value) {
    TODO();
}

bool MyCircularDeque::deleteFront() {
    TODO();
}

bool MyCircularDeque::deleteLast() {
    TODO();
}

int MyCircularDeque::getFront() const {
    TODO();
}

int MyCircularDeque::getRear() const {
    TODO();
}

bool MyCircularDeque::isEmpty() const {
    TODO();
}

bool MyCircularDeque::isFull() const {
    TODO();
}

// C07-C · Example: {1,3,-1,-3,5,3,6,7}, k = 3  =>  {3,3,5,5,6,7}
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    TODO();
}
