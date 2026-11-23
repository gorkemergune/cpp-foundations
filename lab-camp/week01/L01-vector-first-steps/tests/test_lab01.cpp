// Lab 01 tests. The table rows of the PDF (pdf_cases.inc) + RANDOM_CASES random inputs.
// The random inputs are compared with standard-library versions (<numeric>, <algorithm>).
#include <algorithm>
#include <numeric>

#include "lab01.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_SUM_Case { V in; int out; };
struct PDF_EVENS_Case { V in; V out; };
struct PDF_RUNNING_Case { V in; V out; };
struct PDF_CONCAT_Case { V in; V out; };
struct PDF_RUNMAX_Case { V in; V out; };
#include "pdf_cases.inc"

static std::string In(const V& v) { return "in=" + show(v); }

QUESTION("L01-A", "sumAll", "sumAll(") {
    for (auto& c : PDF_SUM) check(In(c.in), c.out, sumAll(c.in));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(20, -50, 50);
        check(In(v), std::accumulate(v.begin(), v.end(), 0), sumAll(v));
    }
}

QUESTION("L01-B", "evensOnly", "evensOnly(") {
    for (auto& c : PDF_EVENS) check(In(c.in), c.out, evensOnly(c.in));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(20, -9, 9), ref;
        std::copy_if(v.begin(), v.end(), std::back_inserter(ref), [](int x) { return x % 2 == 0; });
        check(In(v), ref, evensOnly(v));
    }
}

QUESTION("L01-M", "runningTotals", "runningTotals(") {
    for (auto& c : PDF_RUNNING) check(In(c.in), c.out, runningTotals(c.in));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(25, -100, 100), ref(v.size());
        std::partial_sum(v.begin(), v.end(), ref.begin());
        check(In(v), ref, runningTotals(v));
    }
    V caller = {3, -1, 4, 0};
    runningTotals(caller);
    check("caller's vector after the call (passed by value)", V{3, -1, 4, 0}, caller);
}

OPTIONAL_QUESTION("L01-X", "getConcatenation (LC 1929)", "getConcatenation(") {
    for (auto& c : PDF_CONCAT) check(In(c.in), c.out, getConcatenation(c.in));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(15, 0, 9), ref = v;
        ref.insert(ref.end(), v.begin(), v.end());
        check(In(v), ref, getConcatenation(v));
    }
}

OPTIONAL_QUESTION("L01-V", "runningMax", "runningMax(") {
    for (auto& c : PDF_RUNMAX) check(In(c.in), c.out, runningMax(c.in));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(20, -30, 30), ref = v;
        for (size_t j = 1; j < ref.size(); j++) ref[j] = std::max(ref[j], ref[j - 1]);
        check(In(v), ref, runningMax(v));
    }
}
