// Minimal test framework for the lab camp (adapted from camp/framework/test.h).
// You don't need to touch this file.
#pragma once

#include <algorithm>
#include <atomic>
#include <cctype>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "todo.h"

namespace lab {

// ----- colors ---------------------------------------------------------------
inline const char* GREEN = "\033[32m";
inline const char* RED = "\033[31m";
inline const char* GRAY = "\033[90m";
inline const char* BOLD = "\033[1m";
inline const char* RESET = "\033[0m";

// ----- printing values ------------------------------------------------------
inline std::string show(int v) { return std::to_string(v); }
inline std::string show(long long v) { return std::to_string(v); }
inline std::string show(bool b) { return b ? "true" : "false"; }
inline std::string show(char c) { return std::string("'") + c + "'"; }
inline std::string show(const std::string& s) { return "\"" + s + "\""; }
inline std::string show(const char* s) { return show(std::string(s)); }
template <class A, class B>
std::string show(const std::pair<A, B>& p);
template <class T>
std::string show(const std::vector<T>& v);
template <class A, class B>
std::string show(const std::pair<A, B>& p) {
    return "(" + show(p.first) + ", " + show(p.second) + ")";
}
template <class T>
std::string show(const std::vector<T>& v) {
    std::string r = "{";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) r += ", ";
        r += show(v[i]);
    }
    return r + "}";
}

// ----- random inputs (fixed seed: same cases on every run) ------------------
inline std::mt19937& rng() {
    static std::mt19937 g(211);
    return g;
}
inline int randInt(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng()); }
inline std::vector<int> randVec(int maxLen, int lo, int hi, int minLen = 0) {
    std::vector<int> v(randInt(minLen, maxLen));
    for (int& x : v) x = randInt(lo, hi);
    return v;
}
constexpr int RANDOM_CASES = 200;

// ----- question registry ----------------------------------------------------
struct Question {
    std::string id, title, fn;  // fn: substring searched in __PRETTY_FUNCTION__
    bool optional;
    void (*body)();
};
inline std::vector<Question>& registry() {
    static std::vector<Question> r;
    return r;
}
struct Registrar {
    Registrar(const char* id, const char* title, const char* fn, bool opt, void (*b)()) {
        registry().push_back({id, title, fn, opt, b});
    }
};
#define LAB_CAT2(a, b) a##b
#define LAB_CAT(a, b) LAB_CAT2(a, b)
#define QUESTION_(id, title, fn, opt, n)                                                   \
    static void LAB_CAT(lab_q_, n)();                                                      \
    static lab::Registrar LAB_CAT(lab_r_, n)(id, title, fn, opt, LAB_CAT(lab_q_, n));      \
    static void LAB_CAT(lab_q_, n)()
#define QUESTION(id, title, fn) QUESTION_(id, title, fn, false, __COUNTER__)
#define OPTIONAL_QUESTION(id, title, fn) QUESTION_(id, title, fn, true, __COUNTER__)

// ----- checks ---------------------------------------------------------------
struct State {
    int pass = 0, fail = 0;
    std::vector<std::string> lines;
};
inline State& state() {
    static State s;
    return s;
}
inline void fail(const std::string& msg) {
    state().fail++;
    state().lines.push_back(msg);
}

template <class E, class A>
void check(const std::string& desc, const E& expected, const A& actual) {
    if (expected == actual) state().pass++;
    else fail(desc + "  ->  expected " + show(expected) + ", got " + show(actual));
}

inline void checkTrue(const std::string& desc, bool ok, const std::string& why) {
    if (ok) state().pass++;
    else fail(desc + "  ->  " + why);
}

// ----- runner ---------------------------------------------------------------
inline std::atomic<int> g_seq{0};
inline std::atomic<const Question*> g_cur{nullptr};

inline void onCrash(int) {
    const Question* q = g_cur.load();
    std::printf("\n\n%s💥 %s crashed the program%s (segfault: an index outside the vector, "
                "a null pointer or a deleted node).\n   Run it alone: .\\run.ps1 <lab> %s\n",
                RED, q ? q->id.c_str() : "?", RESET, q ? q->id.c_str() : "");
    std::fflush(stdout);
    std::_Exit(1);
}

