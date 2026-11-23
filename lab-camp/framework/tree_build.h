// Helpers for the tree labs' tests: build a tree from LeetCode's level-order text
// "[1,2,3,null,5]", print a tree back in that form, random trees, free a tree.
// Works with any node type that has `data`, `left`, `right` and a constructor N(int).
#pragma once

#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "test.h"

namespace lab {

template <class N>
N* buildLevel(const std::string& text) {
    std::vector<std::string> tok;
    std::string cur;
    for (char c : text) {
        if (c == '[' || c == ']' || c == ' ') continue;
        if (c == ',') { tok.push_back(cur); cur.clear(); }
        else cur += c;
    }
    if (!cur.empty()) tok.push_back(cur);
    if (tok.empty() || tok[0] == "null") return nullptr;
    N* root = new N(std::stoi(tok[0]));
    std::queue<N*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < tok.size()) {
        N* p = q.front();
        q.pop();
        if (i < tok.size() && tok[i] != "null") { p->left = new N(std::stoi(tok[i])); q.push(p->left); }
        i++;
        if (i < tok.size() && tok[i] != "null") { p->right = new N(std::stoi(tok[i])); q.push(p->right); }
        i++;
    }
    return root;
}

template <class N>
std::string levelString(const N* root, int limit = 200) {   // inverse of buildLevel
    std::vector<std::string> out;
    std::queue<const N*> q;
    q.push(root);
    while (!q.empty() && (int)out.size() < limit) {
        const N* p = q.front();
        q.pop();
        if (!p) { out.push_back("null"); continue; }
        out.push_back(std::to_string(p->data));
        q.push(p->left);
        q.push(p->right);
    }
    while (!out.empty() && out.back() == "null") out.pop_back();
    std::string s = "[";
    for (size_t i = 0; i < out.size(); i++) s += (i ? "," : "") + out[i];
    return s + "]";
}

template <class N>
void freeTree(N* p) {
    if (!p) return;
    freeTree(p->left);
    freeTree(p->right);
    delete p;
}

// a random shape with n nodes (values lo..hi), as level-order text
template <class N>
std::string randomTreeText(int n, int lo, int hi) {
    if (n == 0) return "[]";
    N* root = new N(randInt(lo, hi));
    std::vector<N*> nodes{root};
    for (int k = 1; k < n; k++) {
        for (;;) {
            N* p = nodes[randInt(0, (int)nodes.size() - 1)];
            N*& slot = randInt(0, 1) ? p->left : p->right;
            if (slot) continue;
            slot = new N(randInt(lo, hi));
            nodes.push_back(slot);
            break;
        }
    }
    std::string s = levelString(root, 1000);
    freeTree(root);
    return s;
}

}  // namespace lab
