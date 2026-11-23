// ============================================================================
//  Lab 32 · Adjacency matrix and list · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L32
// ============================================================================
#include "lab32.h"

#include <algorithm>

#include "todo.h"

using namespace std;

// L32-A · Example: n = 3, edges {(0,1), (1,2)}, undirected  =>  {{0,1,0},{1,0,1},{0,1,0}}
// @begin toMatrix
Matrix toMatrix(int n, const Edges& edges, bool directed) {
    Matrix m(n, vector<int>(n, 0));
    for (const auto& e : edges) {
        m[e.first][e.second] = 1;
        if (!directed) m[e.second][e.first] = 1;   // undirected = two directed edges
    }
    return m;
}
// @end toMatrix

// L32-B · Example: n = 3, edges {(1,0), (1,2), (0,1)}, directed  =>  {{1},{0,2},{}}
// @begin toList
AdjList toList(int n, const Edges& edges, bool directed) {
    AdjList adj(n);
    for (const auto& e : edges) {
        adj[e.first].push_back(e.second);
        if (!directed) adj[e.second].push_back(e.first);
    }
    for (auto& nb : adj) {
        sort(nb.begin(), nb.end());                     // a fixed order makes BFS/DFS repeatable
        nb.erase(unique(nb.begin(), nb.end()), nb.end());
    }
    return adj;
}
// @end toList

// L32-M1 · in-degree = column v, out-degree = row v
// @begin indegree
int indegree(const Matrix& m, int v) {
    int c = 0;
    for (int u = 0; u < (int)m.size(); u++) c += m[u][v];
    return c;
}
// @end indegree

// @begin outdegree
int outdegree(const Matrix& m, int v) {
    int c = 0;
    for (int x : m[v]) c += x;
    return c;
}
// @end outdegree

// L32-M2 · Example: the Labwork 6 graph (14 directed edges)  =>  14
// @begin numEdges
int numEdges(const Matrix& m, bool directed) {
    int ones = 0, loops = 0;
    for (int u = 0; u < (int)m.size(); u++) {
        for (int v = 0; v < (int)m.size(); v++) ones += m[u][v];
        loops += m[u][u];
    }
    if (directed) return ones;
    return (ones - loops) / 2 + loops;   // a pair is stored twice, a self-loop once
}
// @end numEdges

// L32-X · Example: n = 3, trust {(1,3), (2,3)}  =>  3
// @begin findJudge
int findJudge(int n, const Edges& trust) {
    vector<int> score(n + 1, 0);            // +1 for being trusted, -1 for trusting
    for (const auto& t : trust) {
        score[t.first]--;
        score[t.second]++;
    }
    for (int p = 1; p <= n; p++)
        if (score[p] == n - 1) return p;
    return -1;
}
// @end findJudge

// L32-V · Example: {{0,1},{1,0}}  =>  {{1},{0}}
// @begin matrixToList
AdjList matrixToList(const Matrix& m) {
    AdjList adj(m.size());
    for (int u = 0; u < (int)m.size(); u++)
        for (int v = 0; v < (int)m.size(); v++)
            if (m[u][v]) adj[u].push_back(v);   // v grows: already ascending
    return adj;
}
// @end matrixToList
