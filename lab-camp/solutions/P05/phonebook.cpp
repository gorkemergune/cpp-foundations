// ============================================================================
//  Mini Project 05 · Phone book on a BST · YOU WORK HERE (about 90 lines)
//  Reference solution. @solution-note
//  Test:  .\run.ps1 P05        Program:  main_demo.cpp (reads contacts.txt)
// ============================================================================
#include "phonebook.h"

#include "todo.h"

using namespace std;

// @begin destroy
void PhoneBook::destroy(Entry* p) {
    if (p == nullptr) return;
    destroy(p->left);
    destroy(p->right);
    delete p;
}
// @end destroy

// @begin PhoneBookDtor empty
PhoneBook::~PhoneBook() {
    destroy(root);
}
// @end PhoneBookDtor

// @begin findLink
PhoneBook::Entry** PhoneBook::findLink(const string& name) {
    Entry** link = &root;
    while (*link != nullptr && (*link)->name != name)
        link = (name < (*link)->name) ? &(*link)->left : &(*link)->right;
    return link;                            // *link == nullptr: name is not in the book
}
// @end findLink

// @begin add
bool PhoneBook::add(const string& name, const string& phone) {
    Entry** link = findLink(name);
    if (*link != nullptr) return false;
    *link = new Entry{name, phone};
    count++;
    return true;
}
// @end add

// @begin update
bool PhoneBook::update(const string& name, const string& phone) {
    Entry* e = *findLink(name);
    if (e == nullptr) return false;
    e->phone = phone;
    return true;
}
// @end update

// @begin find
bool PhoneBook::find(const string& name, string& phone) const {
    const Entry* p = root;                  // const: findLink would need a non-const book
    while (p != nullptr && p->name != name) p = (name < p->name) ? p->left : p->right;
    if (p == nullptr) return false;
    phone = p->phone;
    return true;
}
// @end find

// @begin size
int PhoneBook::size() const {
    return count;
}
// @end size

// @begin remove
bool PhoneBook::remove(const string& name) {
    Entry** link = findLink(name);
    Entry* e = *link;
    if (e == nullptr) return false;
    if (e->left != nullptr && e->right != nullptr) {
        Entry** s = &e->right;              // successor: leftmost of the right subtree
        while ((*s)->left != nullptr) s = &(*s)->left;
        Entry* succ = *s;
        e->name = succ->name;               // copy it up ...
        e->phone = succ->phone;
        *s = succ->right;                   // ... and unlink the old successor node
        e = succ;
    } else {
        *link = (e->left != nullptr) ? e->left : e->right;
    }
    delete e;
    count--;
    return true;
}
// @end remove

// @begin prefixInto
void PhoneBook::prefixInto(const Entry* p, const string& prefix, vector<string>& out) {
    if (p == nullptr) return;
    string head = p->name.substr(0, prefix.size());
    if (head >= prefix) prefixInto(p->left, prefix, out);   // smaller matches can only be left
    if (head == prefix) out.push_back(p->name);
    if (head <= prefix) prefixInto(p->right, prefix, out);  // larger matches can only be right
}
// @end prefixInto

// @begin namesWithPrefix
vector<string> PhoneBook::namesWithPrefix(const string& prefix) const {
    vector<string> out;
    prefixInto(root, prefix, out);
    return out;
}
// @end namesWithPrefix

// @begin saveFrom
void PhoneBook::saveFrom(const Entry* p, ostream& out) {
    if (p == nullptr) return;
    out << p->name << " " << p->phone << "\n";   // preorder: a parent before its children
    saveFrom(p->left, out);
    saveFrom(p->right, out);
}
// @end saveFrom

// @begin save
void PhoneBook::save(ostream& out) const {
    saveFrom(root, out);
}
// @end save

// @begin load
void PhoneBook::load(istream& in) {
    string name, phone;
    while (in >> name >> phone) add(name, phone);
}
// @end load

// @begin heightOf
int PhoneBook::heightOf(const Entry* p) {
    if (p == nullptr) return 0;
    int l = heightOf(p->left), r = heightOf(p->right);
    return 1 + (l > r ? l : r);
}
// @end heightOf

// @begin height
int PhoneBook::height() const {
    return heightOf(root);
}
// @end height
