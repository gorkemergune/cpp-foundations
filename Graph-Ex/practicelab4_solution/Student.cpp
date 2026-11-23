#include "Student.h"

// This file is complete. Do not change it.

Student::Student(int id, const string& name) : ID(id), NAME(name) {}

int Student::getId() const {
    return ID;
}

string Student::getName() const {
    return NAME;
}

const vector<int>& Student::getFriends() const {
    return FRIENDS;
}

bool Student::isFriend(int id) const {
    for (size_t i = 0; i < FRIENDS.size(); i++) {
        if (FRIENDS[i] == id) {
            return true;
        }
    }
    return false;
}

bool Student::addFriend(int id) {
    if (isFriend(id)) {
        return false;
    }
    FRIENDS.push_back(id);
    return true;
}
