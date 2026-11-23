// ST tests. Stacks are written as {top, ..., bottom}.
// The PDF examples + edge cases + RANDOM_CASES random inputs vs. a std::vector reference.
#include "../ds/LLStack.h"

namespace st_test {
using namespace camp;
using V = std::vector<int>;

inline std::string S(const V& v) { return "top→" + show(v); }
inline std::string I(int x) { return std::to_string(x); }

inline std::string randBrackets(int maxLen) {
    const std::string chars = "()[]{}()[]{}ab";
    std::string s;
    int n = randInt(0, maxLen);
    for (int i = 0; i < n; i++) s += chars[randInt(0, (int)chars.size() - 1)];
    return s;
}
// always balanced: built recursively
inline std::string balancedBrackets(int depth) {
    std::string s;
    int parts = randInt(0, 3);
    for (int i = 0; i < parts; i++) {
        int k = randInt(0, 2);
        std::string inner = depth > 0 ? balancedBrackets(depth - 1) : "";
        s += "([{"[k] + inner + ")]}"[k];
    }
    return s;
}
inline bool refBalanced(const std::string& s) {
    std::vector<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push_back(c);
        else if (c == ')' || c == ']' || c == '}') {
            char open = c == ')' ? '(' : c == ']' ? '[' : '{';
            if (st.empty() || st.back() != open) return false;
            st.pop_back();
        }
    }
    return st.empty();
}
// random valid postfix expression and its value
inline std::pair<std::string, int> randPostfix(int depth) {
    if (depth == 0 || randInt(0, 2) == 0) {
        int d = randInt(0, 9);
        return {std::string(1, char('0' + d)), d};
    }
    auto [ls, lv] = randPostfix(depth - 1);
    auto [rs, rv] = randPostfix(depth - 1);
    char op = "+-*/"[randInt(0, 3)];
    if (op == '/' && rv == 0) op = '+';
    int v = op == '+' ? lv + rv : op == '-' ? lv - rv : op == '*' ? lv * rv : lv / rv;
    std::string sep = randInt(0, 1) ? " " : "";
    return {ls + sep + rs + sep + op, v};
}

// ---------------------------------------------------------------- ST-1
QUESTION("ST-1", "Stack size", "LLStack<T>::size(") {
    auto run = [](const V& in) {
        LLStack<int> s;
        s.fill(in);
        check(S(in), (int)in.size(), s.size());
        check(S(in) + " (stack must stay unchanged)", in, s.toVector());
    };
    for (V in : std::vector<V>{{5, 2, 9}, {}, {1}, {0, 0}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(30, -9, 9));
}

// ---------------------------------------------------------------- ST-2
QUESTION("ST-2", "Peek at the top", "LLStack<T>::peek(") {
    auto run = [](const V& in) {
        LLStack<int> s;
        s.fill(in);
        check(S(in), in[0], s.peek());
        check(S(in) + " (stack must stay unchanged)", in, s.toVector());
    };
    for (V in : std::vector<V>{{5, 2}, {7}, {-1, 5, 5}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(10, -9, 9, 1));
    {
        LLStack<int> s;
        checkThrows("empty stack", [&] { s.peek(); });
        s.pushToStack(1);
        s.popFromStack();
        checkThrows("emptied stack (push then pop)", [&] { s.peek(); });
    }
    {
        LLStack<string> s;
        s.fill({"x", "y"});
        check("string stack {\"x\",\"y\"}", string("x"), s.peek());
    }
}

// ---------------------------------------------------------------- ST-3
QUESTION("ST-3", "Contains", "LLStack<T>::contains(") {
    auto run = [](const V& in, int v) {
        LLStack<int> s;
        s.fill(in);
        std::string d = S(in) + ", v=" + I(v);
        check(d, std::find(in.begin(), in.end(), v) != in.end(), s.contains(v));
        check(d + " (stack must stay unchanged)", in, s.toVector());
    };
    run({4, 7, 1}, 7);
    run({4, 7, 1}, 4);  // top
    run({4, 7, 1}, 1);  // bottom
    run({4, 7, 1}, 9);
    run({}, 3);
    run({0}, 0);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(10, 0, 9), randInt(0, 10));
    LLStack<string> s;
    s.fill({"a", "b"});
    check("string stack {\"a\",\"b\"}, v=\"b\"", true, s.contains("b"));
    check("string stack {\"a\",\"b\"}, v=\"c\"", false, s.contains("c"));
}

// ---------------------------------------------------------------- ST-4
QUESTION("ST-4", "Reverse a string with a stack", "reverseString(") {
    auto run = [](const string& in) { check(show(in), string(in.rbegin(), in.rend()), reverseString(in)); };
    for (string in : {"abc", "", "a", "merhaba", "ab", "racecar", "a b c", "12345!"}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) {
        string s;
        int n = randInt(0, 20);
        for (int j = 0; j < n; j++) s += char(randInt('a', 'z'));
        run(s);
    }
}

// ---------------------------------------------------------------- ST-5
QUESTION("ST-5", "Balanced brackets", "isBalanced(") {
    auto run = [](const string& in) { check(show(in), refBalanced(in), isBalanced(in)); };
    for (string in : {"{[()]}", "([)]", "((", "", ")(", "))", "a(b)c", "{[]}()", "(]", "(", ")",
                      "{{{}}}", "([]{})", "(((())))", "]", "[(])", "x", "((a+b)*[c-d])"})
        run(in);
    for (int i = 0; i < RANDOM_CASES / 2; i++) run(randBrackets(12));
    for (int i = 0; i < RANDOM_CASES / 2; i++) run(balancedBrackets(3));
}

// ---------------------------------------------------------------- ST-6
QUESTION("ST-6", "Reverse the stack", "LLStack<T>::reverseStack(") {
    auto run = [](const V& in) {
        LLStack<int> s;
        s.fill(in);
        s.reverseStack();
        check(S(in), V(in.rbegin(), in.rend()), s.toVector());
    };
    for (V in : std::vector<V>{{1, 2, 3}, {}, {7}, {1, 2}, {1, 1, 2}}) run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, -9, 9));
}

