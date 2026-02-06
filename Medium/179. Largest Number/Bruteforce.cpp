#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: LARGEST NUMBER (BRUTE FORCE-ISH GREEDY)
================================================================================
You are given an array of non-negative integers `nums`.
You must arrange them so that when you concatenate them, you get the **largest**
possible number (as a string).[web:106][web:111]

Example:
- nums = [3, 30, 34, 5, 9]
- One possible arrangement: "3033459"
- Best arrangement: "9534330"

We return this best arrangement as a string.

--------------------------------------------------------------------------------
BRUTE FORCE IDEA (THEORETICAL, TOO SLOW):
--------------------------------------------------------------------------------
- Generate all permutations of `nums`.
- For each permutation, concatenate all numbers to form a string.
- Track the maximum string (lexicographically).
- Time: O(n! * n * k) → totally infeasible for large n.[web:110][web:115]

Your code is a **brute-force flavored greedy**:
- Instead of generating all permutations, you **build the answer from left to right**.
- At each step:
  - Scan through all remaining numbers.
  - Pick the one which, if placed next, gives the lexicographically largest result.
- This still does an O(n) scan **for each** of the n positions:
  - Overall complexity ≈ O(n² * k), where k is average digits in a number.

This is worse than the optimal sort-based solution O(n log n * k), but
better than true permutation brute force.[web:111][web:114]

================================================================================
BRUTE FORCE-FORMAT IMPLEMENTATION
================================================================================
*/

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // Final answer string
        string num = "";

        // We will repeatedly choose the "best" number for the next position
        // and erase it from the array, until the array becomes empty.
        while (!nums.empty()) {
            // Assume the first element is the current best
            string currentmax = to_string(nums[0]);
            int pos = 0; // index of that current best

            // Try every remaining number as a candidate for the next position
            for (int i = 1; i < (int)nums.size(); i++) {
                string current = to_string(nums[i]);

                /*
                We compare which concatenation gives a bigger number:
                - current + currentmax
                - currentmax + current

                If placing `current` before `currentmax` yields a larger string,
                then `current` is a better choice for this position.

                Example:
                - current = "9", currentmax = "34"
                  current + currentmax = "934"
                  currentmax + current = "349"
                  "934" > "349" → "9" is better to place before "34".
                */
                if (current + currentmax > currentmax + current) {
                    currentmax = current;
                    pos = i;
                }
            }

            // Append the best choice for this round to the answer
            num += currentmax;

            // Remove that element from nums so it won't be used again
            nums.erase(nums.begin() + pos);  // O(n) erase each time
        }

        // Edge case: if the result starts with '0',
        // that means all numbers were zero, so just return "0"
        if (!num.empty() && num[0] == '0') return "0";

        return num;
    }
};

/*
================================================================================
TIME AND SPACE COMPLEXITY (BRUTE FORCE STYLE)
================================================================================
Let n = nums.size(), k = max digits in any number.

- Outer while loop runs n times (we pick one number per iteration).
- Inside each iteration:
  - We scan all remaining numbers: O(n) comparisons.
  - Each comparison does string concatenation & compare:
    - O(k) per compare.

- So roughly: O(n² * k) time.[web:111][web:114]

- Space:
  - We build the answer string `num` of length ≈ n * k.
  - No big extra data structures → O(n * k) space due to the answer.

================================================================================
NOTES:
- Optimal solution: convert all numbers to strings, sort them once
  using comparator (a + b > b + a), then concatenate in order.[web:111][web:113][web:114]
- That approach is O(n log n * k) and is preferred in interviews.
- Your code matches a **brute-force greedy** where we repeatedly pick
  the best option by scanning all remaining elements.
================================================================================
*/
