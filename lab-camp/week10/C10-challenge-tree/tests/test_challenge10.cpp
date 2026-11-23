// Challenge 10 tests.
#include <algorithm>
#include <functional>

#include "challenge10.h"
#include "test.h"
#include "tree_build.h"

using namespace lab;

struct PDF_LCA_Case { std::string tree; int p; int q; int lca; };
struct PDF_PS_Case { std::string tree; int target; int ret; };
struct PDF_MPS_Case { std::string tree; int ret; };
#include "pdf_cases.inc"

static Node* findVal(Node* r, int v) {
    if (!r) return nullptr;
    if (r->data == v) return r;
    Node* l = findVal(r->left, v);
    return l ? l : findVal(r->right, v);
}
static int slowPathSum(const Node* r, long long target) {   // start a downward walk everywhere
    std::function<int(const Node*, long long)> down = [&](const Node* p, long long s) -> int {
        if (!p) return 0;
        s += p->data;
        return (s == target) + down(p->left, s) + down(p->right, s);
    };
    std::function<int(const Node*)> all = [&](const Node* p) -> int {
        return p ? down(p, 0) + all(p->left) + all(p->right) : 0;
    };
    return all(r);
}
static int slowMax(const Node* r) {                // best over every pair of endpoints
    std::vector<const Node*> nodes;
    std::function<void(const Node*)> gather = [&](const Node* p) { if (p) { nodes.push_back(p); gather(p->left); gather(p->right); } };
    gather(r);
    std::function<bool(const Node*, const Node*, std::vector<const Node*>&)> path =
        [&](const Node* p, const Node* t, std::vector<const Node*>& o) {
            if (!p) return false;
            o.push_back(p);
            if (p == t || path(p->left, t, o) || path(p->right, t, o)) return true;
            o.pop_back();
            return false;
        };
    int best = INT_MIN;
    for (auto a : nodes)
        for (auto b : nodes) {
            std::vector<const Node*> pa, pb;
            path(r, a, pa);
            path(r, b, pb);
            size_t k = 0;
            while (k < pa.size() && k < pb.size() && pa[k] == pb[k]) k++;
            int s = pa[k - 1]->data;               // the common ancestor once
            for (size_t i = k; i < pa.size(); i++) s += pa[i]->data;
            for (size_t i = k; i < pb.size(); i++) s += pb[i]->data;
            best = std::max(best, s);
        }
    return best;
}

QUESTION("C10-A", "lowestCommonAncestor (LC 236)", "lowestCommonAncestor(") {
    for (auto& c : PDF_LCA) {
        Node* r = buildLevel<Node>(c.tree);
        Node* got = lowestCommonAncestor(r, findVal(r, c.p), findVal(r, c.q));
        check("tree " + c.tree + ", p=" + std::to_string(c.p) + ", q=" + std::to_string(c.q), c.lca, got ? got->data : -999);
        freeTree(r);
    }
}

QUESTION("C10-B", "pathSum (LC 437)", "pathSum(") {
    for (auto& c : PDF_PS) {
        Node* r = buildLevel<Node>(c.tree);
        check("tree " + c.tree + ", target " + std::to_string(c.target), c.ret, pathSum(r, c.target));
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randomTreeText<Node>(randInt(0, 12), -4, 4);
        int target = randInt(-4, 4);
        Node* r = buildLevel<Node>(s);
        check("tree " + s + ", target " + std::to_string(target), slowPathSum(r, target), pathSum(r, target));
        freeTree(r);
    }
}

QUESTION("C10-C", "maxPathSum (LC 124)", "maxPathSum(") {
    for (auto& c : PDF_MPS) {
        Node* r = buildLevel<Node>(c.tree);
        check("tree " + c.tree, c.ret, maxPathSum(r));
        freeTree(r);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randomTreeText<Node>(randInt(1, 10), -9, 9);
        Node* r = buildLevel<Node>(s);
        check("tree " + s, slowMax(r), maxPathSum(r));
        freeTree(r);
    }
}
