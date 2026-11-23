// ============================================================================
//  Lab 32 · Adjacency matrix and adjacency list                     DO NOT EDIT
//  Vertices are 0 .. n-1. An edge (u, v) goes from u to v; in an undirected graph it
//  also goes from v to u.
// ============================================================================
#pragma once

#include <utility>
#include <vector>

using Matrix = std::vector<std::vector<int>>;   // m[u][v] == 1  <=>  edge u -> v
using AdjList = std::vector<std::vector<int>>;  // list[u] = neighbours of u, ascending
using Edges = std::vector<std::pair<int, int>>;

// L32-A · Warm-up · n x n adjacency matrix from an edge list.
Matrix toMatrix(int n, const Edges& edges, bool directed);

// L32-B · Warm-up · adjacency list from an edge list; every list sorted ascending,
// no duplicates (an edge given twice appears once).
AdjList toList(int n, const Edges& edges, bool directed);

// L32-M1 · Main (Labwork 6) · in-degree and out-degree of vertex v in a directed graph.
int indegree(const Matrix& m, int v);
int outdegree(const Matrix& m, int v);

// L32-M2 · Main (Labwork 6) · number of edges. directed: every 1 counts; undirected
// (the matrix is symmetric): every pair counts once, a self-loop once.
int numEdges(const Matrix& m, bool directed);

// L32-X · Optional · LeetCode 997: the town judge (trusted by everybody else, trusts nobody),
// people are 1..n; -1 if there is none.
int findJudge(int n, const Edges& trust);

// L32-V · Optional · memory variant: the adjacency list of a matrix (ascending neighbours).
AdjList matrixToList(const Matrix& m);
