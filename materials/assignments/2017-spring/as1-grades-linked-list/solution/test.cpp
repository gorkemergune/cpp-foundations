#include <sstream>

#include "Grades.h"
#include "check.h"
#include "menu.h"

int main() {
    Grades g("CSE211");
    CHECK_EQ(g.get_num_grades(), 0);
    CHECK_EQ(g.get_min(), -1);
    CHECK_EQ(g.get_average(), 0.0);
    g.add_grade(36);
    g.add_grade(15);
    g.add_grade(101);   // ignored
    g.add_grade(-1);    // ignored
    CHECK_EQ(g.get_max(), 36);
    CHECK_EQ(g.get_min(), 15);
    CHECK_EQ(g.get_average(), 25.5);   // example main of the assignment
    CHECK_EQ(g.get_num_grades(), 2);
    g.add_grade(0);
    g.add_grade(100);
    CHECK_EQ(g.get_min(), 0);
    CHECK_EQ(g.get_max(), 100);
    g.remove_all_grades();
    CHECK_EQ(g.get_num_grades(), 0);
    g.add_grade(50);
    CHECK_EQ(g.get_average(), 50.0);

    std::istringstream in("3 1 Math 1 2 70 80 200 -1 3 4 3 5");
    std::ostringstream out;
    run_menu(in, out);
    std::string s = out.str();
    CHECK(s.find("Create a classroom first.") != std::string::npos);
    CHECK(s.find("already exists: Math") != std::string::npos);
    CHECK(s.find("min 70, max 80, average 75, count 2") != std::string::npos);
    CHECK(s.find("No grades yet.") != std::string::npos);
    return check_summary("2017 as1 Grades");
}
