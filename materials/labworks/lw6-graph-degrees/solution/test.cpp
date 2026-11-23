#include <vector>

#include "check.h"
#include "graph.h"
#include "lab6_graph.h"

static std::string s(const std::vector<int>& v) {
    std::string r;
    for (int x : v) r += std::to_string(x) + " ";
    return r;
}

int main() {
    Graph g(&LAB6_ADJ[0][0], 6);
    CHECK_EQ(g.indegree(4), 1);          // example outputs from the PDF
    CHECK_EQ(g.outdegree(3), 4);
    CHECK_EQ(g.num_edges(), 14);
    CHECK_EQ(s(g.dfs(4)), std::string("4 3 2 5 1 0 "));
    CHECK_EQ(s(g.bfs(5)), std::string("5 1 2 0 3 4 "));
    CHECK_EQ(s(g.shortest_path(5, 4)), std::string("5 1 3 4 "));
    int total_in = 0;
    for (int i = 0; i < 6; i++) total_in += g.indegree(i);
    CHECK_EQ(total_in, g.num_edges());   // every edge has one head and one tail
    int one_way[3 * 3] = {0, 1, 0,       // 0 -> 1, 1 -> 2, no way back
                          0, 0, 1,
                          0, 0, 0};
    Graph d(one_way, 3);
    CHECK_EQ(d.indegree(0), 0);
    CHECK_EQ(d.outdegree(2), 0);
    CHECK_EQ(d.num_edges(), 2);
    CHECK_EQ(s(d.shortest_path(2, 0)), std::string(""));  // unreachable: empty path
    return check_summary("lw6 indegree / outdegree / num_edges");
}
