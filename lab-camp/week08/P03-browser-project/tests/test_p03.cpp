// Mini Project 03 tests.
#include "browser.h"
#include "test.h"

using namespace lab;
using S = std::vector<std::string>;

QUESTION("P03-A", "constructor / visit / current", "Browser::visit(") {
    Browser b("home");
    check("start page", std::string("home"), b.current());
    b.visit("a");
    b.visit("b");
    check("after visiting a, b", std::string("b"), b.current());
}

QUESTION("P03-B", "back / forward / historyReport (LC 1472)", "Browser::back(") {
    Browser b("leetcode.com");
    for (const char* u : {"google.com", "facebook.com", "youtube.com"}) b.visit(u);
    check("back(1)", std::string("facebook.com"), b.back(1));
    check("back(1)", std::string("google.com"), b.back(1));
    check("forward(1)", std::string("facebook.com"), b.forward(1));
    b.visit("linkedin.com");
    check("forward(2) after a visit (forward history cleared)", std::string("linkedin.com"), b.forward(2));
    check("back(2)", std::string("google.com"), b.back(2));
    check("back(7): only one page left", std::string("leetcode.com"), b.back(7));
    check("report", std::string("back: - | current: leetcode.com | forward: google.com facebook.com linkedin.com"),
          b.historyReport());
    b.forward(2);
    check("report after forward(2)", std::string("back: leetcode.com google.com | current: facebook.com | forward: linkedin.com"),
          b.historyReport());
    check("report did not change the history", std::string("facebook.com"), b.current());
    Browser single("x");
    check("nothing to go to", std::string("x"), single.forward(3));
    check("report of a fresh browser", std::string("back: - | current: x | forward: -"), single.historyReport());
}

QUESTION("P03-C", "download / tick / pendingDownloads", "Browser::tick(") {
    Browser b("home");
    check("no downloads", 0, b.pendingDownloads());
    check("tick on an empty queue", S{}, b.tick(10));
    b.download("big.iso", 10);
    b.download("small.txt", 1);
    b.download("pic.png", 3);
    check("tick(4): the front file is still running", S{}, b.tick(4));
    check("tick(8): big finishes (6), small (1), 1 MB left for pic", S{"big.iso", "small.txt"}, b.tick(8));
    check("pending", 1, b.pendingDownloads());
    check("tick(2): pic needs exactly 2 more", S{"pic.png"}, b.tick(2));
    check("pending", 0, b.pendingDownloads());
    b.download("a", 2);
    b.download("b", 2);
    check("tick(4) finishes both, in order", S{"a", "b"}, b.tick(4));
}
