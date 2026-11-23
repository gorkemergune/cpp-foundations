// Challenge 11 tests.
#include <algorithm>
#include <set>

#include "challenge11.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;
using G = std::vector<std::vector<std::string>>;

struct PDF_GA_Case { std::vector<std::string> words; G groups; };
struct PDF_LC_Case { V nums; int ret; };
struct PDF_SS_Case { V nums; int k; int ret; };
#include "pdf_cases.inc"

static G canon(G g) {                       // sort inside every group, then the groups
    for (auto& x : g) std::sort(x.begin(), x.end());
    std::sort(g.begin(), g.end());
    return g;
}

QUESTION("C11-A", "groupAnagrams (LC 49)", "groupAnagrams(") {
    for (auto& c : PDF_GA) check("words " + show(c.words), canon(c.groups), canon(groupAnagrams(c.words)));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::vector<std::string> w;
        for (int k = randInt(0, 8); k > 0; k--) {
            std::string s;
            for (int j = randInt(0, 3); j > 0; j--) s += (char)randInt('a', 'c');
            w.push_back(s);
        }
        G want;
        std::vector<bool> used(w.size());
        for (size_t i = 0; i < w.size(); i++) {
            if (used[i]) continue;
            std::string a = w[i];
            std::sort(a.begin(), a.end());
            want.push_back({});
            for (size_t j = i; j < w.size(); j++) {
                std::string b = w[j];
                std::sort(b.begin(), b.end());
                if (!used[j] && a == b) { used[j] = true; want.back().push_back(w[j]); }
            }
        }
        check("words " + show(w), canon(want), canon(groupAnagrams(w)));
    }
}

QUESTION("C11-B", "longestConsecutive (LC 128)", "longestConsecutive(") {
    for (auto& c : PDF_LC) check("nums " + show(c.nums), c.ret, longestConsecutive(c.nums));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, -10, 10);
        std::set<int> s(v.begin(), v.end());
        int best = 0;
        for (int x : s) {
            int len = 0;
            while (s.count(x + len)) len++;
            best = std::max(best, len);
        }
        check("nums " + show(v), best, longestConsecutive(v));
    }
}

QUESTION("C11-C", "subarraySum (LC 560)", "subarraySum(") {
    for (auto& c : PDF_SS) check("nums " + show(c.nums) + ", k=" + std::to_string(c.k), c.ret, subarraySum(c.nums, c.k));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, -3, 3);
        int k = randInt(-4, 4), want = 0;
        for (size_t i = 0; i < v.size(); i++) {
            int s = 0;
            for (size_t j = i; j < v.size(); j++) want += (s += v[j]) == k;
        }
        check("nums " + show(v) + ", k=" + std::to_string(k), want, subarraySum(v, k));
    }
}
