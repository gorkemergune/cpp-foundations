// ============================================================================
//  Lab 34 · Topological sorting and cycles in directed graphs        DO NOT EDIT
//  Directed graph as an adjacency list (vertices 0 .. n-1, Lab 32).
// ============================================================================
#pragma once

#include <vector>

using AdjList = std::vector<std::vector<int>>;

// L34-A · Warm-up · in-degree of every vertex.
std::vector<int> inDegrees(const AdjList& g);

// L34-B · Warm-up · is `order` a topological order of g? (every vertex exactly once and
// for every edge u -> v, u comes before v)
bool isTopologicalOrder(const AdjList& g, const std::vector<int>& order);

// L34-M1 · Main · the slides' topSort1 (slide 35): n times, take a vertex with NO successors
// (among the vertices not removed yet; the smallest such vertex), insert it at the FRONT of
// the result and remove it. No such vertex: the graph has a cycle -> return {}.
std::vector<int> topSort1(const AdjList& g);

// L34-M2 · Main · Kahn's algorithm with std::queue: start with the in-degree-0 vertices,
// remove them and lower the in-degrees of their successors. Any valid order is accepted;
// a cycle -> return {}.
std::vector<int> topSortKahn(const AdjList& g);

// L34-M3 · Main · does the directed graph have a cycle? DFS with three colours.
bool hasCycle(const AdjList& g);

// L34-X · Optional · LeetCode 1557: the smallest set of vertices from which every vertex is
// reachable (= the vertices with in-degree 0), ascending. edges are {from, to}.
std::vector<int> findSmallestSetOfVertices(int n, const std::vector<std::vector<int>>& edges);

// L34-V · Optional · memory variant: the reverse graph (every edge turned around),
// neighbour lists ascending.
AdjList reverseGraph(const AdjList& g);
