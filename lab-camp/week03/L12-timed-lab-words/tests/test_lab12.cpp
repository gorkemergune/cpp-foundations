// Lab 12 tests.
#include <algorithm>
#include <sstream>

#include "lab12.h"
#include "test.h"

using namespace lab;
using S = std::vector<std::string>;

struct PDF_RW_Case { std::string s; std::string out; };
struct PDF_RLE_Case { std::string s; std::string out; };
struct PDF_MM_Case { std::string line; bool ret; int mn; int mx; };
struct PDF_LCP_Case { S strs; std::string out; };
struct PDF_ROT_Case { std::string a; std::string b; bool ret; };
#include "pdf_cases.inc"

QUESTION("L12-A", "reverseWords (LC 151)", "reverseWords(") {
    for (auto& c : PDF_RW) check("s=" + show(c.s), c.out, reverseWords(c.s));
    for (int i = 0; i < RANDOM_CASES; i++) {
        S w;
        std::string s(randInt(0, 2), ' ');
        int n = randInt(0, 5);
        for (int k = 0; k < n; k++) {
            w.push_back(std::string(randInt(1, 3), "abc"[randInt(0, 2)]));
            s += w.back() + std::string(randInt(1, 3), ' ');
        }
        std::string want;
        for (int k = n - 1; k >= 0; k--) want += w[k] + (k ? " " : "");
        check("s=" + show(s), want, reverseWords(s));
    }
}

QUESTION("L12-B", "compress (run-length)", "compress(") {
    for (auto& c : PDF_RLE) check("s=" + show(c.s), c.out, compress(c.s));
}

QUESTION("L12-C", "minMaxTokens (midterm variant)", "minMaxTokens(") {
    for (auto& c : PDF_MM) {
        int mn = 777, mx = 777;
        bool got = minMaxTokens(c.line, mn, mx);
        check("line=" + show(c.line) + " (return)", c.ret, got);
        check("line=" + show(c.line) + " (mn)", c.mn, mn);
        check("line=" + show(c.line) + " (mx)", c.mx, mx);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        std::vector<int> v = randVec(8, -30, 30, 1);
        std::string line;
        for (int x : v) line += " " + std::to_string(x);
        int mn = 777, mx = 777;
        minMaxTokens(line, mn, mx);
        check("line=" + show(line) + " (mn)", *std::min_element(v.begin(), v.end()), mn);
        check("line=" + show(line) + " (mx)", *std::max_element(v.begin(), v.end()), mx);
    }
}

OPTIONAL_QUESTION("L12-X", "longestCommonPrefix (LC 14)", "longestCommonPrefix(") {
    for (auto& c : PDF_LCP) check("strs=" + show(c.strs), c.out, longestCommonPrefix(c.strs));
}

OPTIONAL_QUESTION("L12-V", "isRotationString", "isRotationString(") {
    for (auto& c : PDF_ROT) check("a=" + show(c.a) + ", b=" + show(c.b), c.ret, isRotationString(c.a, c.b));
}
