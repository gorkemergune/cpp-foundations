#include "menu.h"

#include <string>

#include "Grades.h"

void run_menu(std::istream& in, std::ostream& out) {
    Grades* room = nullptr;            // created once by option 1
    int choice;
    while (true) {
        out << "1) Create a classroom  2) Enter grades  3) Show stats  4) Clear classroom  5) Exit\n> ";
        if (!(in >> choice) || choice == 5) break;
        if (choice == 1) {
            if (room != nullptr) { out << "The classroom already exists: " << room->get_name() << "\n"; continue; }
            std::string name;
            out << "Classroom name: ";
            in >> name;
            room = new Grades(name);
        } else if (room == nullptr) {
            out << "Create a classroom first.\n";
        } else if (choice == 2) {
            out << "Grades (-1 to stop): ";
            int g;
            while (in >> g && g != -1) room->add_grade(g);
        } else if (choice == 3) {
            if (room->get_num_grades() == 0) { out << "No grades yet.\n"; continue; }
            out << "min " << room->get_min() << ", max " << room->get_max() << ", average "
                << room->get_average() << ", count " << room->get_num_grades() << "\n";
        } else if (choice == 4) {
            room->remove_all_grades();
            out << "Cleared.\n";
        }
    }
    delete room;
}
