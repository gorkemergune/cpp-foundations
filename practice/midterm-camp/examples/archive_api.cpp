#include <cassert>
#include <iostream>
#include <vector>

#include "../../../materials/labworks/lw1-singly-linked-list/archive-solution/intSLList.h"
#include "../../../materials/labworks/lw2-doubly-linked-list/archive-solution/genDLList.h"
#include "../../../materials/labworks/lw8-min-heap/archive-solution/heap.h"
#include "../../../materials/practice-labs/pl4-campus-friends/practicelab4_solution/Graph.h"

void showLists() {
    IntSLList list;
    list.addToHead(20);
    list.addToHead(10);
    list.addToTail(30);
    assert(list.isInList(20));
    list.deleteNode(20);
    assert(!list.isInList(20));
    const int first = list.deleteFromHead();
    const int last = list.deleteFromTail();
    assert(first == 10 && last == 30 && list.isEmpty());

    DoublyLinkedList<int> ends;
    ends.addToDLLHead(20);
    ends.addToDLLTail(30);
    ends.addToDLLHead(10);
    assert(ends.firstEl() == 10 && ends.find(30) != nullptr);
    const int left = ends.deleteFromDLLHead();
    const int right = ends.deleteFromDLLTail();
    assert(left == 10 && right == 30);
    ends.clear();
    assert(ends.isEmpty());

    std::cout << "IntSLList and DoublyLinkedList: OK\n";
}

void showGraph() {
    Graph graph;
    graph.addStudent(Student{101, "A"});
    graph.addStudent(Student{102, "B"});
    graph.addStudent(Student{103, "C"});
    graph.addStudent(Student{104, "D"});  // Izole öğrenci.
    const bool firstEdge = graph.addFriendship(101, 102);
    const bool secondEdge = graph.addFriendship(102, 103);
    assert(firstEdge && secondEdge && graph.getSize() == 4);

    const Student* student = graph.getStudent(101);
    assert(student != nullptr && student->getId() == 101);
    assert(student->isFriend(102) && graph.indexOf(104) == 3);
    assert(graph.getStudent(999) == nullptr);
    assert((graph.bfs(101) == std::vector<int>{101, 102, 103}));
    assert((graph.dfs(101) == std::vector<int>{101, 102, 103}));
    assert(graph.countGroups() == 2);
    assert(graph.mostPopular() == 102);
    assert((graph.mutualFriends(101, 103) == std::vector<int>{102}));
    assert((graph.suggestFriends(101) == std::vector<int>{103}));

    std::cout << "Campus Friends graph: OK\n";
}

void showHeap() {
    int data[]{4, 1, 7};
    heap minHeap(data, 3);  // Labwork 8 verilen diziyi yerinde düzenler.
    assert(data[0] == 1);
    minHeap.delete_min();
    assert(data[0] == 4);
    minHeap.delete_min();
    assert(data[0] == 7);

    std::cout << "Labwork 8 heap: OK\n";
}

int main() {
    showLists();
    showGraph();
    showHeap();
}
