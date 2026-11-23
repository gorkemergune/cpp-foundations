// Lab 23 tests. Stacks are written top first.
#include <algorithm>
#include <deque>

#include "lab23.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_REV_Case { std::string a; std::string b; bool ret; };
struct PDF_SEQ_Case { V pushed; V popped; bool ret; };
#include "pdf_cases.inc"

static std::stack<int> mk(const V& topFirst) {
    std::stack<int> s;
    for (int i = (int)topFirst.size() - 1; i >= 0; i--) s.push(topFirst[i]);
    return s;
}
static V dump(std::stack<int> s) {
    V r;
    while (!s.empty()) {
        r.push_back(s.top());
        s.pop();
    }
    return r;
}

QUESTION("L23-A", "moveTop (midterm)", "moveTop(") {
    std::stack<int> a = mk({9, 4}), b = mk({7});
    check("moveTop(a, b) returns", true, moveTop(a, b));
    check("a after", V{4}, dump(a));
    check("b after", V{9, 7}, dump(b));
    std::stack<int> e, f = mk({1});
    check("moveTop(empty, f)", false, moveTop(e, f));
    check("f unchanged", V{1}, dump(f));
    check("moveTop(f, empty)", true, moveTop(f, e));
    check("now e", V{1}, dump(e));
}

QUESTION("L23-B", "moveAll", "moveAll(") {
    std::stack<int> a = mk({1, 2, 3}), b;
    moveAll(a, b);
    check("b after moveAll (top first)", V{3, 2, 1}, dump(b));
    checkTrue("a is empty", a.empty(), "a must be empty");
    std::stack<int> e, c = mk({5});
    moveAll(e, c);
    check("moveAll(empty, c) leaves c", V{5}, dump(c));
}

QUESTION("L23-M1", "areReverses with two stacks (midterm)", "areReverses(") {
    for (auto& c : PDF_REV) check("a=" + show(c.a) + ", b=" + show(c.b), c.ret, areReverses(c.a, c.b));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string a, b;
        int n = randInt(0, 6);
        for (int i = 0; i < n; i++) a += "ab"[randInt(0, 1)];
        b = std::string(a.rbegin(), a.rend());
        if (randInt(0, 1) && !b.empty()) b[randInt(0, (int)b.size() - 1)] = "ab"[randInt(0, 1)];
        check("a=" + show(a) + ", b=" + show(b), a == std::string(b.rbegin(), b.rend()), areReverses(a, b));
    }
}

QUESTION("L23-M2", "MyQueue with two stacks (LC 232)", "MyQueue::") {
    MyQueue q;
    check("new queue empty()", true, q.empty());
    q.push(1);
    q.push(2);
    check("peek after push 1, 2", 1, q.peek());
    check("pop", 1, q.pop());
    check("empty()", false, q.empty());
    for (int t = 0; t < RANDOM_CASES; t++) {               // random mixes vs std::deque
        MyQueue m;
        std::deque<int> ref;
        bool ok = true;
        std::string log;
        for (int k = 0; k < 20 && ok; k++) {
            if (ref.empty() || randInt(0, 2) > 0) {
                int x = randInt(0, 99);
                m.push(x);
                ref.push_back(x);
                log += " push" + std::to_string(x);
            } else {
                int got = m.pop();
                log += " pop";
                ok = got == ref.front();
                ref.pop_front();
            }
            ok = ok && m.empty() == ref.empty() && (ref.empty() || m.peek() == ref.front());
        }
        checkTrue("ops:" + log, ok, "FIFO order broken");
    }
}

OPTIONAL_QUESTION("L23-X", "validateStackSequences (LC 946)", "validateStackSequences(") {
    for (auto& c : PDF_SEQ) check("pushed=" + show(c.pushed) + ", popped=" + show(c.popped), c.ret,
                                   validateStackSequences(c.pushed, c.popped));
}

OPTIONAL_QUESTION("L23-V", "sortStack (one extra stack)", "sortStack(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, 0, 9), w = v;
        std::sort(w.begin(), w.end());
        std::stack<int> s = mk(v);
        sortStack(s);
        check("stack " + show(v), w, dump(s));
    }
}
