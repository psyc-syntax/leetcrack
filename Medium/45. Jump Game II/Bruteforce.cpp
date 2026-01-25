#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
JUMP GAME II (BRUTE FORCE DP THAT STORES PATHS)
================================================================================

PROBLEM (LeetCode 45 style):
- You are given an array nums where nums[i] represents
  the maximum jump length from index i.
- Start at index 0 and reach the last index (n-1).
- Return the MINIMUM number of jumps needed to reach the last index.

Example:
nums = [2,3,1,1,4]
- From index 0, you can jump up to 2 steps.
- One optimal way: 0 → 1 → 4
- Answer: 2 jumps.

REAL-LIFE FEEL:
- Each position is like a stepping stone.
- nums[i] tells how far you can jump from that stone.
- You want to reach the last stone using the fewest jumps.

BRUTE FORCE DP APPROACH (YOUR CODE IDEA):
- dp[i] is a vector<int> storing a PATH (sequence of indices)
  that reaches index i with minimum steps found so far.
- Initialization:
  - dp[0] = empty path {} (we're already at index 0, no jump taken yet).
- For each reachable index i:
  - Try all jumps from 1 to nums[i].
  - For each landing index i + j:
    - temp = dp[i] plus the current index i (we're jumping from i).
    - If dp[i + j] is empty OR temp is shorter than current dp[i + j],
      update dp[i + j] = temp.
- In the end, dp[n-1].size() gives the number of jumps 
  (because we push the index used for each jump step).

WHY THIS IS BRUTE FORCE / INEFFICIENT:
1) Time complexity:
   - Outer loop i: runs n times.
   - Inner loop over jumps j: in worst case, nums[i] ~ O(n),
     so about O(n^2) transitions.
   - Plus: each update copies a whole vector path (temp = dp[i]),
     which costs O(length of path) per update, making it even heavier.

2) Space complexity:
   - dp is a vector of n vectors.
   - Each dp[i] can store up to O(n) indices (one per jump),
     so total memory can go up to O(n^2).

3) On LeetCode-scale inputs (n up to 10^4 or more), 
   storing full paths and copying vectors repeatedly can be too slow 
   and memory-heavy, likely causing Time Limit Exceeded or Memory Limit issues,
   even though the logic is correct for small n.

================================================================================
CODE WITH SIMPLE EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();

        // dp[i] will store a path (sequence of indices) used to reach i
        // with the minimal number of jumps found so far.
        vector<vector<int>> dp(n);

        // Starting point: index 0 is the beginning, no jumps taken yet,
        // so the path to reach 0 is an empty path {}.
        dp[0] = {};

        // Try to build paths for all indices
        for (int i = 0; i < n; i++) {
            // If i is not 0 and dp[i] is empty, it means index i is not reachable.
            // Then we skip it.
            if (i != 0 && dp[i].empty()) continue;

            // From index i, we can jump 1 to nums[i] steps forward.
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                // temp is the path to reach i, plus i itself
                // (we "jump from" i to i+j).
                vector<int> temp = dp[i];
                temp.push_back(i);

                // If dp[i+j] is empty (no path yet) OR our new path is shorter,
                // then we update dp[i+j] to be this new path.
                if (dp[i + j].empty() || dp[i + j].size() > temp.size()) {
                    dp[i + j] = temp;
                }
            }
        }

        // dp[n-1] now holds the sequence of indices used to reach n-1
        // The number of jumps = length of that sequence
        return dp[n - 1].size();
    }
};

/*
================================================================================
TEST FUNCTION WITH EXAMPLE
================================================================================
*/
int main() {
    Solution sol;

    vector<int> nums1 = {2,3,1,1,4};
    // One optimal path: 0 -> 1 -> 4
    // dp[n-1] will be something like [0,1], size = 2
    cout << "Test 1: " << sol.jump(nums1) << "  // Expected: 2\n";

    vector<int> nums2 = {2,3,0,1,4};
    // One optimal path: 0 -> 1 -> 4
    cout << "Test 2: " << sol.jump(nums2) << "  // Expected: 2\n";

    /*
    LIMITATION / WHY THIS IS BRUTE FORCE:
    - For each i, we try all possible jumps j from 1..nums[i].
    - For each transition, we copy a whole vector path.
    - This leads to O(n^2) time with heavy vector copying and O(n^2) space.
    - For large arrays, an O(n) greedy solution exists and is preferred:
         - keep track of current farthest reach and next farthest,
           increasing jump count when you move to next range.
    */

    return 0;
}
