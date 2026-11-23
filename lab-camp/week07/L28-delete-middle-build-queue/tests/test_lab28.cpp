// Lab 28 tests. CNode::alive catches leaked or double-deleted nodes.
#include "lab28.h"
#include "test.h"

using namespace lab;

struct PDF_TASK_Case { std::string s; std::string printed; };
#include "pdf_cases.inc"

static std::string listString(CNode* h) {
    std::string r;
    for (int g = 0; h && g < 1000; h = h->next, g++) r += h->ch;
    return r;
}
static void destroy(CNode* h) {
    int g = 0;
    while (h && g++ < 1000) {
        CNode* n = h->next;
        delete h;
        h = n;
    }
}

QUESTION("L28-A", "buildList", "buildList(") {
    for (std::string s : {"abc", "", "z"}) {
        CNode* h = buildList(s);
        check("buildList(" + show(s) + ")", s, listString(h));
        check("buildList(" + show(s) + ") nodes", (int)s.size(), CNode::alive);
        destroy(h);
    }
}

QUESTION("L28-B", "drainToString (dequeue(item&))", "drainToString(") {
    Queue q;
    for (char c : std::string("xy")) q.enqueue(c);
    check("queue x, y", std::string("xy"), drainToString(q));
    checkTrue("queue empty afterwards", q.isEmpty(), "not empty");
    Queue e;
    check("empty queue", std::string(""), drainToString(e));
}

QUESTION("L28-M1", "deleteMiddleToQueue (midterm)", "deleteMiddleToQueue(") {
    for (auto& c : PDF_TASK) {
        CNode* h = buildList(c.s);
        Queue out;
        int before = CNode::alive;
        std::string d = "list " + show(c.s);
        check(d + " (return)", !c.s.empty(), deleteMiddleToQueue(h, out));
        check(d + " (list after)", c.printed, listString(h));
        check(d + " (deleted nodes)", c.s.empty() ? 0 : 1, before - CNode::alive);
        QueueItemType x;
        std::string q;
        while (out.dequeue(x)) q += (char)x;
        check(d + " (queue contents)", c.printed, q);
        destroy(h);
    }
}

QUESTION("L28-M2", "midtermTask (whole task)", "midtermTask(") {
    for (auto& c : PDF_TASK) {
        int before = CNode::alive;
        check("midtermTask(" + show(c.s) + ")", c.printed, midtermTask(c.s));
        check("midtermTask(" + show(c.s) + ") leaves no node", before, CNode::alive);
    }
}

OPTIONAL_QUESTION("L28-X", "LinkedQueue (GfG)", "LinkedQueue::") {
    LinkedQueue q;
    q.push(2);
    q.push(3);
    check("pop", 2, q.pop());
    q.push(4);
    check("pop", 3, q.pop());
    check("pop", 4, q.pop());
    check("pop on empty", -1, q.pop());
    q.push(5);
    check("push after emptying, pop", 5, q.pop());
}

OPTIONAL_QUESTION("L28-V", "interleaveHalves", "interleaveHalves(") {
    std::queue<int> q;
    for (int x : {1, 2, 3, 4, 5, 6}) q.push(x);
    interleaveHalves(q);
    std::vector<int> got;
    while (!q.empty()) { got.push_back(q.front()); q.pop(); }
    check("1..6", std::vector<int>{1, 4, 2, 5, 3, 6}, got);
}
