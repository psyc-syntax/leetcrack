/*
================================================================================
TARGET SUM (BRUTE FORCE RECURSIVE SOLUTION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given an array nums and a target value.
- You can put a '+' or '-' sign in front of every number.
- Count how many different expressions evaluate exactly to target.

Example:
nums  = [1,1,1,1,1], target = 3
Valid expressions:
  -1 + 1 + 1 + 1 + 1 = 3
   1 - 1 + 1 + 1 + 1 = 3
   1 + 1 - 1 + 1 + 1 = 3
   1 + 1 + 1 - 1 + 1 = 3
   1 + 1 + 1 + 1 - 1 = 3
Answer: 5 ways

REAL-LIFE FEEL:
- Like choosing for each number whether it contributes positively (add)
  or negatively (subtract) to reach a desired final score.

APPROACH (Brute Force DFS / Backtracking):
1. At each index pos:
   - Option 1: add current number → target becomes target - nums[pos]
   - Option 2: subtract current number → target becomes target + nums[pos]
2. Recurse to next position (pos + 1).
3. Base case: when pos == nums.size(), check if target == 0.
   - If yes, count 1 way, else 0.
4. Total number of ways = sum of ways from both choices at every step.

TIME COMPLEXITY:
- For every element, 2 choices (+ or -) → O(2^n) calls.
- This is exponential and very slow for large n (can TLE on big inputs).

SPACE COMPLEXITY:
- O(n) recursion depth (call stack).

WHY THIS IS BRUTE FORCE AND CAN “FAIL”:
- No memoization or DP is used.
- The same (pos, target) state is recomputed many times.
- For n up to around 20–25, it’s usually okay.
- For n up to 20+ with larger constraints, it can time out on platforms
  like LeetCode due to O(2^n) growth.

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // helper(nums, pos, target):
    // - pos: current index in nums.
    // - target: value we still want to reach using nums[pos..end]
    int helper(vector<int>& nums, int pos, int target) {
        // BASE CASE:
        // If we processed all numbers:
        // - If target is 0, we found one valid way.
        // - Otherwise, this path is invalid (0 ways).
        if (pos == (int)nums.size()) {
            return target == 0;
        }

        // CHOICE 1: Put '+' before nums[pos]
        //   We do: current_sum + nums[pos]
        //   In terms of "remaining target", that is:
        //       new_target = target - nums[pos]
        int addWays = helper(nums, pos + 1, target - nums[pos]);

        // CHOICE 2: Put '-' before nums[pos]
        //   We do: current_sum - nums[pos]
        //   So remaining target becomes:
        //       new_target = target + nums[pos]
        int subtractWays = helper(nums, pos + 1, target + nums[pos]);

        // Total ways = ways from both choices.
        return addWays + subtractWays;
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        return helper(nums, 0, target);
    }
};

/*
================================================================================
TEST FUNCTION WITH SMALL EXAMPLES
================================================================================
*/
int main() {
    Solution sol;

    // Example 1:
    // nums = [1,1,1,1,1], target = 3
    // Expected: 5
    vector<int> nums1 = {1,1,1,1,1};
    int target1 = 3;
    cout << "Test 1: ways = "
         << sol.findTargetSumWays(nums1, target1)
         << "   // Expected: 5\n";

    // Example 2:
    // nums = [1], target = 1
    // Only: +1 → 1, so answer = 1
    vector<int> nums2 = {1};
    int target2 = 1;
    cout << "Test 2: ways = "
         << sol.findTargetSumWays(nums2, target2)
         << "   // Expected: 1\n";

    // Example 3:
    // nums = [1,2], target = 3
    // +1 +2 = 3 → 1 way
    // +1 -2 = -1
    // -1 +2 = 1
    // -1 -2 = -3
    vector<int> nums3 = {1,2};
    int target3 = 3;
    cout << "Test 3: ways = "
         << sol.findTargetSumWays(nums3, target3)
         << "   // Expected: 1\n";

    /*
    NOTE: LIMITATION / FAILURE ON LARGE INPUTS
    -----------------------------------------
    - For large arrays (e.g. n = 20, 25, 30, ...), this brute-force approach
      explores 2^n combinations.
    - For n = 20 → 1,048,576 calls (still okay).
    - For n = 25 → 33,554,432 calls (already heavy).
    - For n = 30 → over 1 billion calls → too slow → Time Limit Exceeded.
    - That is why an optimized DP or memoization solution is needed for
      full constraints on competitive platforms.
    */

    return 0;
}
