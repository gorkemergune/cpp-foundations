// Lab 45 tests.
#include <algorithm>

#include "lab45.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;
using P = std::vector<std::pair<int, int>>;

struct PDF_HS_Case { V a; V sorted; };
struct PDF_KTH_Case { V nums; int k; int ret; };
#include "pdf_cases.inc"

QUESTION("L45-A", "drainMaxFirst (priority_queue)", "drainMaxFirst(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, -9, 9), w = v;
        std::sort(w.rbegin(), w.rend());
        check(show(v), w, drainMaxFirst(v));
    }
}

QUESTION("L45-B", "drainMinFirst (greater<int>)", "drainMinFirst(") {
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(10, -9, 9), w = v;
        std::sort(w.begin(), w.end());
        check(show(v), w, drainMinFirst(v));
    }
}

QUESTION("L45-M1", "heapSort (slides 21-28)", "heapSort(") {
    for (auto& c : PDF_HS) {
        V a = c.a;
        heapSort(a);
        check("heapSort " + show(c.a), c.sorted, a);
    }
    for (int t = 0; t < RANDOM_CASES; t++) {
        V a = randVec(20, -50, 50), w = a;
        std::sort(w.begin(), w.end());
        heapSort(a);
        check("heapSort", w, a);
    }
}

QUESTION("L45-M2", "findKthLargest (LC 215)", "findKthLargest(") {
    for (auto& c : PDF_KTH) check("nums=" + show(c.nums) + ", k=" + std::to_string(c.k), c.ret, findKthLargest(c.nums, c.k));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(12, -9, 9, 1), w = v;
        int k = randInt(1, (int)v.size());
        std::sort(w.rbegin(), w.rend());
        check("nums=" + show(v) + ", k=" + std::to_string(k), w[k - 1], findKthLargest(v, k));
    }
}

QUESTION("L45-M3", "sortKSorted", "sortKSorted(") {
    check("{6,5,3,2,8,10,9}, k=3", V{2, 3, 5, 6, 8, 9, 10}, sortKSorted({6, 5, 3, 2, 8, 10, 9}, 3));
    check("{2,1,4,3}, k=1", V{1, 2, 3, 4}, sortKSorted({2, 1, 4, 3}, 1));
    check("k=0: already sorted", V{1, 2, 3}, sortKSorted({1, 2, 3}, 0));
    check("empty", V{}, sortKSorted({}, 2));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V s = randVec(15, 0, 30), a;
        std::sort(s.begin(), s.end());
        int k = randInt(0, 4);
        a = s;
        for (size_t i = 0; i + 1 < a.size(); i++)          // small swaps keep everything within k
            if (k > 0 && randInt(0, 1)) {
                size_t j = std::min(a.size() - 1, i + randInt(1, k));
                std::swap(a[i], a[j]);
                i = j;
            }
        check("k=" + std::to_string(k) + " " + show(a), s, sortKSorted(a, k));
    }
}

OPTIONAL_QUESTION("L45-X", "kClosest (LC 973)", "kClosest(") {
    auto sorted = [](P p) { std::sort(p.begin(), p.end()); return p; };
    check("LeetCode example 1", P{{-2, 2}}, sorted(kClosest({{1, 3}, {-2, 2}}, 1)));
    check("LeetCode example 2", sorted(P{{3, 3}, {-2, 4}}), sorted(kClosest({{3, 3}, {5, -1}, {-2, 4}}, 2)));
}

OPTIONAL_QUESTION("L45-V", "byLength (comparator)", "byLength(") {
    check("ccc a bb aa", std::vector<std::string>{"a", "aa", "bb", "ccc"}, byLength({"ccc", "a", "bb", "aa"}));
    check("empty", std::vector<std::string>{}, byLength({}));
}
