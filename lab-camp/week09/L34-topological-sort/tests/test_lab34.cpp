// Lab 34 tests. Random directed graphs are checked against a reference topSort1.
#include <algorithm>

#include "lab34.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_TS_Case { AdjList g; V order; bool cycle; };
#include "pdf_cases.inc"

static AdjList randDigraph() {
    int n = randInt(1, 7);
    AdjList g(n);
    int e = randInt(0, n + 3);
    bool dag = randInt(0, 1);                 // half of them acyclic for sure (edges go up)
    for (int i = 0; i < e; i++) {
        int u = randInt(0, n - 1), v = randInt(0, n - 1);
        if (dag && u >= v) continue;
        g[u].push_back(v);
    }
    for (auto& nb : g) {
        std::sort(nb.begin(), nb.end());
        nb.erase(std::unique(nb.begin(), nb.end()), nb.end());
    }
    return g;
}
static V refTopSort1(const AdjList& g) {
    int n = g.size();
    std::vector<bool> gone(n);
    V list;
    for (int s = 0; s < n; s++) {
        int pick = -1;
        for (int v = 0; v < n && pick < 0; v++) {
            if (gone[v]) continue;
            bool none = true;
            for (int w : g[v]) none = none && gone[w];
            if (none) pick = v;
        }
        if (pick < 0) return {};
        list.insert(list.begin(), pick);
        gone[pick] = true;
    }
    return list;
}
static bool validOrder(const AdjList& g, const V& o) {
    if (o.size() != g.size()) return false;
    V pos(g.size(), -1);
    for (size_t i = 0; i < o.size(); i++) {
        if (o[i] < 0 || o[i] >= (int)g.size() || pos[o[i]] >= 0) return false;
        pos[o[i]] = i;
    }
    for (size_t u = 0; u < g.size(); u++)
        for (int w : g[u]) if (pos[u] > pos[w]) return false;
    return true;
}

QUESTION("L34-A", "inDegrees", "inDegrees(") {
    check("0->1, 0->2, 1->2", V{0, 1, 2}, inDegrees({{1, 2}, {2}, {}}));
    check("self-loop", V{1}, inDegrees({{0}}));
    check("no edges", V{0, 0}, inDegrees({{}, {}}));
}

QUESTION("L34-B", "isTopologicalOrder", "isTopologicalOrder(") {
    AdjList g = {{1}, {2}, {}};
    check("0->1->2, order {0,1,2}", true, isTopologicalOrder(g, {0, 1, 2}));
    check("0->1->2, order {0,2,1}", false, isTopologicalOrder(g, {0, 2, 1}));
    check("missing vertex", false, isTopologicalOrder(g, {0, 1}));
    check("a vertex twice", false, isTopologicalOrder(g, {0, 1, 1}));
    check("no edges, any order", true, isTopologicalOrder({{}, {}}, {1, 0}));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList r = randDigraph();
        V o(r.size());
        for (size_t i = 0; i < o.size(); i++) o[i] = i;
        std::shuffle(o.begin(), o.end(), rng());
        check("graph " + show(r) + ", order " + show(o), validOrder(r, o), isTopologicalOrder(r, o));
    }
}

QUESTION("L34-M1", "topSort1 (slide 35)", "topSort1(") {
    for (auto& c : PDF_TS) check("graph " + show(c.g), c.order, topSort1(c.g));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randDigraph();
        check("graph " + show(g), refTopSort1(g), topSort1(g));
    }
}

QUESTION("L34-M2", "topSortKahn (any valid order)", "topSortKahn(") {
    auto one = [](const AdjList& g) {
        V got = topSortKahn(g);
        bool cyc = refTopSort1(g).empty() && !g.empty();
        if (cyc) check("graph " + show(g) + " has a cycle", V{}, got);
        else checkTrue("graph " + show(g), validOrder(g, got), "not a topological order: " + show(got));
    };
    for (auto& c : PDF_TS) one(c.g);
    for (int t = 0; t < RANDOM_CASES; t++) one(randDigraph());
}

QUESTION("L34-M3", "hasCycle (three colours)", "hasCycle(") {
    for (auto& c : PDF_TS) check("graph " + show(c.g), c.cycle, hasCycle(c.g));
    check("self-loop", true, hasCycle({{0}}));
    check("diamond 0->1->3, 0->2->3 (no cycle)", false, hasCycle({{1, 2}, {3}, {3}, {}}));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randDigraph();
        check("graph " + show(g), refTopSort1(g).empty(), hasCycle(g));
    }
}

OPTIONAL_QUESTION("L34-X", "findSmallestSetOfVertices (LC 1557)", "findSmallestSetOfVertices(") {
    check("LeetCode example 1", V{0, 3}, findSmallestSetOfVertices(6, {{0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}}));
    check("LeetCode example 2", V{0, 2, 3}, findSmallestSetOfVertices(5, {{0, 1}, {2, 1}, {3, 1}, {1, 4}, {2, 4}}));
}

OPTIONAL_QUESTION("L34-V", "reverseGraph", "reverseGraph(") {
    check("0->1, 0->2", AdjList{{}, {0}, {0}}, reverseGraph({{1, 2}, {}, {}}));
    check("2->0, 1->0", AdjList{{1, 2}, {}, {}}, reverseGraph({{}, {0}, {0}}));
}
