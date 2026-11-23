// ============================================================================
//  Lab 34 · Topological sort and cycles · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L34
// ============================================================================
#include "lab34.h"

#include <queue>

#include "todo.h"

using namespace std;

// L34-A · Example: 0->1, 0->2, 1->2  =>  {0, 1, 2}
// @begin inDegrees
vector<int> inDegrees(const AdjList& g) {
    vector<int> in(g.size(), 0);
    for (const auto& nb : g)
        for (int w : nb) in[w]++;
    return in;
}
// @end inDegrees

// L34-B · Example: 0->1, 1->2 and order {0, 2, 1}  =>  false (2 comes before 1)
// @begin isTopologicalOrder
bool isTopologicalOrder(const AdjList& g, const vector<int>& order) {
    int n = g.size();
    if ((int)order.size() != n) return false;
    vector<int> pos(n, -1);                     // pos[v] = place of v in the order
    for (int i = 0; i < n; i++) {
        int v = order[i];
        if (v < 0 || v >= n || pos[v] != -1) return false;   // outside or twice
        pos[v] = i;
    }
    for (int u = 0; u < n; u++)
        for (int w : g[u])
            if (pos[u] > pos[w]) return false;
    return true;
}
// @end isTopologicalOrder

// L34-M1 · Example: 0->1, 0->2, 1->3, 2->3, 3->4  =>  {0, 2, 1, 3, 4}
// @begin topSort1
vector<int> topSort1(const AdjList& g) {
    int n = g.size();
    vector<bool> removed(n, false);
    vector<int> successors(n);                  // successors that are still in the graph
    for (int v = 0; v < n; v++) successors[v] = g[v].size();
    vector<int> list;
    for (int step = 0; step < n; step++) {
        int v = 0;
        while (v < n && (removed[v] || successors[v] > 0)) v++;
        if (v == n) return {};                  // everybody left has a successor: a cycle
        list.insert(list.begin(), v);           // aList.add(1, v)
        removed[v] = true;
        for (int u = 0; u < n; u++)             // remove the edges INTO v
            for (int w : g[u])
                if (w == v) successors[u]--;
    }
    return list;
}
// @end topSort1

// L34-M2 · Example: the same graph  =>  {0, 1, 2, 3, 4} (any valid order)
// @begin topSortKahn
vector<int> topSortKahn(const AdjList& g) {
    vector<int> in = inDegrees(g);
    queue<int> q;
    for (int v = 0; v < (int)g.size(); v++)
        if (in[v] == 0) q.push(v);
    vector<int> order;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : g[v])
            if (--in[w] == 0) q.push(w);        // its last prerequisite just left
    }
    if (order.size() != g.size()) return {};    // vertices on a cycle never reach 0
    return order;
}
// @end topSortKahn

// L34-M3 · Example: 0->1, 1->2, 2->0  =>  true
// @begin cycleFrom
bool cycleFrom(const AdjList& g, int v, vector<int>& colour) {
    colour[v] = 1;                              // grey: on the current DFS path
    for (int w : g[v]) {
        if (colour[w] == 1) return true;        // an edge back into the path
        if (colour[w] == 0 && cycleFrom(g, w, colour)) return true;
    }
    colour[v] = 2;                              // black: finished, no cycle through v
    return false;
}
// @end cycleFrom

// @begin hasCycle
bool hasCycle(const AdjList& g) {
    vector<int> colour(g.size(), 0);            // white: not visited yet
    for (int v = 0; v < (int)g.size(); v++)
        if (colour[v] == 0 && cycleFrom(g, v, colour)) return true;
    return false;
}
// @end hasCycle

// L34-X · Example: n = 6, edges {{0,1},{0,2},{2,5},{3,4},{4,2}}  =>  {0, 3}
// @begin findSmallestSetOfVertices
vector<int> findSmallestSetOfVertices(int n, const vector<vector<int>>& edges) {
    vector<bool> hasIncoming(n, false);
    for (const auto& e : edges) hasIncoming[e[1]] = true;
    vector<int> out;
    for (int v = 0; v < n; v++)
        if (!hasIncoming[v]) out.push_back(v);
    return out;
}
// @end findSmallestSetOfVertices

// L34-V · Example: 0->1, 0->2  =>  {{}, {0}, {0}}
// @begin reverseGraph
AdjList reverseGraph(const AdjList& g) {
    AdjList r(g.size());
    for (int u = 0; u < (int)g.size(); u++)     // u grows: every r[w] stays ascending
        for (int w : g[u]) r[w].push_back(u);
    return r;
}
// @end reverseGraph
