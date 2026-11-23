// ============================================================================
//  Lab 39 · Tree questions from the course archive                   DO NOT EDIT
//  Labwork 7 (getnthelement, printsmallerthan, isbalanced), 2021 Assignment 4
//  (findOnlyChild), 2017 Assignment 5 Q1 (rebuild from preorder + inorder).
// ============================================================================
#pragma once

#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// L39-A · Warm-up (Labwork 7, getnthelement) · the n-th smallest key of a BST, n = 1, 2 ...
// n outside 1..size: false, out unchanged.
bool nthSmallest(const Node* root, int n, int& out);

// L39-B · Warm-up (Labwork 7, printsmallerthan) · the keys of a BST that are < x, ascending.
// Do not enter a right subtree that cannot contain such keys.
std::vector<int> smallerThan(const Node* root, int x);

// L39-M1 · Main (Labwork 7, isbalanced) · at EVERY node the heights of the two subtrees
// differ by at most 1. O(n): do not call a separate height function at every node.
bool isBalanced(const Node* root);

// L39-M2 · Main (2021 Assignment 4, findOnlyChild, 30 pts) · the keys of the nodes that have
// no sibling (they are the only child of their parent), in preorder.
std::vector<int> onlyChildren(const Node* root);

// L39-M3 · Main (2017 Assignment 5 Q1, LeetCode 105) · rebuild the binary tree from its
// preorder and inorder traversals (distinct keys).
Node* buildFromPreIn(const std::vector<int>& pre, const std::vector<int>& in);

// L39-X · Optional · LeetCode 1382 (genBST's balance): a balanced BST with the same keys;
// read the keys in inorder, the middle one becomes the root. Free the old tree.
Node* balanceBST(Node* root);

// L39-V · Optional · memory variant: how many keys of the BST lie in [lo, hi]?
// Skip the subtrees that cannot contain any.
int countInRange(const Node* root, int lo, int hi);
