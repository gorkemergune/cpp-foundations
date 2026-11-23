#include <sstream>
#include <string>
#include <vector>

#include "check.h"
#include "heap.h"

static std::vector<int> nums(const std::string& line) {
    std::istringstream in(line);
    std::vector<int> v;
    int x;
    while (in >> x) v.push_back(x);
    return v;
}
static bool isMinHeap(const std::vector<int>& v) {
    for (size_t i = 1; i < v.size(); i++)
        if (v[(i - 1) / 2] > v[i]) return false;
    return true;
}

int main() {
    int data[] = {13, 10, 9, 12, 55, 23, 34, 1, 2};
    heap h(data, 9);
    CHECK_EQ(data[0], 13);                                   // caller's array is not changed
    std::vector<int> v = nums(captured([&] { h.print(); }));
    CHECK_EQ((int)v.size(), 9);
    CHECK(isMinHeap(v));
    CHECK_EQ(v[0], 1);
    std::string order;
    for (int i = 0; i < 9; i++) {
        h.delete_min();
        std::vector<int> now = nums(captured([&] { h.print(); }));
        CHECK(isMinHeap(now));
        CHECK_EQ((int)now.size(), 8 - i);
        if (!now.empty()) order += std::to_string(now[0]) + " ";
    }
    CHECK_EQ(order, std::string("2 9 10 12 13 23 34 55 "));  // the minimums come out sorted
    h.delete_min();                                          // empty: must not crash
    CHECK_EQ(captured([&] { h.print(); }), std::string("\n"));

    int one[] = {5};
    heap single(one, 1);
    CHECK_EQ(captured([&] { single.inorder(); }), std::string("5 \n"));
    int dup[] = {3, 3, 1, 1, 2};
    heap d(dup, 5);
    CHECK(isMinHeap(nums(captured([&] { d.print(); }))));
    return check_summary("lw8 min-heap");
}