// ---------------------------------------------------------------- ST-7
QUESTION("ST-7", "Evaluate postfix", "evalPostfix(") {
    auto run = [](const string& in, int exp) { check(show(in), exp, evalPostfix(in)); };
    run("2 3 4 * +", 14);
    run("9 3 / 2 -", 1);
    run("5", 5);
    run("0", 0);
    run("23-", -1);  // order of operands
    run("82/", 4);
    run("72/", 3);  // integer division
    run("5 1 2 + 4 * + 3 -", 14);
    run("34*25*+", 22);
    run("  1  2  +  ", 3);
    run("9 9 * 9 *", 729);
    for (int i = 0; i < RANDOM_CASES; i++) {
        auto [s, v] = randPostfix(3);  // at most 8 digits: no int overflow
        run(s, v);
    }
}

// ---------------------------------------------------------------- ST-8
QUESTION("ST-8", "Remove all occurrences", "LLStack<T>::removeAll(") {
    auto run = [](const V& in, int v) {
        V exp;
        for (int x : in)
            if (x != v) exp.push_back(x);
        LLStack<int> s;
        s.fill(in);
        std::string d = S(in) + ", v=" + I(v);
        check(d + " return", (int)(in.size() - exp.size()), s.removeAll(v));
        check(d + " stack", exp, s.toVector());
    };
    run({3, 7, 3, 1}, 3);
    run({1, 2}, 9);
    run({}, 1);
    run({4, 4, 4}, 4);
    run({1, 2, 3}, 1);  // only the top
    run({1, 2, 3}, 3);  // only the bottom
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(15, 0, 4), randInt(0, 5));
}

// ---------------------------------------------------------------- ST-9
QUESTION("ST-9", "Sort the stack", "LLStack<T>::sortStack(") {
    auto run = [](const V& in) {
        LLStack<int> s;
        s.fill(in);
        s.sortStack();
        V exp = in;
        std::sort(exp.begin(), exp.end());
        check(S(in), exp, s.toVector());
    };
    for (V in : std::vector<V>{{3, 1, 4, 2}, {}, {5}, {1, 2, 3}, {3, 2, 1}, {2, 2, 1}, {0, -5, 3},
                               {1, 1, 1}, {5, 4, 3, 2, 1, 0}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, -20, 20));
}

// ---------------------------------------------------------------- ST-10
QUESTION("ST-10", "Next greater element", "nextGreater(") {
    auto run = [](const V& in) {
        V exp(in.size(), -1);
        for (size_t i = 0; i < in.size(); i++)
            for (size_t j = i + 1; j < in.size(); j++)
                if (in[j] > in[i]) {
                    exp[i] = in[j];
                    break;
                }
        check(show(in), exp, nextGreater(in));
    };
    for (V in : std::vector<V>{{4, 5, 2, 10, 8}, {}, {1, 1}, {3, 2, 1}, {1, 2, 3}, {7},
                               {2, 7, 3, 5, 4, 6, 8}, {5, 5, 6}})
        run(in);
    for (int i = 0; i < RANDOM_CASES; i++) run(randVec(20, 0, 30));
}

}  // namespace st_test
