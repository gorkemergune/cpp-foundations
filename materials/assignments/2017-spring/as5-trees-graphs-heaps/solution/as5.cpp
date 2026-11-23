#include "as5.h"

#include <functional>
#include <queue>
#include <utility>

TNode* buildFromPreIn(const std::string& pre, const std::string& in) {
    if (pre.empty()) return nullptr;
    TNode* t = new TNode{pre[0]};
    size_t k = in.find(pre[0]);                 // keys left of the root in inorder = left subtree
    t->left = buildFromPreIn(pre.substr(1, k), in.substr(0, k));
    t->right = buildFromPreIn(pre.substr(1 + k), in.substr(k + 1));
    return t;
}

std::string postorder(const TNode* t) {
    return t ? postorder(t->left) + postorder(t->right) + t->key : "";
}

std::string drawTree(const TNode* t) {
    std::string out;
    std::function<void(const TNode*, int)> go = [&](const TNode* p, int depth) {
        if (!p) return;
        go(p->right, depth + 1);
        out += std::string(4 * depth, ' ') + p->key + "\n";
        go(p->left, depth + 1);
    };
    go(t, 0);
    return out;
}

void freeTree(TNode* t) {
    if (!t) return;
    freeTree(t->left);
    freeTree(t->right);
    delete t;
}

std::vector<std::vector<int>> as5Graph() {
    // Read from the drawing (13 arrows):
    // 1->3 1->7 2->5 2->8 3->2 3->6 4->1 4->6 6->5 7->2 8->7 8->9 9->4
    std::vector<std::vector<int>> a(10, std::vector<int>(10, 0));
    int edges[13][2] = {{1, 3}, {1, 7}, {2, 5}, {2, 8}, {3, 2}, {3, 6}, {4, 1},
                        {4, 6}, {6, 5}, {7, 2}, {8, 7}, {8, 9}, {9, 4}};
    for (auto& e : edges) a[e[0]][e[1]] = 1;
    return a;
}

std::vector<int> bfs(const std::vector<std::vector<int>>& a, int start) {
    int n = a.size();
    std::vector<bool> seen(n, false);
    std::vector<int> order;
    std::queue<int> q;
    q.push(start);
    seen[start] = true;                          // mark when ENQUEUED, not when visited
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w = 1; w < n; w++)              // smallest number first
            if (a[v][w] && !seen[w]) {
                seen[w] = true;
                q.push(w);
            }
    }
    return order;
}

std::vector<int> dfs(const std::vector<std::vector<int>>& a, int start) {
    std::vector<bool> seen(a.size(), false);
    std::vector<int> order;
    std::function<void(int)> go = [&](int v) {
        seen[v] = true;
        order.push_back(v);
        for (int w = 1; w < (int)a.size(); w++)
            if (a[v][w] && !seen[w]) go(w);
    };
    go(start);
    return order;
}

int countEdges(const std::vector<std::vector<int>>& a) {
    int c = 0;
    for (const auto& row : a)
        for (int x : row) c += (x != 0);
    return c;
}

static void siftDown(std::vector<int>& h, int i) {
    int n = (int)h.size() - 1;
    while (2 * i <= n) {
        int c = 2 * i;                                   // left child
        if (c + 1 <= n && h[c + 1] < h[c]) c++;          // smaller child
        if (h[i] <= h[c]) return;
        std::swap(h[i], h[c]);
        i = c;
    }
}

void buildHeap(std::vector<int>& h) {
    for (int i = ((int)h.size() - 1) / 2; i >= 1; i--) siftDown(h, i);
}

void deleteMin(std::vector<int>& h) {
    h[1] = h.back();
    h.pop_back();
    if (h.size() > 1) siftDown(h, 1);
}

void heapInsert(std::vector<int>& h, int x) {
    h.push_back(x);
    for (int i = (int)h.size() - 1; i > 1 && h[i / 2] > h[i]; i /= 2) std::swap(h[i], h[i / 2]);
}

std::vector<int> completeTreeFromPreorder(const std::vector<int>& pre) {
    int n = pre.size();
    std::vector<int> arr(n + 1, 0);
    size_t next = 0;
    std::function<void(int)> go = [&](int i) {           // preorder walk over array positions
        if (i > n) return;
        arr[i] = pre[next++];
        go(2 * i);
        go(2 * i + 1);
    };
    go(1);
    return arr;
}
