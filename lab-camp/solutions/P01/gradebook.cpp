// ============================================================================
//  Mini Project 01 · Gradebook · YOU WORK HERE (about 70 lines)
//  Reference solution. @solution-note
//  Test:  .\run.ps1 P01        Run the program:  see main.cpp
// ============================================================================
#include "gradebook.h"

#include <cctype>
#include <iomanip>
#include <sstream>

#include "todo.h"

using namespace std;

// @begin addLine
bool Gradebook::addLine(const string& line) {
    istringstream in(line);
    string name, scoreText, extra;
    if (!(in >> name >> scoreText) || (in >> extra)) return false;   // exactly two tokens
    for (char c : name)
        if (!isalpha((unsigned char)c)) return false;
    for (char c : scoreText)                                        // digits only: no "9x", no "-5"
        if (!isdigit((unsigned char)c)) return false;
    if (scoreText.size() > 3) return false;                         // keeps stoi far from overflow
    int score = stoi(scoreText);
    if (score > 100) return false;
    records_.push_back({name, score});
    return true;
}
// @end addLine

// @begin readAll
int Gradebook::readAll(istream& in) {
    int rejected = 0;
    string line;
    while (getline(in, line)) {
        if (line.find_first_not_of(' ') == string::npos) continue;  // blank lines are ignored
        if (!addLine(line)) rejected++;
    }
    return rejected;
}
// @end readAll

// @begin count
int Gradebook::count() const {
    return (int)records_.size();
}
// @end count

// @begin average
double Gradebook::average() const {
    if (records_.empty()) return 0;
    int sum = 0;
    for (const Record& r : records_) sum += r.score;
    return (double)sum / records_.size();
}
// @end average

// @begin best
string Gradebook::best() const {
    if (records_.empty()) return "";
    const Record* top = &records_[0];
    for (const Record& r : records_)
        if (r.score > top->score) top = &r;       // strict >: the first one wins a tie
    return top->name;
}
// @end best

// @begin failing
vector<string> Gradebook::failing(int threshold) const {
    vector<string> names;
    for (const Record& r : records_)
        if (r.score < threshold) names.push_back(r.name);
    return names;
}
// @end failing

// @begin report
string Gradebook::report(int threshold) const {
    ostringstream out;
    out << "students: " << count() << "\n";
    if (records_.empty()) return out.str();
    int bestScore = 0;
    for (const Record& r : records_)
        if (r.name == best()) { bestScore = r.score; break; }
    out << "average: " << fixed << setprecision(2) << average() << "\n";
    out << "best: " << best() << " (" << bestScore << ")\n";
    out << "failing (<" << threshold << "):";
    vector<string> f = failing(threshold);
    if (f.empty()) out << " -";
    for (const string& n : f) out << " " << n;
    out << "\n";
    return out.str();
}
// @end report
