// ============================================================================
//  Mini Project 02 · Playlist · YOU WORK HERE (about 90 lines)
//  Test:  .\run.ps1 P02        Program:  main_demo.cpp
// ============================================================================
#include "playlist.h"

#include <sstream>

#include "todo.h"

using namespace std;

Playlist::Playlist() {
    // TODO: write this (it must not throw)
}

Playlist::~Playlist() {
    // TODO: write this (it must not throw)
}

void Playlist::add(const string& title, int seconds) {
    TODO();
}

int Playlist::size() const {
    TODO();
}

int Playlist::totalSeconds() const {
    TODO();
}

string Playlist::current() const {
    TODO();
}

bool Playlist::next() {
    TODO();
}

bool Playlist::prev() {
    TODO();
}

bool Playlist::remove(const string& title) {
    TODO();
}

bool Playlist::moveUp(const string& title) {
    TODO();
}

string Playlist::listing() const {
    TODO();
}

// test helper (given)
string Playlist::backwardTitles() const {
    string r;
    for (Node* p = tail; p != nullptr; p = p->prev) r += p->title + " ";
    return r;
}
