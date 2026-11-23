#pragma once
// The graph of Labwork 6 Q2 as a 6x6 adjacency matrix (row = from, column = to).
// Read from the figure: 0<->1, 0<->3, 1<->3, 1<->5, 2<->3, 2<->5, 3<->4  (7 pairs = 14 edges)
static int LAB6_ADJ[6][6] = {
    // 0  1  2  3  4  5
    {0, 1, 0, 1, 0, 0},  // 0
    {1, 0, 0, 1, 0, 1},  // 1
    {0, 0, 0, 1, 0, 1},  // 2
    {1, 1, 1, 0, 1, 0},  // 3
    {0, 0, 0, 1, 0, 0},  // 4
    {0, 1, 1, 0, 0, 0},  // 5
};
