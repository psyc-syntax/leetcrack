#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
JUMP GAME II — “PATH-STORING DP” VERSION AND ITS ISSUE
================================================================================

PROBLEM:
- nums[i] = max jump length from index i.
- Start at index 0, reach index n-1 using MINIMUM number of jumps.
- Return that minimum jump count.

REAL-LIFE FEEL:
- You stand on stones in a river.
- nums[i] tells how far you can jump from stone i.
- You want to reach the last stone using the fewest jumps.

WHAT THIS CODE IS TRYING TO DO:
- dp[i] = a vector<int> storing the PATH (list of indices) you used to reach i
          using the minimum jumps found so far.
- dp[0] = {} (at index 0, you have taken 0 jumps, path is empty).
- For each reachable i, try all jumps j = 1..nums[i], going to i + j:
    - Build a new path temp = dp[i] + {i}.
    - If dp[i+j] is empty OR the new path is shorter, update dp[i+j].

KEY DIFFERENCE FROM PREVIOUS BRUTE FORCE:
- Previous brute-force version used:
      dp[i + j].size() > temp.size()
  i.e. it correctly compared with the new path’s size.
- This “optimized” version uses:
      dp[i + j].size() > dp.size() + 1
  which is WRONG, because:
  - dp.size() is always n (number of positions), not the current path length.
  - dp.size() + 1 is essentially a big constant (like n+1).
  - That condition almost never reflects “is temp shorter than current path?”.
- So the comparison is meaningless and can **lead to failing to update dp[i+j]**
  even when a shorter path exists, or updating in a wrong way.

In other words:
- This version **does not actually optimize** the path comparison.
- It introduces a bug: it compares against `dp.size()+1` instead of `temp.size()`.
- Correct check should be:
      if (dp[i + j].empty() || dp[i + j].size() > temp.size())

So logically:
- Intention: same O(n^2) “store full paths” DP as before.
- Actual code: path-length condition is broken → may give wrong answers.

Also, even with the correct condition, storing vectors as paths is still
O(n^2) time and O(n^2) space and is not the real greedy O(n) optimized solution.

================================================================================
CODE WITH INLINE EXPLANATION AND BUG POINTED OUT
================================================================================
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();

        // dp[i] = path (sequence of indices) used to reach i
        vector<vector<int>> dp(n);

        // Start position: at index 0, path is empty (0 jumps taken yet).
        dp[0] = {};

        for (int i = 0; i < n; i++) {
            // If i is not 0 and we never found a path to i, skip it.
            if (i != 0 && dp[i].empty()) continue;

            // Try all jumps from i
            for (int j = 1; j <= nums[i] && i + j < n; j++) {

                /*
                ------------------------------------------------------------
                INTENDED LOGIC (correct version from brute-force DP):
                   vector<int> temp = dp[i];
                   temp.push_back(i);  // we jump from i to i+j
                   if (dp[i+j].empty() || dp[i+j].size() > temp.size()) {
                       dp[i+j] = temp;
                   }

                But current code uses:
                   if (dp[i + j].empty() || dp[i + j].size() > dp.size() + 1)

                PROBLEM:
                - dp.size() is just n (number of positions), not path length.
                - dp.size()+1 is a big constant unrelated to temp.size().
                - This condition does NOT compare current path length vs new path.
                - It can:
                    * refuse to update dp[i+j] when we have a shorter path,
                    * or accept/reject updates incorrectly.
                - So this “optimized” condition is logically WRONG and
                  may produce incorrect results.

                To fix, we must compare with temp.size() instead.

                ------------------------------------------------------------
                */
                if (dp[i + j].empty() || dp[i + j].size() > dp.size() + 1) {
                    vector<int> temp = dp[i];
                    temp.push_back(i);
                    dp[i + j] = temp;
                }
            }
        }

        // Number of jumps = number of indices stored in path to n-1
        return dp[n - 1].size();
    }
};

/*
================================================================================
SMALL TEST AND EXPECTED BEHAVIOR
================================================================================
*/
int main() {
    Solution sol;

    vector<int> nums1 = {2,3,1,1,4};
    // True minimum jumps = 2 (0 -> 1 -> 4)
    cout << "Test 1: " << sol.jump(nums1)
         << "  // May be correct by luck, but logic is flawed\n";

    vector<int> nums2 = {2,3,0,1,4};
    // True minimum jumps = 2 (0 -> 1 -> 4)
    cout << "Test 2: " << sol.jump(nums2)
         << "  // Again, might pass small cases, but condition is wrong\n";

    /*
    NOTE:
    - Even ignoring the incorrect condition, this path-storing DP is still
      O(n^2) and heavy on memory (paths stored in dp).
    - The real optimized solution for Jump Game II is a greedy O(n) approach
      that only tracks:
          * current range of reachable indices
          * farthest next reach
          * jump count
      without storing full paths.
    */

    return 0;
}
