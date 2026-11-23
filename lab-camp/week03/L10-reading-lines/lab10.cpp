// ============================================================================
//  Lab 10 · Reading lines · YOU WORK HERE
//  Test everything:      .\run.ps1 L10
//  Allowed: std::istringstream, >>, getline, std::stoi, in.ignore().
// ============================================================================
#include "lab10.h"

#include <cctype>
#include <limits>
#include <sstream>

#include "todo.h"

using namespace std;

// L10-A · Example: "  to be   or "  =>  {"to", "be", "or"}
vector<string> splitWords(const string& line) {
    TODO();
}

// L10-B · Example: "12 -3 5"  =>  14
int sumLine(const string& line) {
    TODO();
}

// L10-M1 · Example: "12 -3 5 -3"  =>  true, out = -3
bool minToken(const string& line, int& out) {
    TODO();
}

// L10-M2 · Example: stream "3\nhello world\n\n  a b c \n"  =>  {2, 0, 3}
vector<int> wordsPerLine(istream& in) {
    TODO();
}

// L10-X · Example: "1 box has 3 blue 4 red 6 green and 12 yellow marbles"  =>  true
bool areNumbersAscending(const string& s) {
    TODO();
}

// L10-V · Example: "4 9 1 9"  =>  true, out = 9, index = 1
bool maxToken(const string& line, int& out, int& index) {
    TODO();
}
