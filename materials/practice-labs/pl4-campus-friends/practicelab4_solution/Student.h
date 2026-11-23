#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

using namespace std;

// A student in the friendship network.
// It keeps its own ID, its name and the IDs of its friends.
// This class is complete. Do not change it.
class Student {
private:
    int ID;
    string NAME;
    vector<int> FRIENDS;

public:
    Student(int id, const string& name);

    int getId() const;
    string getName() const;
    const vector<int>& getFriends() const;

    bool isFriend(int id) const;
    bool addFriend(int id);
};

#endif
