// Lab 04 tests. The table rows of the PDF (pdf_cases.inc) + RANDOM_CASES random inputs,
// compared with std::rotate / std::stable_partition (not allowed in your solution).
#include <algorithm>

#include "lab04.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_ZEROES_Case { V nums; V after; };
struct PDF_ROTATE_Case { V v; int k; V result; };
struct PDF_RIGHT_Case { V nums; int k; V after; };
struct PDF_ISROT_Case { V a; V b; bool ret; };
#include "pdf_cases.inc"

static std::string S(const V& v) { return show(v); }
static std::string I(int x) { return std::to_string(x); }
static V refLeft(V v, int k) {
    if (!v.empty()) std::rotate(v.begin(), v.begin() + k % v.size(), v.end());
    return v;
}

QUESTION("L04-A", "moveZeroes (LC 283)", "moveZeroes(") {
    auto run = [](V v, const V& after) {
        std::string d = "nums=" + S(v);
        moveZeroes(v);
        check(d, after, v);
    };
    for (auto& c : PDF_ZEROES) run(c.nums, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(12, 0, 3), ref = v;
        std::stable_partition(ref.begin(), ref.end(), [](int x) { return x != 0; });
        run(v, ref);
    }
}

QUESTION("L04-B", "rotatedCopy", "rotatedCopy(") {
    auto run = [](const V& v, int k, const V& result) {
        V input = v;
        std::string d = "v=" + S(v) + ", k=" + I(k);
        check(d, result, rotatedCopy(input, k));
        check(d + " (input must not change)", v, input);
    };
    for (auto& c : PDF_ROTATE) run(c.v, c.k, c.result);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9);
        int k = randInt(0, 25);
        run(v, k, refLeft(v, k));
    }
}

QUESTION("L04-C", "rotateLeft (in place)", "rotateLeft(") {
    auto run = [](V v, int k, const V& result) {
        std::string d = "v=" + S(v) + ", k=" + I(k);
        const int* before = v.data();
        size_t capBefore = v.capacity();
        rotateLeft(v, k);
        check(d, result, v);
        checkTrue(d + " (same storage)", v.data() == before && v.capacity() == capBefore,
                  "the vector was given new storage: use swaps in place, no second vector");
    };
    for (auto& c : PDF_ROTATE) run(c.v, c.k, c.result);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9);
        int k = randInt(0, 25);
        run(v, k, refLeft(v, k));
    }
}

OPTIONAL_QUESTION("L04-X", "rotateRight (LC 189)", "rotateRight(") {
    auto run = [](V v, int k, const V& after) {
        std::string d = "nums=" + S(v) + ", k=" + I(k);
        rotateRight(v, k);
        check(d, after, v);
    };
    for (auto& c : PDF_RIGHT) run(c.nums, c.k, c.after);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = randVec(10, 0, 9), ref = v;
        int k = randInt(0, 25);
        if (!ref.empty()) std::rotate(ref.rbegin(), ref.rbegin() + k % ref.size(), ref.rend());
        run(v, k, ref);
    }
}

OPTIONAL_QUESTION("L04-V", "isRotation", "isRotation(") {
    for (auto& c : PDF_ISROT) check("a=" + S(c.a) + ", b=" + S(c.b), c.ret, isRotation(c.a, c.b));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V a = randVec(6, 0, 2), b = refLeft(a, randInt(0, 6));
        if (randInt(0, 1) && !b.empty()) b[randInt(0, (int)b.size() - 1)] = randInt(0, 2);
        bool expected = false;
        for (int k = 0; k <= (int)a.size(); k++) expected |= (refLeft(a, k) == b);
        check("a=" + S(a) + ", b=" + S(b), expected, isRotation(a, b));
    }
}
