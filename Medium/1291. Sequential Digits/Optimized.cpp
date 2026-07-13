#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
SEQUENTIAL DIGITS IN RANGE [low, high] — OPTIMIZED GENERATION BY LENGTH
================================================================================

PROBLEM (LeetCode 1291 style):
- An integer has **sequential digits** if every digit is exactly 1 more than the previous digit.
  Examples: 123, 2345, 789, 12; non‑examples: 124, 135, 98.
- Given integers low and high, return all integers in [low, high] that have sequential digits,
  sorted in increasing order.

NAIVE IDEA (for context):
- Iterate over every number from low to high.
- For each number, check digit by digit whether it has sequential digits.
- Time: O((high − low + 1) * number_of_digits) → too slow if the range is large.

--------------------------------------------------------------------------------
OPTIMIZED IDEA (WHAT THIS CODE DOES)
--------------------------------------------------------------------------------
Instead of checking all numbers in the range, we **directly generate only sequential-digit numbers**:

1) Compute the number of digits in `low` and in `high`:
   - Let `digitsLow = #digits(low)` and `digitsHigh = #digits(high)`.
   - Any valid answer must have between `digitsLow` and `digitsHigh` digits.

2) For each length `digits` from `digitsLow` to `digitsHigh`:
   - For each starting digit `i` from 1 to `10 - digits`:
     - Build a number with `digits` digits starting at digit `i`, then i+1, i+2, ... (e.g., digits=3, i=2 → 234)
     - If this number is greater than `high`, we can stop early and **return** the result (later lengths and starts only make larger numbers).
     - If this number is between `low` and `high`, add it to the answer vector.

3) At the end, return the collected list (it is already in increasing order by construction).

This way we only generate at most a few dozen candidates (since length is ≤ 9), and check each once.

================================================================================
CODE WITH EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    // Helper to count number of digits in a positive integer
    int finddigits(int num) {
        int totaldigits = 0;
        while (num > 0) {
            totaldigits++;
            num /= 10;
        }
        return totaldigits;
    }

    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;

        // Start with the number of digits in 'low'
        int digits = finddigits(low);

        // We only need to go up to the number of digits in 'high'
        while (digits <= finddigits(high)) {
            int currdigits = digits;

            // Starting digit i can go from 1 up to 10 - currdigits
            // so that we don't exceed digit 9 when incrementing.
            for (int i = 1; i <= 10 - currdigits; i++) {
                int curr = 0;
                int temp = currdigits;
                int d = i;

                // Build a sequential digit number of length 'currdigits'
                // starting from digit 'i' (i, i+1, i+2, ...)
                while (temp--) {
                    curr = curr * 10 + d;
                    d++;
                }

                // If this number already exceeds 'high', all further ones
                // for larger starting digits or longer lengths will be bigger.
                if (curr > high) return ans;

                // If within range, store it
                if (curr >= low)
                    ans.push_back(curr);
            }

            // Move to next possible length
            digits++;
        }

        return ans;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
Key observation:
- Sequential-digit numbers have at most 9 digits (123456789 is the largest).
- For each length `d` from digits(low) to digits(high):
  - We try starting digits from 1 to (10 − d).
- Total candidates across all lengths are bounded by a small constant (≤ 36).

Time:
- For each candidate we build it in O(d) (d ≤ 9), and do O(1) comparisons.
- Overall time is O(1) with respect to the magnitude of [low, high] — effectively constant in constraints.

Space:
- We use O(1) extra space besides the output vector `ans`.

This is the standard **optimized generation** approach: generate only valid sequential-digit numbers by length and starting digit, then filter them by [low, high], instead of checking every number in the interval.
================================================================================
*/