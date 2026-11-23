#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include "Graph.h"

using namespace std;

// Adds the 10 students and the 9 friendships of the campus network.
void buildNetwork(Graph& network) {
    network.addStudent(Student(101, "Ayşe"));
    network.addStudent(Student(102, "Burak"));
    network.addStudent(Student(103, "Can"));
    network.addStudent(Student(104, "Deniz"));
    network.addStudent(Student(105, "Elif"));
    network.addStudent(Student(106, "Emre"));
    network.addStudent(Student(107, "Selin"));
    network.addStudent(Student(108, "Kerem"));
    network.addStudent(Student(109, "Zeynep"));
    network.addStudent(Student(110, "Mert"));

    network.addFriendship(101, 102);  // Ayşe - Burak
    network.addFriendship(101, 103);  // Ayşe - Can
    network.addFriendship(102, 104);  // Burak - Deniz
    network.addFriendship(103, 104);  // Can - Deniz
    network.addFriendship(104, 105);  // Deniz - Elif
    network.addFriendship(104, 106);  // Deniz - Emre
    network.addFriendship(105, 106);  // Elif - Emre
    network.addFriendship(106, 107);  // Emre - Selin
    network.addFriendship(108, 109);  // Kerem - Zeynep
}

#ifndef TESTING
// Reads an integer and asks again if the input is not a number.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        if (cin.eof()) {
            cout << endl;
            exit(0);
        }
        cout << "Please enter a number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string nameOf(const Graph& network, int id) {
    return network.getStudent(id)->getName();
}

// Prints the names of the students with these IDs, separated by spaces.
void printNames(const Graph& network, const vector<int>& ids) {
    for (size_t i = 0; i < ids.size(); i++) {
        cout << " " << nameOf(network, ids[i]);
    }
    cout << endl;
}

// The menu is ready. Every option uses the functions you write.
// This file is complete. Do not change it.
int main() {
    Graph network;
    buildNetwork(network);

    int choice;
    do {
        cout << endl;
        cout << "===== Campus Friends =====" << endl;
        cout << "1. Print the network (BFS order)" << endl;
        cout << "2. Print the network (DFS order)" << endl;
        cout << "3. Most popular student" << endl;
        cout << "4. Mutual friends" << endl;
        cout << "5. Friend groups" << endl;
        cout << "6. Suggest friends" << endl;
        cout << "0. Exit" << endl;
        choice = readInt("Choice: ");

        if (choice == 1 || choice == 2) {
            int id = readInt("Start ID: ");
            if (network.getStudent(id) == nullptr) {
                cout << "Invalid student ID." << endl;
                continue;
            }
            network.printNetwork(id, choice == 2);
        } else if (choice == 3) {
            int id = network.mostPopular();
            if (id == -1) {
                cout << "The network is empty." << endl;
            } else {
                cout << "Most popular: " << nameOf(network, id) << " ("
                     << network.getStudent(id)->getFriends().size() << " friends)" << endl;
            }
        } else if (choice == 4) {
            int a = readInt("First ID: ");
            int b = readInt("Second ID: ");
            if (network.getStudent(a) == nullptr || network.getStudent(b) == nullptr) {
                cout << "Invalid student ID." << endl;
                continue;
            }
            vector<int> mutual = network.mutualFriends(a, b);
            if (mutual.empty()) {
                cout << nameOf(network, a) << " and " << nameOf(network, b)
                     << " have no mutual friends." << endl;
            } else {
                cout << "Mutual friends of " << nameOf(network, a) << " and "
                     << nameOf(network, b) << ":";
                printNames(network, mutual);
            }
        } else if (choice == 5) {
            cout << "There are " << network.countGroups() << " friend groups." << endl;
        } else if (choice == 6) {
            int id = readInt("ID: ");
            if (network.getStudent(id) == nullptr) {
                cout << "Invalid student ID." << endl;
                continue;
            }
            vector<int> suggestions = network.suggestFriends(id);
            if (suggestions.empty()) {
                cout << "No suggestions for " << nameOf(network, id) << "." << endl;
            } else {
                cout << "Suggestions for " << nameOf(network, id) << ":";
                printNames(network, suggestions);
            }
        } else if (choice != 0) {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
#endif
