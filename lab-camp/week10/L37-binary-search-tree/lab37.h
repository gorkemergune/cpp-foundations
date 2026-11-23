// ============================================================================
//  Lab 37 · Binary search trees: insert, search, min/max, check, treesort
//  DO NOT EDIT.  Equal keys go to the RIGHT (as insertBST in 2021 Assignment 4).
// ============================================================================
#pragma once

#include <string>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;
};

// L37-A · Warm-up · insert key as a new leaf (slides 49-51).
void insert(Node*& root, int key);

// L37-B · Warm-up · the node holding key, or nullptr (slide 48). Use the BST order:
// do not visit the whole tree.
Node* search(Node* root, int key);

// L37-M1 · Main · smallest and largest key. Precondition: root != nullptr.
int minKey(const Node* root);
int maxKey(const Node* root);

// L37-M2 · Main (2021 Assignment 4, isThisaBST) · is this binary tree a BST?
// Every key must be >= all keys in its left subtree and < all keys in its right subtree.
bool isBST(const Node* root);

// L37-M3 · Main · treesort (slides 65-66): insert into a BST, read it in inorder, free it.
std::vector<int> treeSort(const std::vector<int>& values);

// L37-M4 · Main (2017 Assignment 5, Q2) · the shape as text: "key(left,right)";
// a leaf is just "key"; an empty child is written as nothing. 5(3,5(,5))
std::string shape(const Node* root);

// L37-X · Optional · LeetCode 108: a BST of minimum height (slide 63) from a sorted array;
// the middle element (index (lo + hi) / 2) becomes the root.
Node* sortedArrayToBST(const std::vector<int>& sorted);

// L37-V · Optional · memory variant (2017 Assignment 5, Q5-b): smallest + largest key.
int minPlusMax(const Node* root);
