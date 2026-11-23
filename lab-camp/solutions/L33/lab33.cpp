// ============================================================================
//  Lab 33 · BFS and DFS · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L33
// ============================================================================
#include "lab33.h"

#include <queue>
#include <stack>

#include "todo.h"

using namespace std;

// L33-A · Example: 0-1, 0-2, 1-3, 2-3, start 0  =>  {0, 1, 2, 3}
// @begin bfsOrder
vector<int> bfsOrder(const AdjList& g, int start) {
    vector<bool> seen(g.size(), false);
    vector<int> order;
    queue<int> q;
    seen[start] = true;                     // mark when ENQUEUED: never twice in the queue
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : g[v])
            if (!seen[w]) {
                seen[w] = true;
                q.push(w);
            }
    }
    return order;
}
// @end bfsOrder

// L33-B · Example: the same graph  =>  {0, 1, 3, 2}
// @begin dfsVisit
void dfsVisit(const AdjList& g, int v, vector<bool>& seen, vector<int>& order) {
    seen[v] = true;
    order.push_back(v);
    for (int w : g[v])
        if (!seen[w]) dfsVisit(g, w, seen, order);
}
// @end dfsVisit

// @begin dfsOrder
vector<int> dfsOrder(const AdjList& g, int start) {
    vector<bool> seen(g.size(), false);
    vector<int> order;
    dfsVisit(g, start, seen, order);
    return order;
}
// @end dfsOrder

// L33-M1 · Example: the same graph  =>  {0, 1, 3, 2} (like dfsOrder)
// @begin dfsIterative
vector<int> dfsIterative(const AdjList& g, int start) {
    vector<bool> seen(g.size(), false);
    vector<int> order;
    stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        if (seen[v]) continue;              // pushed twice: the second copy is old
        seen[v] = true;
        order.push_back(v);
        for (int i = (int)g[v].size() - 1; i >= 0; i--)   // reverse: the smallest ends on top
            if (!seen[g[v][i]]) st.push(g[v][i]);
    }
    return order;
}
// @end dfsIterative

// L33-M2 · Example: path 0-1-2, vertex 3 alone, start 0  =>  {0, 1, 2, -1}
// @begin distances
vector<int> distances(const AdjList& g, int start) {
    vector<int> dist(g.size(), -1);         // -1 doubles as "not seen yet"
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : g[v])
            if (dist[w] == -1) {
                dist[w] = dist[v] + 1;      // BFS reaches w first along a shortest path
                q.push(w);
            }
    }
    return dist;
}
// @end distances

// L33-M3 · Example: 0-1, 2-3, 4  =>  3
// @begin countComponents
int countComponents(const AdjList& g) {
    vector<bool> seen(g.size(), false);
    int count = 0;
    for (int s = 0; s < (int)g.size(); s++) {
        if (seen[s]) continue;
        count++;                            // s starts a new component: flood it
        queue<int> q;
        seen[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g[v])
                if (!seen[w]) {
                    seen[w] = true;
                    q.push(w);
                }
        }
    }
    return count;
}
// @end countComponents

// L33-X · Example: n = 3, edges {{0,1},{1,2},{2,0}}, 0 -> 2  =>  true
// @begin validPath
bool validPath(int n, const vector<vector<int>>& edges, int source, int destination) {
    AdjList g(n);
    for (const auto& e : edges) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }
    for (int v : bfsOrder(g, source))
        if (v == destination) return true;
    return false;
}
// @end validPath

// L33-V · Example: 0->1, 2->0, start 0  =>  {0, 1}
// @begin reachable
vector<int> reachable(const AdjList& g, int start) {
    vector<bool> seen(g.size(), false);
    stack<int> st;
    seen[start] = true;
    st.push(start);
    while (!st.empty()) {
        int v = st.top();
        st.pop();
        for (int w : g[v])
            if (!seen[w]) {
                seen[w] = true;
                st.push(w);
            }
    }
    vector<int> out;
    for (int v = 0; v < (int)g.size(); v++)
        if (seen[v]) out.push_back(v);
    return out;
}
// @end reachable
