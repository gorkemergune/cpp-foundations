// ============================================================================
//  Mini Project 04 · Metro route planner · YOU WORK HERE (about 90 lines)
//  Test:  .\run.ps1 P04        Program:  main_demo.cpp (reads metro.txt)
// ============================================================================
#include "metro.h"

#include <algorithm>
#include <queue>

#include "todo.h"

using namespace std;

int Metro::idOf(const string& station) const {
    TODO();
}

int Metro::addStation(const string& station) {
    TODO();
}

void Metro::addLine(const string& line, const vector<string>& stations) {
    TODO();
}

int Metro::stationCount() const {
    TODO();
}

vector<string> Metro::neighbours(const string& station) const {
    TODO();
}

vector<int> Metro::bfs(int from, vector<int>& parent) const {
    TODO();
}

vector<string> Metro::route(const string& from, const string& to) const {
    TODO();
}

int Metro::stops(const string& from, const string& to) const {
    TODO();
}

int Metro::transfers(const vector<string>& route) const {
    TODO();
}

vector<string> Metro::withinStops(const string& from, int k) const {
    TODO();
}
