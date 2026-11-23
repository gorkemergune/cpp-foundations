// ============================================================================
//  Mini Project 06 · Triage · YOU WORK HERE (about 95 lines)
//  Reference solution. @solution-note
//  Test:  .\run.ps1 P06        Program:  main_demo.cpp
// ============================================================================
#include "triage.h"

#include <utility>

#include "todo.h"

using namespace std;

// @begin before
bool Triage::before(const Patient& a, const Patient& b) {
    if (a.severity != b.severity) return a.severity > b.severity;
    return a.arrival < b.arrival;           // equal severity: first come, first served
}
// @end before

// @begin siftUp
void Triage::siftUp(int i) {
    while (i > 0 && before(heap[i], heap[(i - 1) / 2])) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
// @end siftUp

// @begin siftDown
void Triage::siftDown(int i) {
    int n = heap.size();
    while (2 * i + 1 < n) {
        int c = 2 * i + 1;
        if (c + 1 < n && before(heap[c + 1], heap[c])) c++;   // the child treated first
        if (!before(heap[c], heap[i])) return;
        swap(heap[c], heap[i]);
        i = c;
    }
}
// @end siftDown

// @begin indexOf
int Triage::indexOf(const string& name) const {
    for (int i = 0; i < (int)heap.size(); i++)   // a heap is not sorted: linear search
        if (heap[i].name == name) return i;
    return -1;
}
// @end indexOf

// @begin removeAt
void Triage::removeAt(int i) {
    heap[i] = heap.back();                  // the last patient fills the hole ...
    heap.pop_back();
    if (i < (int)heap.size()) {             // ... and may have to go up OR down
        siftUp(i);
        siftDown(i);
    }
}
// @end removeAt

// @begin arrive
void Triage::arrive(const string& name, int severity) {
    heap.push_back({name, severity, arrivals++});
    siftUp(heap.size() - 1);
}
// @end arrive

// @begin peek
bool Triage::peek(string& name) const {
    if (heap.empty()) return false;
    name = heap[0].name;
    return true;
}
// @end peek

// @begin treat
bool Triage::treat(string& name) {
    if (!peek(name)) return false;
    removeAt(0);
    return true;
}
// @end treat

// @begin waiting
int Triage::waiting() const {
    return heap.size();
}
// @end waiting

// @begin upgrade
bool Triage::upgrade(const string& name, int newSeverity) {
    int i = indexOf(name);
    if (i == -1 || newSeverity <= heap[i].severity) return false;
    heap[i].severity = newSeverity;
    siftUp(i);                              // more urgent: it can only move up
    return true;
}
// @end upgrade

// @begin leave
bool Triage::leave(const string& name) {
    int i = indexOf(name);
    if (i == -1) return false;
    removeAt(i);
    return true;
}
// @end leave

// @begin report
string Triage::report() const {
    Triage copy = *this;                    // treat everybody in a copy
    string out, name;
    while (!copy.heap.empty()) {
        Patient p = copy.heap[0];
        copy.treat(name);
        if (!out.empty()) out += " ";
        out += p.name + "(" + to_string(p.severity) + ")";
    }
    return out;
}
// @end report
