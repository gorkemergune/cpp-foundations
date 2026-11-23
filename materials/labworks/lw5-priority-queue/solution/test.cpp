#include <sstream>
#include <string>

#include "check.h"
#include "priority_queue.h"
#include "session.h"

int main() {
    PriorityQueue<std::string> pq;
    pq.enqueue("John", 5);
    pq.enqueue("Michael", 8);
    pq.enqueue("Bill", 7);
    pq.enqueue("Tom", 2);
    pq.enqueue("Jim", 5);
    std::ostringstream o;
    o << pq;
    CHECK_EQ(o.str(), std::string("Michael Bill John Jim Tom "));  // PDF example, FIFO for John/Jim
    std::string& first = pq.dequeue();
    CHECK_EQ(first, std::string("Michael"));
    CHECK_EQ(pq.dequeue(), std::string("Bill"));
    CHECK_EQ(pq.dequeue(), std::string("John"));
    pq.enqueue("Ann", 9);  // new highest goes to the front
    pq.enqueue("Zed", 1);  // new lowest goes to the back
    CHECK_EQ(pq.dequeue(), std::string("Ann"));
    CHECK_EQ(pq.dequeue(), std::string("Jim"));
    CHECK_EQ(pq.dequeue(), std::string("Tom"));
    CHECK_EQ(pq.dequeue(), std::string("Zed"));
    CHECK(pq.isEmpty());

    std::istringstream in("John 5 Michael 8 Jim 5 stop -1");
    std::ostringstream out;
    run_session(in, out);
    CHECK(out.str().find("queue: Michael John Jim ") != std::string::npos);
    CHECK(out.str().find("stop") == std::string::npos);
    return check_summary("lw5 priority queue");
}
