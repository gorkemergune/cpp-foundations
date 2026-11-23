// Mock B tests.
#include <algorithm>
#include <vector>

#include "mock30.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_MIN_Case { std::string s; bool ret; int out; };
struct PDF_REV_Case { std::string a; std::string b; bool ret; };
struct PDF_GRP_Case { V q; int g; V after; };
#include "pdf_cases.inc"

QUESTION("L30-A", "minNumberInText", "minNumberInText(") {
    for (auto& c : PDF_MIN) {
        int out = 777;
        bool got = minNumberInText(c.s, out);
        check("s=" + show(c.s) + " (return)", c.ret, got);
        check("s=" + show(c.s) + " (out)", c.out, out);
    }
}

QUESTION("L30-B", "areReversesSlides (two slides Stacks)", "areReversesSlides(") {
    for (auto& c : PDF_REV) check("a=" + show(c.a) + ", b=" + show(c.b), c.ret, areReversesSlides(c.a, c.b));
}

QUESTION("L30-C", "reverseAlternateGroupsSlides", "reverseAlternateGroupsSlides(") {
    auto run = [](const V& v, int g, const V& want) {
        Queue q;
        for (int x : v) q.enqueue(x);
        reverseAlternateGroupsSlides(q, (int)v.size(), g);
        V got;
        QueueItemType x;
        while (q.dequeue(x)) got.push_back(x);
        check("queue " + show(v) + ", g=" + std::to_string(g), want, got);
    };
    for (auto& c : PDF_GRP) run(c.q, c.g, c.after);
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, 0, 9), w = v;
        int g = randInt(1, 4);
        for (size_t s = 0; s + g <= w.size(); s += 2 * g) std::reverse(w.begin() + s, w.begin() + s + g);
        run(v, g, w);
    }
}
