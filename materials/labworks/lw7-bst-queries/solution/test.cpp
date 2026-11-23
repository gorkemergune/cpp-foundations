#include <stdexcept>
#include <string>

#include "check.h"
#include "genBST.h"

int main() {
    BST<std::string> tree;
    for (const char* k : {"F", "B", "A", "D", "C", "E", "G", "I", "H"}) tree.insert(k);
    CHECK_EQ(captured([&] { tree.printsmallerthan("F"); }), std::string("A B C D E \n"));
    CHECK_EQ(captured([&] { tree.printsmallerthan("D"); }), std::string("A B C \n"));
    CHECK_EQ(captured([&] { tree.printsmallerthan("A"); }), std::string("\n"));
    CHECK_EQ(captured([&] { tree.printsmallerthan("Z"); }), std::string("A B C D E F G H I \n"));
    CHECK_EQ(tree.getnthelement(2), std::string("B"));
    CHECK_EQ(tree.getnthelement(7), std::string("G"));
    CHECK_EQ(tree.getnthelement(1), std::string("A"));
    CHECK_EQ(tree.getnthelement(9), std::string("I"));
    bool threw = false;
    try { tree.getnthelement(10); } catch (const std::out_of_range&) { threw = true; }
    CHECK(threw);
    CHECK(!tree.isbalanced());            // G has an empty left and a right subtree of height 2
    BST<int> b;
    CHECK(b.isbalanced());                // empty tree
    for (int k : {4, 2, 6, 1, 3, 5, 7}) b.insert(k);
    CHECK(b.isbalanced());
    b.insert(8);
    b.insert(9);                          // 7 -> 8 -> 9 chain
    CHECK(!b.isbalanced());
    return check_summary("lw7 printsmallerthan / getnthelement / isbalanced");
}
