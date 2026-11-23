// ============================================================================
//  Lab 38 · BST deletion · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L38
// ============================================================================
#include "lab38.h"

#include "todo.h"

// L38-A · Example: 50(30(20,40),70)  =>  20, tree 50(30(,40),70)
// @begin removeMin
int removeMin(Node*& root) {
    Node** link = &root;
    while ((*link)->left != nullptr) link = &(*link)->left;
    Node* victim = *link;
    int key = victim->data;
    *link = victim->right;                  // the right subtree moves up
    delete victim;
    return key;
}
// @end removeMin

// L38-B · Example: the node 30 of 50(30(20,40(35,)),70)  =>  35
// @begin successorKey
int successorKey(const Node* node) {
    const Node* p = node->right;
    while (p->left != nullptr) p = p->left;
    return p->data;
}
// @end successorKey

// L38-M1 · Example: [50,30,70,20,40,60,80], delete 50  =>  [60,30,70,20,40,null,80]
// @begin deleteByCopying
bool deleteByCopying(Node*& root, int key) {
    Node** link = &root;                    // the pointer that holds the node to delete
    while (*link != nullptr && (*link)->data != key)
        link = (key < (*link)->data) ? &(*link)->left : &(*link)->right;
    Node* node = *link;
    if (node == nullptr) return false;
    if (node->left == nullptr || node->right == nullptr) {     // leaf or one child
        *link = (node->left != nullptr) ? node->left : node->right;
        delete node;
    } else {                                                  // two children
        node->data = removeMin(node->right);  // successor = min of the right subtree
    }
    return true;
}
// @end deleteByCopying

// L38-M2 · Example: [50,30,70,20,40,60,80], delete 50  =>  [30,20,40,null,null,null,70,60,80]
// @begin deleteByMerging
bool deleteByMerging(Node*& root, int key) {
    Node** link = &root;
    while (*link != nullptr && (*link)->data != key)
        link = (key < (*link)->data) ? &(*link)->left : &(*link)->right;
    Node* node = *link;
    if (node == nullptr) return false;
    if (node->left == nullptr) *link = node->right;
    else if (node->right == nullptr) *link = node->left;
    else {
        Node* m = node->left;
        while (m->right != nullptr) m = m->right;   // rightmost of the left subtree
        m->right = node->right;             // every key on the right is >= m's key
        *link = node->left;
    }
    delete node;
    return true;
}
// @end deleteByMerging

// L38-X · Example: [3,0,4,null,2,null,null,1], low 1, high 3  =>  [3,2,null,1]
// @begin trimBST
Node* trimBST(Node* root, int low, int high) {
    if (root == nullptr) return nullptr;
    root->left = trimBST(root->left, low, high);      // postorder: children first
    root->right = trimBST(root->right, low, high);
    if (root->data < low || root->data > high) {
        // root < low: its left subtree was all < low, so it is already empty (and vice versa)
        Node* keep = (root->data < low) ? root->right : root->left;
        delete root;
        return keep;
    }
    return root;
}
// @end trimBST

// L38-V · Example: AS5 Q2 tree, delete 26 then 10  =>  9(8(1(,2(,4(,7))),),21(11,35(30,)))
// @begin deleteByCopyingPred
bool deleteByCopyingPred(Node*& root, int key) {
    Node** link = &root;
    while (*link != nullptr && (*link)->data != key)
        link = (key < (*link)->data) ? &(*link)->left : &(*link)->right;
    Node* node = *link;
    if (node == nullptr) return false;
    if (node->left == nullptr || node->right == nullptr) {
        *link = (node->left != nullptr) ? node->left : node->right;
        delete node;
        return true;
    }
    Node** pred = &node->left;              // rightmost node of the left subtree
    while ((*pred)->right != nullptr) pred = &(*pred)->right;
    Node* p = *pred;
    node->data = p->data;
    *pred = p->left;
    delete p;
    return true;
}
// @end deleteByCopyingPred
