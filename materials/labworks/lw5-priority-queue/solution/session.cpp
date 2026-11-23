#include "session.h"

#include <string>

#include "priority_queue.h"

void run_session(std::istream& in, std::ostream& out) {
    PriorityQueue<std::string> pq;
    std::string name;
    int priority;
    while (true) {
        out << "name: ";
        if (!(in >> name)) break;
        out << "priority: ";
        if (!(in >> priority) || priority == -1) break;
        pq.enqueue(name, priority);
        out << "queue: " << pq << "\n";
    }
}
