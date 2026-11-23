// ============================================================================
//  Mini Project 03 · Browser · YOU WORK HERE (about 80 lines)
//  Reference solution. @solution-note
//  Test:  .\run.ps1 P03        Program:  main_demo.cpp
// ============================================================================
#include "browser.h"

#include <sstream>

#include "todo.h"

using namespace std;

// @begin Browser
Browser::Browser(const string& homepage)
    : cur(homepage) {
}
// @end Browser

// @begin visit
void Browser::visit(const string& url) {
    backPages.push(cur);
    cur = url;
    while (!forwardPages.empty()) forwardPages.pop();   // a new branch: forget the old future
}
// @end visit

// @begin current
string Browser::current() const {
    return cur;
}
// @end current

// @begin back
string Browser::back(int steps) {
    while (steps-- > 0 && !backPages.empty()) {
        forwardPages.push(cur);             // the page we leave can be reached forward again
        cur = backPages.top();
        backPages.pop();
    }
    return cur;
}
// @end back

// @begin forward
string Browser::forward(int steps) {
    while (steps-- > 0 && !forwardPages.empty()) {
        backPages.push(cur);
        cur = forwardPages.top();
        forwardPages.pop();
    }
    return cur;
}
// @end forward

// @begin historyReport
string Browser::historyReport() const {
    stack<string> b = backPages, f = forwardPages;      // copies: the report must not change history
    vector<string> backList;
    while (!b.empty()) { backList.push_back(b.top()); b.pop(); }   // newest first ...
    ostringstream out;
    out << "back:";
    if (backList.empty()) out << " -";
    for (int i = (int)backList.size() - 1; i >= 0; i--)   // ... printed oldest first
        out << " " << backList[i];
    out << " | current: " << cur << " | forward:";
    if (f.empty()) out << " -";
    while (!f.empty()) { out << " " << f.top(); f.pop(); }
    return out.str();
}
// @end historyReport

// @begin download
void Browser::download(const string& file, int sizeMB) {
    downloads.push({file, sizeMB});
}
// @end download

// @begin tick
vector<string> Browser::tick(int mb) {
    vector<string> finished;
    while (mb > 0 && !downloads.empty()) {
        Download& d = downloads.front();
        int used = d.remaining < mb ? d.remaining : mb;
        d.remaining -= used;
        mb -= used;
        if (d.remaining == 0) {
            finished.push_back(d.file);
            downloads.pop();                // d is gone after this line: do not use it
        }
    }
    return finished;
}
// @end tick

// @begin pendingDownloads
int Browser::pendingDownloads() const {
    return (int)downloads.size();
}
// @end pendingDownloads
