// ============================================================================
//  Lab 33 · Breadth-first and depth-first traversal                  DO NOT EDIT
//  The graph is an adjacency list (vertices 0 .. n-1, neighbours ascending, Lab 32).
//  "Visit neighbours in list order" makes every traversal order unique.
// ============================================================================
#pragma once

#include <vector>

using AdjList = std::vector<std::vector<int>>;

// L33-A · Warm-up · the order in which BFS from `start` visits the vertices (std::queue).
std::vector<int> bfsOrder(const AdjList& g, int start);

// L33-B · Warm-up · the order of the RECURSIVE depth-first traversal from `start`
// (slide 27: visit v, then recurse into every unvisited neighbour in list order).
std::vector<int> dfsOrder(const AdjList& g, int start);

// L33-M1 · Main · the ITERATIVE DFS of slide 28 with std::stack that gives the SAME order
// as dfsOrder: a vertex is marked when it is popped, neighbours are pushed in REVERSE.
std::vector<int> dfsIterative(const AdjList& g, int start);

// L33-M2 · Main · fewest edges from `start` to every vertex; -1 if it cannot be reached.
std::vector<int> distances(const AdjList& g, int start);

// L33-M3 · Main · the number of connected components of an UNDIRECTED graph.
int countComponents(const AdjList& g);

// L33-X · Optional · LeetCode 1971: is there a path from source to destination?
// n vertices, undirected edges given as {u, v} pairs.
bool validPath(int n, const std::vector<std::vector<int>>& edges, int source, int destination);

// L33-V · Optional · memory variant: the vertices reachable from start, ascending.
std::vector<int> reachable(const AdjList& g, int start);
