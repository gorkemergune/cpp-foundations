// Mini Project 04 tests (the map of metro.txt).
#include "metro.h"
#include "test.h"

using namespace lab;
using S = std::vector<std::string>;

static Metro city() {
    Metro m;
    m.addLine("M1", {"Gar", "Carsi", "Kampus", "Kutuphane", "Stadyum"});
    m.addLine("M2", {"Liman", "Carsi", "Muze", "Park"});
    m.addLine("M3", {"Kampus", "Hastane", "Park"});
    return m;
}

QUESTION("P04-A", "addLine / stationCount / neighbours", "Metro::addLine(") {
    Metro m = city();
    check("stations", 9, m.stationCount());
    check("neighbours of Carsi (connection order)", S{"Gar", "Kampus", "Liman", "Muze"}, m.neighbours("Carsi"));
    check("neighbours of Park", S{"Muze", "Hastane"}, m.neighbours("Park"));
    check("unknown station", S{}, m.neighbours("Havalimani"));
    m.addLine("M4", {"Carsi", "Kampus"});
    check("an existing pair is not connected twice", S{"Gar", "Kampus", "Liman", "Muze"}, m.neighbours("Carsi"));
    m.addLine("M5", {"Depo"});
    check("a line with one station adds it", 10, m.stationCount());
}

QUESTION("P04-B", "route / stops (BFS)", "Metro::route(") {
    Metro m = city();
    check("Gar -> Park", S{"Gar", "Carsi", "Muze", "Park"}, m.route("Gar", "Park"));
    check("Stadyum -> Park", S{"Stadyum", "Kutuphane", "Kampus", "Hastane", "Park"}, m.route("Stadyum", "Park"));
    check("Liman -> Hastane", S{"Liman", "Carsi", "Kampus", "Hastane"}, m.route("Liman", "Hastane"));
    check("same station", S{"Muze"}, m.route("Muze", "Muze"));
    check("unknown station", S{}, m.route("Gar", "Ay"));
    check("stops Gar -> Park", 3, m.stops("Gar", "Park"));
    check("stops Muze -> Muze", 0, m.stops("Muze", "Muze"));
    m.addLine("M5", {"Depo"});
    check("no route to Depo", S{}, m.route("Gar", "Depo"));
    check("stops to Depo", -1, m.stops("Gar", "Depo"));
}

QUESTION("P04-C", "transfers / withinStops", "Metro::transfers(") {
    Metro m = city();
    check("Gar Carsi Muze Park (M1, M2, M2)", 1, m.transfers(m.route("Gar", "Park")));
    check("Liman Carsi Kampus Hastane (M2, M1, M3)", 2, m.transfers(m.route("Liman", "Hastane")));
    check("one line only", 0, m.transfers({"Gar", "Carsi", "Kampus"}));
    check("one stop", 0, m.transfers({"Gar", "Carsi"}));
    check("within 1 of Carsi", S{"Gar", "Kampus", "Liman", "Muze"}, m.withinStops("Carsi", 1));
    check("within 2 of Park", S{"Carsi", "Hastane", "Kampus", "Muze"}, m.withinStops("Park", 2));
    check("within 0", S{}, m.withinStops("Park", 0));
    check("unknown", S{}, m.withinStops("Ay", 3));
}
