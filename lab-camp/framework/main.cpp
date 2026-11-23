// Entry point of every lab's test program. You don't need to touch this file.
#include "test.h"

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
    return lab::runAll(argc > 1 ? argv[1] : "");
}
