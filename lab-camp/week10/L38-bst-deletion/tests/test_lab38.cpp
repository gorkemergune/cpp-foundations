// Lab 38 tests. Random trees are compared with small reference deletions.
#include <algorithm>
#include <functional>

#include "lab38.h"
#include "test.h"
#include "tree_build.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_DEL_Case { std::string tree; int key; bool ret; std::string copying; std::string merging; };
#include "pdf_cases.inc"

static Node* refBuild(const V& keys) {
    Node* root = nullptr;
    for (int k : keys) {
        Node** l = &root;
        while (*l) l = k < (*l)->data ? &(*l)->left : &(*l)->right;
        *l = new Node(k);
    }
    return root;
}
static Node** refFind(Node*& root, int key) {
    Node** l = &root;
    while (*l && (*l)->data != key) l = key < (*l)->data ? &(*l)->left : &(*l)->right;
    return l;
}
static void refCopy(Node*& root, int key, bool pred) {
    Node** l = refFind(root, key);
    Node* n = *l;
    if (!n) return;
    if (!n->left || !n->right) { *l = n->left ? n->left : n->right; delete n; return; }
    Node** s = pred ? &n->left : &n->right;
    while (pred ? (*s)->right : (*s)->left) s = pred ? &(*s)->right : &(*s)->left;
    Node* v = *s;
    n->data = v->data;
    *s = pred ? v->left : v->right;
    delete v;
}
static void refMerge(Node*& root, int key) {
    Node** l = refFind(root, key);
    Node* n = *l;
    if (!n) return;
    if (!n->left) *l = n->right;
    else if (!n->right) *l = n->left;
    else {
        Node* m = n->left;
        while (m->right) m = m->right;
        m->right = n->right;
        *l = n->left;
    }
    delete n;
}

QUESTION("L38-A", "removeMin", "removeMin(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(10, 0, 9, 1);
        Node* r = refBuild(keys);
        Node* w = refBuild(keys);
        int alive = Node::alive;
        check("removeMin of " + levelString(r), *std::min_element(keys.begin(), keys.end()), removeMin(r));
        Node** l = &w;
        while ((*l)->left) l = &(*l)->left;
        Node* v = *l;
        *l = v->right;
        delete v;
        check("tree after removeMin", levelString(w), levelString(r));
        check("one node deleted", alive - 2, Node::alive);
        freeTree(r);
        freeTree(w);
    }
}

QUESTION("L38-B", "successorKey", "successorKey(") {
    Node* r = buildLevel<Node>("[50,30,70,20,40,60,80,null,null,35]");
    check("successor of 30", 35, successorKey(r->left));
    check("successor of 50", 60, successorKey(r));
    check("successor of 70", 80, successorKey(r->right));
    freeTree(r);
}

QUESTION("L38-M1", "deleteByCopying (slides: successor)", "deleteByCopying(") {
    for (auto& c : PDF_DEL) {
        Node* r = buildLevel<Node>(c.tree);
        int alive = Node::alive;
        std::string d = "delete " + std::to_string(c.key) + " from " + c.tree;
        check(d + " (return)", c.ret, deleteByCopying(r, c.key));
        check(d, c.copying, levelString(r));
        check(d + " (nodes freed)", c.ret ? 1 : 0, alive - Node::alive);
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(10, 0, 9);
        int k = randInt(0, 9);
        Node* r = refBuild(keys);
        Node* w = refBuild(keys);
        std::string d = "delete " + std::to_string(k) + " from " + levelString(r);
        deleteByCopying(r, k);
        refCopy(w, k, false);
        check(d, levelString(w), levelString(r));
        freeTree(r);
        freeTree(w);
    }
}

QUESTION("L38-M2", "deleteByMerging (Labwork 7)", "deleteByMerging(") {
    for (auto& c : PDF_DEL) {
        Node* r = buildLevel<Node>(c.tree);
        int alive = Node::alive;
        std::string d = "delete " + std::to_string(c.key) + " from " + c.tree;
        check(d + " (return)", c.ret, deleteByMerging(r, c.key));
        check(d, c.merging, levelString(r));
        check(d + " (nodes freed)", c.ret ? 1 : 0, alive - Node::alive);
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(10, 0, 9);
        int k = randInt(0, 9);
        Node* r = refBuild(keys);
        Node* w = refBuild(keys);
        std::string d = "delete " + std::to_string(k) + " from " + levelString(r);
        deleteByMerging(r, k);
        refMerge(w, k);
        check(d, levelString(w), levelString(r));
        freeTree(r);
        freeTree(w);
    }
}

OPTIONAL_QUESTION("L38-X", "trimBST (LC 669)", "trimBST(") {
    int before = Node::alive;
    Node* r = trimBST(buildLevel<Node>("[1,0,2]"), 1, 2);
    check("LeetCode example 1", std::string("[1,null,2]"), levelString(r));
    freeTree(r);
    r = trimBST(buildLevel<Node>("[3,0,4,null,2,null,null,1]"), 1, 3);
    check("LeetCode example 2", std::string("[3,2,null,1]"), levelString(r));
    freeTree(r);
    check("removed nodes are freed", before, Node::alive);
}

OPTIONAL_QUESTION("L38-V", "deleteByCopyingPred (AS5 Q2)", "deleteByCopyingPred(") {
    Node* r = refBuild({9, 10, 8, 1, 2, 26, 35, 30, 4, 11, 7, 21});
    deleteByCopyingPred(r, 26);
    deleteByCopyingPred(r, 10);
    check("AS5 Q2: delete 26, then 10", std::string("[9,8,21,1,null,11,35,null,2,null,null,30,null,null,4,null,null,null,7]"),
          levelString(r));
    check("missing key", false, deleteByCopyingPred(r, 99));
    freeTree(r);
}
