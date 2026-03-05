#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
CHECK IF NUMBER IS A SUM OF DISTINCT POWERS OF THREE — OPTIMIZED GREEDY
================================================================================

PROBLEM (LeetCode 1780 style):
- Given an integer n > 0.
- You need to check if n can be written as a sum of **distinct powers of 3**:
    n = 3^a1 + 3^a2 + ... + 3^ak, all exponents different.

KEY MATH IDEA (base‑3 view, for context):
- If n can be written as a sum of distinct powers of 3, then its base‑3
  representation contains only digits 0 or 1 (no digit 2).
- Many optimal solutions just repeatedly divide by 3 and fail if a remainder 2 appears.

YOUR GREEDY IMPLEMENTATION IDEA:
- Start from 3^0, 3^1, 3^2, ... until the current power sum exceeds n.
- Whenever `sum` (running power) exceeds the remaining n:
  - Subtract the **previous power** (sum / 3) from n (i.e., choose that power).
  - Make sure you don't pick the **same power twice** using `num` as last-used power.
  - Reset `sum` back to 1 to start checking powers again from 3^0 with the reduced n.
- When the loop finishes, return true if n became 0 (all accounted for); otherwise false.

This is a greedy “take largest usable power at each step without repetition” interpretation, implemented with multiplication by 3.[web:181]

================================================================================
OPTIMIZED C++ IMPLEMENTATION (DIRECT TRANSLATION + EXPLANATION COMMENTS)
================================================================================
*/

bool checkPowersOfThree(int n) {
    int sum = 1;   // will walk through powers of 3: 1, 3, 9, 27, ...
    int num = 0;   // remembers last power of 3 used to avoid using same power twice

    while (sum <= n) {
        sum *= 3;  // move to next power boundary (sum is 3, 9, 27, ...)

        if (sum > n) {
            // The previous power (sum / 3) is the largest power of 3 <= current n
            int lastPow = sum / 3;

            // Use this power: subtract it from n
            n -= lastPow;

            // If we already used this exact power before, representation not distinct
            if (num == lastPow) return false;

            // Mark this power as used
            num = lastPow;

            // Reset sum to start scanning powers again for the new n
            sum = 1;
        }
    }

    // If n reduced exactly to 0, it can be written as sum of distinct powers of 3
    return n == 0;
}

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
- In each outer pass, `sum` walks through powers of 3 until it exceeds current n.
- n is reduced by at least one power of 3 whenever `sum > n`, and powers grow
  exponentially, so the number of iterations is O(log₃ n).
- Time: O(log n).
- Space: O(1) extra (only a few ints).

Note:
- A more common optimized solution is to repeatedly check `n % 3` and ensure
  no remainder 2 appears, but this greedy “growing power and subtract” version
  is also an optimized O(log n) approach compared to any brute-force subset search.
================================================================================
*/
