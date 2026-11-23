// Tiny test helper for the materials/ solutions. Each test.cpp includes it and
// returns check_summary() from main. Run every test: python materials/_check/run_all.py
#pragma once
#include <iostream>
#include <sstream>
#include <string>

inline int& check_failures() { static int n = 0; return n; }
inline int& check_count() { static int n = 0; return n; }

#define CHECK(cond)                                                                   \
    do {                                                                              \
        check_count()++;                                                              \
        if (!(cond)) {                                                                \
            check_failures()++;                                                       \
            std::cout << "  FAIL " << __FILE__ << ":" << __LINE__ << "  " #cond "\n"; \
        }                                                                             \
    } while (0)

#define CHECK_EQ(actual, expected)                                                         \
    do {                                                                                   \
        check_count()++;                                                                   \
        auto check_a_ = (actual);                                                          \
        auto check_e_ = (expected);                                                        \
        if (!(check_a_ == check_e_)) {                                                     \
            check_failures()++;                                                            \
            std::cout << "  FAIL " << __FILE__ << ":" << __LINE__ << "  " #actual "\n"     \
                      << "       expected: " << check_e_ << "\n       got:      " << check_a_ \
                      << "\n";                                                             \
        }                                                                                  \
    } while (0)

// Captures what a piece of code prints to std::cout.
struct CaptureCout {
    std::ostringstream buf;
    std::streambuf* old;
    CaptureCout() : old(std::cout.rdbuf(buf.rdbuf())) {}
    ~CaptureCout() { std::cout.rdbuf(old); }
    std::string str() const { return buf.str(); }
};
template <class F>
std::string captured(F f) {
    CaptureCout c;
    f();
    return c.str();
}

inline int check_summary(const char* name) {
    std::cout << (check_failures() ? "FAILED " : "ok     ") << name << "  (" << check_count() - check_failures()
              << "/" << check_count() << " checks)\n";
    return check_failures() ? 1 : 0;
}
