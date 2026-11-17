// Minimal test framework. You don't need to touch this file.
#pragma once

#include <algorithm>
#include <atomic>
#include <cctype>
#include <chrono>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

// ---------------------------------------------------------------------------
// TODO(): placeholder for functions you haven't written yet.
// Delete the line and write your own code.
// ---------------------------------------------------------------------------
namespace camp {
struct NotImplemented : std::exception {
    std::string where;
    explicit NotImplemented(const char* w) : where(w) {}
    const char* what() const noexcept override { return where.c_str(); }
};
}  // namespace camp

[[noreturn]] inline void camp_todo(const char* where) { throw camp::NotImplemented(where); }
#define TODO() camp_todo(__PRETTY_FUNCTION__)

namespace camp {

// ----- colors ---------------------------------------------------------------
inline const char* GREEN = "\033[32m";
inline const char* RED = "\033[31m";
inline const char* GRAY = "\033[90m";
inline const char* BOLD = "\033[1m";
inline const char* RESET = "\033[0m";

// ----- printing values ------------------------------------------------------
inline std::string show(int v) { return std::to_string(v); }
inline std::string show(bool b) { return b ? "true" : "false"; }
inline std::string show(char c) { return std::string("'") + c + "'"; }
inline std::string show(const std::string& s) { return "\"" + s + "\""; }
inline std::string show(const char* s) { return show(std::string(s)); }
template <class T>
std::string show(const std::vector<T>& v) {
    std::string r = "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (i) r += ", ";
        r += show(v[i]);
    }
    return r + "]";
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
    void (*body)();
};
inline std::vector<Question>& registry() {
    static std::vector<Question> r;
    return r;
}
struct Registrar {
    Registrar(const char* id, const char* title, const char* fn, void (*b)()) {
        registry().push_back({id, title, fn, b});
    }
};
#define CAMP_CAT2(a, b) a##b
#define CAMP_CAT(a, b) CAMP_CAT2(a, b)
#define QUESTION_(id, title, fn, n)                                                   \
    static void CAMP_CAT(camp_q_, n)();                                               \
    static camp::Registrar CAMP_CAT(camp_r_, n)(id, title, fn, CAMP_CAT(camp_q_, n)); \
    static void CAMP_CAT(camp_q_, n)()
#define QUESTION(id, title, fn) QUESTION_(id, title, fn, __COUNTER__)

// ----- checks ---------------------------------------------------------------
struct State {
    int pass = 0, fail = 0;
    std::vector<std::string> lines;
};
inline State& state() {
    static State s;
    return s;
}
inline void pass() { state().pass++; }
inline void fail(const std::string& msg) {
    state().fail++;
    state().lines.push_back(msg);
}

template <class E, class A>
void check(const std::string& desc, const E& expected, const A& actual) {
    if (expected == actual) pass();
    else fail(desc + "  →  expected " + show(expected) + ", got " + show(actual));
}

inline void checkTrue(const std::string& desc, bool ok, const std::string& why) {
    if (ok) pass();
    else fail(desc + "  →  " + why);
}

template <class F>
void checkThrows(const std::string& desc, F f) {
    try {
        f();
    } catch (const NotImplemented&) {
        throw;
    } catch (const std::runtime_error&) {
        pass();
        return;
    } catch (...) {
        fail(desc + "  →  threw something other than runtime_error");
        return;
    }
    fail(desc + "  →  should throw runtime_error, but didn't");
}

// ----- runner ---------------------------------------------------------------
inline std::atomic<int> g_seq{0};
inline std::atomic<const Question*> g_cur{nullptr};

