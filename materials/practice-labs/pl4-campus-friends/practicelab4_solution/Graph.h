#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>
#include "Student.h"

using namespace std;

// The friendship network: an undirected graph stored as an adjacency list.
// Every vertex is a Student. The int in each pair is the student ID.
// Do not change this file.
class Graph {
private:
    vector<pair<int, Student> > STUDENTS;
    int SIZE;

    // Helper for Question 1: recursive DFS from the student with this ID.
    void dfsVisit(int id, vector<int>& order) const;

public:
    Graph() : SIZE(0) {}

    // Provided (ready)
    int indexOf(int id) const;
    void addStudent(const Student& student);
    const Student* getStudent(int id) const;
    int getSize() const;
    bool addFriendship(int id1, int id2);

    void printNetwork(int startId, bool useDfs) const;   // uses bfs / dfs

    // Friendship questions (you write these)
    vector<int> bfs(int startId) const;                   // Question 1
    vector<int> dfs(int startId) const;                   // Question 1
    int mostPopular() const;                              // Question 2
    vector<int> mutualFriends(int id1, int id2) const;    // Question 3
    int countGroups() const;                              // Question 4
    vector<int> suggestFriends(int id) const;             // Question 5
};

// Provided: returns true if id is in list.
bool contains(const vector<int>& list, int id);

#endif
