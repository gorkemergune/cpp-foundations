// Lab 05 tests. PDF rows (pdf_cases.inc) + random arrays compared with <algorithm>.
#include <algorithm>

#include "lab05.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_SUM_Case { V a; int ret; };
struct PDF_SQ_Case { int n; V after; };
struct PDF_MINMAX_Case { V a; bool ret; int minIdx; int maxIdx; };
struct PDF_GETMM_Case { V a; int mn; int mx; };
struct PDF_SECOND_Case { V a; int ret; };
#include "pdf_cases.inc"

static std::string S(const V& v) { return "a=" + show(v) + ", n=" + std::to_string(v.size()); }

QUESTION("L05-A", "sumArray", "sumArray(") {
    for (auto& c : PDF_SUM) check(S(c.a), c.ret, sumArray(c.a.data(), (int)c.a.size()));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(20, -50, 50);
        int sum = 0;
        for (int x : v) sum += x;
        check(S(v), sum, sumArray(v.data(), (int)v.size()));
    }
}

QUESTION("L05-B", "fillSquares", "fillSquares(") {
    for (auto& c : PDF_SQ) {
        V buf(c.n + 2, -7);                       // two guard cells after the n slots
        fillSquares(buf.data(), c.n);
        check("n=" + std::to_string(c.n), c.after, V(buf.begin(), buf.begin() + c.n));
        check("n=" + std::to_string(c.n) + " (cells after a[n-1] must stay untouched)", V{-7, -7}, V(buf.end() - 2, buf.end()));
    }
}

QUESTION("L05-M", "minMaxIndex", "minMaxIndex(") {
    auto run = [](const V& a, bool ret, int mi, int ma) {
        int lo = -100, hi = -100;
        bool got = minMaxIndex(a.data(), (int)a.size(), lo, hi);
        check(S(a) + " (return)", ret, got);
        check(S(a) + " (minIdx)", mi, lo);
        check(S(a) + " (maxIdx)", ma, hi);
    };
    for (auto& c : PDF_MINMAX) run(c.a, c.ret, c.minIdx, c.maxIdx);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, -9, 9, 1);
        run(v, true, (int)(std::min_element(v.begin(), v.end()) - v.begin()),
            (int)(std::max_element(v.begin(), v.end()) - v.begin()));
    }
}

OPTIONAL_QUESTION("L05-X", "getMinMax (GfG)", "getMinMax(") {
    for (auto& c : PDF_GETMM) {
        auto p = getMinMax(c.a.data(), (int)c.a.size());
        check(S(c.a) + " (min)", c.mn, p.first);
        check(S(c.a) + " (max)", c.mx, p.second);
    }
}

OPTIONAL_QUESTION("L05-V", "secondLargest (GfG)", "secondLargest(") {
    for (auto& c : PDF_SECOND) check(S(c.a), c.ret, secondLargest(c.a.data(), (int)c.a.size()));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9);
        V d = v;
        std::sort(d.begin(), d.end());
        d.erase(std::unique(d.begin(), d.end()), d.end());
        check(S(v), d.size() >= 2 ? d[d.size() - 2] : -1, secondLargest(v.data(), (int)v.size()));
    }
}
