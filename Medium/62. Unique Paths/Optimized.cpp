#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
UNIQUE PATHS IN GRID (DP TABULATION) — OPTIMIZED vs BRUTE FORCE
================================================================================

PROBLEM (LeetCode 62 style):
- Robot starts at top-left cell (0,0) in an m x n grid.
- It can move only:
  - DOWN  (i+1, j)
  - RIGHT (i, j+1)
- Goal: count how many different paths reach bottom-right (m-1, n-1).

SMALL EXAMPLE:
m = 3, n = 7
Number of unique paths = 28

REAL-LIFE FEEL:
- Like walking on grid streets from top-left to bottom-right,
  only going east (right) or south (down).
- We want to count all distinct ways to walk there.

BRUTE FORCE (for comparison, not in this code):
- Try all possible move sequences (DFS/backtracking).
- At each cell, branch to “down” and “right”.
- Time ≈ O(2^(m+n)) in worst case — explodes quickly.

THIS OPTIMIZED DP APPROACH:
- grid[i][j] = number of ways to reach cell (i,j).
- Start:
    grid[0][0] = 1  (1 way: starting there).
- Transition:
    Ways to reach (i+1, j) add grid[i][j].
    Ways to reach (i, j+1) add grid[i][j].
- We fill the grid row by row using previous values.

WHY THIS IS MUCH BETTER THAN BRUTE FORCE:
- Each cell (i,j) is computed exactly once.
- Time: O(m * n).
- Space: O(m * n) (can even be optimized to O(n) with 1D DP).
- No recursion, no exponential explosion.

================================================================================
CODE WITH SIMPLE EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    int uniquePaths(int m, int n) {
        // grid[i][j] = number of ways to reach cell (i, j)
        vector<vector<int>> grid(m, vector<int>(n, 0));

        // Start at top-left corner: exactly 1 way to be at (0,0)
        grid[0][0] = 1;

        // Fill the DP table
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // From (i, j), you can go DOWN to (i+1, j) if inside grid
                // and RIGHT to (i, j+1) if inside grid.
                if (i + 1 < m && j + 1 < n) {
                    grid[i + 1][j] += grid[i][j];
                    grid[i][j + 1] += grid[i][j];
                }
                // Only DOWN is possible
                else if (i + 1 < m) {
                    grid[i + 1][j] += grid[i][j];
                }
                // Only RIGHT is possible
                else if (j + 1 < n) {
                    grid[i][j + 1] += grid[i][j];
                }
            }
        }

        // Answer: ways to reach bottom-right cell (m-1, n-1)
        return grid[m - 1][n - 1];
    }
};

/*
================================================================================
TESTING WITH EXAMPLES
================================================================================
*/

int main() {
    Solution sol;

    cout << "Test 1: m=3, n=7 → " << sol.uniquePaths(3, 7)
         << "  // Expected: 28\n";

    cout << "Test 2: m=3, n=2 → " << sol.uniquePaths(3, 2)
         << "  // Expected: 3\n";
    // Paths: DDR, DRD, RDD in a 3x2 grid.

    cout << "Test 3: m=1, n=1 → " << sol.uniquePaths(1, 1)
         << "  // Expected: 1\n";

    /*
    COMPARISON SUMMARY (IN COMMENTS):

    - Brute force:
      * Explore all paths with recursion (go down/right until bottom).
      * Time ≈ exponential in m+n (very slow for large grids).

    - This DP solution:
      * Use grid[i][j] to store number of ways to reach (i,j).
      * Each cell calculated once from its top and left neighbors.
      * Time:  O(m * n)
      * Space: O(m * n)
      * Always fast enough for typical constraints.

    */

    return 0;
}
