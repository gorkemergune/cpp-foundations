// ============================================================================
//  Challenge Set 09 · graphs (medium)                               DO NOT EDIT
// ============================================================================
#pragma once

#include <vector>

// C09-A · LeetCode 207: numCourses courses, prerequisites[i] = {a, b} means "take b before a".
// Can every course be finished?
bool canFinish(int numCourses, const std::vector<std::vector<int>>& prerequisites);

// C09-B · LeetCode 994: 0 empty, 1 fresh orange, 2 rotten. Every minute a rotten orange
// rots its 4 neighbours. Minutes until no fresh orange is left; -1 if impossible.
int orangesRotting(std::vector<std::vector<int>> grid);

// C09-C · LeetCode 785: can the vertices be split into two groups so that every edge
// goes between the groups? graph[u] = neighbours of u (undirected, maybe disconnected).
bool isBipartite(const std::vector<std::vector<int>>& graph);
