// Lab 42 tests.
#include <algorithm>
#include <set>

#include "lab42.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;
using WC = std::vector<std::pair<std::string, int>>;

struct PDF_U_Case { std::string s; int ret; };
struct PDF_NB_Case { V nums; int k; bool ret; };
struct PDF_LS_Case { std::string s; int ret; };
#include "pdf_cases.inc"

static std::string randWord(int maxLen, char hi) {
    std::string s;
    for (int k = randInt(0, maxLen); k > 0; k--) s += (char)randInt('a', hi);
    return s;
}

QUESTION("L42-A", "wordCount (std::map)", "wordCount(") {
    check("\"b a b\"", WC{{"a", 1}, {"b", 2}}, wordCount("b a b"));
    check("sorted by word", WC{{"be", 2}, {"not", 1}, {"or", 1}, {"to", 2}}, wordCount("to be\tor\nnot  to be"));
    check("empty text", WC{}, wordCount("   "));
    check("case matters", WC{{"A", 1}, {"a", 1}}, wordCount("a A"));
}

QUESTION("L42-B", "firstUniqChar (LC 387)", "firstUniqChar(") {
    for (auto& c : PDF_U) check("s=" + show(c.s), c.ret, firstUniqChar(c.s));
}

QUESTION("L42-M1", "containsNearbyDuplicate (LC 219)", "containsNearbyDuplicate(") {
    for (auto& c : PDF_NB) check("nums=" + show(c.nums) + ", k=" + std::to_string(c.k), c.ret, containsNearbyDuplicate(c.nums, c.k));
    for (int t = 0; t < RANDOM_CASES; t++) {
        V v = randVec(15, 0, 6);
        int k = randInt(0, 5);
        bool want = false;
        for (size_t i = 0; i < v.size(); i++)
            for (size_t j = i + 1; j < v.size() && (int)(j - i) <= k; j++) want = want || v[i] == v[j];
        check("nums=" + show(v) + ", k=" + std::to_string(k), want, containsNearbyDuplicate(v, k));
    }
}

QUESTION("L42-M2", "isAnagram (LC 242)", "isAnagram(") {
    check("anagram / nagaram", true, isAnagram("anagram", "nagaram"));
    check("rat / car", false, isAnagram("rat", "car"));
    check("ab / a", false, isAnagram("ab", "a"));
    check("aab / abb", false, isAnagram("aab", "abb"));
    check("empty", true, isAnagram("", ""));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string a = randWord(8, 'c'), b = randInt(0, 1) ? a : randWord(8, 'c');
        std::shuffle(b.begin(), b.end(), rng());
        std::string sa = a, sb = b;
        std::sort(sa.begin(), sa.end());
        std::sort(sb.begin(), sb.end());
        check(show(a) + " / " + show(b), sa == sb, isAnagram(a, b));
    }
}

QUESTION("L42-M3", "lengthOfLongestSubstring (LC 3)", "lengthOfLongestSubstring(") {
    for (auto& c : PDF_LS) check("s=" + show(c.s), c.ret, lengthOfLongestSubstring(c.s));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randWord(14, 'e');
        int best = 0;
        for (size_t i = 0; i < s.size(); i++) {
            std::set<char> seen;
            for (size_t j = i; j < s.size() && seen.insert(s[j]).second; j++) best = std::max(best, (int)(j - i + 1));
        }
        check("s=" + show(s), best, lengthOfLongestSubstring(s));
    }
}

OPTIONAL_QUESTION("L42-X", "isIsomorphic (LC 205)", "isIsomorphic(") {
    check("egg / add", true, isIsomorphic("egg", "add"));
    check("foo / bar", false, isIsomorphic("foo", "bar"));
    check("paper / title", true, isIsomorphic("paper", "title"));
    check("badc / baba (two letters to one)", false, isIsomorphic("badc", "baba"));
}

OPTIONAL_QUESTION("L42-V", "countDistinct", "countDistinct(") {
    check("{3,1,3,2,1}", 3, countDistinct({3, 1, 3, 2, 1}));
    check("{}", 0, countDistinct({}));
}
