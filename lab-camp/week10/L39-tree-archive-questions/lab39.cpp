// ============================================================================
//  Lab 39 · Tree questions from the archive · YOU WORK HERE
//  Test everything:      .\run.ps1 L39
// ============================================================================
#include "lab39.h"

#include "todo.h"

using namespace std;

// L39-A · Example: BST of 1..9, n = 7  =>  true, out = 7
const Node* nthFrom(const Node* p, int& remaining) {
    TODO();
}

bool nthSmallest(const Node* root, int n, int& out) {
    TODO();
}

// L39-B · Example: BST of 1..9, x = 4  =>  {1, 2, 3}
void smallerInto(const Node* p, int x, vector<int>& out) {
    TODO();
}

vector<int> smallerThan(const Node* root, int x) {
    TODO();
}

// L39-M1 · Example: [1,null,2,null,3]  =>  false
int checkedHeight(const Node* p) {          // height, or -1 if some subtree is unbalanced
    if (p == nullptr) return 0;
    int l = checkedHeight(p->left);
    if (l < 0) return -1;
    int r = checkedHeight(p->right);
    if (r < 0) return -1;
    if (l - r > 1 || r - l > 1) return -1;
    return 1 + (l > r ? l : r);
}
// @end checkedHeight

// @begin isBalanced
bool isBalanced(const Node* root) {
    TODO();
}

// L39-M2 · Example: [1,2,3,4,null,null,5,6]  =>  {4, 6, 5}
void onlyInto(const Node* p, vector<int>& out) {
    TODO();
}

vector<int> onlyChildren(const Node* root) {
    TODO();
}

// L39-M3 · Example: pre {3,9,20,15,7}, in {9,3,15,20,7}  =>  [3,9,20,null,null,15,7]
Node* buildRange(const vector<int>& pre, int& next, const vector<int>& in, int lo, int hi) {
    TODO();
}

Node* buildFromPreIn(const vector<int>& pre, const vector<int>& in) {
    TODO();
}

// L39-X · Example: [1,null,2,null,3,null,4]  =>  [2,1,3,null,null,null,4]
void collect(Node* p, vector<int>& keys) {  // inorder, freeing as we go
    if (p == nullptr) return;
    collect(p->left, keys);
    keys.push_back(p->data);
    collect(p->right, keys);
    delete p;
}
// @end collect

// @begin fromSorted
Node* fromSorted(const vector<int>& a, int lo, int hi) {
    TODO();
}

Node* balanceBST(Node* root) {
    TODO();
}

// L39-V · Example: BST of 1..9, [3, 6]  =>  4
int countInRange(const Node* root, int lo, int hi) {
    TODO();
}
