// Lab 33 tests. Random graphs are checked against small reference traversals.
#include <algorithm>
#include <functional>
#include <numeric>

#include "lab33.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_TR_Case { AdjList g; int start; V bfs; V dfs; };
struct PDF_DIST_Case { AdjList g; int start; V dist; };
struct PDF_CC_Case { AdjList g; int count; };
#include "pdf_cases.inc"

static AdjList randGraph(bool directed, int maxN = 8) {
    int n = randInt(1, maxN);
    AdjList g(n);
    int e = randInt(0, n * 2);
    for (int i = 0; i < e; i++) {
        int u = randInt(0, n - 1), v = randInt(0, n - 1);
        if (u == v) continue;
        g[u].push_back(v);
        if (!directed) g[v].push_back(u);
    }
    for (auto& nb : g) {
        std::sort(nb.begin(), nb.end());
        nb.erase(std::unique(nb.begin(), nb.end()), nb.end());
    }
    return g;
}
static V refBfs(const AdjList& g, int s, V* dist = nullptr) {
    V d(g.size(), -1), order{s};
    d[s] = 0;
    for (size_t i = 0; i < order.size(); i++)
        for (int w : g[order[i]])
            if (d[w] < 0) { d[w] = d[order[i]] + 1; order.push_back(w); }
    if (dist) *dist = d;
    return order;
}
static V refDfs(const AdjList& g, int s) {
    std::vector<bool> seen(g.size());
    V order;
    std::function<void(int)> go = [&](int v) {
        seen[v] = true;
        order.push_back(v);
        for (int w : g[v]) if (!seen[w]) go(w);
    };
    go(s);
    return order;
}

QUESTION("L33-A", "bfsOrder", "bfsOrder(") {
    for (auto& c : PDF_TR) check("graph " + show(c.g) + ", start " + std::to_string(c.start), c.bfs, bfsOrder(c.g, c.start));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randGraph(randInt(0, 1));
        int s = randInt(0, (int)g.size() - 1);
        check("graph " + show(g) + ", start " + std::to_string(s), refBfs(g, s), bfsOrder(g, s));
    }
}

QUESTION("L33-B", "dfsOrder (recursive)", "dfsOrder(") {
    for (auto& c : PDF_TR) check("graph " + show(c.g) + ", start " + std::to_string(c.start), c.dfs, dfsOrder(c.g, c.start));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randGraph(randInt(0, 1));
        int s = randInt(0, (int)g.size() - 1);
        check("graph " + show(g) + ", start " + std::to_string(s), refDfs(g, s), dfsOrder(g, s));
    }
}

QUESTION("L33-M1", "dfsIterative (same order with a stack)", "dfsIterative(") {
    for (auto& c : PDF_TR) check("graph " + show(c.g) + ", start " + std::to_string(c.start), c.dfs, dfsIterative(c.g, c.start));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randGraph(randInt(0, 1));
        int s = randInt(0, (int)g.size() - 1);
        check("graph " + show(g) + ", start " + std::to_string(s), refDfs(g, s), dfsIterative(g, s));
    }
}

QUESTION("L33-M2", "distances (BFS levels)", "distances(") {
    for (auto& c : PDF_DIST) check("graph " + show(c.g) + ", start " + std::to_string(c.start), c.dist, distances(c.g, c.start));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randGraph(randInt(0, 1));
        int s = randInt(0, (int)g.size() - 1);
        V d;
        refBfs(g, s, &d);
        check("graph " + show(g) + ", start " + std::to_string(s), d, distances(g, s));
    }
}

QUESTION("L33-M3", "countComponents", "countComponents(") {
    for (auto& c : PDF_CC) check("graph " + show(c.g), c.count, countComponents(c.g));
    for (int t = 0; t < RANDOM_CASES; t++) {
        AdjList g = randGraph(false);
        V parent(g.size());
        std::iota(parent.begin(), parent.end(), 0);
        std::function<int(int)> find = [&](int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); };
        int comps = (int)g.size();
        for (int u = 0; u < (int)g.size(); u++)
            for (int w : g[u])
                if (find(u) != find(w)) { parent[find(u)] = find(w); comps--; }
        check("graph " + show(g), comps, countComponents(g));
    }
}

OPTIONAL_QUESTION("L33-X", "validPath (LC 1971)", "validPath(") {
    check("triangle, 0 -> 2", true, validPath(3, {{0, 1}, {1, 2}, {2, 0}}, 0, 2));
    check("two islands, 0 -> 5", false, validPath(6, {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}}, 0, 5));
    check("source == destination", true, validPath(1, {}, 0, 0));
}

OPTIONAL_QUESTION("L33-V", "reachable", "reachable(") {
    check("0->1, 2->0, start 0", V{0, 1}, reachable({{1}, {}, {0}}, 0));
    check("0->1, 2->0, start 2", V{0, 1, 2}, reachable({{1}, {}, {0}}, 2));
}
