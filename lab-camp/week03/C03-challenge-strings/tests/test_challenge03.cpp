// Challenge 03 tests: PDF rows + random strings against brute force.
#include <set>

#include "challenge03.h"
#include "test.h"

using namespace lab;

struct PDF_LONG_Case { std::string s; int ret; };
struct PDF_PAL_Case { std::string s; std::string out; };
struct PDF_ATOI_Case { std::string s; int ret; };
#include "pdf_cases.inc"

static std::string randStr(int maxLen, const std::string& abc) {
    std::string s;
    int n = randInt(0, maxLen);
    for (int i = 0; i < n; i++) s += abc[randInt(0, (int)abc.size() - 1)];
    return s;
}

QUESTION("C03-A", "lengthOfLongestSubstring (LC 3)", "lengthOfLongestSubstring(") {
    for (auto& c : PDF_LONG) check("s=" + show(c.s), c.ret, lengthOfLongestSubstring(c.s));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randStr(14, "abcd ");
        int best = 0;
        for (size_t i = 0; i < s.size(); i++) {
            std::set<char> seen;
            for (size_t j = i; j < s.size() && !seen.count(s[j]); j++) seen.insert(s[j]);
            best = std::max(best, (int)seen.size());
        }
        check("s=" + show(s), best, lengthOfLongestSubstring(s));
    }
}

QUESTION("C03-B", "longestPalindrome (LC 5)", "longestPalindrome(") {
    for (auto& c : PDF_PAL) check("s=" + show(c.s), c.out, longestPalindrome(c.s));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randStr(12, "ab"), best;
        for (size_t i = 0; i < s.size(); i++)
            for (size_t len = 1; i + len <= s.size(); len++) {
                std::string sub = s.substr(i, len), r(sub.rbegin(), sub.rend());
                if (sub == r && len > best.size()) best = sub;
            }
        check("s=" + show(s), best, longestPalindrome(s));
    }
}

QUESTION("C03-C", "myAtoi (LC 8)", "myAtoi(") {
    for (auto& c : PDF_ATOI) check("s=" + show(c.s), c.ret, myAtoi(c.s));
}
