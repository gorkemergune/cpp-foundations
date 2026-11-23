#include "bday.h"
#include "calendar.h"
#include "check.h"
#include "date.h"

int main() {
    date d1(17, 3, 2017), d2(5, 2, 2017);
    CHECK_EQ(d1.get_string(), std::string("17 March 2017"));
    CHECK_EQ(d1.compare(d2), 40);                     // example_main_date
    CHECK_EQ(d2.compare(d1), -40);
    CHECK_EQ(d1.compare(d1), 0);
    CHECK_EQ(date(1, 3, 2016).compare(date(28, 2, 2016)), 2);  // 2016 is leap: 29 Feb exists
    CHECK_EQ(date(1, 3, 1700).compare(date(28, 2, 1700)), 1);  // 1700 is not leap
    CHECK_EQ(date(1, 3, 1600).compare(date(28, 2, 1600)), 2);  // 1600 is leap
    CHECK_EQ(date(1, 1, 2018).compare(date(31, 12, 2017)), 1);
    d2.set_day(1); d2.set_month(11); d2.set_year(3229);
    CHECK_EQ(d2.get_string(), std::string("1 November 3229"));

    bday b("Test Subject", date(24, 11, 1971));
    CHECK_EQ(b.get_string(), std::string("Test Subject, 24 November 1971"));

    calendar cal;
    cal.add(bday("John Doe", date(2, 5, 2017)));
    cal.add(bday("Jane Doe", date(13, 9, 2016)));
    cal.add(bday("Mr. Brown", date(21, 3, 1999)));
    cal.add(bday("Jane Doe", date(14, 9, 2016)));     // update, not a second entry
    CHECK_EQ(captured([&] { cal.print(); }),
             std::string("John Doe, 2 May 2017\nJane Doe, 14 September 2016\nMr. Brown, 21 March 1999\n"));
    cal.remove("John Doe");
    cal.remove("Some Guy");                          // nothing happens
    cal.add(bday("New Person", date(11, 9, 2016)));
    cal.add(bday("Another Person", date(9, 9, 2016)));
    CHECK_EQ(captured([&] { cal.print_incoming(date(10, 9, 2016)); }),
             std::string("Jane Doe, 14 September 2016\nNew Person, 11 September 2016\n"));
    calendar wrap;                                   // across the end of the year
    wrap.add(bday("Ny", date(2, 1, 1990)));
    wrap.add(bday("Old", date(20, 12, 1990)));
    CHECK_EQ(captured([&] { wrap.print_incoming(date(28, 12, 2020)); }), std::string("Ny, 2 January 1990\n"));
    return check_summary("2017 as4 date / bday / calendar");
}
