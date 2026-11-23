// Assignment 4 (2017) · date
#include "date.h"

namespace {
bool isLeap(int y) { return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0); }
int daysInMonth(int m, int y) {
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (m == 2 && isLeap(y)) ? 29 : days[m - 1];
}
const char* MONTHS[12] = {"January", "February", "March",     "April",   "May",      "June",
                          "July",    "August",   "September", "October", "November", "December"};
}  // namespace

date::date() : day(0), month(0), year(0) {}
date::date(int d, int m, int y) : day(d), month(m), year(y) {}

void date::set_day(int d) { day = d; }
void date::set_month(int m) { month = m; }
void date::set_year(int y) { year = y; }
int date::get_day() const { return day; }
int date::get_month() const { return month; }
int date::get_year() const { return year; }

std::string date::get_string() const {  // "18 March 2017"
    if (month < 1 || month > 12) return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    return std::to_string(day) + " " + MONTHS[month - 1] + " " + std::to_string(year);
}

// Days from year 0 to this date. Whole years first, then whole months of this year.
int date::days_since_0() const {
    int total = 0;
    for (int y = 0; y < year; y++) total += isLeap(y) ? 366 : 365;
    for (int m = 1; m < month; m++) total += daysInMonth(m, year);
    return total + day;
}

// Positive when *this comes after other.
int date::compare(const date& other) const { return days_since_0() - other.days_since_0(); }
