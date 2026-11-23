// Lab 37 tests. Trees in LeetCode's level order: "[50,30,70]".
#include <algorithm>
#include <functional>

#include "lab37.h"
#include "test.h"
#include "tree_build.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_INS_Case { V keys; std::string tree; std::string shape; };
struct PDF_ISBST_Case { std::string tree; bool ret; };
#include "pdf_cases.inc"

static Node* refBuild(const V& keys) {          // inserts without using the student's insert
    Node* root = nullptr;
    for (int k : keys) {
        Node** l = &root;
        while (*l) l = k < (*l)->data ? &(*l)->left : &(*l)->right;
        *l = new Node(k);
    }
    return root;
}
static void refIn(const Node* p, V& o) { if (p) { refIn(p->left, o); o.push_back(p->data); refIn(p->right, o); } }
static bool refIsBST(const Node* p) {
    V in;
    refIn(p, in);
    for (size_t i = 1; i < in.size(); i++) if (in[i] < in[i - 1]) return false;
    // equal keys must sit on the right: check every node against its left subtree max
    std::function<bool(const Node*)> ok = [&](const Node* q) {
        if (!q) return true;
        if (q->left) {
            const Node* m = q->left;
            while (m->right) m = m->right;
            if (m->data >= q->data) return false;
        }
        return ok(q->left) && ok(q->right);
    };
    return ok(p);
}

QUESTION("L37-A", "insert", "insert(") {
    for (auto& c : PDF_INS) {
        Node* root = nullptr;
        for (int k : c.keys) insert(root, k);
        check("insert " + show(c.keys), c.tree, levelString(root));
        freeTree(root);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(12, 0, 9);
        Node* root = nullptr;
        for (int k : keys) insert(root, k);
        Node* want = refBuild(keys);
        check("insert " + show(keys), levelString(want), levelString(root));
        freeTree(root);
        freeTree(want);
    }
}

QUESTION("L37-B", "search", "search(") {
    Node* root = refBuild({50, 30, 70, 20, 40, 60, 80});
    Node* got = search(root, 70);
    checkTrue("search 70", got == root->right, "not the node 70");
    checkTrue("search 40", search(root, 40) == root->left->right, "not the node 40");
    checkTrue("search 65", search(root, 65) == nullptr, "should be nullptr");
    checkTrue("search in an empty tree", search(nullptr, 1) == nullptr, "should be nullptr");
    // a tree that is NOT a BST: a correct BST search must not find 99 in the left subtree
    Node* fake = buildLevel<Node>("[50,99,70]");
    checkTrue("search follows the BST order", search(fake, 99) == nullptr,
              "found 99 on the left of 50: the search visits the whole tree instead of one path");
    freeTree(fake);
    freeTree(root);
}

QUESTION("L37-M1", "minKey / maxKey", "Key(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(12, -20, 20, 1);
        Node* root = refBuild(keys);
        check("min of " + show(keys), *std::min_element(keys.begin(), keys.end()), minKey(root));
        check("max of " + show(keys), *std::max_element(keys.begin(), keys.end()), maxKey(root));
        freeTree(root);
    }
}

QUESTION("L37-M2", "isBST (Assignment 4)", "isBST(") {
    for (auto& c : PDF_ISBST) {
        Node* r = buildLevel<Node>(c.tree);
        check("tree " + c.tree, c.ret, isBST(r));
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randInt(0, 1) ? randomTreeText<Node>(randInt(0, 8), 0, 9) : levelString(refBuild(randVec(8, 0, 9)));
        Node* r = buildLevel<Node>(s);
        check("tree " + s, refIsBST(r), isBST(r));
        freeTree(r);
    }
}

QUESTION("L37-M3", "treeSort", "treeSort(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, -9, 9), w = v;
        std::sort(w.begin(), w.end());
        int before = Node::alive;
        check("treeSort " + show(v), w, treeSort(v));
        check("treeSort " + show(v) + " frees its nodes", before, Node::alive);
    }
}

QUESTION("L37-M4", "shape (Assignment 5, Q2)", "shape(") {
    for (auto& c : PDF_INS) {
        Node* r = refBuild(c.keys);
        check("shape after inserting " + show(c.keys), c.shape, shape(r));
        freeTree(r);
    }
    Node* as5 = refBuild({9, 10, 8, 1, 2, 26, 35, 30, 4, 11, 7, 21});
    check("Assignment 5, Q2", std::string("9(8(1(,2(,4(,7))),),10(,26(11(,21),35(30,))))"), shape(as5));
    freeTree(as5);
}

OPTIONAL_QUESTION("L37-X", "sortedArrayToBST (LC 108)", "sortedArrayToBST(") {
    Node* r = sortedArrayToBST({-10, -3, 0, 5, 9});
    check("{-10,-3,0,5,9}", std::string("[0,-10,5,null,-3,null,9]"), levelString(r));
    freeTree(r);
    checkTrue("empty array", sortedArrayToBST({}) == nullptr, "should be nullptr");
}

OPTIONAL_QUESTION("L37-V", "minPlusMax (Assignment 5, Q5-b)", "minPlusMax(") {
    Node* r = refBuild({50, 30, 70, 20, 40, 60, 80});
    check("50 30 70 20 40 60 80", 100, minPlusMax(r));
    freeTree(r);
}
