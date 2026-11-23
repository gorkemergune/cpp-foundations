#include "expr.h"

#include <cctype>
#include <sstream>
#include <stack>
#include <stdexcept>

namespace {
template <class T>
std::string show(std::stack<T> st) {  // bottom ... top (st is a copy)
    std::vector<std::string> items;
    while (!st.empty()) {
        std::ostringstream o;
        o << st.top();
        items.push_back(o.str());
        st.pop();
    }
    std::string r;
    for (int i = (int)items.size() - 1; i >= 0; i--) r += items[i] + (i ? " " : "");
    return r.empty() ? "(empty)" : r;
}
int prec(char op) { return (op == '*' || op == '/') ? 2 : 1; }
bool isOp(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
std::string normalize(const std::string& s) {  // the PDF uses an en dash for minus
    std::string r;
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char a = s[i];
        if (a == 0xE2 && i + 2 < s.size() && (unsigned char)s[i + 1] == 0x80 &&
            ((unsigned char)s[i + 2] == 0x93 || (unsigned char)s[i + 2] == 0x94)) {
            r += '-';
            i += 2;
        } else {
            r += s[i];
        }
    }
    return r;
}
}  // namespace

bool balanced(const std::string& s, std::vector<std::string>* trace) {
    std::stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            char open = c == ')' ? '(' : c == ']' ? '[' : '{';
            if (st.empty() || st.top() != open) {
                if (trace)
                    trace->push_back(std::string("read ") + c + " -> mismatch, top is " +
                                     (st.empty() ? std::string("nothing") : std::string(1, st.top())));
                return false;
            }
            st.pop();
        } else {
            continue;
        }
        if (trace) trace->push_back(std::string("read ") + c + " -> stack: " + show(st));
    }
    if (trace && !st.empty()) trace->push_back("end of input, stack not empty -> unbalanced");
    return st.empty();
}

std::string toPostfix(const std::string& raw, std::vector<std::string>* trace) {
    std::string in = normalize(raw), out;
    std::stack<char> ops;
    auto emit = [&](const std::string& tok) { out += (out.empty() ? "" : " ") + tok; };
    for (size_t i = 0; i < in.size(); i++) {
        char c = in[i];
        std::string what;
        if (std::isspace((unsigned char)c)) continue;
        if (std::isalnum((unsigned char)c)) {
            std::string tok(1, c);
            while (std::isdigit((unsigned char)c) && i + 1 < in.size() && std::isdigit((unsigned char)in[i + 1]))
                tok += in[++i];
            emit(tok);
            what = tok;
        } else if (c == '(') {
            ops.push(c);
            what = "(";
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                emit(std::string(1, ops.top()));
                ops.pop();
            }
            if (ops.empty()) throw std::invalid_argument("unbalanced )");
            ops.pop();  // drop the matching (
            what = ")";
        } else if (isOp(c)) {
            // pop operators of higher OR EQUAL precedence: equal -> left associative
            while (!ops.empty() && ops.top() != '(' && prec(ops.top()) >= prec(c)) {
                emit(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(c);
            what = std::string(1, c);
        } else {
            throw std::invalid_argument(std::string("unexpected character ") + c);
        }
        if (trace) trace->push_back("read " + what + " -> stack: " + show(ops) + " | output: " + out);
    }
    while (!ops.empty()) {
        if (ops.top() == '(') throw std::invalid_argument("unbalanced (");
        emit(std::string(1, ops.top()));
        ops.pop();
    }
    if (trace) trace->push_back("end -> output: " + out);
    return out;
}

long long evalPostfix(const std::string& postfix, std::vector<std::string>* trace) {
    std::istringstream in(postfix);
    std::stack<long long> st;
    std::string tok;
    while (in >> tok) {
        if (tok.size() == 1 && isOp(tok[0])) {
            if (st.size() < 2) throw std::invalid_argument("missing operand");
            long long right = st.top();  // popped first = RIGHT operand
            st.pop();
            long long left = st.top();
            st.pop();
            if (tok[0] == '/' && right == 0) throw std::domain_error("division by zero");
            long long r = tok[0] == '+' ? left + right
                        : tok[0] == '-' ? left - right
                        : tok[0] == '*' ? left * right
                                        : left / right;
            st.push(r);
        } else {
            st.push(std::stoll(tok));
        }
        if (trace) trace->push_back("read " + tok + " -> stack: " + show(st));
    }
    if (st.size() != 1) throw std::invalid_argument("malformed expression");
    return st.top();
}
