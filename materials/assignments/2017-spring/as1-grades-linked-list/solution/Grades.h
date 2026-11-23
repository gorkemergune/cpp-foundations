// Assignment 1 (2017) · Grades stores the grades of one course in an IntSLList.
#ifndef GRADES_H
#define GRADES_H

#include <string>

#include "intSLList.h"

class Grades {
public:
    explicit Grades(const std::string& name) : courseName(name) {}
    void add_grade(int grade);     // ignored unless 0 <= grade <= 100
    int get_min();                 // -1 if there are no grades
    int get_max();                 // -1 if there are no grades
    double get_average();          // 0 if there are no grades
    int get_num_grades();
    void remove_all_grades();
    std::string get_name() const { return courseName; }

private:
    std::string courseName;
    IntSLList gradeList;
};

#endif
