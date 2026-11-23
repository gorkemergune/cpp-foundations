// Entry point of the test program. Everything is compiled as a single unit (run.ps1 / run.sh).
#include "../framework/test.h"

#include "../solutions/linkedlist.cpp"
#include "../solutions/stack.cpp"
#include "../solutions/queue.cpp"

#include "../tests/linkedlist_test.cpp"
#include "../tests/stack_test.cpp"
#include "../tests/queue_test.cpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
static void setupConsole() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode)) SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#else
static void setupConsole() {}
#endif

int main(int argc, char** argv) {
    setupConsole();
    return camp::runAll(argc > 1 ? argv[1] : "");
}
