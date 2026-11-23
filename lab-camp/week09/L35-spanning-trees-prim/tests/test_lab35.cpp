// Lab 35 tests. Random weighted graphs use distinct weights, so the Prim order is unique.
#include <algorithm>
#include <functional>
#include <numeric>

#include "lab35.h"
#include "test.h"

using namespace lab;

struct PDF_SP_Case { AdjList g; int start; Edges dfs; Edges bfs; };
struct PDF_PRIM_Case { WMatrix w; int start; Edges tree; int weight; };
#include "pdf_cases.inc"

static WMatrix randWeighted() {
    int n = randInt(1, 7);
    WMatrix w(n, std::vector<int>(n, 0));
    std::vector<std::pair<int, int>> pairs;
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++)
            if (randInt(0, 99) < 55) pairs.push_back({u, v});
    std::vector<int> weights(pairs.size());
    std::iota(weights.begin(), weights.end(), 1);
    std::shuffle(weights.begin(), weights.end(), rng());
    for (size_t i = 0; i < pairs.size(); i++)
        w[pairs[i].first][pairs[i].second] = w[pairs[i].second][pairs[i].first] = weights[i];
    return w;
}
static Edges refPrim(const WMatrix& w, int s) {        // brute force: scan every (u, v)
    int n = w.size();
    std::vector<bool> in(n);
    in[s] = true;
    Edges out;
    for (int step = 1; step < n; step++) {
        int bu = -1, bv = -1;
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (in[u] && !in[v] && w[u][v] > 0 && (bu < 0 || w[u][v] < w[bu][bv])) bu = u, bv = v;
        if (bu < 0) return {};
        in[bv] = true;
        out.push_back({bu, bv});
    }
    return out;
}
static int refKruskal(const WMatrix& w) {
    int n = w.size(), total = 0, used = 0;
    std::vector<std::tuple<int, int, int>> e;
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++)
            if (w[u][v]) e.push_back({w[u][v], u, v});
    std::sort(e.begin(), e.end());
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
    for (auto& [c, u, v] : e)
        if (f(u) != f(v)) { p[f(u)] = f(v); total += c; used++; }
    return used == n - 1 ? total : -1;
}

QUESTION("L35-A", "dfsTreeEdges", "dfsTreeEdges(") {
    for (auto& c : PDF_SP) check("graph " + show(c.g) + ", start " + std::to_string(c.start), c.dfs, dfsTreeEdges(c.g, c.start));
}

QUESTION("L35-B", "bfsTreeEdges", "bfsTreeEdges(") {
    for (auto& c : PDF_SP) check("graph " + show(c.g) + ", start " + std::to_string(c.start), c.bfs, bfsTreeEdges(c.g, c.start));
}

QUESTION("L35-M1", "prim (slides 40-45)", "prim(") {
    for (auto& c : PDF_PRIM) check("matrix " + show(c.w) + ", start " + std::to_string(c.start), c.tree, prim(c.w, c.start));
    for (int t = 0; t < RANDOM_CASES; t++) {
        WMatrix w = randWeighted();
        int s = randInt(0, (int)w.size() - 1);
        check("matrix " + show(w) + ", start " + std::to_string(s), refPrim(w, s), prim(w, s));
    }
}

QUESTION("L35-M2", "mstWeight", "mstWeight(") {
    for (auto& c : PDF_PRIM) check("matrix " + show(c.w), c.weight, mstWeight(c.w));
    for (int t = 0; t < RANDOM_CASES; t++) {
        WMatrix w = randWeighted();
        check("matrix " + show(w), refKruskal(w), mstWeight(w));
    }
}

OPTIONAL_QUESTION("L35-X", "minCostConnectPoints (LC 1584)", "minCostConnectPoints(") {
    check("LeetCode example 1", 20, minCostConnectPoints({{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}}));
    check("LeetCode example 2", 18, minCostConnectPoints({{3, 12}, {-2, 5}, {-4, 1}}));
    check("one point", 0, minCostConnectPoints({{5, 5}}));
}

OPTIONAL_QUESTION("L35-V", "isTree", "isTree(") {
    check("path 0-1-2", true, isTree({{1}, {0, 2}, {1}}));
    check("triangle", false, isTree({{1, 2}, {0, 2}, {0, 1}}));
    check("two edges, but 0-1 twice and 2 alone", false, isTree({{1, 1}, {0, 0}, {}}));
    check("one vertex", true, isTree({{}}));
}
