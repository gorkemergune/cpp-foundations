// ============================================================================
//  Challenge Set 10 · binary trees · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C10        one problem:  .\run.ps1 C10 C10-C
// ============================================================================
#include "challenge10.h"

#include <climits>
#include <unordered_map>

#include "todo.h"

using namespace std;

// C10-A · Example: [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4  =>  5
// @begin lowestCommonAncestor
Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
    if (root == nullptr || root == p || root == q) return root;
    Node* l = lowestCommonAncestor(root->left, p, q);     // p or q (or their LCA) on the left?
    Node* r = lowestCommonAncestor(root->right, p, q);
    if (l != nullptr && r != nullptr) return root;        // one on each side: root is the LCA
    return l != nullptr ? l : r;
}
// @end lowestCommonAncestor

// C10-B · Example: [10,5,-3,3,2,null,11,3,-2,null,1], target 8  =>  3
// @begin countFrom
int countFrom(const Node* p, long long sum, long long target, unordered_map<long long, int>& seen) {
    if (p == nullptr) return 0;
    sum += p->data;                         // prefix sum root .. p
    int found = seen.count(sum - target) ? seen[sum - target] : 0;   // paths ending at p
    seen[sum]++;
    found += countFrom(p->left, sum, target, seen) + countFrom(p->right, sum, target, seen);
    seen[sum]--;                            // leave p: its prefix is not an ancestor of others
    return found;
}
// @end countFrom

// @begin pathSum
int pathSum(const Node* root, long long target) {
    unordered_map<long long, int> seen;
    seen[0] = 1;                            // the empty prefix: paths that start at the root
    return countFrom(root, 0, target, seen);
}
// @end pathSum

// C10-C · Example: [-10,9,20,null,null,15,7]  =>  42 (15 -> 20 -> 7)
// @begin bestDown
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
    int best = INT_MIN;
    bestDown(root, best);
    return best;
}
// @end maxPathSum
