// ============================================================================
//  Lab 37 · Binary search trees · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L37
// ============================================================================
#include "lab37.h"

#include <climits>

#include "todo.h"

using namespace std;

// L37-A · Example: insert 50, 30, 70  =>  50(30,70)
// @begin insert
void insert(Node*& root, int key) {
    Node** link = &root;                    // the pointer that will hold the new leaf
    while (*link != nullptr)
        link = (key < (*link)->data) ? &(*link)->left : &(*link)->right;
    *link = new Node(key);
}
// @end insert

// L37-B · Example: 50(30,70), key 70  =>  the node 70;  key 65  =>  nullptr
// @begin search
Node* search(Node* root, int key) {
    Node* p = root;
    while (p != nullptr && p->data != key)
        p = (key < p->data) ? p->left : p->right;   // one path down: O(h)
    return p;
}
// @end search

// L37-M1 · Example: 50(30(20,40),70(60,80))  =>  min 20, max 80
// @begin minKey
int minKey(const Node* root) {
    while (root->left != nullptr) root = root->left;     // keep going left
    return root->data;
}
// @end minKey

// @begin maxKey
int maxKey(const Node* root) {
    while (root->right != nullptr) root = root->right;   // keep going right
    return root->data;
}
// @end maxKey

// L37-M2 · Example: [10,5,15,null,null,6,20]  =>  false (6 is in the right subtree of 10)
// @begin inRange
bool inRange(const Node* p, long long lo, long long hi) {   // lo <= key < hi
    if (p == nullptr) return true;
    if (p->data < lo || p->data >= hi) return false;
    return inRange(p->left, lo, p->data) && inRange(p->right, p->data, hi);
}
// @end inRange

// @begin isBST
bool isBST(const Node* root) {
    return inRange(root, LLONG_MIN, LLONG_MAX);
}
// @end isBST

// L37-M3 · Example: {5, 1, 4, 1}  =>  {1, 1, 4, 5}
// @begin readAndFree
void readAndFree(Node* p, vector<int>& out) {
    if (p == nullptr) return;
    readAndFree(p->left, out);
    out.push_back(p->data);
    readAndFree(p->right, out);
    delete p;                               // both subtrees are done with p
}
// @end readAndFree

// @begin treeSort
vector<int> treeSort(const vector<int>& values) {
    Node* root = nullptr;
    for (int v : values) insert(root, v);
    vector<int> out;
    readAndFree(root, out);
    return out;
}
// @end treeSort

// L37-M4 · Example: insert 5, 5, 3, 5  =>  "5(3,5(,5))"
// @begin shape
string shape(const Node* root) {
    if (root == nullptr) return "";
    string s = to_string(root->data);
    if (root->left || root->right) s += "(" + shape(root->left) + "," + shape(root->right) + ")";
    return s;
}
// @end shape

// L37-X · Example: {-10, -3, 0, 5, 9}  =>  [0,-10,5,null,-3,null,9]
// @begin build
Node* build(const vector<int>& a, int lo, int hi) {
    if (lo > hi) return nullptr;
    int mid = (lo + hi) / 2;
    return new Node(a[mid], build(a, lo, mid - 1), build(a, mid + 1, hi));
}
// @end build

// @begin sortedArrayToBST
Node* sortedArrayToBST(const vector<int>& sorted) {
    return build(sorted, 0, (int)sorted.size() - 1);
}
// @end sortedArrayToBST

// L37-V · Example: 50(30(20,40),70(60,80))  =>  100
// @begin minPlusMax
int minPlusMax(const Node* root) {
    return minKey(root) + maxKey(root);
}
// @end minPlusMax
