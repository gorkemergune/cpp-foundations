// ============================================================================
//  Lab 46 · Priority queues at work · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L46
// ============================================================================
#include "lab46.h"

#include <algorithm>
#include <functional>
#include <utility>

#include "todo.h"

using namespace std;

template <class T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;   // top = the smallest

// L46-A · Example: enqueue a 1, b 5, c 5  =>  dequeue b, c, a
// @begin enqueue
void StablePQ::enqueue(const string& element, int priority) {
    pq.push({priority, -arrivals, element});   // earlier arrival = larger second field
    arrivals++;
}
// @end enqueue

// @begin dequeue
bool StablePQ::dequeue(string& out) {
    if (pq.empty()) return false;
    out = get<2>(pq.top());
    pq.pop();
    return true;
}
// @end dequeue

// @begin size
int StablePQ::size() const {
    return pq.size();
}
// @end size

// L46-M1 · Example: 0->1 (4), 0->2 (1), 2->1 (2), 1->3 (1)  =>  {0, 3, 1, 4}
// @begin dijkstra
vector<long long> dijkstra(int n, const WEdges& edges, int src) {
    vector<vector<pair<int, int>>> adj(n);          // u -> (v, w)
    for (const auto& e : edges) adj[e[0]].push_back({e[1], e[2]});
    vector<long long> dist(n, -1);
    MinHeap<pair<long long, int>> pq;                // (distance so far, vertex)
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] != -1) continue;                // an old, longer entry: skip it
        dist[u] = d;                                // the first time u comes out is the best
        for (auto [v, w] : adj[u])
            if (dist[v] == -1) pq.push({d + w, v});
    }
    return dist;
}
// @end dijkstra

// L46-M2 · Example: the Lab 35 graph  =>  16
// @begin primHeap
long long primHeap(int n, const WEdges& edges) {
    if (n <= 1) return 0;
    vector<vector<pair<int, int>>> adj(n);
    for (const auto& e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
        adj[e[1]].push_back({e[0], e[2]});
    }
    vector<bool> inTree(n, false);
    MinHeap<pair<int, int>> pq;                      // (edge weight, vertex)
    pq.push({0, 0});
    long long total = 0;
    int added = 0;
    while (!pq.empty() && added < n) {
        auto [w, v] = pq.top();
        pq.pop();
        if (inTree[v]) continue;                    // a cheaper edge already brought v in
        inTree[v] = true;
        total += w;
        added++;
        for (auto [x, wx] : adj[v])
            if (!inTree[x]) pq.push({wx, x});
    }
    return added == n ? total : -1;
}
// @end primHeap

// L46-M3 · Example: {{1,2},{2,4},{3,2},{4,1}}  =>  {0, 2, 3, 1}
// @begin getOrder
vector<int> getOrder(const vector<vector<int>>& tasks) {
    int n = tasks.size();
    vector<int> byTime(n);
    for (int i = 0; i < n; i++) byTime[i] = i;
    sort(byTime.begin(), byTime.end(), [&](int a, int b) { return tasks[a][0] < tasks[b][0]; });
    MinHeap<pair<int, int>> ready;                   // (processing time, index)
    vector<int> order;
    long long time = 0;
    int next = 0;                                   // the next task to arrive, in byTime
    while ((int)order.size() < n) {
        if (ready.empty() && time < tasks[byTime[next]][0])
            time = tasks[byTime[next]][0];          // idle: jump to the next arrival
        while (next < n && tasks[byTime[next]][0] <= time) {
            ready.push({tasks[byTime[next]][1], byTime[next]});
            next++;
        }
        auto [proc, i] = ready.top();
        ready.pop();
        order.push_back(i);
        time += proc;
    }
    return order;
}
// @end getOrder

// L46-X · Example: {4,2,7,6,9,14,12}, bricks 5, ladders 1  =>  4
// @begin furthestBuilding
int furthestBuilding(const vector<int>& heights, int bricks, int ladders) {
    MinHeap<int> climbs;                             // the climbs that use a ladder
    for (int i = 0; i + 1 < (int)heights.size(); i++) {
        int d = heights[i + 1] - heights[i];
        if (d <= 0) continue;
        climbs.push(d);
        if ((int)climbs.size() > ladders) {         // too many: pay the SMALLEST one in bricks
            bricks -= climbs.top();
            climbs.pop();
            if (bricks < 0) return i;
        }
    }
    return heights.size() - 1;
}
// @end furthestBuilding

// L46-V · Example: {2, 7, 4, 1, 8, 1}  =>  1
// @begin lastStoneWeightPQ
int lastStoneWeightPQ(const vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    while (pq.size() > 1) {
        int y = pq.top();
        pq.pop();
        int x = pq.top();
        pq.pop();
        if (y != x) pq.push(y - x);
    }
    return pq.empty() ? 0 : pq.top();
}
// @end lastStoneWeightPQ
