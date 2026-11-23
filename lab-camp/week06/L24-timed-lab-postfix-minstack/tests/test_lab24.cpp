// Lab 24 tests.
#include <algorithm>

#include "lab24.h"
#include "test.h"

using namespace lab;
using S = std::vector<std::string>;

struct PDF_RPN_Case { S tokens; int ret; };
struct PDF_IN_Case { std::string infix; std::string out; };
struct PDF_BB_Case { S ops; int ret; };
struct PDF_DIG_Case { std::string s; int ret; };
#include "pdf_cases.inc"

QUESTION("L24-A", "evalRPN (LC 150)", "evalRPN(") {
    for (auto& c : PDF_RPN) check("tokens=" + show(c.tokens), c.ret, evalRPN(c.tokens));
}

QUESTION("L24-B", "MinStack (LC 155)", "MinStack::") {
    MinStack m;
    m.push(-2);
    m.push(0);
    m.push(-3);
    check("getMin after push -2, 0, -3", -3, m.getMin());
    m.pop();
    check("top after pop", 0, m.top());
    check("getMin after pop", -2, m.getMin());
    for (int t = 0; t < RANDOM_CASES; t++) {          // compare with a vector + min_element
        MinStack s;
        std::vector<int> ref;
        bool ok = true;
        std::string log;
        for (int k = 0; k < 25 && ok; k++) {
            if (ref.empty() || randInt(0, 2) > 0) {
                int x = randInt(-9, 9);
                s.push(x);
                ref.push_back(x);
                log += " push" + std::to_string(x);
            } else {
                s.pop();
                ref.pop_back();
                log += " pop";
            }
            if (!ref.empty()) ok = s.top() == ref.back() && s.getMin() == *std::min_element(ref.begin(), ref.end());
        }
        checkTrue("ops:" + log, ok, "top or getMin is wrong");
    }
}

QUESTION("L24-C", "toPostfix", "toPostfix(") {
    for (auto& c : PDF_IN) check("infix=" + show(c.infix), c.out, toPostfix(c.infix));
}

OPTIONAL_QUESTION("L24-X", "calPoints (LC 682)", "calPoints(") {
    for (auto& c : PDF_BB) check("ops=" + show(c.ops), c.ret, calPoints(c.ops));
}

OPTIONAL_QUESTION("L24-V", "evalPostfixDigits", "evalPostfixDigits(") {
    for (auto& c : PDF_DIG) check("s=" + show(c.s), c.ret, evalPostfixDigits(c.s));
}
