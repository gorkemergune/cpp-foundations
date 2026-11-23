// ============================================================================
//  Lab 10 · Reading lines · YOU WORK HERE
//  Reference solution. @solution-note
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
// @begin splitWords
vector<string> splitWords(const string& line) {
    istringstream in(line);        // a stream that reads from the string
    vector<string> words;
    string w;
    while (in >> w) words.push_back(w);   // >> skips any whitespace before a word
    return words;
}
// @end splitWords

// L10-B · Example: "12 -3 5"  =>  14
// @begin sumLine
int sumLine(const string& line) {
    istringstream in(line);
    int x, sum = 0;
    while (in >> x) sum += x;      // the loop stops when no int can be read
    return sum;
}
// @end sumLine

// L10-M1 · Example: "12 -3 5 -3"  =>  true, out = -3
// @begin minToken
bool minToken(const string& line, int& out) {
    istringstream in(line);
    int temp;                      // "first number into temp, then compare"
    if (!(in >> temp)) return false;
    int x;
    while (in >> x)
        if (x < temp) temp = x;
    out = temp;
    return true;
}
// @end minToken

// L10-M2 · Example: stream "3\nhello world\n\n  a b c \n"  =>  {2, 0, 3}
// @begin wordsPerLine
vector<int> wordsPerLine(istream& in) {
    int n;
    in >> n;                       // reads "3" and STOPS before the newline
    in.ignore(numeric_limits<streamsize>::max(), '\n');   // drop the rest of that line
    vector<int> counts;
    string line;
    for (int i = 0; i < n && getline(in, line); i++)
        counts.push_back((int)splitWords(line).size());
    return counts;
}
// @end wordsPerLine

// L10-X · Example: "1 box has 3 blue 4 red 6 green and 12 yellow marbles"  =>  true
// @begin areNumbersAscending
bool areNumbersAscending(const string& s) {
    istringstream in(s);
    string tok;
    int last = -1;
    while (in >> tok) {
        if (isdigit((unsigned char)tok[0])) {      // tokens are either words or numbers
            int x = stoi(tok);
            if (x <= last) return false;
            last = x;
        }
    }
    return true;
}
// @end areNumbersAscending

// L10-V · Example: "4 9 1 9"  =>  true, out = 9, index = 1
// @begin maxToken
bool maxToken(const string& line, int& out, int& index) {
    istringstream in(line);
    int best, x, i = 1, bestAt = 0;
    if (!(in >> best)) return false;
    while (in >> x) {
        if (x > best) {
            best = x;
            bestAt = i;
        }
        i++;
    }
    out = best;
    index = bestAt;
    return true;
}
// @end maxToken
