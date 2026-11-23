// ============================================================================
//  Lab 41 · Open addressing · YOU WORK HERE
//  Reference solution. @solution-note
//  Test everything:      .\run.ps1 L41
// ============================================================================
#include "lab41.h"

#include "todo.h"

using namespace std;

// @begin OpenTable
OpenTable::OpenTable(int size, Probing mode)
    : keys(size, 0), state(size, EMPTY), mode(mode) {
}
// @end OpenTable

// L41-A · Example: size 11, key 24, quadratic: i = 0, 1, 2  =>  2, 3, 6
// @begin probe
int OpenTable::probe(int key, int i) const {
    long long n = keys.size(), h1 = key % n;
    long long step;
    if (mode == Probing::LINEAR) step = i;
    else if (mode == Probing::QUADRATIC) step = (long long)i * i;
    else step = (long long)i * (7 - key % 7);   // h2 is never 0
    return (int)((h1 + step) % n);
}
// @end probe

// L41-B · Example: an empty table of size 3  =>  "_ _ _"
// @begin layout
string OpenTable::layout() const {
    string out;
    for (size_t i = 0; i < keys.size(); i++) {
        if (i > 0) out += " ";
        if (state[i] == EMPTY) out += "_";
        else if (state[i] == DELETED) out += "x";
        else out += to_string(keys[i]);
    }
    return out;
}
// @end layout

// L41-M1 · Example: linear, size 11: 20 30 2 13 25 24  =>  24 lands in slot 5
// @begin insert
int OpenTable::insert(int key) {
    if (find(key) != -1) return -1;              // never twice
    int n = keys.size();
    for (int i = 0; i < n; i++) {
        int s = probe(key, i);
        if (state[s] != OCCUPIED) {              // EMPTY or DELETED: reuse it
            keys[s] = key;
            state[s] = OCCUPIED;
            return s;
        }
    }
    return -1;                                   // every probed slot was taken
}
// @end insert

// L41-M2 · Example: after removing 13 (slot 3), find 24  =>  5 (passes the DELETED slot)
// @begin find
int OpenTable::find(int key) const {
    int n = keys.size();
    for (int i = 0; i < n; i++) {
        int s = probe(key, i);
        if (state[s] == EMPTY) return -1;        // the key would have been put here
        if (state[s] == OCCUPIED && keys[s] == key) return s;
    }
    return -1;
}
// @end find

// L41-M3 · Example: remove 13  =>  true, its slot shows "x"
// @begin remove
bool OpenTable::remove(int key) {
    int s = find(key);
    if (s == -1) return false;
    state[s] = DELETED;                          // NOT EMPTY: later searches must go on
    return true;
}
// @end remove

// L41-X · Example: size 5 with 1 6  =>  size 11 (first prime >= 10), keys 1 6
// @begin rehash
void OpenTable::rehash() {
    int n = 2 * keys.size();
    auto prime = [](int x) {
        if (x < 2) return false;
        for (int d = 2; d * d <= x; d++)
            if (x % d == 0) return false;
        return true;
    };
    while (!prime(n)) n++;
    vector<int> oldKeys = keys;
    vector<State> oldState = state;
    keys.assign(n, 0);
    state.assign(n, EMPTY);
    for (size_t i = 0; i < oldKeys.size(); i++)
        if (oldState[i] == OCCUPIED) insert(oldKeys[i]);
}
// @end rehash

// L41-V · Example: "9 _ 2 13 25 24 _ _ 30 20 10"  =>  4
// @begin longestCluster
int OpenTable::longestCluster() const {
    int best = 0, run = 0;
    for (State s : state) {
        run = (s == OCCUPIED) ? run + 1 : 0;
        if (run > best) best = run;
    }
    return best;
}
// @end longestCluster
