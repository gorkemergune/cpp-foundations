// Lab 08 tests. PDF rows + random sorted arrays compared with <algorithm>.
#include <algorithm>

#include "lab08.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_MERGE_Case { V a; V b; V out; };
struct PDF_LC88_Case { V nums1; int m; V nums2; int n; V after; };
struct PDF_INTER_Case { V a; V b; V out; };
struct PDF_SQ_Case { V nums; V out; };
struct PDF_DEDUP_Case { V a; V prefix; };
#include "pdf_cases.inc"

static V sortedRand(int maxLen) {
    V v = randVec(maxLen, -9, 9);
    std::sort(v.begin(), v.end());
    return v;
}

QUESTION("L08-A", "mergeInto", "mergeInto(") {
    auto run = [](const V& a, const V& b, const V& want) {
        V out(a.size() + b.size() + 1, 12345);
        int k = mergeInto(a.data(), (int)a.size(), b.data(), (int)b.size(), out.data());
        std::string d = "a=" + show(a) + ", b=" + show(b);
        check(d + " (return)", (int)want.size(), k);
        check(d, want, V(out.begin(), out.begin() + want.size()));
        check(d + " (no write past na + nb)", 12345, out.back());
    };
    for (auto& c : PDF_MERGE) run(c.a, c.b, c.out);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V a = sortedRand(8), b = sortedRand(8), want;
        std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(want));
        run(a, b, want);
    }
}

QUESTION("L08-B", "merge (LC 88)", "merge(") {
    for (auto c : PDF_LC88) {
        std::string d = "nums1=" + show(c.nums1) + ", m=" + std::to_string(c.m) + ", nums2=" + show(c.nums2);
        merge(c.nums1, c.m, c.nums2, c.n);
        check(d, c.after, c.nums1);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V a = sortedRand(8), b = sortedRand(8), want;
        std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(want));
        V nums1 = a;
        nums1.resize(a.size() + b.size(), 0);
        std::string d = "nums1=" + show(nums1) + ", nums2=" + show(b);
        merge(nums1, (int)a.size(), b, (int)b.size());
        check(d, want, nums1);
    }
}

QUESTION("L08-C", "intersectSorted", "intersectSorted(") {
    auto run = [](const V& a, const V& b, const V& want) {
        V out(a.size() + b.size() + 1, 12345);
        int k = intersectSorted(a.data(), (int)a.size(), b.data(), (int)b.size(), out.data());
        std::string d = "a=" + show(a) + ", b=" + show(b);
        check(d + " (return)", (int)want.size(), k);
        if (k == (int)want.size()) check(d, want, V(out.begin(), out.begin() + k));
    };
    for (auto& c : PDF_INTER) run(c.a, c.b, c.out);
    for (int i = 0; i < RANDOM_CASES; i++) {
        V a = sortedRand(8), b = sortedRand(8), want;
        std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(want));
        want.erase(std::unique(want.begin(), want.end()), want.end());
        run(a, b, want);
    }
}

OPTIONAL_QUESTION("L08-X", "sortedSquares (LC 977)", "sortedSquares(") {
    for (auto& c : PDF_SQ) check("nums=" + show(c.nums), c.out, sortedSquares(c.nums));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v = sortedRand(10), want;
        for (int x : v) want.push_back(x * x);
        std::sort(want.begin(), want.end());
        check("nums=" + show(v), want, sortedSquares(v));
    }
}

OPTIONAL_QUESTION("L08-V", "removeDuplicatesSorted", "removeDuplicatesSorted(") {
    for (auto c : PDF_DEDUP) {
        std::string d = "a=" + show(c.a);
        int k = removeDuplicatesSorted(c.a.data(), (int)c.a.size());
        check(d + " (return)", (int)c.prefix.size(), k);
        if (k == (int)c.prefix.size()) check(d + " (first k)", c.prefix, V(c.a.begin(), c.a.begin() + k));
    }
}
