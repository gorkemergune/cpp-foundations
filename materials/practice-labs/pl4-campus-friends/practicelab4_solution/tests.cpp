// Tests for the five friendship questions.
// Run with: make test   (or make test Q=1 ... Q=5 for one question)
// DO NOT CHANGE THIS FILE.
#define TESTING
#include "main.cpp"

#include <sstream>
#include <stdexcept>

static int passed = 0;
static int total = 0;
static int questionsPassed = 0;
static int questionsTested = 0;

static void report(const char* name, bool ok) {
    ++total;
    if (ok) ++passed;
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << std::endl;
}

// Builds a network without printing anything.
static void quiet(void (*f)(Graph&), Graph& g) {
    std::ostringstream out;
    std::streambuf* old = std::cout.rdbuf(out.rdbuf());
    f(g);
    std::cout.rdbuf(old);
}

static void campus(Graph& g) { buildNetwork(g); }

// Builds the 10 campus students with the given friendships.
static void campusWith(Graph& g, const std::vector<std::pair<int, int>>& friendships) {
    const char* names[] = { "Ayşe", "Burak", "Can", "Deniz", "Elif",
                            "Emre", "Selin", "Kerem", "Zeynep", "Mert" };
    for (int i = 0; i < 10; i++) g.addStudent(Student(101 + i, names[i]));
    for (size_t i = 0; i < friendships.size(); i++)
        g.addFriendship(friendships[i].first, friendships[i].second);
}

// The campus network without Deniz - Emre.
static void campusWithoutDenizEmre(Graph& g) {
    campusWith(g, { { 101, 102 }, { 101, 103 }, { 102, 104 }, { 103, 104 }, { 104, 105 },
                    { 105, 106 }, { 106, 107 }, { 108, 109 } });
}

// The campus network without Deniz - Emre and Elif - Emre: four groups.
static void campusSplit(Graph& g) {
    campusWith(g, { { 101, 102 }, { 101, 103 }, { 102, 104 }, { 103, 104 }, { 104, 105 },
                    { 106, 107 }, { 108, 109 } });
}

// Four students, two friendships: everyone has 1 friend.
static void tie(Graph& g) {
    g.addStudent(Student(5, "A")); g.addStudent(Student(3, "B"));
    g.addStudent(Student(9, "C")); g.addStudent(Student(1, "D"));
    g.addFriendship(5, 9); g.addFriendship(3, 1);
}

// Three friends in a triangle.
static void triangle(Graph& g) {
    g.addStudent(Student(1, "A")); g.addStudent(Student(2, "B")); g.addStudent(Student(3, "C"));
    g.addFriendship(1, 2); g.addFriendship(2, 3); g.addFriendship(3, 1);
}

// Five students in a ring: 1-2-3-4-5-1.
static void ring(Graph& g) {
    for (int i = 1; i <= 5; i++) g.addStudent(Student(i, "S" + std::to_string(i)));
    for (int i = 1; i <= 4; i++) g.addFriendship(i, i + 1);
    g.addFriendship(5, 1);
}

// Four students with no friendships.
static void loners(Graph& g) {
    for (int i = 1; i <= 4; i++) g.addStudent(Student(i, "S" + std::to_string(i)));
}

#define NETWORK(name, builder) Graph name; quiet(builder, name)

template <typename F>
static bool safe(F f) {
    try { return f(); }
    catch (const std::exception&) { return false; }
}

static std::vector<int> v(std::initializer_list<int> list) { return std::vector<int>(list); }

// ---------------- Question 1: bfs and dfs ----------------

static void testQ1() {
    report("BFS order from Ayşe", safe([] {
        NETWORK(g, campus);
        return g.bfs(101) == v({ 101, 102, 103, 104, 105, 106, 107 });
    }));
    report("DFS order from Ayşe", safe([] {
        NETWORK(g, campus);
        return g.dfs(101) == v({ 101, 102, 104, 103, 105, 106, 107 });
    }));
    report("BFS and DFS from Emre", safe([] {
        NETWORK(g, campus);
        return g.bfs(106) == v({ 106, 104, 105, 107, 102, 103, 101 })
            && g.dfs(106) == v({ 106, 104, 102, 101, 103, 105, 107 });
    }));
    report("BFS and DFS differ on a ring", safe([] {
        NETWORK(g, ring);
        return g.bfs(1) == v({ 1, 2, 5, 3, 4 }) && g.dfs(1) == v({ 1, 2, 3, 4, 5 });
    }));
    report("Only the student's own group is visited", safe([] {
        NETWORK(g, campus);
        return g.bfs(108) == v({ 108, 109 }) && g.dfs(109) == v({ 109, 108 })
            && g.bfs(110) == v({ 110 }) && g.dfs(110) == v({ 110 });
    }));
    report("Invalid ID", safe([] {
        NETWORK(g, campus);
        return g.bfs(999).empty() && g.dfs(999).empty();
    }));
    report("printNetwork in DFS order from Emre", safe([] {
        NETWORK(g, campus);
        std::ostringstream out;
        std::streambuf* old = std::cout.rdbuf(out.rdbuf());
        g.printNetwork(106, true);
        std::cout.rdbuf(old);
        return out.str() ==
            "106 Emre (3): Deniz Elif Selin\n"
            "104 Deniz (4): Burak Can Elif Emre\n"
            "102 Burak (2): Ayşe Deniz\n"
            "101 Ayşe (2): Burak Can\n"
            "103 Can (2): Ayşe Deniz\n"
            "105 Elif (2): Deniz Emre\n"
            "107 Selin (1): Emre\n"
            "\n"
            "108 Kerem (1): Zeynep\n"
            "109 Zeynep (1): Kerem\n"
            "\n"
            "110 Mert (0):\n";
    }));
}

