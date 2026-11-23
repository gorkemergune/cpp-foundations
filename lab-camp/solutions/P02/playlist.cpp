// ============================================================================
//  Mini Project 02 · Playlist · YOU WORK HERE (about 90 lines)
//  Reference solution. @solution-note
//  Test:  .\run.ps1 P02        Program:  main_demo.cpp
// ============================================================================
#include "playlist.h"

#include <sstream>

#include "todo.h"

using namespace std;

// @begin Playlist empty
Playlist::Playlist()
    : head(nullptr), tail(nullptr), cur(nullptr), count(0) {
}
// @end Playlist

// @begin ~Playlist empty
Playlist::~Playlist() {
    while (head != nullptr) {
        Node* n = head->next;
        delete head;
        head = n;
    }
}
// @end ~Playlist

// @begin add
void Playlist::add(const string& title, int seconds) {
    Node* n = new Node{title, seconds, tail, nullptr};
    if (tail == nullptr) head = n;
    else tail->next = n;
    tail = n;
    if (cur == nullptr) cur = n;
    count++;
}
// @end add

// @begin size
int Playlist::size() const {
    return count;
}
// @end size

// @begin totalSeconds
int Playlist::totalSeconds() const {
    int total = 0;
    for (Node* p = head; p != nullptr; p = p->next) total += p->seconds;
    return total;
}
// @end totalSeconds

// @begin current
string Playlist::current() const {
    return cur ? cur->title : "";
}
// @end current

// @begin next
bool Playlist::next() {
    if (cur == nullptr || cur->next == nullptr) return false;
    cur = cur->next;
    return true;
}
// @end next

// @begin prev
bool Playlist::prev() {
    if (cur == nullptr || cur->prev == nullptr) return false;
    cur = cur->prev;
    return true;
}
// @end prev

// @begin remove
bool Playlist::remove(const string& title) {
    Node* p = head;
    while (p != nullptr && p->title != title) p = p->next;
    if (p == nullptr) return false;
    if (p == cur) cur = p->next ? p->next : p->prev;   // keep a sensible current song
    if (p->prev) p->prev->next = p->next;
    else head = p->next;
    if (p->next) p->next->prev = p->prev;
    else tail = p->prev;
    delete p;
    count--;
    return true;
}
// @end remove

// @begin moveUp
bool Playlist::moveUp(const string& title) {
    Node* b = head;
    while (b != nullptr && b->title != title) b = b->next;
    if (b == nullptr || b->prev == nullptr) return false;
    Node* a = b->prev;                 // ... x <-> a <-> b <-> y ...  becomes  x <-> b <-> a <-> y
    Node* x = a->prev;
    Node* y = b->next;
    if (x) x->next = b;
    else head = b;
    if (y) y->prev = a;
    else tail = a;
    b->prev = x;
    b->next = a;
    a->prev = b;
    a->next = y;
    return true;
}
// @end moveUp

// @begin listing
string Playlist::listing() const {
    ostringstream out;
    int i = 1;
    for (Node* p = head; p != nullptr; p = p->next, i++) {
        int s = p->seconds % 60;
        out << i << ". " << (p == cur ? "*" : "") << p->title << " (" << p->seconds / 60 << ":"
            << (s < 10 ? "0" : "") << s << ")\n";
    }
    return out.str();
}
// @end listing

// test helper (given)
string Playlist::backwardTitles() const {
    string r;
    for (Node* p = tail; p != nullptr; p = p->prev) r += p->title + " ";
    return r;
}
