// Lab 09 tests. PDF rows + random strings compared with the standard library.
#include <algorithm>
#include <cctype>

#include "lab09.h"
#include "test.h"

using namespace lab;

struct PDF_REV_Case { std::string s; std::string out; };
struct PDF_COUNT_Case { std::string s; std::string c; int ret; };
struct PDF_AREREV_Case { std::string a; std::string b; bool ret; };
struct PDF_PAL_Case { std::string s; bool ret; };
struct PDF_WORD_Case { std::string text; std::string word; int ret; };
#include "pdf_cases.inc"

static std::string randStr(int maxLen, const std::string& alphabet) {
    std::string s;
    int n = randInt(0, maxLen);
    for (int i = 0; i < n; i++) s += alphabet[randInt(0, (int)alphabet.size() - 1)];
    return s;
}

QUESTION("L09-A", "reversed", "reversed(") {
    for (auto& c : PDF_REV) check("s=" + show(c.s), c.out, reversed(c.s));
    for (int i = 0; i < RANDOM_CASES; i++) {
        std::string s = randStr(12, "abcxyz "), r = s;
        std::reverse(r.begin(), r.end());
        check("s=" + show(s), r, reversed(s));
    }
}

QUESTION("L09-B", "countChar", "countChar(") {
    for (auto& c : PDF_COUNT) check("s=" + show(c.s) + ", c=" + show(c.c), c.ret, countChar(c.s, c.c[0]));
}

QUESTION("L09-M1", "areReverses (midterm)", "areReverses(") {
    for (auto& c : PDF_AREREV) check("a=" + show(c.a) + ", b=" + show(c.b), c.ret, areReverses(c.a, c.b));
    for (int i = 0; i < RANDOM_CASES; i++) {
        std::string a = randStr(6, "ab"), b = a;
        std::reverse(b.begin(), b.end());
        if (randInt(0, 1) && !b.empty()) b[randInt(0, (int)b.size() - 1)] = "ab"[randInt(0, 1)];
        std::string rb = b;
        std::reverse(rb.begin(), rb.end());
        check("a=" + show(a) + ", b=" + show(b), a == rb, areReverses(a, b));
    }
}

QUESTION("L09-M2", "isPalindromeAlnum (LC 125)", "isPalindromeAlnum(") {
    for (auto& c : PDF_PAL) check("s=" + show(c.s), c.ret, isPalindromeAlnum(c.s));
    for (int i = 0; i < RANDOM_CASES; i++) {
        std::string s = randStr(10, "aAbB1 ,:"), clean;
        for (char ch : s)
            if (std::isalnum((unsigned char)ch)) clean += (char)std::tolower((unsigned char)ch);
        std::string r = clean;
        std::reverse(r.begin(), r.end());
        check("s=" + show(s), clean == r, isPalindromeAlnum(s));
    }
}

OPTIONAL_QUESTION("L09-X", "reverseString (LC 344)", "reverseString(") {
    std::vector<char> h = {'h', 'e', 'l', 'l', 'o'};
    reverseString(h);
    check("{'h','e','l','l','o'}", std::string("olleh"), std::string(h.begin(), h.end()));
    std::vector<char> e;
    reverseString(e);
    check("{}", std::string(""), std::string(e.begin(), e.end()));
}

OPTIONAL_QUESTION("L09-V", "countWord", "countWord(") {
    for (auto& c : PDF_WORD) check("text=" + show(c.text) + ", word=" + show(c.word), c.ret, countWord(c.text, c.word));
}
