// ============================================================================
//  Lab 35 · Spanning trees and Prim · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L35
// ============================================================================
#include "lab35.h"

#include <climits>
#include <cstdlib>
#include <queue>

#include "todo.h"

using namespace std;

// L35-A · Example: the square 0-1, 0-2, 1-3, 2-3 from 0  =>  {(0,1), (1,3), (3,2)}
// @begin dfsTreeVisit
void dfsTreeVisit(const AdjList& g, int v, vector<bool>& seen, Edges& out) {
    seen[v] = true;
    for (int w : g[v])
        if (!seen[w]) {
            out.push_back({v, w});          // the edge used to reach w for the first time
            dfsTreeVisit(g, w, seen, out);
        }
}
// @end dfsTreeVisit

// @begin dfsTreeEdges
Edges dfsTreeEdges(const AdjList& g, int start) {
    vector<bool> seen(g.size(), false);
    Edges out;
    dfsTreeVisit(g, start, seen, out);
    return out;
}
// @end dfsTreeEdges

// L35-B · Example: the square from 0  =>  {(0,1), (0,2), (1,3)}
// @begin bfsTreeEdges
Edges bfsTreeEdges(const AdjList& g, int start) {
    vector<bool> seen(g.size(), false);
    Edges out;
    queue<int> q;
    seen[start] = true;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : g[v])
            if (!seen[w]) {
                seen[w] = true;
                out.push_back({v, w});
                q.push(w);
            }
    }
    return out;
}
// @end bfsTreeEdges

// L35-M1 · Example: the lab graph from 0  =>  {(0,1), (1,2), (1,4), (0,3)}
// @begin prim
Edges prim(const WMatrix& w, int start) {
    int n = w.size();
    vector<bool> inTree(n, false);
    vector<int> best(n, INT_MAX);           // cheapest edge from the tree to v so far
    vector<int> from(n, -1);                // ... and its tree end
    Edges out;
    inTree[start] = true;
    for (int v = 0; v < n; v++)
        if (w[start][v] > 0) { best[v] = w[start][v]; from[v] = start; }
    for (int step = 1; step < n; step++) {
        int v = -1;
        for (int x = 0; x < n; x++)          // the cheapest vertex outside the tree
            if (!inTree[x] && from[x] != -1 && (v == -1 || best[x] < best[v])) v = x;
        if (v == -1) return {};             // nothing reachable is left: not connected
        inTree[v] = true;
        out.push_back({from[v], v});
        for (int x = 0; x < n; x++)          // v may offer cheaper edges to the others
            if (!inTree[x] && w[v][x] > 0 && w[v][x] < best[x]) { best[x] = w[v][x]; from[x] = v; }
    }
    return out;
}
// @end prim

// L35-M2 · Example: the lab graph  =>  16
// @begin mstWeight
int mstWeight(const WMatrix& w) {
    if (w.empty()) return 0;
    Edges tree = prim(w, 0);
    if ((int)tree.size() != (int)w.size() - 1) return -1;
    int total = 0;
    for (const auto& e : tree) total += w[e.first][e.second];
    return total;
}
// @end mstWeight

// L35-X · Example: {{0,0},{2,2},{3,10},{5,2},{7,0}}  =>  20
// @begin minCostConnectPoints
int minCostConnectPoints(const vector<vector<int>>& points) {
    int n = points.size();
    vector<bool> inTree(n, false);
    vector<int> best(n, INT_MAX);
    best[0] = 0;
    int total = 0;
    for (int step = 0; step < n; step++) {   // Prim on the complete graph, no matrix needed
        int v = -1;
        for (int x = 0; x < n; x++)
            if (!inTree[x] && (v == -1 || best[x] < best[v])) v = x;
        inTree[v] = true;
        total += best[v];
        for (int x = 0; x < n; x++) {
            int d = abs(points[v][0] - points[x][0]) + abs(points[v][1] - points[x][1]);
            if (!inTree[x] && d < best[x]) best[x] = d;
        }
    }
    return total;
}
// @end minCostConnectPoints

// L35-V · Example: 0-1, 1-2  =>  true;  0-1, 1-2, 2-0  =>  false
// @begin isTree
bool isTree(const AdjList& g) {
    int n = g.size(), ends = 0;
    for (const auto& nb : g) ends += nb.size();
    if (ends / 2 != n - 1) return false;    // every edge is listed twice
    if (n == 0) return true;
    vector<bool> seen(n, false);
    queue<int> q;
    seen[0] = true;
    q.push(0);
    int count = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int x : g[v])
            if (!seen[x]) { seen[x] = true; count++; q.push(x); }
    }
    return count == n;
}
// @end isTree
