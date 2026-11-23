// Challenge 09 tests.
#include <functional>

#include "challenge09.h"
#include "test.h"

using namespace lab;
using M = std::vector<std::vector<int>>;

struct PDF_CF_Case { int n; M pre; bool ret; };
struct PDF_OR_Case { M grid; int ret; };
struct PDF_BP_Case { M graph; bool ret; };
#include "pdf_cases.inc"

static bool slowCanFinish(int n, const M& pre) {      // cycle test by DFS colours
    M g(n);
    for (auto& p : pre) g[p[1]].push_back(p[0]);
    std::vector<int> col(n);
    std::function<bool(int)> cyc = [&](int v) {
        col[v] = 1;
        for (int w : g[v]) if (col[w] == 1 || (col[w] == 0 && cyc(w))) return true;
        col[v] = 2;
        return false;
    };
    for (int v = 0; v < n; v++) if (!col[v] && cyc(v)) return false;
    return true;
}
static int slowOranges(M g) {                          // simulate minute by minute
    for (int m = 0;; m++) {
        bool fresh = false, changed = false;
        M next = g;
        for (size_t r = 0; r < g.size(); r++)
            for (size_t c = 0; c < g[r].size(); c++) {
                if (g[r][c] != 1) continue;
                fresh = true;
                bool near = (r > 0 && g[r - 1][c] == 2) || (r + 1 < g.size() && g[r + 1][c] == 2) ||
                            (c > 0 && g[r][c - 1] == 2) || (c + 1 < g[r].size() && g[r][c + 1] == 2);
                if (near) { next[r][c] = 2; changed = true; }
            }
        if (!fresh) return m;
        if (!changed) return -1;
        g = next;
    }
}
static bool slowBipartite(const M& g) {                // try every 2-colouring (n <= 10)
    int n = g.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int u = 0; u < n && ok; u++)
            for (int w : g[u]) if (((mask >> u) & 1) == ((mask >> w) & 1)) ok = false;
        if (ok) return true;
    }
    return false;
}

QUESTION("C09-A", "canFinish (LC 207)", "canFinish(") {
    for (auto& c : PDF_CF) check("n=" + std::to_string(c.n) + ", prerequisites=" + show(c.pre), c.ret, canFinish(c.n, c.pre));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(1, 7);
        M pre;
        for (int k = randInt(0, n + 2); k > 0; k--) pre.push_back({randInt(0, n - 1), randInt(0, n - 1)});
        check("n=" + std::to_string(n) + ", prerequisites=" + show(pre), slowCanFinish(n, pre), canFinish(n, pre));
    }
}

QUESTION("C09-B", "orangesRotting (LC 994)", "orangesRotting(") {
    for (auto& c : PDF_OR) check("grid " + show(c.grid), c.ret, orangesRotting(c.grid));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int r = randInt(1, 4), cc = randInt(1, 4);
        M g(r, std::vector<int>(cc));
        for (auto& row : g) for (int& x : row) x = randInt(0, 2);
        check("grid " + show(g), slowOranges(g), orangesRotting(g));
    }
}

QUESTION("C09-C", "isBipartite (LC 785)", "isBipartite(") {
    for (auto& c : PDF_BP) check("graph " + show(c.graph), c.ret, isBipartite(c.graph));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(1, 8);
        M g(n);
        for (int k = randInt(0, n + 2); k > 0; k--) {
            int u = randInt(0, n - 1), v = randInt(0, n - 1);
            if (u == v || std::find(g[u].begin(), g[u].end(), v) != g[u].end()) continue;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        check("graph " + show(g), slowBipartite(g), isBipartite(g));
    }
}
