// ============================================================================
//  Challenge Set 10 · binary trees · YOU WORK HERE
//  Test:  .\run.ps1 C10        one problem:  .\run.ps1 C10 C10-C
// ============================================================================
#include "challenge10.h"

#include <climits>
#include <unordered_map>

#include "todo.h"

using namespace std;

// C10-A · Example: [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4  =>  5
Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
    TODO();
}

// C10-B · Example: [10,5,-3,3,2,null,11,3,-2,null,1], target 8  =>  3
int countFrom(const Node* p, long long sum, long long target, unordered_map<long long, int>& seen) {
    TODO();
}

int pathSum(const Node* root, long long target) {
    TODO();
}

// C10-C · Example: [-10,9,20,null,null,15,7]  =>  42 (15 -> 20 -> 7)
int bestDown(const Node* p, int& best) {    // best path that STARTS at p and goes down
    if (p == nullptr) return 0;
    int l = bestDown(p->left, best), r = bestDown(p->right, best);
    if (l < 0) l = 0;                       // a negative branch is better left out
    if (r < 0) r = 0;
    if (p->data + l + r > best) best = p->data + l + r;   // the path bends at p
    return p->data + (l > r ? l : r);       // the parent can continue only one branch
}
// @end bestDown

// @begin maxPathSum
int maxPathSum(const Node* root) {
    TODO();
}
