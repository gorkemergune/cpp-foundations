// ============================================================================
//  Lab 35 · Spanning trees and Prim · YOU WORK HERE
//  Test everything:      .\run.ps1 L35
// ============================================================================
#include "lab35.h"

#include <climits>
#include <cstdlib>
#include <queue>

#include "todo.h"

using namespace std;

// L35-A · Example: the square 0-1, 0-2, 1-3, 2-3 from 0  =>  {(0,1), (1,3), (3,2)}
void dfsTreeVisit(const AdjList& g, int v, vector<bool>& seen, Edges& out) {
    TODO();
}

Edges dfsTreeEdges(const AdjList& g, int start) {
    TODO();
}

// L35-B · Example: the square from 0  =>  {(0,1), (0,2), (1,3)}
Edges bfsTreeEdges(const AdjList& g, int start) {
    TODO();
}

// L35-M1 · Example: the lab graph from 0  =>  {(0,1), (1,2), (1,4), (0,3)}
Edges prim(const WMatrix& w, int start) {
    TODO();
}

// L35-M2 · Example: the lab graph  =>  16
int mstWeight(const WMatrix& w) {
    TODO();
}

// L35-X · Example: {{0,0},{2,2},{3,10},{5,2},{7,0}}  =>  20
int minCostConnectPoints(const vector<vector<int>>& points) {
    TODO();
}

// L35-V · Example: 0-1, 1-2  =>  true;  0-1, 1-2, 2-0  =>  false
bool isTree(const AdjList& g) {
    TODO();
}
