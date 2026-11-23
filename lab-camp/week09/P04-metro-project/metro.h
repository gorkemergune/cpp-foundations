// ============================================================================
//  Mini Project 04 · Metro route planner (graph + BFS)              DO NOT EDIT
//  Stations are vertices, consecutive stations of a line are joined by an
//  undirected edge that remembers its line.
// ============================================================================
#ifndef METRO_H
#define METRO_H

#include <map>
#include <string>
#include <vector>

class Metro {
public:
    // P04-A · add a line: every station is added if new; consecutive stations are connected.
    // A pair that is already connected keeps its first line.
    void addLine(const std::string& line, const std::vector<std::string>& stations);
    int stationCount() const;
    // P04-A · neighbours in the order they were connected; unknown station -> {}
    std::vector<std::string> neighbours(const std::string& station) const;

    // P04-B · a route with the fewest stops (BFS, neighbours in connection order),
    // from and to included. Unknown station or no route -> {}.
    std::vector<std::string> route(const std::string& from, const std::string& to) const;
    int stops(const std::string& from, const std::string& to) const;   // -1 if no route

    // P04-C · how many times the line changes along a route.
    int transfers(const std::vector<std::string>& route) const;
    // P04-C · every station within k stops of `from` (not `from` itself), sorted by name.
    std::vector<std::string> withinStops(const std::string& from, int k) const;

private:
    struct Link {
        int to;
        std::string line;
    };
    std::map<std::string, int> ids;       // station name -> vertex number
    std::vector<std::string> names;       // vertex number -> station name
    std::vector<std::vector<Link>> adj;

    int idOf(const std::string& station) const;   // -1 if unknown
    int addStation(const std::string& station);   // existing id or a new one
    std::vector<int> bfs(int from, std::vector<int>& parent) const;   // distances
};

#endif
