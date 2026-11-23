// ============================================================================
//  Lab 38 · BST deletion · YOU WORK HERE
//  Test everything:      .\run.ps1 L38
// ============================================================================
#include "lab38.h"

#include "todo.h"

// L38-A · Example: 50(30(20,40),70)  =>  20, tree 50(30(,40),70)
int removeMin(Node*& root) {
    TODO();
}

// L38-B · Example: the node 30 of 50(30(20,40(35,)),70)  =>  35
int successorKey(const Node* node) {
    TODO();
}

// L38-M1 · Example: [50,30,70,20,40,60,80], delete 50  =>  [60,30,70,20,40,null,80]
bool deleteByCopying(Node*& root, int key) {
    TODO();
}

// L38-M2 · Example: [50,30,70,20,40,60,80], delete 50  =>  [30,20,40,null,null,null,70,60,80]
bool deleteByMerging(Node*& root, int key) {
    TODO();
}

// L38-X · Example: [3,0,4,null,2,null,null,1], low 1, high 3  =>  [3,2,null,1]
Node* trimBST(Node* root, int low, int high) {
    TODO();
}

// L38-V · Example: AS5 Q2 tree, delete 26 then 10  =>  9(8(1(,2(,4(,7))),),21(11,35(30,)))
bool deleteByCopyingPred(Node*& root, int key) {
    TODO();
}
