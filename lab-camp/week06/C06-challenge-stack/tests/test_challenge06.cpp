// Challenge 06 tests: PDF rows + random inputs against brute force.
#include <algorithm>

#include "challenge06.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_TEMP_Case { V t; V out; };
struct PDF_DEC_Case { std::string s; std::string out; };
struct PDF_HIST_Case { V h; int ret; };
#include "pdf_cases.inc"

QUESTION("C06-A", "dailyTemperatures (LC 739)", "dailyTemperatures(") {
    for (auto& c : PDF_TEMP) check("t=" + show(c.t), c.out, dailyTemperatures(c.t));
    for (int k = 0; k < RANDOM_CASES; k++) {
        V t = randVec(15, 30, 40), w(t.size(), 0);
        for (size_t i = 0; i < t.size(); i++)
            for (size_t j = i + 1; j < t.size(); j++)
                if (t[j] > t[i]) { w[i] = (int)(j - i); break; }
        check("t=" + show(t), w, dailyTemperatures(t));
    }
}

QUESTION("C06-B", "decodeString (LC 394)", "decodeString(") {
    for (auto& c : PDF_DEC) check("s=" + show(c.s), c.out, decodeString(c.s));
}

QUESTION("C06-C", "largestRectangleArea (LC 84)", "largestRectangleArea(") {
    for (auto& c : PDF_HIST) check("heights=" + show(c.h), c.ret, largestRectangleArea(c.h));
    for (int k = 0; k < RANDOM_CASES; k++) {
        V h = randVec(12, 0, 8);
        int best = 0;
        for (size_t i = 0; i < h.size(); i++) {
            int lo = h[i];
            for (size_t j = i; j < h.size(); j++) {
                lo = std::min(lo, h[j]);
                best = std::max(best, lo * (int)(j - i + 1));
            }
        }
        check("heights=" + show(h), best, largestRectangleArea(h));
    }
}
