// ============================================================================
//  Mini Project 04 · Metro route planner · YOU WORK HERE (about 90 lines)
//  Reference solution. @solution-note
//  Test:  .\run.ps1 P04        Program:  main_demo.cpp (reads metro.txt)
// ============================================================================
#include "metro.h"

#include <algorithm>
#include <queue>

#include "todo.h"

using namespace std;

// @begin idOf
int Metro::idOf(const string& station) const {
    auto it = ids.find(station);
    return it == ids.end() ? -1 : it->second;
}
// @end idOf

// @begin addStation
int Metro::addStation(const string& station) {
    int id = idOf(station);
    if (id != -1) return id;
    id = names.size();
    ids[station] = id;
    names.push_back(station);
    adj.push_back({});
    return id;
}
// @end addStation

// @begin addLine
void Metro::addLine(const string& line, const vector<string>& stations) {
    for (size_t i = 0; i < stations.size(); i++) {
        int b = addStation(stations[i]);
        if (i == 0) continue;
        int a = idOf(stations[i - 1]);
        bool known = false;
        for (const Link& l : adj[a]) known = known || l.to == b;
        if (known || a == b) continue;      // keep the first line of a pair
        adj[a].push_back({b, line});
        adj[b].push_back({a, line});
    }
}
// @end addLine

// @begin stationCount
int Metro::stationCount() const {
    return names.size();
}
// @end stationCount

// @begin neighbours
vector<string> Metro::neighbours(const string& station) const {
    vector<string> out;
    int id = idOf(station);
    if (id == -1) return out;
    for (const Link& l : adj[id]) out.push_back(names[l.to]);
    return out;
}
// @end neighbours

// @begin bfs
vector<int> Metro::bfs(int from, vector<int>& parent) const {
    vector<int> dist(names.size(), -1);
    parent.assign(names.size(), -1);
    queue<int> q;
    dist[from] = 0;
    q.push(from);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const Link& l : adj[v])
            if (dist[l.to] == -1) {
                dist[l.to] = dist[v] + 1;
                parent[l.to] = v;           // remember how we got here
                q.push(l.to);
            }
    }
    return dist;
}
// @end bfs

// @begin route
vector<string> Metro::route(const string& from, const string& to) const {
    int a = idOf(from), b = idOf(to);
    if (a == -1 || b == -1) return {};
    vector<int> parent;
    if (bfs(a, parent)[b] == -1) return {};
    vector<string> path;
    for (int v = b; v != -1; v = parent[v]) path.push_back(names[v]);   // walk back
    reverse(path.begin(), path.end());
    return path;
}
// @end route

// @begin stops
int Metro::stops(const string& from, const string& to) const {
    vector<string> r = route(from, to);
    return r.empty() ? -1 : (int)r.size() - 1;
}
// @end stops

// @begin transfers
int Metro::transfers(const vector<string>& route) const {
    int changes = 0;
    string last;
    for (size_t i = 1; i < route.size(); i++) {
        int a = idOf(route[i - 1]), b = idOf(route[i]);
        string line;
        for (const Link& l : adj[a])
            if (l.to == b) line = l.line;
        if (i > 1 && line != last) changes++;
        last = line;
    }
    return changes;
}
// @end transfers

// @begin withinStops
vector<string> Metro::withinStops(const string& from, int k) const {
    int a = idOf(from);
    if (a == -1) return {};
    vector<int> parent;
    vector<int> dist = bfs(a, parent);
    vector<string> out;
    for (int v = 0; v < (int)names.size(); v++)
        if (v != a && dist[v] != -1 && dist[v] <= k) out.push_back(names[v]);
    sort(out.begin(), out.end());
    return out;
}
// @end withinStops
