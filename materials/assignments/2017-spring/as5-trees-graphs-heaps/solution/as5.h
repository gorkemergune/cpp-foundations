// Assignment 5 (2017) · every question is computed by code, so the drawings can be checked.
#pragma once
#include <string>
#include <vector>

#include "genBST.h"

// ---- Q1: rebuild a binary tree from preorder + inorder (distinct keys) ----------
struct TNode {
    char key;
    TNode *left = nullptr, *right = nullptr;
};
TNode* buildFromPreIn(const std::string& pre, const std::string& in);
std::string postorder(const TNode* t);
std::string drawTree(const TNode* t);           // sideways drawing, right subtree on top
void freeTree(TNode* t);

// ---- Q2: BST shape as text ("9(8(1(,2(,4(,7))),),10(,26(11(,21),35(30,))))") ------
template <class T>
class ShowBST : public BST<T> {                 // derived class: root is protected in BST
public:
    std::string shape() const { return shape(this->root); }
    // Q5-a: nodes that have two children
    int twoChildren() const { return twoChildren(this->root); }
    // Q5-b: smallest + largest key (precondition: not empty)
    T minPlusMax() const {
        BSTNode<T>* lo = this->root;
        while (lo->left) lo = lo->left;            // smallest: keep going left
        BSTNode<T>* hi = this->root;
        while (hi->right) hi = hi->right;          // largest: keep going right
        return lo->el + hi->el;
    }

private:
    static std::string shape(BSTNode<T>* p) {
        if (!p) return "";
        std::string s = std::to_string(p->el);
        if (p->left || p->right) s += "(" + shape(p->left) + "," + shape(p->right) + ")";
        return s;
    }
    static int twoChildren(BSTNode<T>* p) {
        if (!p) return 0;
        return (p->left && p->right ? 1 : 0) + twoChildren(p->left) + twoChildren(p->right);
    }
};

// ---- Q3: the directed graph of the assignment, vertices 1..9 -------------------
std::vector<std::vector<int>> as5Graph();       // adjacency matrix, index 0 unused
std::vector<int> bfs(const std::vector<std::vector<int>>& a, int start);
std::vector<int> dfs(const std::vector<std::vector<int>>& a, int start);
int countEdges(const std::vector<std::vector<int>>& a);   // O(V^2)

// ---- Q4: min-heap in a 1-based array (index 0 unused) ---------------------------
void buildHeap(std::vector<int>& h);            // bottom-up heapify, O(n)
void deleteMin(std::vector<int>& h);
void heapInsert(std::vector<int>& h, int x);
// heap given by its preorder: the shape of a complete tree is fixed, so the preorder
// positions decide where each value sits. Returns the level-order (array) layout.
std::vector<int> completeTreeFromPreorder(const std::vector<int>& pre);
