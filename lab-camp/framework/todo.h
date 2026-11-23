// TODO(): placeholder for functions you haven't written yet.
// Delete the TODO(); line inside a function and write your own code.
// You don't need to touch this file.
#pragma once

#include <exception>
#include <string>

namespace lab {
struct NotImplemented : std::exception {
    std::string where;
    explicit NotImplemented(const char* w) : where(w) {}
    const char* what() const noexcept override { return where.c_str(); }
};
}  // namespace lab

[[noreturn]] inline void lab_todo(const char* where) { throw lab::NotImplemented(where); }
#define TODO() lab_todo(__PRETTY_FUNCTION__)
