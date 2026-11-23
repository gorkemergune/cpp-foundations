// ============================================================================
//  Lab 41 · Open addressing: linear, quadratic and double hashing    DO NOT EDIT
//  Slides 17-25. Keys are >= 0, h1(key) = key % size, h2(key) = 7 - key % 7.
//  Every slot is EMPTY, OCCUPIED or DELETED (slide 25).
// ============================================================================
#pragma once

#include <string>
#include <vector>

enum class Probing { LINEAR, QUADRATIC, DOUBLE };

class OpenTable {
public:
    OpenTable(int size, Probing mode);

    // L41-A · Warm-up · the i-th location tried for key (i = 0, 1, 2 ...):
    // linear h1 + i, quadratic h1 + i*i, double h1 + i*h2 — all % size.
    int probe(int key, int i) const;

    // L41-B · Warm-up · the slots as text: the key, "_" for EMPTY, "x" for DELETED,
    // separated by single spaces. An empty table of size 3: "_ _ _".
    std::string layout() const;

    // L41-M1 · Main · insert key: if it is already in the table return -1; otherwise store it
    // in the FIRST empty-or-deleted slot of its probe sequence (i = 0 .. size-1) and return
    // that index; -1 if none of these slots is free.
    int insert(int key);

    // L41-M2 · Main · the index of key, or -1. Probe until the key or an EMPTY slot is found
    // (a DELETED slot does not stop the search), at most size probes.
    int find(int key) const;

    // L41-M3 · Main · remove key: mark its slot DELETED. false if it is not there.
    bool remove(int key);

    // L41-X · Optional · rebuild into the smallest PRIME size >= 2 * size; re-insert the keys
    // in slot order (0, 1, 2 ...); DELETED slots disappear.
    void rehash();

    // L41-V · Optional · memory variant: the longest run of consecutive OCCUPIED slots
    // (no wrap-around) — the clustering of slide 20.
    int longestCluster() const;

private:
    enum State { EMPTY, OCCUPIED, DELETED };
    std::vector<int> keys;
    std::vector<State> state;
    Probing mode;
};
