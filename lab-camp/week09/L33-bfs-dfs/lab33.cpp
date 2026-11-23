// ============================================================================
//  Lab 33 · BFS and DFS · YOU WORK HERE
//  Test everything:      .\run.ps1 L33
// ============================================================================
#include "lab33.h"

#include <queue>
#include <stack>

#include "todo.h"

using namespace std;

// L33-A · Example: 0-1, 0-2, 1-3, 2-3, start 0  =>  {0, 1, 2, 3}
vector<int> bfsOrder(const AdjList& g, int start) {
    TODO();
}

// L33-B · Example: the same graph  =>  {0, 1, 3, 2}
void dfsVisit(const AdjList& g, int v, vector<bool>& seen, vector<int>& order) {
    TODO();
}

vector<int> dfsOrder(const AdjList& g, int start) {
    TODO();
}

// L33-M1 · Example: the same graph  =>  {0, 1, 3, 2} (like dfsOrder)
vector<int> dfsIterative(const AdjList& g, int start) {
    TODO();
}

// L33-M2 · Example: path 0-1-2, vertex 3 alone, start 0  =>  {0, 1, 2, -1}
vector<int> distances(const AdjList& g, int start) {
    TODO();
}

// L33-M3 · Example: 0-1, 2-3, 4  =>  3
int countComponents(const AdjList& g) {
    TODO();
}

// L33-X · Example: n = 3, edges {{0,1},{1,2},{2,0}}, 0 -> 2  =>  true
bool validPath(int n, const vector<vector<int>>& edges, int source, int destination) {
    TODO();
}

// L33-V · Example: 0->1, 2->0, start 0  =>  {0, 1}
vector<int> reachable(const AdjList& g, int start) {
    TODO();
}
