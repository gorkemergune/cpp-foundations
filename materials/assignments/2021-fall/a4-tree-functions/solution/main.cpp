// Assignment 4 (2021) · g++ -std=c++17 main.cpp
#include <iostream>

#include "tree.h"

int main() {
    Tree<int> tree;
    for (int k : {9, 7, 12, 8, 10, 15, 17}) tree.insertBST(k);
    std::cout << "inOrder: ";
    tree.inOrder(tree.root);                                   // 7 8 9 10 12 15 17
    std::cout << "\nheight: " << tree.findHeight(tree.root) << "\n";
    std::cout << "BST? " << tree.isThisaBST(tree.root) << "\n";
    std::cout << "only children:";
    for (int x : tree.findOnlyChild(tree.root)) std::cout << " " << x;  // 8 17
    Tree<int> wrong;
    for (int k : {9, 7, 12, 8, 10, 15, 17}) wrong.insertWrong(k);
    std::cout << "\ninsertWrong tree is a BST? " << wrong.isThisaBST(wrong.root) << "\n";
}
