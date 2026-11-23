// Challenge 01 tests: PDF rows + random inputs compared with brute force.
#include <algorithm>
#include <set>

#include "challenge01.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_PROD_Case { V nums; V out; };
struct PDF_WATER_Case { V h; int ret; };
struct PDF_MISSING_Case { V nums; int ret; };
#include "pdf_cases.inc"

QUESTION("C01-A", "productExceptSelf (LC 238)", "productExceptSelf(") {
    for (auto& c : PDF_PROD) check("nums=" + show(c.nums), c.out, productExceptSelf(c.nums));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(8, -3, 3, 2), want(v.size(), 1);
        for (size_t a = 0; a < v.size(); a++)
            for (size_t b = 0; b < v.size(); b++)
                if (a != b) want[a] *= v[b];
        check("nums=" + show(v), want, productExceptSelf(v));
    }
}

QUESTION("C01-B", "maxArea (LC 11)", "maxArea(") {
    for (auto& c : PDF_WATER) check("height=" + show(c.h), c.ret, maxArea(c.h));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V h = randVec(30, 0, 20, 2);
        int best = 0;
        for (size_t a = 0; a < h.size(); a++)
            for (size_t b = a + 1; b < h.size(); b++) best = std::max(best, std::min(h[a], h[b]) * (int)(b - a));
        check("height=" + show(h), best, maxArea(h));
    }
}

QUESTION("C01-C", "firstMissingPositive (LC 41)", "firstMissingPositive(") {
    for (auto c : PDF_MISSING) {
        std::string d = "nums=" + show(c.nums);
        check(d, c.ret, firstMissingPositive(c.nums));
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, -3, 12);
        std::set<int> s(v.begin(), v.end());
        int want = 1;
        while (s.count(want)) want++;
        std::string d = "nums=" + show(v);
        check(d, want, firstMissingPositive(v));
    }
}
