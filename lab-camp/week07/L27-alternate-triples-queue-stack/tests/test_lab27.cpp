// Lab 27 tests: PDF rows + random queues against a vector + std::reverse version.
#include <algorithm>

#include "lab27.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_TRI_Case { V q; V after; };
struct PDF_FK_Case { V q; int k; V after; };
#include "pdf_cases.inc"

static std::queue<int> mk(const V& v) {
    std::queue<int> q;
    for (int x : v) q.push(x);
    return q;
}
static V dump(std::queue<int> q) {
    V r;
    while (!q.empty()) { r.push_back(q.front()); q.pop(); }
    return r;
}
static V seq(int n) {
    V v;
    for (int i = 1; i <= n; i++) v.push_back(i);
    return v;
}

QUESTION("L27-A", "reverseQueue", "reverseQueue(") {
    for (V v : {V{1, 2, 3}, V{}, V{7}, V{4, 4, 1}}) {
        std::queue<int> q = mk(v);
        reverseQueue(q);
        check("queue " + show(v), V(v.rbegin(), v.rend()), dump(q));
    }
}

QUESTION("L27-B", "reverseFirstK (GfG)", "reverseFirstK(") {
    for (auto& c : PDF_FK) {
        std::queue<int> q = mk(c.q);
        reverseFirstK(q, c.k);
        check("queue " + show(c.q) + ", k=" + std::to_string(c.k), c.after, dump(q));
    }
}

QUESTION("L27-M", "reverseAlternateTriples (midterm)", "reverseAlternateTriples(") {
    for (auto& c : PDF_TRI) {
        std::queue<int> q = mk(c.q);
        reverseAlternateTriples(q);
        check("queue " + show(c.q), c.after, dump(q));
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(20, 0, 9), w = v;
        for (size_t s = 0; s + 3 <= w.size(); s += 6) std::reverse(w.begin() + s, w.begin() + s + 3);
        std::queue<int> q = mk(v);
        reverseAlternateTriples(q);
        check("queue " + show(v), w, dump(q));
    }
}

OPTIONAL_QUESTION("L27-X", "reverseFirstKGfG (queue by value)", "reverseFirstKGfG(") {
    std::queue<int> q = mk({1, 2, 3, 4, 5});
    check("GfG example 1", V{3, 2, 1, 4, 5}, dump(reverseFirstKGfG(q, 3)));
    check("the caller's queue is unchanged", V{1, 2, 3, 4, 5}, dump(q));
    check("GfG example 2: k = n", V{4, 3, 2, 1}, dump(reverseFirstKGfG(mk({1, 2, 3, 4}), 4)));
}

OPTIONAL_QUESTION("L27-V", "reverseGroups", "reverseGroups(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, 0, 9), w = v;
        int g = randInt(1, 5);
        for (size_t s = 0; s + g <= w.size(); s += g) std::reverse(w.begin() + s, w.begin() + s + g);
        std::queue<int> q = mk(v);
        reverseGroups(q, g);
        check("queue " + show(v) + ", g=" + std::to_string(g), w, dump(q));
    }
    check("seq 1..7, g = 3", V{3, 2, 1, 6, 5, 4, 7}, [] {
        std::queue<int> q = mk(seq(7));
        reverseGroups(q, 3);
        return dump(q);
    }());
}
