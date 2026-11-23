#include "check.h"
#include "tree.h"

static std::string s(const std::vector<int>& v) {
    std::string r;
    for (int x : v) r += std::to_string(x) + " ";
    return r;
}

int main() {
    Tree<int> t;
    CHECK(t.isThisaBST(t.root));
    CHECK_EQ(t.findHeight(t.root), 0);
    for (int k : {9, 7, 12, 8, 10, 15, 17}) t.insertBST(k);
    CHECK_EQ(captured([&] { t.inOrder(t.root); }), std::string("7 8 9 10 12 15 17 "));
    CHECK_EQ(t.findHeight(t.root), 4);                 // 9 -> 12 -> 15 -> 17
    CHECK(t.isThisaBST(t.root));
    CHECK_EQ(s(t.findOnlyChild(t.root)), std::string("8 17 "));

    Tree<int> w;
    for (int k : {9, 7, 12, 8, 10, 15, 17}) w.insertWrong(k);
    CHECK(!w.isThisaBST(w.root));
    CHECK_EQ(w.findHeight(w.root), 3);                 // complete tree of 7 nodes
    CHECK_EQ(s(w.findOnlyChild(w.root)), std::string(""));

    // parent-only check would accept this tree: 10 -> left 5 -> right 15 (15 > 10!)
    Tree<int> trap;
    trap.insertWrong(10);
    trap.insertWrong(5);
    trap.insertWrong(20);
    trap.insertWrong(1);
    trap.insertWrong(15);                              // right child of 5
    CHECK(!trap.isThisaBST(trap.root));

    Tree<int> chain;
    for (int k : {1, 2, 3, 4, 5}) chain.insertBST(k);
    CHECK_EQ(chain.findHeight(chain.root), 5);
    CHECK_EQ(s(chain.findOnlyChild(chain.root)), std::string("2 3 4 5 "));
    Tree<int> dup;
    for (int k : {5, 5, 5}) dup.insertBST(k);          // equal keys go right
    CHECK(dup.isThisaBST(dup.root));
    return check_summary("2021 a4 tree functions");
}
