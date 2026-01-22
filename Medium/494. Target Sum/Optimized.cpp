#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    ============================================================================
    OPTIMIZED TARGET SUM (RECURSION + MEMOIZATION)
    ----------------------------------------------------------------------------
    PROBLEM:
    - Given nums and target.
    - For each nums[i], choose '+' or '-' in front of it.
    - Count how many different expressions evaluate exactly to target.

    SIMPLE IDEA (same as brute force):
    - At index pos, we have 2 choices:
      1) Use '+'  → remaining target becomes (target - nums[pos])
      2) Use '-'  → remaining target becomes (target + nums[pos])
    - Recurse to pos + 1 for both choices.

    BRUTE FORCE VERSION (PREVIOUS CODE) BEHAVIOR:
    ------------------------------------------------------------------------
    int helper(vector<int>& nums, int pos, int target) {
        if (pos == nums.size()) {
            return target == 0;
        }
        return helper(nums, pos + 1, target - nums[pos]) +
               helper(nums, pos + 1, target + nums[pos]);
    }

    - This explores ALL 2^n sign combinations.
    - PROBLEM:
      * The same (pos, target) state is recomputed many times.
      * Time complexity ~ O(2^n) → exponential.
      * For larger n, this can lead to TLE (Time Limit Exceeded).

    HOW THIS OPTIMIZED VERSION IMPROVES IT:
    ------------------------------------------------------------------------
    - Uses memoization with unordered_map<string,int> dp.
    - KEY IDEA:
      * Each unique state is defined by (pos, target).
      * We build a key = "pos,target" and store the computed ways in dp.
      * If the same (pos, target) appears again, we just reuse dp[key]
        instead of doing recursion again.

    EFFECT OF MEMOIZATION:
    - Avoids repeated work on the same (pos, target).
    - Greatly reduces the number of recursive calls compared to brute force.
    - Turns exponential behavior into "number of distinct (pos, target) states",
      which is much smaller in practice.

    ============================================================================
    */

    int helper(vector<int>& nums, int pos, int target,
               unordered_map<string, int> &dp) {
        // Create a unique key for the current state (pos, target)
        string key = to_string(pos) + "," + to_string(target);

        // If we already computed this state, return the stored answer.
        // This is what the brute force version did NOT have.
        if (dp.find(key) != dp.end()) return dp[key];

        // BASE CASE: we have assigned '+' or '-' to all numbers
        if (pos == (int)nums.size()) {
            // If remaining target is exactly 0, this is 1 valid way, else 0 ways.
            dp[key] = (target == 0);
            return dp[key];
        }

        // RECURSIVE CASE: two choices at this position

        // Choice 1: put '+' in front of nums[pos]
        // We want the rest to reach (target - nums[pos])
        int waysWithPlus = helper(nums, pos + 1, target - nums[pos], dp);

        // Choice 2: put '-' in front of nums[pos]
        // We want the rest to reach (target + nums[pos])
        int waysWithMinus = helper(nums, pos + 1, target + nums[pos], dp);

        // Store total ways for this (pos, target) in dp
        dp[key] = waysWithPlus + waysWithMinus;

        return dp[key];
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<string, int> dp;  // memoization table for (pos, target)
        return helper(nums, 0, target, dp);
    }
};

/*
================================================================================
TESTING AND EXPECTED OUTPUT (TO SEE IT WORKING)
================================================================================
*/
int main() {
    Solution sol;

    // Test 1: Example from problem
    vector<int> nums1 = {1,1,1,1,1};
    int target1 = 3;
    cout << "Test 1: ways = "
         << sol.findTargetSumWays(nums1, target1)
         << "   // Expected: 5\n";

    // Test 2: Single element
    vector<int> nums2 = {1};
    int target2 = 1;
    cout << "Test 2: ways = "
         << sol.findTargetSumWays(nums2, target2)
         << "   // Expected: 1\n";

    // Test 3: Small mixed example
    vector<int> nums3 = {1,2,1};
    int target3 = 0;
    // Valid expressions:
    // +1 -2 +1 = 0
    // -1 +2 -1 = 0
    // So answer = 2.
    cout << "Test 3: ways = "
         << sol.findTargetSumWays(nums3, target3)
         << "   // Expected: 2\n";

    return 0;
}
