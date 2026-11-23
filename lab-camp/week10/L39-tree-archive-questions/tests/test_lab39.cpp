// Lab 39 tests.
#include <algorithm>
#include <functional>

#include "lab39.h"
#include "test.h"
#include "tree_build.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_BAL_Case { std::string tree; bool balanced; V only; };
struct PDF_PI_Case { V pre; V in; std::string tree; };
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
static int refH(const Node* p) { return p ? 1 + std::max(refH(p->left), refH(p->right)) : 0; }
static bool refBal(const Node* p) {
    return !p || (std::abs(refH(p->left) - refH(p->right)) <= 1 && refBal(p->left) && refBal(p->right));
}
static void refPre(const Node* p, V& o) { if (p) { o.push_back(p->data); refPre(p->left, o); refPre(p->right, o); } }
static void refIn(const Node* p, V& o) { if (p) { refIn(p->left, o); o.push_back(p->data); refIn(p->right, o); } }

QUESTION("L39-A", "nthSmallest (Labwork 7)", "nthSmallest(") {
    Node* r = refBuild({6, 2, 8, 1, 4, 7, 9, 3, 5});
    for (int n = 1; n <= 9; n++) {
        int out = -1;
        check("n=" + std::to_string(n) + " (return)", true, nthSmallest(r, n, out));
        check("n=" + std::to_string(n), n, out);
    }
    int out = 777;
    check("n=10 (return)", false, nthSmallest(r, 10, out));
    check("n=0 (return)", false, nthSmallest(r, 0, out));
    check("out unchanged", 777, out);
    check("empty tree", false, nthSmallest(nullptr, 1, out));
    freeTree(r);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V keys = randVec(10, 0, 20, 1), s = keys;
        std::sort(s.begin(), s.end());
        Node* q = refBuild(keys);
        int n = randInt(1, (int)keys.size()), got = -1;
        nthSmallest(q, n, got);
        check("keys " + show(keys) + ", n=" + std::to_string(n), s[n - 1], got);
        freeTree(q);
    }
}

QUESTION("L39-B", "smallerThan (Labwork 7)", "smallerThan(") {
    Node* r = refBuild({6, 2, 8, 1, 4, 7, 9, 3, 5});
    check("x=6", V{1, 2, 3, 4, 5}, smallerThan(r, 6));
    check("x=4", V{1, 2, 3}, smallerThan(r, 4));
    check("x=1", V{}, smallerThan(r, 1));
    check("x=100", V{1, 2, 3, 4, 5, 6, 7, 8, 9}, smallerThan(r, 100));
    freeTree(r);
    Node* fake = buildLevel<Node>("[5,null,1]");   // not a BST: a pruned search never sees the 1
    check("does not enter the right subtree of 5 when x=3", V{}, smallerThan(fake, 3));
    freeTree(fake);
}

QUESTION("L39-M1", "isBalanced (Labwork 7)", "isBalanced(") {
    for (auto& c : PDF_BAL) {
        Node* r = buildLevel<Node>(c.tree);
        check("tree " + c.tree, c.balanced, isBalanced(r));
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randomTreeText<Node>(randInt(0, 12), 0, 9);
        Node* r = buildLevel<Node>(s);
        check("tree " + s, refBal(r), isBalanced(r));
        freeTree(r);
    }
}

QUESTION("L39-M2", "onlyChildren (Assignment 4)", "onlyChildren(") {
    for (auto& c : PDF_BAL) {
        Node* r = buildLevel<Node>(c.tree);
        check("tree " + c.tree, c.only, onlyChildren(r));
        freeTree(r);
    }
}

QUESTION("L39-M3", "buildFromPreIn (AS5 Q1, LC 105)", "buildFromPreIn(") {
    for (auto& c : PDF_PI) {
        Node* r = buildFromPreIn(c.pre, c.in);
        check("pre " + show(c.pre) + ", in " + show(c.in), c.tree, levelString(r));
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(0, 10);
        std::string s = randomTreeText<Node>(n, 0, 0);
        Node* shape = buildLevel<Node>(s);
        int k = 0;                               // give the nodes distinct keys
        std::function<void(Node*)> number = [&](Node* p) { if (p) { p->data = k++; number(p->left); number(p->right); } };
        number(shape);
        V pre, in;
        refPre(shape, pre);
        refIn(shape, in);
        Node* r = buildFromPreIn(pre, in);
        check("pre " + show(pre) + ", in " + show(in), levelString(shape), levelString(r));
        freeTree(r);
        freeTree(shape);
    }
}

OPTIONAL_QUESTION("L39-X", "balanceBST (LC 1382)", "balanceBST(") {
    int before = Node::alive;
    Node* r = balanceBST(buildLevel<Node>("[1,null,2,null,3,null,4]"));
    check("1 2 3 4", std::string("[2,1,3,null,null,null,4]"), levelString(r));
    freeTree(r);
    check("old nodes freed", before, Node::alive);
}

OPTIONAL_QUESTION("L39-V", "countInRange", "countInRange(") {
    Node* r = refBuild({6, 2, 8, 1, 4, 7, 9, 3, 5});
    check("[3, 6]", 4, countInRange(r, 3, 6));
    check("[10, 20]", 0, countInRange(r, 10, 20));
    check("[1, 9]", 9, countInRange(r, 1, 9));
    freeTree(r);
}
