// Assignment 5 (2017) · prints the answer of every question.
// g++ -std=c++17 main.cpp as5.cpp
#include <iostream>

#include "as5.h"
using namespace std;

static void line(const vector<int>& v, size_t from = 0) {
    for (size_t i = from; i < v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}

int main() {
    TNode* t = buildFromPreIn("CBADEFG", "ABDCEFG");
    cout << "Q1 tree (sideways, root on the left):\n" << drawTree(t) << "   postorder check: " << postorder(t) << "\n\n";
    freeTree(t);

    ShowBST<int> bst;
    for (int k : {9, 10, 8, 1, 2, 26, 35, 30, 4, 11, 7, 21}) bst.insert(k);
    cout << "Q2 BST:              " << bst.shape() << "\n";
    bst.findAndDeleteByCopying(26);
    bst.findAndDeleteByCopying(10);
    cout << "   after delete 26, 10: " << bst.shape() << "\n\n";

    auto g = as5Graph();
    cout << "Q3-a adjacency matrix (rows = from 1..9):\n";
    for (int i = 1; i <= 9; i++) line(g[i], 1);
    cout << "Q3-b BFS from 1: ";
    line(bfs(g, 1));
    cout << "Q3-c DFS from 1: ";
    line(dfs(g, 1));
    cout << "Q3-d edges: " << countEdges(g) << "  (matrix O(V^2), lists O(V+E))\n\n";

    vector<int> h = {0, 12, 28, 14, 41, 18, 67, 52, 25, 10, 11, 4, 19, 37, 7, 22};
    buildHeap(h);
    cout << "Q4-a build-heap: ";
    line(h, 1);
    deleteMin(h);
    cout << "Q4-b delete-min: ";
    line(h, 1);
    heapInsert(h, 19);
    cout << "Q4-c insert 19:  ";
    line(h, 1);
    cout << "Q4-d array layout from the preorder 21 19 24 18 62 10 46 25 18: ";
    line(completeTreeFromPreorder({21, 19, 24, 18, 62, 10, 46, 25, 18}), 1);

    cout << "\nQ5 on the Q2 tree (before deletions)\n";
    ShowBST<int> b2;
    for (int k : {9, 10, 8, 1, 2, 26, 35, 30, 4, 11, 7, 21}) b2.insert(k);
    cout << "   nodes with two children: " << b2.twoChildren() << "\n   min + max: " << b2.minPlusMax() << "\n";
}
