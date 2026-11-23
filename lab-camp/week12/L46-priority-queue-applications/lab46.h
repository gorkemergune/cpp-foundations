// ============================================================================
//  Lab 46 · Priority queues at work                                   DO NOT EDIT
//  Labwork 5's queue on a heap, Dijkstra, Prim with a heap, a CPU scheduler.
// ============================================================================
#pragma once

#include <queue>
#include <string>
#include <tuple>
#include <vector>

// L46-A · Warm-up (Labwork 5) · enqueue(element, priority): a HIGHER number is served first;
// equal priorities are served first-in-first-out. dequeue(out): false if empty.
class StablePQ {
public:
    void enqueue(const std::string& element, int priority);
    bool dequeue(std::string& out);
    int size() const;
private:
    // (priority, -arrival number, element): the largest tuple is on top
    std::priority_queue<std::tuple<int, long long, std::string>> pq;
    long long arrivals = 0;
};

// Weighted edges {u, v, w} with w >= 0; vertices 0 .. n-1.
using WEdges = std::vector<std::vector<int>>;

// L46-M1 · Main · Dijkstra: the cheapest total weight from src to every vertex of the
// DIRECTED graph (edge u -> v); -1 if unreachable. O((V + E) log V) with a min-heap.
std::vector<long long> dijkstra(int n, const WEdges& edges, int src);

// L46-M2 · Main · Prim with a min-heap (Lab 35 used O(V^2)): the weight of a minimum
// spanning tree of the UNDIRECTED graph; -1 if it is not connected; 0 for n <= 1.
long long primHeap(int n, const WEdges& edges);

// L46-M3 · Main · LeetCode 1834: tasks[i] = {enqueueTime, processingTime}. A single CPU
// takes, whenever it is idle, the available task with the shortest processing time (ties:
// smaller index); if none is available it waits for the next one. The order of indexes.
std::vector<int> getOrder(const std::vector<std::vector<int>>& tasks);

// L46-X · Optional · LeetCode 1642: climbing from building i to i+1 costs
// heights[i+1] - heights[i] bricks if positive, or one ladder. The furthest index reachable.
int furthestBuilding(const std::vector<int>& heights, int bricks, int ladders);

// L46-V · Optional · memory variant: LeetCode 1046 with std::priority_queue.
int lastStoneWeightPQ(const std::vector<int>& stones);
