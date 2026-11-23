// Lab 36 tests. Trees are written in LeetCode's level order: "[1,2,3,null,5]".
#include <algorithm>

#include "lab36.h"
#include "test.h"
#include "tree_build.h"

using namespace lab;
using V = std::vector<int>;
using VV = std::vector<std::vector<int>>;

struct PDF_TRAV_Case { std::string tree; V pre; V in; V post; };
struct PDF_SHAPE_Case { std::string tree; int nodes; int leaves; int height; VV levels; };
#include "pdf_cases.inc"

// small references for random trees
static void refPre(const Node* p, V& o) { if (p) { o.push_back(p->data); refPre(p->left, o); refPre(p->right, o); } }
static void refIn(const Node* p, V& o) { if (p) { refIn(p->left, o); o.push_back(p->data); refIn(p->right, o); } }
static void refPost(const Node* p, V& o) { if (p) { refPost(p->left, o); refPost(p->right, o); o.push_back(p->data); } }
static int refH(const Node* p) { return p ? 1 + std::max(refH(p->left), refH(p->right)) : 0; }
static int refLeaves(const Node* p) { return !p ? 0 : (!p->left && !p->right) ? 1 : refLeaves(p->left) + refLeaves(p->right); }

template <class F>
static void forTrees(F f) {                       // PDF shapes first, then random ones
    for (auto& c : PDF_SHAPE) f(c.tree);
    for (int t = 0; t < RANDOM_CASES; t++) f(randomTreeText<Node>(randInt(0, 12), 0, 9));
}

QUESTION("L36-A", "countNodes", "countNodes(") {
    forTrees([](const std::string& s) {
        Node* r = buildLevel<Node>(s);
        V all;
        refPre(r, all);
        check("tree " + s, (int)all.size(), countNodes(r));
        freeTree(r);
    });
}

QUESTION("L36-B", "countLeaves", "countLeaves(") {
    forTrees([](const std::string& s) {
        Node* r = buildLevel<Node>(s);
        check("tree " + s, refLeaves(r), countLeaves(r));
        freeTree(r);
    });
}

QUESTION("L36-M1", "preorder / inorder / postorder", "preorder") {
    for (auto& c : PDF_TRAV) {
        Node* r = buildLevel<Node>(c.tree);
        check("preorder of " + c.tree, c.pre, preorder(r));
        check("inorder of " + c.tree, c.in, inorder(r));
        check("postorder of " + c.tree, c.post, postorder(r));
        freeTree(r);
    }
    forTrees([](const std::string& s) {
        Node* r = buildLevel<Node>(s);
        V a, b, c;
        refPre(r, a);
        refIn(r, b);
        refPost(r, c);
        check("preorder of " + s, a, preorder(r));
        check("inorder of " + s, b, inorder(r));
        check("postorder of " + s, c, postorder(r));
        freeTree(r);
    });
}

QUESTION("L36-M2", "height (Assignment 4)", "height(") {
    for (auto& c : PDF_SHAPE) {
        Node* r = buildLevel<Node>(c.tree);
        check("height of " + c.tree, c.height, height(r));
        freeTree(r);
    }
    forTrees([](const std::string& s) {
        Node* r = buildLevel<Node>(s);
        check("height of " + s, refH(r), height(r));
        freeTree(r);
    });
}

QUESTION("L36-M3", "levelOrder (LC 102)", "levelOrder(") {
    for (auto& c : PDF_SHAPE) {
        Node* r = buildLevel<Node>(c.tree);
        check("levels of " + c.tree, c.levels, levelOrder(r));
        freeTree(r);
    }
    forTrees([](const std::string& s) {
        Node* r = buildLevel<Node>(s);
        VV got = levelOrder(r);
        V flat;
        for (auto& l : got) for (int x : l) flat.push_back(x);
        checkTrue("levels of " + s, (int)got.size() == refH(r), "wrong number of levels: " + show(got));
        V all;
        refPre(r, all);
        checkTrue("levels of " + s, flat.size() == all.size(), "wrong number of values: " + show(got));
        freeTree(r);
    });
}

QUESTION("L36-M4", "destroyTree", "destroyTree(") {
    forTrees([](const std::string& s) {
        int before = Node::alive;
        Node* r = buildLevel<Node>(s);
        destroyTree(r);
        checkTrue("destroy " + s, r == nullptr, "root is not nullptr afterwards");
        check("destroy " + s + ": live nodes", before, Node::alive);
    });
}

OPTIONAL_QUESTION("L36-X", "invertTree (LC 226)", "invertTree(") {
    Node* r = buildLevel<Node>("[4,2,7,1,3,6,9]");
    r = invertTree(r);
    check("LeetCode example 1", std::string("[4,7,2,9,6,3,1]"), levelString(r));
    freeTree(r);
    checkTrue("empty tree", invertTree(nullptr) == nullptr, "should return nullptr");
}

OPTIONAL_QUESTION("L36-V", "twoChildren (AS5 Q5-a)", "twoChildren(") {
    for (auto& [s, n] : std::vector<std::pair<std::string, int>>{{"[1,2,3,4,5,null,6]", 2}, {"[1,null,2,null,3]", 0}, {"[]", 0}}) {
        Node* r = buildLevel<Node>(s);
        check("tree " + s, n, twoChildren(r));
        freeTree(r);
    }
}
