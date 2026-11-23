// ============================================================================
//  Mini Project 05 · Phone book on a BST · YOU WORK HERE (about 90 lines)
//  Test:  .\run.ps1 P05        Program:  main_demo.cpp (reads contacts.txt)
// ============================================================================
#include "phonebook.h"

#include "todo.h"

using namespace std;

void PhoneBook::destroy(Entry* p) {
    TODO();
}

PhoneBook::~PhoneBook() {
    // TODO: write this (it must not throw)
}

PhoneBook::Entry** PhoneBook::findLink(const string& name) {
    TODO();
}

bool PhoneBook::add(const string& name, const string& phone) {
    TODO();
}

bool PhoneBook::update(const string& name, const string& phone) {
    TODO();
}

bool PhoneBook::find(const string& name, string& phone) const {
    TODO();
}

int PhoneBook::size() const {
    TODO();
}

bool PhoneBook::remove(const string& name) {
    TODO();
}

void PhoneBook::prefixInto(const Entry* p, const string& prefix, vector<string>& out) {
    TODO();
}

vector<string> PhoneBook::namesWithPrefix(const string& prefix) const {
    TODO();
}

void PhoneBook::saveFrom(const Entry* p, ostream& out) {
    TODO();
}

void PhoneBook::save(ostream& out) const {
    TODO();
}

void PhoneBook::load(istream& in) {
    TODO();
}

int PhoneBook::heightOf(const Entry* p) {
    TODO();
}

int PhoneBook::height() const {
    TODO();
}
