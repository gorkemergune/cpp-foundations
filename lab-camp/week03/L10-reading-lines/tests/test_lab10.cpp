// Lab 10 tests. PDF rows + random lines.
#include <algorithm>
#include <sstream>

#include "lab10.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;
using S = std::vector<std::string>;

struct PDF_SPLIT_Case { std::string line; S words; };
struct PDF_SUM_Case { std::string line; int ret; };
struct PDF_MIN_Case { std::string line; bool ret; int out; };
struct PDF_WPL_Case { std::string input; V counts; };
struct PDF_ASC_Case { std::string s; bool ret; };
struct PDF_MAX_Case { std::string line; bool ret; int out; int index; };
#include "pdf_cases.inc"

static std::string joinRand(V& v) {
    v = randVec(8, -20, 20);
    std::string s;
    for (int x : v) s += std::string(randInt(1, 3), ' ') + std::to_string(x);
    return s + std::string(randInt(0, 2), ' ');
}

QUESTION("L10-A", "splitWords", "splitWords(") {
    for (auto& c : PDF_SPLIT) check("line=" + show(c.line), c.words, splitWords(c.line));
}

QUESTION("L10-B", "sumLine", "sumLine(") {
    for (auto& c : PDF_SUM) check("line=" + show(c.line), c.ret, sumLine(c.line));
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v;
        std::string s = joinRand(v);
        int sum = 0;
        for (int x : v) sum += x;
        check("line=" + show(s), sum, sumLine(s));
    }
}

QUESTION("L10-M1", "minToken (midterm)", "minToken(") {
    for (auto& c : PDF_MIN) {
        int out = 777;
        bool got = minToken(c.line, out);
        check("line=" + show(c.line) + " (return)", c.ret, got);
        check("line=" + show(c.line) + " (out)", c.out, out);
    }
    for (int i = 0; i < RANDOM_CASES; i++) {
        V v;
        std::string s = joinRand(v);
        int out = 777;
        bool got = minToken(s, out);
        check("line=" + show(s) + " (return)", !v.empty(), got);
        check("line=" + show(s) + " (out)", v.empty() ? 777 : *std::min_element(v.begin(), v.end()), out);
    }
}

QUESTION("L10-M2", "wordsPerLine (cin >> n, then getline)", "wordsPerLine(") {
    for (auto& c : PDF_WPL) {
        std::istringstream in(c.input);
        check("input=" + show(c.input), c.counts, wordsPerLine(in));
    }
}

OPTIONAL_QUESTION("L10-X", "areNumbersAscending (LC 2042)", "areNumbersAscending(") {
    for (auto& c : PDF_ASC) check("s=" + show(c.s), c.ret, areNumbersAscending(c.s));
}

OPTIONAL_QUESTION("L10-V", "maxToken", "maxToken(") {
    for (auto& c : PDF_MAX) {
        int out = 777, idx = 777;
        bool got = maxToken(c.line, out, idx);
        check("line=" + show(c.line) + " (return)", c.ret, got);
        check("line=" + show(c.line) + " (out)", c.out, out);
        check("line=" + show(c.line) + " (index)", c.index, idx);
    }
}