// ---------------- Question 2: mostPopular ----------------

static void testQ2() {
    report("Student with the most friends", safe([] {
        NETWORK(g, campus);
        return g.mostPopular() == 104;
    }));
    report("Tie: the student that comes first", safe([] {
        NETWORK(g, tie);
        return g.mostPopular() == 5;
    }));
    report("Nobody has friends", safe([] {
        NETWORK(g, loners);
        return g.mostPopular() == 1;
    }));
    report("Empty network", safe([] {
        Graph g;
        return g.mostPopular() == -1;
    }));
}

// ---------------- Question 3: mutualFriends ----------------

static void testQ3() {
    report("Mutual friends in the order of id1's list", safe([] {
        NETWORK(g, campus);
        return g.mutualFriends(101, 104) == v({ 102, 103 })
            && g.mutualFriends(104, 101) == v({ 102, 103 })
            && g.mutualFriends(104, 106) == v({ 105 });
    }));
    report("No mutual friends", safe([] {
        NETWORK(g, campus);
        return g.mutualFriends(101, 107).empty() && g.mutualFriends(101, 110).empty();
    }));
    report("Two friends in a triangle", safe([] {
        NETWORK(g, triangle);
        return g.mutualFriends(1, 2) == v({ 3 });
    }));
    report("Invalid ID", safe([] {
        NETWORK(g, campus);
        return g.mutualFriends(101, 999).empty() && g.mutualFriends(999, 101).empty();
    }));
}

// ---------------- Question 4: countGroups ----------------

static void testQ4() {
    report("Groups in the campus network", safe([] {
        NETWORK(g, campus);
        return g.countGroups() == 3;
    }));
    report("Fewer friendships, more groups", safe([] {
        NETWORK(a, campusWithoutDenizEmre);
        NETWORK(b, campusSplit);
        return a.countGroups() == 3 && b.countGroups() == 4;
    }));
    report("Everyone in one group", safe([] {
        NETWORK(a, ring);
        NETWORK(b, triangle);
        return a.countGroups() == 1 && b.countGroups() == 1;
    }));
    report("Nobody has friends, empty network", safe([] {
        NETWORK(a, loners);
        Graph b;
        return a.countGroups() == 4 && b.countGroups() == 0;
    }));
}

// ---------------- Question 5: suggestFriends ----------------

static void testQ5() {
    report("Friends of friends in the order you meet them", safe([] {
        NETWORK(g, campus);
        return g.suggestFriends(104) == v({ 101, 107 })
            && g.suggestFriends(107) == v({ 104, 105 });
    }));
    report("Same student reached through two friends is suggested once", safe([] {
        NETWORK(g, campus);
        return g.suggestFriends(101) == v({ 104 });
    }));
    report("The student and current friends are not suggested", safe([] {
        NETWORK(a, triangle);
        NETWORK(b, campusWithoutDenizEmre);
        return a.suggestFriends(1).empty() && b.suggestFriends(104) == v({ 101, 106 });
    }));
    report("No friends or no friends of friends", safe([] {
        NETWORK(g, campus);
        return g.suggestFriends(110).empty() && g.suggestFriends(108).empty();
    }));
    report("Invalid ID", safe([] {
        NETWORK(g, campus);
        return g.suggestFriends(999).empty();
    }));
}

static void runQuestion(const char* title, void (*test)()) {
    std::cout << "\n" << title << "\n";
    const int previousPassed = passed;
    const int previousTotal = total;
    test();
    const int questionPassed = passed - previousPassed;
    const int questionTotal = total - previousTotal;
    const bool ok = questionPassed == questionTotal;
    ++questionsTested;
    if (ok) ++questionsPassed;
    std::cout << "Result: " << (ok ? "PASS" : "FAIL")
        << " (" << questionPassed << "/" << questionTotal << " tests passed)\n";
}

int main(int argc, char* argv[]) {
    const std::string selection = argc == 1 ? "all" : argv[1];
    if (argc > 2 || (selection != "all" && (selection.size() != 1 || selection[0] < '1' || selection[0] > '5'))) {
        std::cerr << "Usage: lab4_tests [1|2|3|4|5|all]\n";
        return 2;
    }
    const bool all = selection == "all";
    if (all || selection == "1") runQuestion("Q1 - BFS and DFS traversal", testQ1);
    if (all || selection == "2") runQuestion("Q2 - Most popular student", testQ2);
    if (all || selection == "3") runQuestion("Q3 - Mutual friends", testQ3);
    if (all || selection == "4") runQuestion("Q4 - Friend groups", testQ4);
    if (all || selection == "5") runQuestion("Q5 - Suggest friends", testQ5);
    std::cout << "\n" << questionsPassed << "/" << questionsTested << " questions passed all tests.\n";
    if (passed == total) std::cout << "ALL TESTS PASSED\n";
    else std::cout << "Some tests failed. Review the failed cases above.\n";
    return passed == total ? 0 : 1;
}
