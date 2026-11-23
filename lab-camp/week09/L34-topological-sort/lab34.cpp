// ============================================================================
//  Lab 34 · Topological sort and cycles · YOU WORK HERE
//  Test everything:      .\run.ps1 L34
// ============================================================================
#include "lab34.h"

#include <queue>

#include "todo.h"

using namespace std;

// L34-A · Example: 0->1, 0->2, 1->2  =>  {0, 1, 2}
vector<int> inDegrees(const AdjList& g) {
    TODO();
}

// L34-B · Example: 0->1, 1->2 and order {0, 2, 1}  =>  false (2 comes before 1)
bool isTopologicalOrder(const AdjList& g, const vector<int>& order) {
    TODO();
}

// L34-M1 · Example: 0->1, 0->2, 1->3, 2->3, 3->4  =>  {0, 2, 1, 3, 4}
vector<int> topSort1(const AdjList& g) {
    TODO();
}

// L34-M2 · Example: the same graph  =>  {0, 1, 2, 3, 4} (any valid order)
vector<int> topSortKahn(const AdjList& g) {
    TODO();
}

// L34-M3 · Example: 0->1, 1->2, 2->0  =>  true
bool cycleFrom(const AdjList& g, int v, vector<int>& colour) {
    TODO();
}

bool hasCycle(const AdjList& g) {
    TODO();
}

// L34-X · Example: n = 6, edges {{0,1},{0,2},{2,5},{3,4},{4,2}}  =>  {0, 3}
vector<int> findSmallestSetOfVertices(int n, const vector<vector<int>>& edges) {
    TODO();
}

// L34-V · Example: 0->1, 0->2  =>  {{}, {0}, {0}}
AdjList reverseGraph(const AdjList& g) {
    TODO();
}
