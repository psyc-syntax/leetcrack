#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
CAN JUMP (REACH LAST INDEX) — DP / BRUTE FORCE STYLE
================================================================================

PROBLEM:
- You are given nums where nums[i] is the maximum jump length from index i.
- Start at index 0.
- Question: can you reach the last index (n-1) or not?

Example:
nums = [2,3,1,1,4]
- From index 0, you can jump up to 2 steps: to index 1 or 2.
- From index 1, you can jump up to 3 steps (2,3,4).
- You can reach index 4 → return true.

REAL-LIFE FEEL:
- Each position is a stone.
- nums[i] is how far you can jump from that stone.
- You want to know if it is **possible at all** to reach the last stone.

APPROACH IN THIS CODE (DP REACHABILITY, BRUTE-FORCEY):
- Use a boolean array dp of size n.
- dp[i] = true means “index i is reachable from index 0”.
- Steps:
  1) Set dp[0] = true (we start at index 0).
  2) For each index i from 0 to n-1:
       - If dp[i] is false, skip (we cannot stand on i).
       - Otherwise, from i, mark all i+1, i+2, ..., i+nums[i]
         as reachable (set dp[i+j] = true).
       - If at any point dp[n-1] becomes true, we can early return true.
  3) At the end, return dp[n-1].

COMPLEXITY / WHY THIS IS BRUTE-FORCE STYLE:
- For each i, inner loop tries up to nums[i] jumps.
- Worst case: nums[i] could be as large as n, so:
    - Outer loop over i is O(n).
    - Inner loop total across all i can be O(n^2) in worst case.
- So time complexity is O(n^2) in worst case.
- There is a known **greedy O(n)** solution that scans once and tracks the
  farthest reachable index, which is more optimal than this DP approach.

================================================================================
CODE WITH STEP-BY-STEP COMMENTS
================================================================================
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();

        // dp[i] = true if index i is reachable from index 0
        vector<bool> dp(n, false);

        // Starting position: index 0 is reachable
        dp[0] = true;

        // Try to propagate reachability
        for (int i = 0; i < n; i++) {
            // If we cannot reach i, skip it
            if (!dp[i]) continue;

            // From index i, we can jump to i+1, i+2, ..., i+nums[i]
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                dp[i + j] = true;
            }

            // Early exit: if last index became reachable, we are done
            if (dp[n - 1]) return true;
        }

        // After processing all possible jumps, check if last index is reachable
        return dp[n - 1];
    }
};

/*
================================================================================
TESTING WITH EXAMPLES
================================================================================
*/

int main() {
    Solution sol;

    vector<int> nums1 = {2,3,1,1,4};
    // We can reach the end: true
    cout << boolalpha;
    cout << "Test 1: " << sol.canJump(nums1)
         << "  // Expected: true\n";

    vector<int> nums2 = {3,2,1,0,4};
    // We get stuck at index 3 (0 jump length), cannot reach last index: false
    cout << "Test 2: " << sol.canJump(nums2)
         << "  // Expected: false\n";

    /*
    NOTE / LIMITATION:
    - This DP solution simulates all reachable jumps explicitly.
    - In worst cases (e.g., nums = [n,n,n,...] or large values),
      it becomes O(n^2), which is slower than necessary.
    - The greedy optimal solution only keeps the current farthest reachable index
      and runs in O(n) time, making it better for large inputs.
    */

    return 0;
}
