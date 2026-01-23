#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
3SUM (OPTIMIZED TWO-POINTER SOLUTION)
================================================================================

PROBLEM:
- Given array nums, find all UNIQUE triplets [a,b,c] such that:
      a + b + c == 0
- No duplicate triplets in the answer.

RECALL: BRUTE FORCE (PREVIOUS SOLUTION) BEHAVIOR
--------------------------------------------------------------------------------
Brute force recursive approach:

- For every element, choose:
    - take it into current subset (curr)
    - or skip it
- Whenever curr.size() == 3:
    - Check if sum == 0, if yes, push into ans.
- After recursion, sort ans and remove duplicates.

ISSUES WITH BRUTE FORCE:
- For n elements, recursion explores about 2^n subsets.
- Even though only combinations of size 3 matter (C(n,3)), it still explores
  all subsets before filtering.
- Time complexity ≈ O(2^n) (very slow for large n).
- Needs extra sort + unique to remove duplicate triplets.

CURRENT OPTIMIZED APPROACH (THIS CODE)
--------------------------------------------------------------------------------
KEY IDEAS:
1. Sort the array first.
2. Fix one number nums[i] as the first element of the triplet.
3. For the remaining part (i+1 .. n-1), use TWO POINTERS (left, right) to find
   pairs such that:
      nums[i] + nums[left] + nums[right] == 0
4. Move pointers smartly:
   - If sum < 0 → need larger value → left++
   - If sum > 0 → need smaller value → right--
   - If sum == 0 → record triplet, then skip duplicates.

COMPARISON WITH BRUTE FORCE:
- Brute force:
  - Time: O(2^n) (explores all subsets).
  - Space: can store many duplicate triplets, then deduplicate.
  - Very slow for larger arrays (will likely TLE).
- Two-pointer optimized:
  - Time: O(n^2) after sort:
        * Sorting: O(n log n)
        * Outer loop i: O(n)
        * Inner while with two pointers: O(n) per i
        * Total ≈ O(n^2)
  - Space: O(1) extra (ignoring output).
  - Efficient and standard accepted solution.

================================================================================
CODE WITH STEP-BY-STEP COMMENTS
================================================================================
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();

        // STEP 1: Sort the array
        // - Helps to:
        //   a) Use two-pointer technique.
        //   b) Easily skip duplicates.
        sort(nums.begin(), nums.end());

        // STEP 2: Fix first element of triplet as nums[i]
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicate values for i to avoid duplicate triplets:
            // If nums[i] is same as previous, all triplets starting with nums[i]
            // would be duplicates of ones already found with nums[i-1].
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            // STEP 3: Two-pointer scan on [i+1..n-1]
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    // Found a valid triplet
                    ans.push_back({nums[i], nums[left], nums[right]});

                    // Move both pointers inward
                    left++;
                    right--;

                    // Skip duplicates on the left side
                    while (left < right && nums[left] == nums[left - 1]) left++;

                    // Skip duplicates on the right side
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
                else if (sum < 0) {
                    // Sum too small, need a larger value → move left forward
                    left++;
                }
                else {
                    // Sum too large, need a smaller value → move right backward
                    right--;
                }
            }
        }

        return ans;
    }
};

/*
================================================================================
TEST FUNCTION WITH EXPECTED OUTPUT (SAME EXAMPLE AS BEFORE)
================================================================================
*/

int main() {
    Solution sol;

    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    // After sorting: [-4, -1, -1, 0, 1, 2]
    // Valid unique triplets with sum 0:
    //   [-1, -1, 2]
    //   [-1,  0, 1]

    vector<vector<int>> res = sol.threeSum(nums);

    cout << "Triplets summing to 0 (optimized two-pointer):\n";
    for (auto &t : res) {
        cout << "[" << t[0] << ", " << t[1] << ", " << t[2] << "]\n";
    }

    /*
    EXPECTED OUTPUT (order may vary):
    [-1, -1, 2]
    [-1, 0, 1]
    */

    return 0;
}

/*
================================================================================
SUMMARY OF BRUTE FORCE vs OPTIMIZED (IN WORDS)
================================================================================
- Brute Force (previous code):
  - Try all subsets via recursion (take/skip each element).
  - When subset size == 3, check sum.
  - Many repeated/unused subsets, leads to O(2^n) time.

- Optimized (this code):
  - Sort array, fix one element at a time as first of triplet.
  - Use two-pointer on remaining part to find matching pair in O(n).
  - Overall O(n^2) which is much faster for typical constraints.

- Both find correct triplets, but only the optimized version is practical
  for large input sizes.
*/
