// ============================================================================
//  Lab 46 · Priority queues at work · YOU WORK HERE
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
void StablePQ::enqueue(const string& element, int priority) {
    TODO();
}

bool StablePQ::dequeue(string& out) {
    TODO();
}

int StablePQ::size() const {
    TODO();
}

// L46-M1 · Example: 0->1 (4), 0->2 (1), 2->1 (2), 1->3 (1)  =>  {0, 3, 1, 4}
vector<long long> dijkstra(int n, const WEdges& edges, int src) {
    TODO();
}

// L46-M2 · Example: the Lab 35 graph  =>  16
long long primHeap(int n, const WEdges& edges) {
    TODO();
}

// L46-M3 · Example: {{1,2},{2,4},{3,2},{4,1}}  =>  {0, 2, 3, 1}
vector<int> getOrder(const vector<vector<int>>& tasks) {
    TODO();
}

// L46-X · Example: {4,2,7,6,9,14,12}, bricks 5, ladders 1  =>  4
int furthestBuilding(const vector<int>& heights, int bricks, int ladders) {
    TODO();
}

// L46-V · Example: {2, 7, 4, 1, 8, 1}  =>  1
int lastStoneWeightPQ(const vector<int>& stones) {
    TODO();
}
