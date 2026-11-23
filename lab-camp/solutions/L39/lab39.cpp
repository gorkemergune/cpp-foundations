// ============================================================================
//  Lab 39 · Tree questions from the archive · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L39
// ============================================================================
#include "lab39.h"

#include "todo.h"

using namespace std;

// L39-A · Example: BST of 1..9, n = 7  =>  true, out = 7
// @begin nthFrom
const Node* nthFrom(const Node* p, int& remaining) {
    if (p == nullptr) return nullptr;
    if (const Node* found = nthFrom(p->left, remaining)) return found;
    if (--remaining == 0) return p;         // inorder: this is the next smallest key
    return nthFrom(p->right, remaining);
}
// @end nthFrom

// @begin nthSmallest
bool nthSmallest(const Node* root, int n, int& out) {
    if (n < 1) return false;
    int remaining = n;
    const Node* found = nthFrom(root, remaining);
    if (found == nullptr) return false;     // fewer than n keys
    out = found->data;
    return true;
}
// @end nthSmallest

// L39-B · Example: BST of 1..9, x = 4  =>  {1, 2, 3}
// @begin smallerInto
void smallerInto(const Node* p, int x, vector<int>& out) {
    if (p == nullptr) return;
    smallerInto(p->left, x, out);
    if (p->data >= x) return;               // p and its whole right subtree are >= x
    out.push_back(p->data);
    smallerInto(p->right, x, out);
}
// @end smallerInto

// @begin smallerThan
vector<int> smallerThan(const Node* root, int x) {
    vector<int> out;
    smallerInto(root, x, out);
    return out;
}
// @end smallerThan

// L39-M1 · Example: [1,null,2,null,3]  =>  false
// @begin checkedHeight
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
    return checkedHeight(root) >= 0;
}
// @end isBalanced

// L39-M2 · Example: [1,2,3,4,null,null,5,6]  =>  {4, 6, 5}
// @begin onlyInto
void onlyInto(const Node* p, vector<int>& out) {
    if (p == nullptr) return;
    if (p->left != nullptr && p->right == nullptr) out.push_back(p->left->data);
    if (p->right != nullptr && p->left == nullptr) out.push_back(p->right->data);
    onlyInto(p->left, out);
    onlyInto(p->right, out);
}
// @end onlyInto

// @begin onlyChildren
vector<int> onlyChildren(const Node* root) {
    vector<int> out;
    onlyInto(root, out);
    return out;
}
// @end onlyChildren

// L39-M3 · Example: pre {3,9,20,15,7}, in {9,3,15,20,7}  =>  [3,9,20,null,null,15,7]
// @begin buildRange
Node* buildRange(const vector<int>& pre, int& next, const vector<int>& in, int lo, int hi) {
    if (lo > hi) return nullptr;            // in[lo..hi] is this subtree's inorder
    int key = pre[next++];                  // preorder: the root comes first
    int mid = lo;
    while (in[mid] != key) mid++;           // left of it: left subtree; right: right subtree
    Node* left = buildRange(pre, next, in, lo, mid - 1);
    Node* right = buildRange(pre, next, in, mid + 1, hi);
    return new Node(key, left, right);
}
// @end buildRange

// @begin buildFromPreIn
Node* buildFromPreIn(const vector<int>& pre, const vector<int>& in) {
    int next = 0;
    return buildRange(pre, next, in, 0, (int)in.size() - 1);
}
// @end buildFromPreIn

// L39-X · Example: [1,null,2,null,3,null,4]  =>  [2,1,3,null,null,null,4]
// @begin collect
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
    if (lo > hi) return nullptr;
    int mid = (lo + hi) / 2;
    return new Node(a[mid], fromSorted(a, lo, mid - 1), fromSorted(a, mid + 1, hi));
}
// @end fromSorted

// @begin balanceBST
Node* balanceBST(Node* root) {
    vector<int> keys;
    collect(root, keys);
    return fromSorted(keys, 0, (int)keys.size() - 1);
}
// @end balanceBST

// L39-V · Example: BST of 1..9, [3, 6]  =>  4
// @begin countInRange
int countInRange(const Node* root, int lo, int hi) {
    if (root == nullptr) return 0;
    if (root->data < lo) return countInRange(root->right, lo, hi);   // left side is smaller still
    if (root->data > hi) return countInRange(root->left, lo, hi);
    return 1 + countInRange(root->left, lo, hi) + countInRange(root->right, lo, hi);
}
// @end countInRange
