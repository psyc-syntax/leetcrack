#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
MINIMUM PATH SUM IN GRID (DP TABULATION) — OPTIMIZED VS BRUTE FORCE
================================================================================

PROBLEM (LeetCode 64 style):
- You are given an m x n grid of non-negative integers.
- Start at top-left (0,0), end at bottom-right (m-1,n-1).
- You can only move:
  - DOWN  (i+1, j)
  - RIGHT (i, j+1)
- Each cell’s value is a cost. You want the **minimum total cost** path.

Example:
grid = [
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
Best path: 1 → 3 → 1 → 1 → 1 = 7

REAL-LIFE FEEL:
- Tiles on a floor each have a walking cost.
- You want the cheapest route from top-left corner to bottom-right,
  only moving down or right.

NAIVE / BRUTE FORCE (for comparison, not coded here):
- Try all possible paths with recursion/DFS:
  - From each cell, branch to DOWN and RIGHT until you reach the end.
- Compute sum of each path and take minimum.
- Time ≈ O(2^(m+n)) in worst case (very slow for bigger grids).

THIS OPTIMIZED DP APPROACH:
- dp[i][j] = minimum path sum to reach cell (i,j) from (0,0).
- Initialize:
  - dp[0][0] = grid[0][0]
  - others as INT_MAX (we’ll relax them).
- For each cell (i,j), we “relax” its neighbors:
  - If we move DOWN to (i+1,j), newVal = dp[i][j] + grid[i+1][j]
    and we keep the minimum in dp[i+1][j].
  - If we move RIGHT to (i,j+1), newVal = dp[i][j] + grid[i][j+1]
    and we keep the minimum in dp[i][j+1].
- After we sweep the grid, dp[m-1][n-1] holds the minimum path sum.

WHY THIS IS BETTER THAN BRUTE FORCE:
- Each cell’s best value is computed by using its top/left predecessors.
- No exponential branching.
- Time:  O(m * n)
- Space: O(m * n) (can be optimized to O(n) with 1D DP).

================================================================================
CODE WITH SIMPLE EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j] will store the minimum sum needed to reach (i,j)
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));

        // Start cell: only one way to stand here at the beginning
        dp[0][0] = grid[0][0];

        // Traverse the grid top-left to bottom-right
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Move DOWN: from (i,j) to (i+1,j)
                if (i + 1 < m) {
                    int newVal = dp[i][j] + grid[i + 1][j];
                    if (newVal < dp[i + 1][j]) dp[i + 1][j] = newVal;
                }

                // Move RIGHT: from (i,j) to (i,j+1)
                if (j + 1 < n) {
                    int newVal = dp[i][j] + grid[i][j + 1];
                    if (newVal < dp[i][j + 1]) dp[i][j + 1] = newVal;
                }
            }
        }

        // Minimum path sum to bottom-right cell
        return dp[m - 1][n - 1];
    }
};

/*
================================================================================
TESTING WITH EXAMPLES
================================================================================
*/

int main() {
    Solution sol;

    vector<vector<int>> grid1 = {
        {1,3,1},
        {1,5,1},
        {4,2,1}
    };
    // Best path: 1 → 3 → 1 → 1 → 1 = 7
    cout << "Test 1: " << sol.minPathSum(grid1)
         << "  // Expected: 7\n";

    vector<vector<int>> grid2 = {
        {1,2,3},
        {4,5,6}
    };
    // Best path: 1 → 2 → 3 → 6 = 12
    cout << "Test 2: " << sol.minPathSum(grid2)
         << "  // Expected: 12\n";

    /*
    COMPARISON TO BRUTE FORCE:
    - Brute force:
      * Recursively try DOWN/RIGHT from each cell.
      * Explores all paths, roughly O(2^(m+n)), too slow for larger grids.

    - This DP solution:
      * Each cell uses only info from its reachable predecessors
        (effectively shortest path in DAG-style grid).
      * Both time and space are polynomial (O(m*n)),
        which is efficient and accepted by online judges.
    */

    return 0;
}
