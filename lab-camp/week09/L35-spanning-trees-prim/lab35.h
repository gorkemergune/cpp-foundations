// ============================================================================
//  Lab 35 · Spanning trees and Prim's algorithm                     DO NOT EDIT
//  Undirected graphs. AdjList as in Lab 32; a weighted graph is a matrix where
//  w[u][v] == w[v][u] > 0 is the weight of edge u-v and 0 means "no edge".
// ============================================================================
#pragma once

#include <utility>
#include <vector>

using AdjList = std::vector<std::vector<int>>;
using WMatrix = std::vector<std::vector<int>>;
using Edges = std::vector<std::pair<int, int>>;   // (parent / tree vertex, new vertex)

// L35-A · Warm-up · the edges of the DFS spanning tree (recursive DFS from start,
// neighbours in list order), in the order they are discovered.
Edges dfsTreeEdges(const AdjList& g, int start);

// L35-B · Warm-up · the same for the BFS spanning tree.
Edges bfsTreeEdges(const AdjList& g, int start);

// L35-M1 · Main · Prim (slides 40-45): start with {start}; n-1 times add the CHEAPEST edge
// (u, v) with u in the tree and v outside. Return the edges in the order they are added.
// The graph is not connected: return {}.
Edges prim(const WMatrix& w, int start);

// L35-M2 · Main · the total weight of a minimum spanning tree; -1 if not connected.
int mstWeight(const WMatrix& w);

// L35-X · Optional · LeetCode 1584: connect all points with the minimum total
// Manhattan distance |x1 - x2| + |y1 - y2|.
int minCostConnectPoints(const std::vector<std::vector<int>>& points);

// L35-V · Optional · memory variant: is the undirected graph a tree?
// (connected and exactly n - 1 edges; g lists every edge in both directions)
bool isTree(const AdjList& g);
