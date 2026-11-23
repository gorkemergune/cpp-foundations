// Lab 32 tests. The Labwork 6 graph is used for M1 and M2.
#include <set>

#include "lab32.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_MAT_Case { int n; Edges edges; bool directed; Matrix m; };
struct PDF_LIST_Case { int n; Edges edges; bool directed; AdjList adj; };
struct PDF_JUDGE_Case { int n; Edges trust; int ret; };
#include "pdf_cases.inc"

// Labwork 6, read from the figure: 0<->1, 0<->3, 1<->3, 1<->5, 2<->3, 2<->5, 3<->4
static const Matrix LW6 = {{0, 1, 0, 1, 0, 0}, {1, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 1},
                           {1, 1, 1, 0, 1, 0}, {0, 0, 0, 1, 0, 0}, {0, 1, 1, 0, 0, 0}};

static Edges randEdges(int n, int maxE) {
    Edges e;
    int k = randInt(0, maxE);
    for (int i = 0; i < k; i++) e.push_back({randInt(0, n - 1), randInt(0, n - 1)});
    return e;
}

QUESTION("L32-A", "toMatrix", "toMatrix(") {
    for (auto& c : PDF_MAT) check("n=" + std::to_string(c.n) + ", edges=" + show(c.edges) + (c.directed ? ", directed" : ", undirected"),
                                   c.m, toMatrix(c.n, c.edges, c.directed));
}

QUESTION("L32-B", "toList (sorted, no duplicates)", "toList(") {
    for (auto& c : PDF_LIST) check("n=" + std::to_string(c.n) + ", edges=" + show(c.edges) + (c.directed ? ", directed" : ", undirected"),
                                    c.adj, toList(c.n, c.edges, c.directed));
    for (int t = 0; t < RANDOM_CASES; t++) {
        int n = randInt(1, 6);
        Edges e = randEdges(n, 10);
        bool directed = randInt(0, 1);
        std::vector<std::set<int>> s(n);
        for (auto& p : e) {
            s[p.first].insert(p.second);
            if (!directed) s[p.second].insert(p.first);
        }
        AdjList want(n);
        for (int u = 0; u < n; u++) want[u] = V(s[u].begin(), s[u].end());
        check("random edges " + show(e), want, toList(n, e, directed));
    }
}

QUESTION("L32-M1", "indegree / outdegree (Labwork 6)", "degree(") {
    check("Labwork 6: in-degree of node 4", 1, indegree(LW6, 4));
    check("Labwork 6: out-degree of node 3", 4, outdegree(LW6, 3));
    Matrix d = {{0, 1, 1}, {0, 0, 1}, {0, 0, 0}};   // 0->1, 0->2, 1->2
    check("in-degree of 2", 2, indegree(d, 2));
    check("out-degree of 2", 0, outdegree(d, 2));
    check("in-degree of 0", 0, indegree(d, 0));
    check("out-degree of 0", 2, outdegree(d, 0));
}

QUESTION("L32-M2", "numEdges (Labwork 6)", "numEdges(") {
    check("Labwork 6 as a directed graph", 14, numEdges(LW6, true));
    check("Labwork 6 as an undirected graph (7 pairs)", 7, numEdges(LW6, false));
    check("self-loop, undirected", 2, numEdges({{1, 1}, {1, 0}}, false));
    check("empty graph", 0, numEdges({{0, 0}, {0, 0}}, true));
}

OPTIONAL_QUESTION("L32-X", "findJudge (LC 997)", "findJudge(") {
    for (auto& c : PDF_JUDGE) check("n=" + std::to_string(c.n) + ", trust=" + show(c.trust), c.ret, findJudge(c.n, c.trust));
}

OPTIONAL_QUESTION("L32-V", "matrixToList", "matrixToList(") {
    check("Labwork 6 graph", AdjList{{1, 3}, {0, 3, 5}, {3, 5}, {0, 1, 2, 4}, {3}, {1, 2}}, matrixToList(LW6));
    check("one vertex", AdjList{{}}, matrixToList({{0}}));
}
