// ============================================================================
//  Lab 36 · Binary trees · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L36
// ============================================================================
#include "lab36.h"

#include <queue>

#include "todo.h"

using namespace std;

// L36-A · Example: 1(2(4,5),3(,6))  =>  6
// @begin countNodes
int countNodes(const Node* root) {
    if (root == nullptr) return 0;          // base case: the empty tree
    return 1 + countNodes(root->left) + countNodes(root->right);
}
// @end countNodes

// L36-B · Example: 1(2(4,5),3(,6))  =>  3 (4, 5, 6)
// @begin countLeaves
int countLeaves(const Node* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}
// @end countLeaves

// L36-M1 · Example: 1(2(4,5),3(,6))  =>  pre 1 2 4 5 3 6, in 4 2 5 1 3 6, post 4 5 2 6 3 1
// @begin preorderInto
void preorderInto(const Node* p, vector<int>& out) {
    if (p == nullptr) return;
    out.push_back(p->data);                 // root FIRST
    preorderInto(p->left, out);
    preorderInto(p->right, out);
}
// @end preorderInto

// @begin preorder
vector<int> preorder(const Node* root) {
    vector<int> out;
    preorderInto(root, out);
    return out;
}
// @end preorder

// @begin inorderInto
void inorderInto(const Node* p, vector<int>& out) {
    if (p == nullptr) return;
    inorderInto(p->left, out);
    out.push_back(p->data);                 // root IN the middle
    inorderInto(p->right, out);
}
// @end inorderInto

// @begin inorder
vector<int> inorder(const Node* root) {
    vector<int> out;
    inorderInto(root, out);
    return out;
}
// @end inorder

// @begin postorderInto
void postorderInto(const Node* p, vector<int>& out) {
    if (p == nullptr) return;
    postorderInto(p->left, out);
    postorderInto(p->right, out);
    out.push_back(p->data);                 // root LAST
}
// @end postorderInto

// @begin postorder
vector<int> postorder(const Node* root) {
    vector<int> out;
    postorderInto(root, out);
    return out;
}
// @end postorder

// L36-M2 · Example: 1(2(4,5),3(,6))  =>  3
// @begin height
int height(const Node* root) {
    if (root == nullptr) return 0;
    int l = height(root->left), r = height(root->right);
    return 1 + (l > r ? l : r);
}
// @end height

// L36-M3 · Example: 1(2(4,5),3(,6))  =>  {{1}, {2, 3}, {4, 5, 6}}
// @begin levelOrder
vector<vector<int>> levelOrder(const Node* root) {
    vector<vector<int>> levels;
    if (root == nullptr) return levels;
    queue<const Node*> q;
    q.push(root);
    while (!q.empty()) {
        int width = q.size();               // exactly the nodes of this level
        levels.push_back({});
        for (int i = 0; i < width; i++) {
            const Node* p = q.front();
            q.pop();
            levels.back().push_back(p->data);
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
    }
    return levels;
}
// @end levelOrder

// L36-M4 · Example: any tree  =>  every node deleted, root == nullptr
// @begin destroyTree
void destroyTree(Node*& root) {
    if (root == nullptr) return;
    destroyTree(root->left);                // postorder: children first ...
    destroyTree(root->right);
    delete root;                            // ... then the node that points to them
    root = nullptr;
}
// @end destroyTree

// L36-X · Example: 4(2(1,3),7(6,9))  =>  4(7(9,6),2(3,1))
// @begin invertTree
Node* invertTree(Node* root) {
    if (root == nullptr) return nullptr;
    Node* t = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(t);
    return root;
}
// @end invertTree

// L36-V · Example: 1(2(4,5),3(,6))  =>  2
// @begin twoChildren
int twoChildren(const Node* root) {
    if (root == nullptr) return 0;
    int me = (root->left && root->right) ? 1 : 0;
    return me + twoChildren(root->left) + twoChildren(root->right);
}
// @end twoChildren
