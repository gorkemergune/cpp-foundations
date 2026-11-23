#include "as5.h"
#include "check.h"

static std::string s(const std::vector<int>& v, size_t from = 0) {
    std::string r;
    for (size_t i = from; i < v.size(); i++) r += std::to_string(v[i]) + " ";
    return r;
}
static bool isMinHeap1(const std::vector<int>& h) {
    for (size_t i = 2; i < h.size(); i++)
        if (h[i / 2] > h[i]) return false;
    return true;
}

int main() {
    TNode* t = buildFromPreIn("CBADEFG", "ABDCEFG");
    CHECK_EQ(postorder(t), std::string("ADBGFEC"));      // the third traversal given in the task
    CHECK_EQ(t->key, 'C');
    CHECK_EQ(t->left->key, 'B');
    CHECK_EQ(t->right->right->right->key, 'G');          // E -> F -> G is a right chain
    freeTree(t);

    ShowBST<int> bst;
    for (int k : {9, 10, 8, 1, 2, 26, 35, 30, 4, 11, 7, 21}) bst.insert(k);
    CHECK_EQ(bst.shape(), std::string("9(8(1(,2(,4(,7))),),10(,26(11(,21),35(30,))))"));
    CHECK_EQ(bst.twoChildren(), 2);
    CHECK_EQ(bst.minPlusMax(), 36);
    bst.findAndDeleteByCopying(26);   // two children: replaced by its predecessor 21
    bst.findAndDeleteByCopying(10);   // one child: its subtree moves up
    CHECK_EQ(bst.shape(), std::string("9(8(1(,2(,4(,7))),),21(11,35(30,)))"));

    auto g = as5Graph();
    CHECK_EQ(countEdges(g), 13);
    CHECK_EQ(s(bfs(g, 1)), std::string("1 3 7 2 6 5 8 9 4 "));
    CHECK_EQ(s(dfs(g, 1)), std::string("1 3 2 5 8 7 9 4 6 "));

    std::vector<int> h = {0, 12, 28, 14, 41, 18, 67, 52, 25, 10, 11, 4, 19, 37, 7, 22};
    buildHeap(h);
    CHECK_EQ(s(h, 1), std::string("4 10 7 12 11 19 14 25 41 28 18 67 37 52 22 "));
    CHECK(isMinHeap1(h));
    deleteMin(h);
    CHECK_EQ(s(h, 1), std::string("7 10 14 12 11 19 22 25 41 28 18 67 37 52 "));
    heapInsert(h, 19);
    CHECK_EQ(s(h, 1), std::string("7 10 14 12 11 19 19 25 41 28 18 67 37 52 22 "));
    CHECK(isMinHeap1(h));
    std::vector<int> layout = completeTreeFromPreorder({21, 19, 24, 18, 62, 10, 46, 25, 18});
    CHECK_EQ(s(layout, 1), std::string("21 19 46 24 10 25 18 18 62 "));
    CHECK(!isMinHeap1(layout));   // the sequence in the task is not a valid min-heap
    return check_summary("2017 as5 trees / graph / heap");
}
