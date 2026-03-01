#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PARTITIONING INTO MINIMUM NUMBER OF DECI-BINARY NUMBERS — OPTIMIZED GREEDY
================================================================================

PROBLEM (LeetCode 1689 style):
- You are given a string `n` representing a positive decimal integer.
- A **deci-binary** number is a decimal number where every digit is either 0 or 1
  (e.g., 101, 1100; but not 112).[web:150][web:153][web:158]
- You want the minimum number of positive deci-binary numbers such that
  their sum equals the given number `n`.[web:150][web:152]

KEY INSIGHT (why this solution is optimal):
- Look at a single digit position (say the units or tens place).
- Suppose at some position the digit is `d` (0–9).
- Each deci-binary number can contribute at most `1` at that position.
- To reach a sum digit `d` at that position, you need at least `d`
  deci-binary numbers having `1` in that position.[web:155][web:159]
- Therefore, across the whole number:
  - The minimum number of deci-binary numbers needed is exactly the
    **maximum digit** in `n`.[web:152][web:155]

So the optimized algorithm is simply:
- Scan the string once.
- Track the largest digit.
- Return that largest digit.

================================================================================
OPTIMIZED IMPLEMENTATION (O(n) TIME, O(1) EXTRA SPACE)
================================================================================
*/

class Solution {
public:
    int minPartitions(string n) {
        int maxval = 0;                         // will store the maximum digit
        for (int i = 0; i < (int)n.length(); i++) {
            // convert character to digit
            int digit = n[i] - '0';
            // update maximum digit seen so far
            maxval = max(maxval, digit);
        }
        // minimum number of deci-binary numbers needed
        // is equal to the maximum digit of n
        return maxval;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
- Let L = n.length().
- We do a single pass over the string:
  - Time: O(L).
  - Space: O(1) extra (just a few integer variables).[web:152][web:154]
This is the **optimal greedy** solution; any simulation-based approach that
actually constructs deci-binary numbers is more complex and slower.[web:152][web:155][web:159]
================================================================================
*/
