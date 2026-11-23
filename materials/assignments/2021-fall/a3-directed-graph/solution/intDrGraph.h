// Assignment 3 (2021) · directed graph with adjacency lists (one IntSLList per vertex).
// Vertices are numbered 1..n as in the input file; listoflist[v-1] holds v's successors.
#ifndef INTDRGRAPH_H
#define INTDRGRAPH_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "IntSLList.h"
#include "queue.h"

class intDrGraph {
public:
    // First number: vertex count n. Then pairs "from to". Vertices are 1..n.
    explicit intDrGraph(const std::string& filename) {
        std::ifstream file(filename.c_str());
        if (!file.is_open() || !(file >> arraysize) || arraysize <= 0) {
            std::cout << "Couldn't open the file" << std::endl;
            arraysize = 0;
            return;
        }
        listoflist = new IntSLList*[arraysize];
        for (int i = 0; i < arraysize; i++) listoflist[i] = new IntSLList;
        int from, to;
        // `while (!file.eof())` would repeat the last edge when the file ends with a
        // newline; testing the read itself stops exactly after the last pair.
        while (file >> from >> to) {
            if (valid(from) && valid(to)) listoflist[from - 1]->addToTail(to);
        }
    }
    ~intDrGraph() {
        for (int i = 0; i < arraysize; i++) delete listoflist[i];
        delete[] listoflist;
    }
    intDrGraph(const intDrGraph&) = delete;             // owns raw memory: no copies
    intDrGraph& operator=(const intDrGraph&) = delete;

    int size() const { return arraysize; }

    // "1 -> 2 3" for every vertex
    void printAdjList() {
        for (int v = 1; v <= arraysize; v++) {
            std::cout << v << " ->";
            for (int w : neighbours(v)) std::cout << " " << w;
            std::cout << std::endl;
        }
    }

    // Breadth-first order from start, using the queue class of the assignment.
    std::vector<int> bfsOrder(int start) {
        std::vector<int> order;
        if (!valid(start)) return order;
        std::vector<bool> seen(arraysize + 1, false);
        queue<int> q;
        q.enqueue(start);
        seen[start] = true;                              // mark on enqueue: no duplicates
        while (!q.isEmpty()) {
            int v = q.dequeue();
            order.push_back(v);
            for (int w : neighbours(v))
                if (!seen[w]) {
                    seen[w] = true;
                    q.enqueue(w);
                }
        }
        return order;
    }
    void performBFS(int start) {
        for (int v : bfsOrder(start)) std::cout << v << " ";
        std::cout << std::endl;
    }

    // Is dest reachable from src? (a vertex reaches itself)
    bool isThereWay(int src, int dest) {
        if (!valid(src) || !valid(dest)) return false;
        for (int v : bfsOrder(src))
            if (v == dest) return true;
        return false;
    }

    // BONUS · every simple path from src to dest (depth-first, neighbours in list order)
    std::vector<std::vector<int>> routes(int src, int dest) {
        std::vector<std::vector<int>> all;
        if (!valid(src) || !valid(dest)) return all;
        std::vector<int> path{src};
        std::vector<bool> onPath(arraysize + 1, false);
        onPath[src] = true;
        collect(src, dest, path, onPath, all);
        return all;
    }
    void findRoutes(int src, int dest) {
        for (const auto& p : routes(src, dest)) {
            for (int v : p) std::cout << v << " ";
            std::cout << std::endl;
        }
    }

private:
    int arraysize = 0;
    IntSLList** listoflist = nullptr;

    bool valid(int v) const { return v >= 1 && v <= arraysize; }

    std::vector<int> neighbours(int v) {                 // copy of v's list, in order
        std::vector<int> r;
        IntSLList* l = listoflist[v - 1];
        for (int i = 1; i <= l->GetSize(); i++) r.push_back(l->GetAt(i));
        return r;
    }

    void collect(int v, int dest, std::vector<int>& path, std::vector<bool>& onPath,
                 std::vector<std::vector<int>>& all) {
        if (v == dest) {
            all.push_back(path);
            return;
        }
        for (int w : neighbours(v)) {
            if (onPath[w]) continue;                     // a simple path never repeats a vertex
            onPath[w] = true;
            path.push_back(w);
            collect(w, dest, path, onPath, all);
            path.pop_back();                             // backtrack
            onPath[w] = false;
        }
    }
};

#endif
