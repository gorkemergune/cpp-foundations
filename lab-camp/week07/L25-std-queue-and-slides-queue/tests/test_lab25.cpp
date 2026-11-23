// Lab 25 tests. Queues are written front first.
#include <algorithm>

#include "lab25.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_PING_Case { V times; V counts; };
struct PDF_SAME_Case { V a; V b; bool ret; };
struct PDF_LUNCH_Case { V students; V sandwiches; int ret; };
#include "pdf_cases.inc"

static std::queue<int> mkStd(const V& v) {
    std::queue<int> q;
    for (int x : v) q.push(x);
    return q;
}
static void fillSlides(Queue& q, const V& v) {
    for (int x : v) q.enqueue(x);
}
static V readSlides(const Queue& q) {
    Queue c(q);
    V r;
    QueueItemType x;
    while (c.dequeue(x)) r.push_back(x);
    return r;
}

QUESTION("L25-A", "drainStd", "drainStd(") {
    for (V v : {V{1, 2, 3}, V{}, V{0, 0}}) {
        std::queue<int> q = mkStd(v);
        check("queue " + show(v), v, drainStd(q));
        checkTrue("queue " + show(v) + " is empty afterwards", q.empty(), "not empty");
    }
}

QUESTION("L25-B", "drainSlides (dequeue(out))", "drainSlides(") {
    for (V v : {V{1, 2, 3}, V{}, V{0, 0, 5}}) {
        Queue q;
        fillSlides(q, v);
        check("queue " + show(v) + " (0 must not stop the loop)", v, drainSlides(q));
        checkTrue("queue " + show(v) + " is empty afterwards", q.isEmpty(), "not empty");
    }
}

QUESTION("L25-M1", "RecentCounter (LC 933, slides Queue)", "RecentCounter::ping(") {
    for (auto& c : PDF_PING) {
        RecentCounter rc;
        V got;
        for (int t : c.times) got.push_back(rc.ping(t));
        check("pings " + show(c.times), c.counts, got);
    }
}

QUESTION("L25-M2", "sameQueue (copies, originals unchanged)", "sameQueue(") {
    for (auto& c : PDF_SAME) {
        Queue a, b;
        fillSlides(a, c.a);
        fillSlides(b, c.b);
        std::string d = "a=" + show(c.a) + ", b=" + show(c.b);
        check(d, c.ret, sameQueue(a, b));
        check(d + " (a unchanged)", c.a, readSlides(a));
        check(d + " (b unchanged)", c.b, readSlides(b));
    }
}

OPTIONAL_QUESTION("L25-X", "countStudents (LC 1700)", "countStudents(") {
    for (auto& c : PDF_LUNCH)
        check("students=" + show(c.students) + ", sandwiches=" + show(c.sandwiches), c.ret,
              countStudents(c.students, c.sandwiches));
}

OPTIONAL_QUESTION("L25-V", "rotateK", "rotateK(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(8, 0, 9), w = v;
        int k = randInt(0, 20);
        if (!w.empty()) std::rotate(w.begin(), w.begin() + k % w.size(), w.end());
        std::queue<int> q = mkStd(v);
        rotateK(q, k);
        V got;
        while (!q.empty()) { got.push_back(q.front()); q.pop(); }
        check("queue " + show(v) + ", k=" + std::to_string(k), w, got);
    }
}