inline void onCrash(int) {
    const Question* q = g_cur.load();
    std::printf("\n\n%s💥 %s crashed the program%s (segfault: most likely a null pointer "
                "or access to a deleted node).\n   Run it alone to inspect: .\\run.ps1 %s\n",
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
                std::printf("\n\n%s⏱  %s did not finish in 3 seconds%s: looks like an infinite loop "
                            "(is the pointer advancing? calling size() in the loop condition?)\n",
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

// number of utf-8 characters (for alignment)
inline int width(const std::string& s) {
    int n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) n++;
    return n;
}

inline int runAll(const std::string& filterRaw) {
    std::string filter = lower(filterRaw);
    std::vector<std::string> mockSet = {"ll-6", "ll-9", "st-5", "st-9", "qu-8", "qu-9"};

    std::vector<const Question*> selected;
    for (auto& q : registry())
        if (lower(q.id) == filter) selected.push_back(&q);
    if (selected.empty()) {
        for (auto& q : registry()) {
            std::string id = lower(q.id);
            bool take = filter.empty() || filter == "all" || id.rfind(filter, 0) == 0 ||
                        ((filter == "mock" || filter == "exam") &&
                         std::find(mockSet.begin(), mockSet.end(), id) != mockSet.end());
            if (take) selected.push_back(&q);
        }
    }
    if (selected.empty()) {
        std::printf("No question matches '%s'. Examples: ll, st, qu, LL-6, mock\n", filterRaw.c_str());
        return 1;
    }

    std::signal(SIGSEGV, onCrash);
    std::signal(SIGFPE, onCrash);
    startWatchdog();

    struct Topic {
        std::string name;
        int done = 0, total = 0;
    };
    std::vector<Topic> topics = {{"LL"}, {"ST"}, {"QU"}};
    int done = 0, todo = 0;

    std::printf("\n");
    for (const Question* q : selected) {
        state() = State{};
        rng().seed((unsigned)std::hash<std::string>{}(q->id));  // same inputs no matter the filter
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
            if (e.where.find(q->fn) != std::string::npos) {
                status = "· not written yet";
            } else if (const Question* dep = findByFn(e.where)) {
                status = "· needs " + dep->id + " (" + dep->title + ") first";
            } else {
                status = "· not written yet: " + e.where.substr(0, e.where.find(" [with"));
            }
        } catch (const std::exception& e) {
            color = RED;
            status = "💥 exception";
            extra = e.what();
        } catch (...) {
            color = RED;
            status = "💥 unknown exception";
        }
        g_cur = nullptr;

        std::string id = q->id;
        while (id.size() < 5) id += " ";
        int pad = 38 - width(q->title);
        std::string dots = " ";
        for (int i = 0; i < pad; i++) dots += ".";
        std::printf("%s%s%s  %s%s %s%s%s\n", BOLD, id.c_str(), RESET, q->title.c_str(),
                    dots.c_str(), color.c_str(), status.c_str(), RESET);

        int shown = 0;
        for (auto& l : state().lines) {
            if (shown++ == 6) {
                std::printf("      %s… +%d more failures%s\n", GRAY, (int)state().lines.size() - 6, RESET);
                break;
            }
            std::printf("      %s✗%s %s\n", RED, RESET, l.c_str());
        }
        if (!extra.empty()) std::printf("      %s%s%s\n", RED, extra.c_str(), RESET);

        if (ok) done++;
        for (auto& t : topics)
            if (q->id.rfind(t.name, 0) == 0) {
                t.total++;
                if (ok) t.done++;
            }
    }

    std::printf("\n");
    for (auto& t : topics) {
        if (t.total == 0) continue;
        std::string bar;
        for (int i = 0; i < t.total; i++) bar += i < t.done ? "█" : "░";
        std::printf("  %s  %s%s%s  %d/%d\n", t.name.c_str(), GREEN, bar.c_str(), RESET, t.done, t.total);
    }
    std::printf("\n  %s%d/%d solved%s", BOLD, done, (int)selected.size(), RESET);
    if (todo) std::printf("  %s(%d not written yet)%s", GRAY, todo, RESET);
    std::printf("\n\n");
    std::fflush(stdout);
    return done == (int)selected.size() ? 0 : 1;
}

}  // namespace camp
