// ============================================================================
//  Lab 32 · Adjacency matrix and list · YOU WORK HERE
//  Test everything:      .\run.ps1 L32
// ============================================================================
#include "lab32.h"

#include <algorithm>

#include "todo.h"

using namespace std;

// L32-A · Example: n = 3, edges {(0,1), (1,2)}, undirected  =>  {{0,1,0},{1,0,1},{0,1,0}}
Matrix toMatrix(int n, const Edges& edges, bool directed) {
    TODO();
}

// L32-B · Example: n = 3, edges {(1,0), (1,2), (0,1)}, directed  =>  {{1},{0,2},{}}
AdjList toList(int n, const Edges& edges, bool directed) {
    TODO();
}

// L32-M1 · in-degree = column v, out-degree = row v
int indegree(const Matrix& m, int v) {
    TODO();
}

int outdegree(const Matrix& m, int v) {
    TODO();
}

// L32-M2 · Example: the Labwork 6 graph (14 directed edges)  =>  14
int numEdges(const Matrix& m, bool directed) {
    TODO();
}

// L32-X · Example: n = 3, trust {(1,3), (2,3)}  =>  3
int findJudge(int n, const Edges& trust) {
    TODO();
}

// L32-V · Example: {{0,1},{1,0}}  =>  {{1},{0}}
AdjList matrixToList(const Matrix& m) {
    TODO();
}
