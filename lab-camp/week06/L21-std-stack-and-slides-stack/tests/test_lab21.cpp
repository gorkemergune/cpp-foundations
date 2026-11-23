// Lab 21 tests. Stacks are written top first: {3, 2, 1} means 3 is on top.
#include <string>
#include <vector>

#include "lab21.h"
#include "test.h"

using namespace lab;
using V = std::vector<int>;

struct PDF_VALID_Case { std::string s; bool ret; };
struct PDF_DUP_Case { std::string s; std::string out; };
#include "pdf_cases.inc"

static std::stack<int> makeStd(const V& topFirst) {
    std::stack<int> st;
    for (int i = (int)topFirst.size() - 1; i >= 0; i--) st.push(topFirst[i]);
    return st;
}
static void fillSlides(Stack& st, const V& topFirst) {
    for (int i = (int)topFirst.size() - 1; i >= 0; i--) st.push(topFirst[i]);
}
static V drainSlides(Stack& st) {
    V r;
    StackItemType x;
    while (st.pop(x)) r.push_back(x);
    return r;
}
static std::string randBrackets() {
    std::string s;
    int n = randInt(0, 10);
    for (int i = 0; i < n; i++) s += "()[]{}"[randInt(0, 5)];
    return s;
}
static bool refValid(const std::string& s) {
    std::string st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st += c;
        else {
            char o = c == ')' ? '(' : c == ']' ? '[' : '{';
            if (st.empty() || st.back() != o) return false;
            st.pop_back();
        }
    }
    return st.empty();
}

QUESTION("L21-A", "popAllSum (std::stack)", "popAllSum(") {
    for (V v : {V{3, 2, 1}, V{}, V{-5}, V{4, 4}}) {
        std::stack<int> st = makeStd(v);
        int sum = 0;
        for (int x : v) sum += x;
        check("stack " + show(v), sum, popAllSum(st));
        checkTrue("stack " + show(v) + " is empty afterwards", st.empty(), "the stack is not empty");
    }
}

QUESTION("L21-B", "popAllSumSlides (slides Stack)", "popAllSumSlides(") {
    for (V v : {V{3, 2, 1}, V{}, V{-5}}) {
        Stack st;
        fillSlides(st, v);
        int sum = 0;
        for (int x : v) sum += x;
        check("stack " + show(v), sum, popAllSumSlides(st));
        checkTrue("stack " + show(v) + " is empty afterwards", st.isEmpty(), "the stack is not empty");
    }
}

QUESTION("L21-M1", "isValid (LC 20, std::stack)", "isValid(") {
    for (auto& c : PDF_VALID) check("s=" + show(c.s), c.ret, isValid(c.s));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randBrackets();
        check("s=" + show(s), refValid(s), isValid(s));
    }
}

QUESTION("L21-M2", "isValidSlides (slides Stack)", "isValidSlides(") {
    for (auto& c : PDF_VALID) check("s=" + show(c.s), c.ret, isValidSlides(c.s));
    for (int t = 0; t < RANDOM_CASES; t++) {
        std::string s = randBrackets();
        check("s=" + show(s), refValid(s), isValidSlides(s));
    }
}

OPTIONAL_QUESTION("L21-X", "removeDuplicates (LC 1047)", "removeDuplicates(") {
    for (auto& c : PDF_DUP) check("s=" + show(c.s), c.out, removeDuplicates(c.s));
}

OPTIONAL_QUESTION("L21-V", "maxKeep (stack restored)", "maxKeep(") {
    for (V v : {V{3, 9, 1}, V{7}, V{-4, -2, -9}, V{5, 5}}) {
        Stack st;
        fillSlides(st, v);
        int best = v[0];
        for (int x : v) best = std::max(best, x);
        check("stack " + show(v), best, maxKeep(st));
        check("stack " + show(v) + " afterwards (top first)", v, drainSlides(st));
    }
}
