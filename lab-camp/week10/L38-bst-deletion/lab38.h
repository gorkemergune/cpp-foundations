// ============================================================================
//  Lab 38 · Deleting from a binary search tree                       DO NOT EDIT
//  Equal keys go to the RIGHT. "Delete key" = delete the FIRST node with that key
//  on the search path from the root.
// ============================================================================
#pragma once

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// L38-A · Warm-up · delete the node with the smallest key and return that key.
// Precondition: root != nullptr. (Its right subtree takes its place.)
int removeMin(Node*& root);

// L38-B · Warm-up · the inorder successor of a node that HAS a right subtree:
// the smallest key in node->right.
int successorKey(const Node* node);

// L38-M1 · Main · the slides' deletion (slides 52-62). Leaf: remove it. One child: the child
// takes its place. Two children: copy the inorder SUCCESSOR's key into the node and delete
// the successor node. Returns false if key is not in the tree.
bool deleteByCopying(Node*& root, int key);

// L38-M2 · Main · deletion by merging (Labwork 7, genBST.h). Two children: the right
// subtree becomes the right child of the RIGHTMOST node of the left subtree, and the left
// subtree takes the node's place. Returns false if key is not in the tree.
bool deleteByMerging(Node*& root, int key);

// L38-X · Optional · LeetCode 669: delete every node whose key is outside [low, high];
// return the new root. Free the removed nodes.
Node* trimBST(Node* root, int low, int high);

// L38-V · Optional · memory variant (genBST.h / 2017 Assignment 5, Q2): like M1, but use the
// inorder PREDECESSOR (largest key of the left subtree). Distinct keys only.
bool deleteByCopyingPred(Node*& root, int key);
