// ============================================================================
//  Challenge Set 09 · graphs · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C09        one problem:  .\run.ps1 C09 C09-B
// ============================================================================
#include "challenge09.h"

#include <queue>
#include <utility>

#include "todo.h"

using namespace std;

// C09-A · Example: 2, {{1,0}}  =>  true;  2, {{1,0},{0,1}}  =>  false
// @begin canFinish
bool canFinish(int numCourses, const vector<vector<int>>& prerequisites) {
    vector<vector<int>> next(numCourses);   // b -> a: after b, a can follow
    vector<int> in(numCourses, 0);
    for (const auto& p : prerequisites) {
        next[p[1]].push_back(p[0]);
        in[p[0]]++;
    }
    queue<int> q;                           // Kahn (Lab 34)
    for (int c = 0; c < numCourses; c++)
        if (in[c] == 0) q.push(c);
    int taken = 0;
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        taken++;
        for (int d : next[c])
            if (--in[d] == 0) q.push(d);
    }
    return taken == numCourses;             // the courses on a cycle are never taken
}
// @end canFinish

// C09-B · Example: {{2,1,1},{1,1,0},{0,1,1}}  =>  4
// @begin orangesRotting
int orangesRotting(vector<vector<int>> grid) {
    int rows = grid.size(), cols = rows ? grid[0].size() : 0, fresh = 0;
    queue<pair<int, int>> q;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) q.push({r, c});    // multi-source BFS: all rotten at once
            if (grid[r][c] == 1) fresh++;
        }
    int minutes = 0;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    while (!q.empty() && fresh > 0) {
        int ring = q.size();                // everything rotten at THIS minute
        for (int i = 0; i < ring; i++) {
            auto [r, c] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] != 1) continue;
                grid[nr][nc] = 2;
                fresh--;
                q.push({nr, nc});
            }
        }
        minutes++;
    }
    return fresh == 0 ? minutes : -1;
}
// @end orangesRotting

// C09-C · Example: {{1,3},{0,2},{1,3},{0,2}}  =>  true (a square)
// @begin isBipartite
bool isBipartite(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> side(n, -1);                // -1 not coloured yet, 0 / 1 the two groups
    for (int s = 0; s < n; s++) {
        if (side[s] != -1) continue;        // every component gets its own BFS
        side[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : graph[v]) {
                if (side[w] == -1) {
                    side[w] = 1 - side[v];
                    q.push(w);
                } else if (side[w] == side[v]) {
                    return false;           // an edge inside one group: an odd cycle
                }
            }
        }
    }
    return true;
}
// @end isBipartite
