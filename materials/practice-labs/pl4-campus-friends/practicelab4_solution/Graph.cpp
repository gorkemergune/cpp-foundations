#include "Graph.h"
#include <iostream>
#include <queue>

// ====================================================================
//              PROVIDED FUNCTIONS - READY, DO NOT CHANGE
// ====================================================================

bool contains(const vector<int>& list, int id) {
    for (size_t i = 0; i < list.size(); i++) {
        if (list[i] == id) {
            return true;
        }
    }
    return false;
}


int Graph::indexOf(int id) const {
    for (int i = 0; i < SIZE; i++) {
        if (STUDENTS[i].first == id) {
            return i;
        }
    }
    return -1;
}

// Adds the student to STUDENTS. Used by buildNetwork.
void Graph::addStudent(const Student& student) {
    if (indexOf(student.getId()) != -1) {
        return;                          // ID already used
    }
    STUDENTS.push_back(make_pair(student.getId(), student));
    SIZE++;
}

const Student* Graph::getStudent(int id) const {
    int i = indexOf(id);
    if (i == -1) {
        return nullptr;
    }
    return &STUDENTS[i].second;
}

int Graph::getSize() const {
    return SIZE;
}

// Adds the friendship to both friend lists. Used by buildNetwork.
bool Graph::addFriendship(int id1, int id2) {
    int i = indexOf(id1);
    int j = indexOf(id2);
    if (i == -1 || j == -1 || i == j || STUDENTS[i].second.isFriend(id2)) {
        return false;                    // invalid, same student or already friends
    }
    STUDENTS[i].second.addFriend(id2);
    STUDENTS[j].second.addFriend(id1);
    return true;
}

// Prints every student with their friends (menu options 1 and 2).
// The order comes from YOUR bfs or dfs (Question 1): first the group of
// startId, then every group that is not printed yet. Until bfs and dfs
// are written, nothing is printed.
void Graph::printNetwork(int startId, bool useDfs) const {
    vector<bool> printed(SIZE, false);
    vector<int> starts;                  // startId first, then everyone in order
    starts.push_back(startId);
    for (int i = 0; i < SIZE; i++) {
        starts.push_back(STUDENTS[i].first);
    }

    bool firstGroup = true;
    for (size_t s = 0; s < starts.size(); s++) {
        int pos = indexOf(starts[s]);
        if (pos == -1 || printed[pos]) {
            continue;
        }
        vector<int> order = useDfs ? dfs(starts[s]) : bfs(starts[s]);
        if (order.empty()) {
            continue;
        }
        if (!firstGroup) {
            cout << endl;                // blank line between groups
        }
        firstGroup = false;
        for (size_t k = 0; k < order.size(); k++) {
            int i = indexOf(order[k]);
            if (i == -1 || printed[i]) {
                continue;
            }
            printed[i] = true;
            const Student& st = STUDENTS[i].second;
            const vector<int>& friends = st.getFriends();
            cout << STUDENTS[i].first << " " << st.getName() << " (" << friends.size() << "):";
            for (size_t f = 0; f < friends.size(); f++) {
                cout << " " << getStudent(friends[f])->getName();
            }
            cout << endl;
        }
    }
}

// ====================================================================
//              FRIENDSHIP QUESTIONS - YOUR CODE GOES HERE
// ====================================================================

// Question 1: BFS visits the start, then everyone 1 step away, then 2 steps...
// order is the result and also the list of visited students.
vector<int> Graph::bfs(int startId) const {
    vector<int> order;
    if (getStudent(startId) == nullptr) {
        return order;
    }
    queue<int> q;
    order.push_back(startId);
    q.push(startId);
    while (!q.empty()) {
        int id = q.front();
        q.pop();
        for (int f : getStudent(id)->getFriends()) {
            if (!contains(order, f)) {   // not visited yet
                order.push_back(f);
                q.push(f);
            }
        }
    }
    return order;
}

// Question 1: DFS goes as deep as possible through the first unvisited
// friend before coming back to try the next one.
vector<int> Graph::dfs(int startId) const {
    vector<int> order;
    if (getStudent(startId) == nullptr) {
        return order;
    }
    dfsVisit(startId, order);
    return order;
}

void Graph::dfsVisit(int id, vector<int>& order) const {
    order.push_back(id);
    for (int f : getStudent(id)->getFriends()) {
        if (!contains(order, f)) {       // not visited yet
            dfsVisit(f, order);          // go deeper first
        }
    }
}

// Question 2: The most popular student is the vertex with the highest degree.
int Graph::mostPopular() const {
    int best = -1;
    int bestCount = -1;
    for (int i = 0; i < SIZE; i++) {
        int count = STUDENTS[i].second.getFriends().size();
        if (count > bestCount) {          // ">" keeps the first one on a tie
            bestCount = count;
            best = STUDENTS[i].first;
        }
    }
    return best;
}

// Question 3: Mutual friends are the common neighbors of two vertices.
vector<int> Graph::mutualFriends(int id1, int id2) const {
    vector<int> result;
    const Student* a = getStudent(id1);
    const Student* b = getStudent(id2);
    if (a == nullptr || b == nullptr) {
        return result;
    }
    const vector<int>& friends = a->getFriends();
    for (size_t k = 0; k < friends.size(); k++) {
        if (b->isFriend(friends[k])) {
            result.push_back(friends[k]);
        }
    }
    return result;
}

// Question 4: Friend groups are the connected components.
// One bfs from a student returns that student's whole group.
int Graph::countGroups() const {
    vector<int> seen;
    int groups = 0;
    for (int i = 0; i < SIZE; i++) {
        int id = STUDENTS[i].first;
        if (!contains(seen, id)) {
            groups++;                    // a new group starts here
            vector<int> group = bfs(id);
            for (int g : group) {
                seen.push_back(g);
            }
        }
    }
    return groups;
}

// Question 5: Suggestions are the vertices at distance exactly 2.
vector<int> Graph::suggestFriends(int id) const {
    vector<int> result;
    const Student* s = getStudent(id);
    if (s == nullptr) {
        return result;
    }
    for (int f : s->getFriends()) {                       // each friend f
        for (int candidate : getStudent(f)->getFriends()) {  // each friend of f
            if (candidate != id && !s->isFriend(candidate) && !contains(result, candidate)) {
                result.push_back(candidate);
            }
        }
    }
    return result;
}
