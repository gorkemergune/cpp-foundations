// Mini Project 05 tests (the contacts of contacts.txt).
#include <sstream>

#include "phonebook.h"
#include "test.h"

using namespace lab;
using S = std::vector<std::string>;

static void fill(PhoneBook& b) {
    std::istringstream in("Mert 0532-111\nAyse 0533-222\nZeynep 0534-333\nAli 0535-444\nCan 0536-555\nSelin 0537-666\n");
    std::string n, p;
    while (in >> n >> p) b.add(n, p);
}
static std::string saved(const PhoneBook& b) {
    std::ostringstream out;
    b.save(out);
    return out.str();
}

QUESTION("P05-A", "add / update / find / size", "PhoneBook::add(") {
    PhoneBook b;
    check("empty size", 0, b.size());
    fill(b);
    check("size", 6, b.size());
    std::string phone = "none";
    check("find Can", true, b.find("Can", phone));
    check("Can's phone", std::string("0536-555"), phone);
    check("add an existing name", false, b.add("Can", "000"));
    check("update Can", true, b.update("Can", "0599-999"));
    b.find("Can", phone);
    check("Can's new phone", std::string("0599-999"), phone);
    phone = "none";
    check("find a missing name", false, b.find("Deniz", phone));
    check("phone unchanged", std::string("none"), phone);
    check("update a missing name", false, b.update("Deniz", "1"));
    check("size unchanged", 6, b.size());
}

QUESTION("P05-B", "remove / namesWithPrefix", "PhoneBook::remove(") {
    PhoneBook b;
    fill(b);
    b.add("Ahmet", "0538-777");
    b.add("Asli", "0539-888");
    check("prefix A", S{"Ahmet", "Ali", "Asli", "Ayse"}, b.namesWithPrefix("A"));
    check("prefix As", S{"Asli"}, b.namesWithPrefix("As"));
    check("prefix Q", S{}, b.namesWithPrefix("Q"));
    check("empty prefix: everybody", 8, (int)b.namesWithPrefix("").size());
    check("remove Mert (the root, two children)", true, b.remove("Mert"));
    check("remove Mert again", false, b.remove("Mert"));
    check("size", 7, b.size());
    std::string phone;
    check("Selin still there", true, b.find("Selin", phone));
    check("Selin's phone", std::string("0537-666"), phone);
    check("remove Ali (leaf)", true, b.remove("Ali"));
    check("remove Zeynep (one child)", true, b.remove("Zeynep"));
    check("prefix A after removals", S{"Ahmet", "Asli", "Ayse"}, b.namesWithPrefix("A"));
    check("size", 5, b.size());
}

QUESTION("P05-C", "save (preorder) / load / height", "PhoneBook::save(") {
    PhoneBook b;
    fill(b);
    std::string text = "Mert 0532-111\nAyse 0533-222\nAli 0535-444\nCan 0536-555\nZeynep 0534-333\nSelin 0537-666\n";
    check("save", text, saved(b));
    check("height", 3, b.height());
    PhoneBook c;
    std::istringstream in(text);
    c.load(in);
    check("load(save()) gives the same tree", text, saved(c));
    check("loaded size", 6, c.size());
    b.remove("Mert");
    check("save after removing the root", std::string("Selin 0537-666\nAyse 0533-222\nAli 0535-444\nCan 0536-555\nZeynep 0534-333\n"),
          saved(b));
    PhoneBook e;
    check("empty book", std::string(""), saved(e));
    check("empty height", 0, e.height());
}
