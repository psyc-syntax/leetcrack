#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
NUMBER OF SUBSTRINGS CONTAINING 'a', 'b', AND 'c' — OPTIMIZED COUNTING TRICK
================================================================================

PROBLEM (LeetCode 1358 style):
- You are given a string s consisting only of the characters 'a', 'b', and 'c'.
- Count how many substrings of s contain **at least one** 'a', one 'b', and one 'c'.

NAIVE IDEA (for context):
- For every start index i, consider every end index j ≥ i and check if substring
  s[i..j] contains 'a', 'b', and 'c'. This is O(n³) if we check counts each time.

APPROACH (OPTIMIZED O(n²) WITH EARLY BREAK):
- Outer loop fixes a starting index i.
- Inner loop extends the end index j from i to the end of the string.
- For each substring s[i..j], track three booleans:
  - `afound`, `bfound`, `cfound` for whether we've seen each character in s[i..j].
- As soon as s[i..j] contains all three characters:
  - **Every** longer substring s[i..j'], where j' ≥ j, also contains all three chars
    because adding more characters cannot remove any of 'a', 'b', or 'c'.
  - Number of valid substrings starting at i is `s.length() - j`.
  - Add that to the answer and **break** the inner loop, moving to the next i.

This avoids checking all longer endings for the same start i and saves time.

================================================================================
CODE WITH STEP-BY-STEP COMMENTS
================================================================================
*/

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = (int)s.length();
        int count = 0;  // total number of valid substrings

        // Fix the starting index i of the substring
        for (int i = 0; i < n; i++) {
            bool afound = false, bfound = false, cfound = false;

            // Extend the substring end index j from i to n-1
            for (int j = i; j < n; j++) {
                // Update flags based on current character
                if (s[j] == 'a') afound = true;
                if (s[j] == 'b') bfound = true;
                if (s[j] == 'c') cfound = true;

                // Once s[i..j] has at least one 'a', 'b', and 'c'
                if (afound && bfound && cfound) {
                    // All substrings s[i..j], s[i..j+1], ..., s[i..n-1] are valid
                    // Number of such substrings = n - j
                    count += (n - j);
                    // No need to check larger j for this i
                    break;
                }
            }
        }

        return count;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
- Outer loop: i goes from 0 to n-1.
- Inner loop: j goes from i to at most n-1, but often stops early once all three
  characters are found.[web:222][web:223]
- In worst case (e.g., many prefixes without all three chars), the inner loop
  can run almost full length for each i:
  - Time: O(n²).
- Space: O(1) extra, just a few booleans and integers.

This is an **optimized counting trick** built on top of a brute-force double loop:
as soon as a substring satisfies the condition for a given start i, we account
for all longer substrings in one step and stop scanning further endings.
================================================================================
*/