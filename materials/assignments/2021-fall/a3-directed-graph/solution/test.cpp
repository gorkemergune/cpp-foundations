#include <fstream>

#include "check.h"
#include "intDrGraph.h"

static std::string s(const std::vector<int>& v) {
    std::string r;
    for (int x : v) r += std::to_string(x) + " ";
    return r;
}

int main() {
    intDrGraph g("in.txt");                         // the example file of the assignment
    CHECK_EQ(g.size(), 11);
    CHECK_EQ(s(g.bfsOrder(1)), std::string("1 2 3 6 7 8 4 5 9 10 11 "));
    CHECK(g.isThereWay(1, 11));
    CHECK(!g.isThereWay(5, 11));                    // example from the PDF
    CHECK(g.isThereWay(6, 11));
    CHECK(!g.isThereWay(11, 1));                    // edges are directed
    CHECK(g.isThereWay(4, 4));
    auto r = g.routes(1, 8);
    CHECK_EQ((int)r.size(), 2);                     // 1 2 6 8 and 1 2 8
    if (r.size() == 2) {
        CHECK_EQ(s(r[0]), std::string("1 2 6 8 "));
        CHECK_EQ(s(r[1]), std::string("1 2 8 "));
    }
    CHECK_EQ((int)g.routes(5, 11).size(), 0);
    CHECK_EQ(captured([&] { g.printAdjList(); }).substr(0, 9), std::string("1 -> 2 3\n"));

    { std::ofstream f("tmp_cycle.txt"); f << "3\n1 2\n2 3\n3 1\n"; }   // a cycle, trailing newline
    intDrGraph c("tmp_cycle.txt");
    CHECK_EQ(s(c.bfsOrder(2)), std::string("2 3 1 "));
    CHECK_EQ((int)c.routes(1, 3).size(), 1);
    std::remove("tmp_cycle.txt");
    intDrGraph missing("does_not_exist.txt");
    CHECK_EQ(missing.size(), 0);
    CHECK(!missing.isThereWay(1, 2));
    return check_summary("2021 a3 directed graph");
}
