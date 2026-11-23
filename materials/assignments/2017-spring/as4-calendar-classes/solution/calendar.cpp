// Assignment 4 (2017) · calendar: one birthday per name, stored in a std::list<bday>.
#include "calendar.h"

void calendar::add(const bday& b) {
    for (bday& existing : bdaylist) {               // reference: we update the stored object
        if (existing.get_name() == b.get_name()) {
            existing.set_birthday(b.get_birthdate());
            return;
        }
    }
    bdaylist.push_back(b);
}

void calendar::remove(std::string name) {
    for (auto it = bdaylist.begin(); it != bdaylist.end(); ++it) {
        if (it->get_name() == name) {
            bdaylist.erase(it);                     // erase invalidates it: stop right here
            return;
        }
    }
}

void calendar::print() const {
    for (const bday& b : bdaylist) std::cout << b.get_string() << std::endl;
}

// A birthday repeats every year. It is "incoming" if its next occurrence (this year's,
// or next year's if this year's has passed) is 0..7 days after `today`.
void calendar::print_incoming(const date& today) const {
    for (const bday& b : bdaylist) {
        const date& bd = b.get_birthdate();
        date next(bd.get_day(), bd.get_month(), today.get_year());
        if (next.compare(today) < 0) next.set_year(today.get_year() + 1);
        int diff = next.compare(today);
        if (diff >= 0 && diff <= 7) std::cout << b.get_string() << std::endl;
    }
}
