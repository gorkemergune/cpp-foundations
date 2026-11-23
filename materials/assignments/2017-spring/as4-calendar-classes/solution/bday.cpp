// Assignment 4 (2017) · bday
#include "bday.h"

bday::bday(std::string n, const date& d) : name(n), birthdate(d) {}

std::string bday::get_name() const { return name; }
const date& bday::get_birthdate() const { return birthdate; }
void bday::set_name(std::string n) { name = n; }
void bday::set_birthday(const date& d) { birthdate = d; }

// "John Doe, 1 January 2000": reuse date::get_string instead of formatting again
std::string bday::get_string() const { return name + ", " + birthdate.get_string(); }
