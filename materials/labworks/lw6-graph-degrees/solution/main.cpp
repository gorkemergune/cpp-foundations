// Labwork 6 Q2 · g++ -std=c++17 main.cpp graph.cpp
#include <iostream>
#include <vector>

#include "graph.h"
#include "lab6_graph.h"
using namespace std;

static void print(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    Graph g(&LAB6_ADJ[0][0], 6);   // the 2-D array is passed as a pointer to its first int
    for (int i = 0; i < 6; i++) cout << "In-degree of node " << i << ": " << g.indegree(i) << "\n";
    for (int i = 0; i < 6; i++) cout << "Out-degree of node " << i << ": " << g.outdegree(i) << "\n";
    cout << "Number of edges: " << g.num_edges() << "\n";
    cout << "DFS from node 2: ";
    print(g.dfs(2));
    cout << "BFS from node 5: ";
    print(g.bfs(5));
    cout << "Shortest path from 5 to 4: ";
    print(g.shortest_path(5, 4));
}
