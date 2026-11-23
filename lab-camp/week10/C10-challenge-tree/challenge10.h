// ============================================================================
//  Challenge Set 10 · binary trees (medium / hard)                   DO NOT EDIT
// ============================================================================
#pragma once

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d, Node* l = nullptr, Node* r = nullptr) : data(d), left(l), right(r) {}
};

// C10-A · LeetCode 236 (medium): the lowest node that has both p and q as descendants
// (a node is a descendant of itself). p and q are in the tree. NOT necessarily a BST.
Node* lowestCommonAncestor(Node* root, Node* p, Node* q);

// C10-B · LeetCode 437 (medium): the number of downward paths (from any node to any node
// below it) whose values add up to target.
int pathSum(const Node* root, long long target);

// C10-C · LeetCode 124 (hard): the largest sum of a path between any two nodes (a path
// goes up and down along edges, uses every node at most once, has at least one node).
int maxPathSum(const Node* root);
