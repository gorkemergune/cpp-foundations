// ============================================================================
//  Lab 36 · Binary trees · YOU WORK HERE
//  Test everything:      .\run.ps1 L36
// ============================================================================
#include "lab36.h"

#include <queue>

#include "todo.h"

using namespace std;

// L36-A · Example: 1(2(4,5),3(,6))  =>  6
int countNodes(const Node* root) {
    TODO();
}

// L36-B · Example: 1(2(4,5),3(,6))  =>  3 (4, 5, 6)
int countLeaves(const Node* root) {
    TODO();
}

// L36-M1 · Example: 1(2(4,5),3(,6))  =>  pre 1 2 4 5 3 6, in 4 2 5 1 3 6, post 4 5 2 6 3 1
void preorderInto(const Node* p, vector<int>& out) {
    TODO();
}

vector<int> preorder(const Node* root) {
    TODO();
}

void inorderInto(const Node* p, vector<int>& out) {
    TODO();
}

vector<int> inorder(const Node* root) {
    TODO();
}

void postorderInto(const Node* p, vector<int>& out) {
    TODO();
}

vector<int> postorder(const Node* root) {
    TODO();
}

// L36-M2 · Example: 1(2(4,5),3(,6))  =>  3
int height(const Node* root) {
    TODO();
}

// L36-M3 · Example: 1(2(4,5),3(,6))  =>  {{1}, {2, 3}, {4, 5, 6}}
vector<vector<int>> levelOrder(const Node* root) {
    TODO();
}

// L36-M4 · Example: any tree  =>  every node deleted, root == nullptr
void destroyTree(Node*& root) {
    TODO();
}

// L36-X · Example: 4(2(1,3),7(6,9))  =>  4(7(9,6),2(3,1))
Node* invertTree(Node* root) {
    TODO();
}

// L36-V · Example: 1(2(4,5),3(,6))  =>  2
int twoChildren(const Node* root) {
    TODO();
}
