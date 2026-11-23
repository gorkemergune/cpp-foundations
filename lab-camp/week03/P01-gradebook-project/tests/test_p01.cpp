// Mini Project 01 tests.
#include <cmath>
#include <sstream>

#include "gradebook.h"
#include "test.h"

using namespace lab;

struct PDF_LINE_Case { std::string line; bool ret; };
#include "pdf_cases.inc"

QUESTION("P01-A", "addLine / readAll (validation)", "Gradebook::addLine(") {
    for (auto& c : PDF_LINE) {
        Gradebook g;
        check("addLine(" + show(c.line) + ")", c.ret, g.addLine(c.line));
        check("addLine(" + show(c.line) + ") -> count", c.ret ? 1 : 0, g.count());
    }
    Gradebook g;
    std::istringstream in("Ada 95\nBob 48\n\nCem 72\nDeniz 101\nEce 7x\nFatih 95\n");
    check("readAll(grades.txt) -> rejected lines", 2, g.readAll(in));
    check("readAll(grades.txt) -> count", 4, g.count());
}

QUESTION("P01-B", "count / average / best", "Gradebook::average(") {
    Gradebook g;
    check("empty: count", 0, g.count());
    checkTrue("empty: average", g.average() == 0, "expected 0");
    check("empty: best", std::string(""), g.best());
    g.addLine("Ada 95");
    g.addLine("Bob 48");
    g.addLine("Cem 72");
    checkTrue("average of 95, 48, 72", std::fabs(g.average() - 215.0 / 3) < 1e-9, "expected 71.666...");
    check("best", std::string("Ada"), g.best());
    g.addLine("Fatih 95");
    check("best on a tie: the first", std::string("Ada"), g.best());
}

QUESTION("P01-C", "failing / report", "Gradebook::report(") {
    Gradebook g;
    check("empty report", std::string("students: 0\n"), g.report(60));
    g.addLine("Ada 95");
    g.addLine("Bob 48");
    g.addLine("Cem 72");
    check("failing(60)", std::vector<std::string>{"Bob"}, g.failing(60));
    check("failing(80) keeps input order", std::vector<std::string>{"Bob", "Cem"}, g.failing(80));
    check("report(60)", std::string("students: 3\naverage: 71.67\nbest: Ada (95)\nfailing (<60): Bob\n"), g.report(60));
    check("report(10): nobody fails", std::string("students: 3\naverage: 71.67\nbest: Ada (95)\nfailing (<10): -\n"),
          g.report(10));
}
