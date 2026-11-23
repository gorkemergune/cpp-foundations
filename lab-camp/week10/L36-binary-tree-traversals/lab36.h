// ============================================================================
//  Lab 36 · Binary trees: counting, traversals, height, freeing      DO NOT EDIT
//  Node = the slides' TreeNode (item, leftChildPtr, rightChildPtr) with short names.
// ============================================================================
#pragma once

#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) { alive++; }
    ~Node() { alive--; }
    static inline int alive = 0;   // tests count live nodes
};

// L36-A · Warm-up · number of nodes.
int countNodes(const Node* root);

// L36-B · Warm-up · number of leaves (no children).
int countLeaves(const Node* root);

// L36-M1 · Main · the three depth-first traversals (slides 35-38), as vectors.
std::vector<int> preorder(const Node* root);
std::vector<int> inorder(const Node* root);
std::vector<int> postorder(const Node* root);

// L36-M2 · Main (2021 Assignment 4) · number of nodes on the longest root-to-leaf path;
// empty tree: 0.
int height(const Node* root);

// L36-M3 · Main · LeetCode 102: the values level by level, left to right (std::queue).
std::vector<std::vector<int>> levelOrder(const Node* root);

// L36-M4 · Main · delete every node (slide 34: the destructor) and set root to nullptr.
void destroyTree(Node*& root);

// L36-X · Optional · LeetCode 226: mirror the tree in place, return the root.
Node* invertTree(Node* root);

// L36-V · Optional · memory variant (2017 Assignment 5, Q5-a): nodes with two children.
int twoChildren(const Node* root);
