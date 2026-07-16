#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
COUNT SUBARRAYS WITH SCORE < k — BRUTE FORCE (DOUBLE LOOP) VERSION
================================================================================

PROBLEM (LeetCode 2302 style):
- You are given:
  - A vector `nums` of positive integers.
  - An integer `k`.[web:240]
- A subarray is any contiguous slice `nums[i..j]`.
- Define the **score** of a subarray as:
    score = (sum of elements in subarray) * (length of subarray).
- Task: Count how many non-empty subarrays have score **strictly less than k**.

--------------------------------------------------------------------------------
BRUTE FORCE IDEA (WHAT YOUR CODE DOES)
--------------------------------------------------------------------------------
- For every possible starting index `i`:
  - Initialize `currsum = 0` and `size = 0`.
  - Extend the subarray to the right with index `j` from `i` to `n-1`:
    - Add `nums[j]` to `currsum`.
    - Increase `size` (current subarray length).
    - Compute `score = currsum * size`.
    - If `score < k`, this subarray `nums[i..j]` is valid → increment `subarray` count.
    - If `score >= k`, break the inner loop because adding more positive numbers will only increase the score, so longer subarrays starting at this `i` cannot be valid.

This is a **brute force over all subarray starts**, but with an early break optimization thanks to the positivity of elements (score is monotonic as `j` grows).

================================================================================
CODE WITH BRUTE FORCE STYLE COMMENTS
================================================================================
*/

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long subarray = 0;                 // answer: number of valid subarrays

        // Outer loop: choose starting index i
        for (int i = 0; i < (int)nums.size(); i++) {
            long long currsum = 0;              // sum of current subarray nums[i..j]
            int size = 0;                       // length of current subarray

            // Inner loop: extend end index j from i to end
            for (int j = i; j < (int)nums.size(); j++) {
                currsum += nums[j];             // add current element
                size++;                         // increase length

                // score = currsum * size
                if (currsum * size < k) {
                    // subarray nums[i..j] is valid
                    subarray++;
                } else {
                    // Since nums contains only positive integers, further extending
                    // this subarray will only increase sum and length, so score
                    // will become even larger. No longer subarrays starting at i
                    // can be valid → break.
                    break;
                }
            }
        }

        return subarray;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
Let n = nums.size().

- Outer loop runs n times.
- Inner loop, in worst case, can run up to n times for each i:
  - Total iterations ≈ n + (n−1) + ... + 1 = O(n²).
- For each (i, j), we do O(1) work (update sum, size, and check condition).

Time:
- Worst-case time complexity: O(n²).

Space:
- Uses only a few scalar variables (`currsum`, `size`, `subarray`) plus the input array.
- Extra space: O(1).

This is the straightforward **brute force** double-loop solution with an early break.
The optimal solution uses a sliding window / two-pointer technique to achieve O(n) time by
counting valid subarrays ending at each index in one pass.
================================================================================
*/