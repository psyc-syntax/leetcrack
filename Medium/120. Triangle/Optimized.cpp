#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
TRIANGLE MINIMUM PATH SUM — IN-PLACE DP (OPTIMIZED)
================================================================================

PROBLEM (Triangle / LeetCode 120 style):
- You are given a triangle of integers:
    [
      [2],
      [3,4],
      [6,5,7],
      [4,1,8,3]
    ]
- Start at the top (row 0, col 0).
- At each step, you may move to **one of the two adjacent** numbers in the next row:
  from (i,j) to (i+1,j) or (i+1,j+1).
- Find the **minimum path sum** from top to bottom.

Example:
2
3 4
6 5 7
4 1 8 3

Minimum path: 2 → 3 → 5 → 1 = 11

REAL-LIFE FEEL:
- Think of a triangle of stepping stones with costs.
- You start at the top and move down one row at a time, either straight down or down-right.
- You want the cheapest total cost to reach the bottom.

NAIVE / BRUTE FORCE (for comparison, not coded here):
- Recursively try both moves (down, down-right) at each level.
- Explore all paths from top to bottom.
- Time ≈ O(2^n) for n rows (each row doubles choices).

THIS OPTIMIZED IN-PLACE DP APPROACH:
- We re-use the given triangle as a DP table.
- After processing row by row, triangle[i][j] will store the **minimum path sum**
  to reach that cell from the top.

TRANSITION:
Row i → Row i+1:
- Left edge (j = 0):
    triangle[i+1][0] += triangle[i][0];
- Middle elements (1 <= j < i+1):
    triangle[i+1][j] += min(triangle[i][j-1], triangle[i][j]);
  (you can come to (i+1,j) either from (i,j-1) or (i,j))
- Right edge (j = i+1):
    triangle[i+1][i+1] += triangle[i][i];

At the end:
- The last row triangle[n-1] contains the minimum sums to each bottom cell.
- The answer is the minimum of that row.

COMPLEXITY:
- Time:  O(n^2) for n rows (total elements ~ n(n+1)/2).
- Space: O(1) extra (we modify triangle in-place, no extra DP array).

================================================================================
CODE WITH SIMPLE EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();

        // We will accumulate minimum path sums directly into `triangle`.
        // triangle[i][j] becomes: minimum sum to reach (i,j) from the top.

        for (int i = 0; i < n - 1; i++) {
            // LEFT EDGE of next row: only one parent (straight above).
            triangle[i + 1][0] += triangle[i][0];

            // MIDDLE ELEMENTS: can come from two parents.
            // Row i has size (i+1), so valid j in that row: 0..i.
            // For the next row (i+1), indices j: 1..i (middle elements).
            for (int j = 1; j < (int)triangle[i].size(); j++) {
                // For (i+1,j), parents are:
                //  - (i, j-1)
                //  - (i, j)
                triangle[i + 1][j] += min(triangle[i][j - 1], triangle[i][j]);
            }

            // RIGHT EDGE of next row: only one parent (top-right).
            // The last element in row i+1 is at index i+1,
            // and it can only be reached from triangle[i][i].
            triangle[i + 1][i + 1] += triangle[i][i];
        }

        // The bottom row now holds the minimum sums to each bottom position.
        // The answer is the minimum of those.
        return *min_element(triangle[n - 1].begin(), triangle[n - 1].end());
    }
};

/*
================================================================================
TESTING WITH EXAMPLE
================================================================================
*/

int main() {
    Solution sol;

    vector<vector<int>> tri = {
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };

    cout << "Minimum path sum: " << sol.minimumTotal(tri)
         << "  // Expected: 11 (2 + 3 + 5 + 1)\n";

    /*
    COMPARISON TO BRUTE FORCE:
    - Brute force:
      * Explore all paths (down / down-right) recursively.
      * About 2^(rows-1) paths → too slow for bigger triangles.

    - This DP solution:
      * Uses each cell once with simple arithmetic and min.
      * Time:  O(n^2) where n is number of rows.
      * Space: O(1) extra (reuses given triangle), very efficient.

    */

    return 0;
}
