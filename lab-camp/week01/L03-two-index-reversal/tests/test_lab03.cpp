// Lab 03 tests. The table rows of the PDF (pdf_cases.inc) + RANDOM_CASES random inputs,
// compared with std::reverse (which this lab does not allow in your solution).
#include <algorithm>

#include "lab03.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_RANGE_Case { V v; int lo; int hi; V after; };
struct PDF_ISREV_Case { V a; V b; bool ret; };
struct PDF_TRIPLES_Case { V v; V after; };
struct PDF_GROUPS_Case { V arr; int k; V after; };
struct PDF_FIRSTK_Case { V v; int k; V after; };
#include "pdf_cases.inc"

static std::string S(const V& v) { return show(v); }
static std::string I(int x) { return std::to_string(x); }

static V refTriples(V v) {
    for (size_t s = 0; s + 3 <= v.size(); s += 6) std::reverse(v.begin() + s, v.begin() + s + 3);
    return v;
}

QUESTION("L03-A", "reverseRange", "reverseRange(") {
    auto run = [](V v, int lo, int hi, const V& after) {
        std::string d = "v=" + S(v) + ", lo=" + I(lo) + ", hi=" + I(hi);
        reverseRange(v, lo, hi);
        check(d, after, v);
    };
    for (auto& c : PDF_RANGE) run(c.v, c.lo, c.hi, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9), ref = v;
        int lo = randInt(-1, (int)v.size()), hi = randInt(-1, (int)v.size());
        if (lo >= 0 && hi < (int)v.size() && lo < hi) std::reverse(ref.begin() + lo, ref.begin() + hi + 1);
        run(v, lo, hi, ref);
    }
}

QUESTION("L03-B", "isReverseOf", "isReverseOf(") {
    for (auto& c : PDF_ISREV) check("a=" + S(c.a) + ", b=" + S(c.b), c.ret, isReverseOf(c.a, c.b));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V a = randVec(6, 0, 2), b = a;
        std::reverse(b.begin(), b.end());
        int mode = randInt(0, 2);
        if (mode == 1 && !b.empty()) b[randInt(0, (int)b.size() - 1)] = randInt(0, 2);
        if (mode == 2) b.push_back(randInt(0, 2));
        V rb = b;
        std::reverse(rb.begin(), rb.end());
        check("a=" + S(a) + ", b=" + S(b), a == rb, isReverseOf(a, b));
    }
}

QUESTION("L03-M", "reverseAlternateTriples (midterm)", "reverseAlternateTriples(") {
    for (auto c : PDF_TRIPLES) {
        std::string d = "v=" + S(c.v);
        reverseAlternateTriples(c.v);
        check(d, c.after, c.v);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(20, 0, 9), ref = refTriples(v);
        std::string d = "v=" + S(v);
        reverseAlternateTriples(v);
        check(d, ref, v);
    }
}

OPTIONAL_QUESTION("L03-X", "reverseInGroups (GfG)", "reverseInGroups(") {
    auto run = [](V v, int k, const V& after) {
        std::string d = "arr=" + S(v) + ", k=" + I(k);
        reverseInGroups(v, k);
        check(d, after, v);
    };
    for (auto& c : PDF_GROUPS) run(c.arr, c.k, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, 0, 9), ref = v;
        int k = randInt(1, 6);
        for (size_t s = 0; s < ref.size(); s += k) std::reverse(ref.begin() + s, ref.begin() + std::min(ref.size(), s + k));
        run(v, k, ref);
    }
}

OPTIONAL_QUESTION("L03-V", "reverseFirstK", "reverseFirstK(") {
    auto run = [](V v, int k, const V& after) {
        std::string d = "v=" + S(v) + ", k=" + I(k);
        reverseFirstK(v, k);
        check(d, after, v);
    };
    for (auto& c : PDF_FIRSTK) run(c.v, c.k, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9), ref = v;
        int k = randInt(-1, (int)v.size() + 1);
        if (k > 0 && k <= (int)v.size()) std::reverse(ref.begin(), ref.begin() + k);
        run(v, k, ref);
    }
}
