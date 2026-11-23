// ============================================================================
//  Lab 37 · Binary search trees · YOU WORK HERE
//  Test everything:      .\run.ps1 L37
// ============================================================================
#include "lab37.h"

#include <climits>

#include "todo.h"

using namespace std;

// L37-A · Example: insert 50, 30, 70  =>  50(30,70)
void insert(Node*& root, int key) {
    TODO();
}

// L37-B · Example: 50(30,70), key 70  =>  the node 70;  key 65  =>  nullptr
Node* search(Node* root, int key) {
    TODO();
}

// L37-M1 · Example: 50(30(20,40),70(60,80))  =>  min 20, max 80
int minKey(const Node* root) {
    TODO();
}

int maxKey(const Node* root) {
    TODO();
}

// L37-M2 · Example: [10,5,15,null,null,6,20]  =>  false (6 is in the right subtree of 10)
bool inRange(const Node* p, long long lo, long long hi) {   // lo <= key < hi
    if (p == nullptr) return true;
    if (p->data < lo || p->data >= hi) return false;
    return inRange(p->left, lo, p->data) && inRange(p->right, p->data, hi);
}
// @end inRange

// @begin isBST
bool isBST(const Node* root) {
    TODO();
}

// L37-M3 · Example: {5, 1, 4, 1}  =>  {1, 1, 4, 5}
void readAndFree(Node* p, vector<int>& out) {
    TODO();
}

vector<int> treeSort(const vector<int>& values) {
    TODO();
}

// L37-M4 · Example: insert 5, 5, 3, 5  =>  "5(3,5(,5))"
string shape(const Node* root) {
    TODO();
}

// L37-X · Example: {-10, -3, 0, 5, 9}  =>  [0,-10,5,null,-3,null,9]
Node* build(const vector<int>& a, int lo, int hi) {
    TODO();
}

Node* sortedArrayToBST(const vector<int>& sorted) {
    TODO();
}

// L37-V · Example: 50(30(20,40),70(60,80))  =>  100
int minPlusMax(const Node* root) {
    TODO();
}
