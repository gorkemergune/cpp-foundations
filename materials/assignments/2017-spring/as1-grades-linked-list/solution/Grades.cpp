#include "Grades.h"

void Grades::add_grade(int grade) {
    if (grade >= 0 && grade <= 100) gradeList.addToTail(grade);
}

int Grades::get_min() {
    if (gradeList.isEmpty()) return -1;
    int best = gradeList.head->info;
    for (IntSLLNode* p = gradeList.head->next; p != 0; p = p->next)
        if (p->info < best) best = p->info;
    return best;
}

int Grades::get_max() {
    if (gradeList.isEmpty()) return -1;
    int best = gradeList.head->info;
    for (IntSLLNode* p = gradeList.head->next; p != 0; p = p->next)
        if (p->info > best) best = p->info;
    return best;
}

double Grades::get_average() {
    int n = get_num_grades();
    if (n == 0) return 0;
    long long sum = 0;
    for (IntSLLNode* p = gradeList.head; p != 0; p = p->next) sum += p->info;
    return (double)sum / n;           // cast first: integer division would drop the .5
}

int Grades::get_num_grades() {
    int n = 0;
    for (IntSLLNode* p = gradeList.head; p != 0; p = p->next) n++;
    return n;
}

void Grades::remove_all_grades() {
    while (!gradeList.isEmpty()) gradeList.deleteFromHead();   // every node is deleted
}
