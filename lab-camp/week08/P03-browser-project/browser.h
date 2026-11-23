// ============================================================================
//  Mini Project 03 · Browser: history with two stacks, downloads in a queue
//  DO NOT EDIT
// ============================================================================
#ifndef BROWSER_H
#define BROWSER_H

#include <queue>
#include <stack>
#include <string>
#include <vector>

class Browser {
public:
    explicit Browser(const std::string& homepage);   // P03-A · the first current page

    // P03-A · open url: the current page goes to the back history, the forward
    // history is cleared (like every browser).
    void visit(const std::string& url);
    std::string current() const;

    // P03-B · LeetCode 1472: go back / forward at most `steps` pages; return the current page.
    std::string back(int steps);
    std::string forward(int steps);
    // P03-B · "back: a b | current: c | forward: d e" — back pages oldest first,
    // forward pages nearest first; an empty side prints "-".
    std::string historyReport() const;

    // P03-C · downloads, first come first served. tick(mb) transfers up to mb megabytes:
    // the front file gets the bandwidth first; when it finishes, the rest of the bandwidth
    // goes to the next file. Returns the files finished in this tick, in order.
    void download(const std::string& file, int sizeMB);
    std::vector<std::string> tick(int mb);
    int pendingDownloads() const;

private:
    std::stack<std::string> backPages;      // top = the page just before the current one
    std::stack<std::string> forwardPages;   // top = the page just after the current one
    std::string cur;
    struct Download {
        std::string file;
        int remaining;
    };
    std::queue<Download> downloads;
};

#endif
