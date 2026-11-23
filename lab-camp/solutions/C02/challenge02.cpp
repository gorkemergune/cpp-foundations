// ============================================================================
//  Challenge Set 02 · matrices · YOU WORK HERE
//  Reference solution. @solution-note
//  Test:  .\run.ps1 C02        one problem:  .\run.ps1 C02 C02-B
// ============================================================================
#include "challenge02.h"

#include <utility>

#include "todo.h"

using namespace std;

// C02-A · Example: {{1,2,3},{4,5,6},{7,8,9}}  =>  {1,2,3,6,9,8,7,4,5}
// @begin spiralOrder
vector<int> spiralOrder(const Matrix& m) {
    vector<int> out;
    if (m.empty()) return out;
    int top = 0, bottom = (int)m.size() - 1, left = 0, right = (int)m[0].size() - 1;
    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) out.push_back(m[top][j]);        // top row ->
        top++;
        for (int i = top; i <= bottom; i++) out.push_back(m[i][right]);      // right column v
        right--;
        if (top <= bottom) {                                                 // a row is left
            for (int j = right; j >= left; j--) out.push_back(m[bottom][j]); // bottom row <-
            bottom--;
        }
        if (left <= right) {                                                 // a column is left
            for (int i = bottom; i >= top; i--) out.push_back(m[i][left]);   // left column ^
            left++;
        }
    }
    return out;
}
// @end spiralOrder

// C02-B · Example: {{1,2},{3,4}}  =>  {{3,1},{4,2}}
// @begin rotateImage
void rotateImage(Matrix& m) {
    int n = m.size();
    for (int i = 0; i < n; i++)                 // 1) transpose (Lab 07, M2)
        for (int j = i + 1; j < n; j++) swap(m[i][j], m[j][i]);
    for (int i = 0; i < n; i++)                 // 2) reverse every row (Lab 03)
        for (int lo = 0, hi = n - 1; lo < hi; lo++, hi--) swap(m[i][lo], m[i][hi]);
}
// @end rotateImage

// C02-C · Example: {{1,1,1},{1,0,1},{1,1,1}}  =>  {{1,0,1},{0,0,0},{1,0,1}}
// @begin setZeroes
void setZeroes(Matrix& m) {
    if (m.empty()) return;
    int R = m.size(), C = m[0].size();
    bool firstRowZero = false, firstColZero = false;
    for (int j = 0; j < C; j++) if (m[0][j] == 0) firstRowZero = true;
    for (int i = 0; i < R; i++) if (m[i][0] == 0) firstColZero = true;
    // use row 0 and column 0 as the "this row / column must become 0" markers
    for (int i = 1; i < R; i++)
        for (int j = 1; j < C; j++)
            if (m[i][j] == 0) m[i][0] = m[0][j] = 0;
    for (int i = 1; i < R; i++)
        for (int j = 1; j < C; j++)
            if (m[i][0] == 0 || m[0][j] == 0) m[i][j] = 0;
    if (firstRowZero) for (int j = 0; j < C; j++) m[0][j] = 0;   // markers last
    if (firstColZero) for (int i = 0; i < R; i++) m[i][0] = 0;
}
// @end setZeroes
