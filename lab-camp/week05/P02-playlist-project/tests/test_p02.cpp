// Mini Project 02 tests. backwardTitles() walks the prev links.
#include "playlist.h"
#include "test.h"

using namespace lab;

static void fill(Playlist& p) {
    p.add("Intro", 65);
    p.add("Song", 185);
    p.add("Outro", 59);
}

QUESTION("P02-A", "add / size / totalSeconds / current", "Playlist::add(") {
    Playlist p;
    check("empty: size", 0, p.size());
    check("empty: current", std::string(""), p.current());
    fill(p);
    check("size", 3, p.size());
    check("totalSeconds", 309, p.totalSeconds());
    check("the first song becomes current", std::string("Intro"), p.current());
    check("prev links", std::string("Outro Song Intro "), p.backwardTitles());
}

QUESTION("P02-B", "next / prev / remove", "Playlist::remove(") {
    Playlist p;
    fill(p);
    check("prev at the first song", false, p.prev());
    check("next", true, p.next());
    check("current after next", std::string("Song"), p.current());
    check("next", true, p.next());
    check("next at the last song", false, p.next());
    check("remove(\"Outro\") (the current, last song)", true, p.remove("Outro"));
    check("current falls back to the previous song", std::string("Song"), p.current());
    check("remove(\"Song\") (current, now last)", true, p.remove("Song"));
    check("current", std::string("Intro"), p.current());
    check("remove(\"Nope\")", false, p.remove("Nope"));
    p.add("New", 10);
    check("list after removals and add", std::string("New Intro "), p.backwardTitles());
    check("remove(\"Intro\") (current, first)", true, p.remove("Intro"));
    check("current moves to the next song", std::string("New"), p.current());
    check("remove(\"New\")", true, p.remove("New"));
    check("empty: current", std::string(""), p.current());
    check("empty: size", 0, p.size());
    p.add("Again", 1);
    check("add after emptying", std::string("Again"), p.current());
}

QUESTION("P02-C", "moveUp / listing", "Playlist::listing(") {
    Playlist p;
    check("empty listing", std::string(""), p.listing());
    fill(p);
    p.next();
    check("listing", std::string("1. Intro (1:05)\n2. *Song (3:05)\n3. Outro (0:59)\n"), p.listing());
    check("moveUp(\"Outro\")", true, p.moveUp("Outro"));
    check("listing after moveUp", std::string("1. Intro (1:05)\n2. Outro (0:59)\n3. *Song (3:05)\n"), p.listing());
    check("prev links after moveUp", std::string("Song Outro Intro "), p.backwardTitles());
    check("moveUp(\"Outro\") again: to the front", true, p.moveUp("Outro"));
    check("prev links", std::string("Song Intro Outro "), p.backwardTitles());
    check("moveUp of the first song", false, p.moveUp("Outro"));
    check("moveUp of a missing song", false, p.moveUp("Nope"));
}