inline void startWatchdog() {
    std::thread([] {
        int last = -1;
        auto since = std::chrono::steady_clock::now();
        for (;;) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            int s = g_seq.load();
            auto now = std::chrono::steady_clock::now();
            if (s != last) {
                last = s;
                since = now;
            } else if (g_cur.load() && now - since > std::chrono::seconds(3)) {
                const Question* q = g_cur.load();
                std::printf("\n\n%s⏱  %s did not finish in 3 seconds%s: probably an infinite loop "
                            "(does the index move? push_back inside a loop over the same vector?)\n",
                            RED, q->id.c_str(), RESET);
                std::fflush(stdout);
                std::_Exit(1);
            }
        }
    }).detach();
}

inline std::string lower(std::string s) {
    for (auto& c : s) c = (char)std::tolower((unsigned char)c);
    return s;
}

inline const Question* findByFn(const std::string& where) {
    for (auto& q : registry())
        if (where.find(q.fn) != std::string::npos) return &q;
    return nullptr;
}

inline int width(const std::string& s) {  // number of utf-8 characters
    int n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) n++;
    return n;
}

inline int runAll(const std::string& filterRaw) {
    std::string filter = lower(filterRaw);
    std::vector<const Question*> selected;
    for (auto& q : registry())
        if (filter.empty() || lower(q.id) == filter) selected.push_back(&q);
    if (selected.empty()) {
        std::printf("No question with id '%s'. Ids in this lab:", filterRaw.c_str());
        for (auto& q : registry()) std::printf(" %s", q.id.c_str());
        std::printf("\n");
        return 1;
    }

    std::signal(SIGSEGV, onCrash);
    std::signal(SIGFPE, onCrash);
    startWatchdog();

    int done = 0, required = 0, requiredDone = 0, todo = 0;
    std::printf("\n");
    for (const Question* q : selected) {
        state() = State{};
        rng().seed((unsigned)std::hash<std::string>{}(q->id));
        g_cur = q;
        g_seq++;

        std::string status, color, extra;
        bool ok = false;
        try {
            q->body();
            if (state().fail == 0) {
                ok = true;
                color = GREEN;
                status = "✓ " + std::to_string(state().pass) + "/" + std::to_string(state().pass);
            } else {
                color = RED;
                status = "✗ " + std::to_string(state().pass) + "/" +
                         std::to_string(state().pass + state().fail);
            }
        } catch (const NotImplemented& e) {
            todo++;
            color = GRAY;
            if (e.where.find(q->fn) != std::string::npos) status = "· not written yet";
            else if (const Question* dep = findByFn(e.where))
                status = "· needs " + dep->id + " (" + dep->title + ") first";
            else status = "· not written yet: " + e.where;
        } catch (const std::exception& e) {
            color = RED;
            status = "💥 exception";
            extra = e.what();
        }
        g_cur = nullptr;

        std::string id = q->id;
        while (id.size() < 6) id += " ";
        std::string title = q->title + (q->optional ? " (optional)" : "");
        int pad = 44 - width(title);
        std::string dots = " ";
        for (int i = 0; i < pad; i++) dots += ".";
        std::printf("%s%s%s  %s%s %s%s%s\n", BOLD, id.c_str(), RESET, title.c_str(), dots.c_str(),
                    color.c_str(), status.c_str(), RESET);

        int shown = 0;
        for (auto& l : state().lines) {
            if (shown++ == 6) {
                std::printf("        %s… +%d more failures%s\n", GRAY, (int)state().lines.size() - 6, RESET);
                break;
            }
            std::printf("        %s✗%s %s\n", RED, RESET, l.c_str());
        }
        if (!extra.empty()) std::printf("        %s%s%s\n", RED, extra.c_str(), RESET);

        if (ok) done++;
        if (!q->optional) {
            required++;
            if (ok) requiredDone++;
        }
    }

    std::printf("\n  %s%d/%d required solved%s", BOLD, requiredDone, required, RESET);
    if (todo) std::printf("  %s(%d not written yet)%s", GRAY, todo, RESET);
    std::printf("\n\n");
    std::fflush(stdout);
    return requiredDone == required ? 0 : 1;
}

}  // namespace lab
