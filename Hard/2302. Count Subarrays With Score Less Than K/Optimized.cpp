#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
COUNT SUBARRAYS WITH SCORE < k — OPTIMIZED SLIDING WINDOW (O(n), TWO POINTERS)
================================================================================

PROBLEM (LeetCode 2302 style):
- nums: array of **positive** integers.
- k: integer.
- For a subarray nums[L..R], define:
    score = (sum of nums[L..R]) * (length of nums[L..R]).
- Return the number of non-empty subarrays whose score is **strictly less than k**.

KEY OBSERVATIONS:
- nums[i] > 0 ⇒ as you extend a subarray to the right:
  - sum increases or stays same.
  - length increases.
  - So score = sum * length is **monotonic non-decreasing** with R for fixed L.
- This monotonic behavior allows a classic **sliding window / two-pointer** approach:
  - Keep a window [left, right] where its score is < k.
  - If score becomes ≥ k, shrink from left until it’s valid again.

--------------------------------------------------------------------------------
OPTIMIZED SLIDING WINDOW IDEA (WHAT YOUR CODE DOES)
--------------------------------------------------------------------------------
Definitions in code:
- `subarray` = current window sum of elements from `prevpos` (left) to `i` (right).
- `size`     = current window length = i - prevpos + 1.
- `prevpos`  = left pointer of the window.
- `total`    = total count of valid subarrays.

Algorithm:
1) Iterate `i` from 0 to n-1 as the **right** end of the window:
   - Add `nums[i]` to `subarray` (window sum).
   - Increment `size` (window length).

2) While the current window score is invalid:
   - Condition: `subarray * size >= k`.
   - Shrink window from the **left**:
     - Subtract `nums[prevpos]` from `subarray`.
     - Increment `prevpos` (move left pointer right).
     - Decrement `size`.

   After this loop finishes, window [prevpos, i] is the **largest** window ending at i
   such that its score < k.

3) Now, all subarrays that **end at i** and **start at any index between prevpos and i**
   are valid:
   - Number of such subarrays = `size`.
   - Add `size` to `total`.

4) After processing all i, `total` is the answer.

Why counting `size` works:
- Current valid window is [prevpos, i].
- Valid subarrays ending at i:
  - [i, i] (length 1)
  - [i-1, i]
  - ...
  - [prevpos, i] (length size)
- Exactly `size` different starts, so `size` valid subarrays.

================================================================================
CODE WITH EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        long long total = 0;      // total number of valid subarrays
        long long subarray = 0;   // current window sum
        long long size = 0;       // current window length
        int prevpos = 0;          // left pointer of the window

        // Right pointer i moves from 0 to n-1
        for (int i = 0; i < (int)nums.size(); i++) {
            // Expand window to include nums[i]
            subarray += nums[i];
            size++;

            // Shrink window from the left while score >= k
            while (subarray * size >= k) {
                subarray -= nums[prevpos];  // remove leftmost element
                prevpos++;                  // move left pointer right
                size--;                     // decrease window length
            }

            // Now [prevpos, i] is the largest window ending at i with score < k
            // Number of valid subarrays ending at i is exactly 'size'
            total += size;
        }

        return total;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
Let n = nums.size().

- Right pointer i visits each element once.
- Left pointer prevpos also moves forward at most n steps (never moves backward).
- Each element is added to the window once and removed at most once.
- The while loop overall across the entire array runs O(n) total, not O(n²).

Time:
- O(n) — linear in array length.

Space:
- O(1) extra: we use only scalar variables (`subarray`, `size`, `prevpos`, `total`).

This is the standard **optimized sliding window / two-pointer** solution for
“Count Subarrays With Score Less Than K”, leveraging the positivity of nums to
maintain a shrinking/growing window that always satisfies the score constraint.
================================================================================
*/