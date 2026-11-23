// Assignment 4 (2021) · reference solution for tree.h
// Changes to the given skeleton: <climits>/<queue> includes, std:: in front of vector,
// a destructor (the skeleton leaked every node), and the six functions.
#ifndef TREE_H
#define TREE_H

#include <climits>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
class Tree;

template <class T>
class TreeNode {
private:
    TreeNode<T>* left;
    TreeNode<T>* right;
    int data;

public:
    TreeNode(const T& el) {
        data = el;
        left = NULL;
        right = NULL;
    }
    friend class Tree<T>;
};

template <class T>
class Tree {
public:
    TreeNode<T>* root;

    Tree() { root = NULL; }
    ~Tree() { destroy(root); }
    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;

    // 10 pts · smaller keys to the left, larger or equal to the right
    void insertBST(int el) {
        TreeNode<T>** link = &root;            // pointer to the link we may fill
        while (*link != NULL) link = (el < (*link)->data) ? &(*link)->left : &(*link)->right;
        *link = new TreeNode<T>(el);
    }

    // 10 pts · "random" insertion: fills the tree level by level, left to right
    // (a complete tree), ignoring the keys. Any order but BST order is accepted.
    void insertWrong(int el) {
        TreeNode<T>* node = new TreeNode<T>(el);
        if (root == NULL) { root = node; return; }
        std::queue<TreeNode<T>*> q;
        q.push(root);
        while (true) {
            TreeNode<T>* p = q.front();
            q.pop();
            if (p->left == NULL) { p->left = node; return; }
            if (p->right == NULL) { p->right = node; return; }
            q.push(p->left);
            q.push(p->right);
        }
    }

    // 20 pts · every key must lie in the range allowed by ALL of its ancestors,
    // not only its parent (checking only the parent misses deeper violations).
    bool isThisaBST(TreeNode<T>* treeNode) { return inRange(treeNode, LLONG_MIN, LLONG_MAX); }

    // 20 pts · number of nodes on the longest root-to-leaf path (empty tree: 0)
    int findHeight(TreeNode<T>* treeNode) {
        if (treeNode == NULL) return 0;
        int l = findHeight(treeNode->left), r = findHeight(treeNode->right);
        return 1 + (l > r ? l : r);
    }

    // 30 pts · nodes that have no sibling (the only child of their parent), preorder
    std::vector<int> findOnlyChild(TreeNode<T>* treeNode) {
        std::vector<int> result;
        collectOnly(treeNode, result);
        return result;
    }

    // 5 pts
    void inOrder(TreeNode<T>* treeNode) {
        if (treeNode == NULL) return;
        inOrder(treeNode->left);
        std::cout << treeNode->data << " ";
        inOrder(treeNode->right);
    }

private:
    static bool inRange(TreeNode<T>* p, long long lo, long long hi) {  // lo <= key < hi
        if (p == NULL) return true;
        if (p->data < lo || p->data >= hi) return false;
        return inRange(p->left, lo, p->data) && inRange(p->right, p->data, hi);
    }
    static void collectOnly(TreeNode<T>* p, std::vector<int>& out) {
        if (p == NULL) return;
        if (p->left != NULL && p->right == NULL) out.push_back(p->left->data);
        if (p->right != NULL && p->left == NULL) out.push_back(p->right->data);
        collectOnly(p->left, out);
        collectOnly(p->right, out);
    }
    static void destroy(TreeNode<T>* p) {
        if (p == NULL) return;
        destroy(p->left);
        destroy(p->right);
        delete p;
    }
};

#endif
