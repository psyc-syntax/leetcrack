#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
DECODE WAYS (BOTTOM‑UP DP)
================================================================================

PROBLEM (LeetCode 91 style):
- You are given a string s containing only digits '0'–'9'.
- Map: '1' → 'A', '2' → 'B', ..., '26' → 'Z'.
- Count how many different ways you can decode the whole string.

Example:
s = "226"
Valid decodings:
  "2 2 6"  → "B B F"
  "22 6"   → "V F"
  "2 26"   → "B Z"
Answer = 3.

REAL‑LIFE FEEL:
- Like reading a coded message where each one or two digits can form a letter.
- You want to know in how many distinct ways you can interpret the message.

NAIVE / BRUTE FORCE (for comparison, not coded here):
- At each position i:
  1) Try to use 1 digit s[i] if it's between '1' and '9'.
  2) Try to use 2 digits s[i..i+1] if it's between "10" and "26".
- Recurse forward from i by 1 or 2 steps.
- Count all valid paths.
- Time: roughly O(2^n) in worst case (exponential branching).

THIS OPTIMIZED DP APPROACH (YOUR CODE):
- dp[i] = number of ways to decode the substring s[i..n-1].
- We fill dp from right to left.

KEY TRANSITIONS:
1) Base case:
   - dp[n] = 1
   - Meaning: there is exactly 1 way to decode an empty suffix (do nothing).

2) For each i from n-1 down to 0:
   - Let temp = s[i] - '0' (the digit at position i).
   - If temp == 0:
       - '0' by itself cannot map to any letter.
       - So dp[i] = 0 (no valid decoding starting with '0').
   - Else:
       - First, use the 1-digit number s[i] (1..9):
           dp[i] = dp[i+1]
         (we take 1 digit, remaining ways are dp[i+1])
       - Then, if i+1 exists, check the 2-digit number s[i..i+1]:
           twoDigit = temp*10 + (s[i+1]-'0')
           If 10 <= twoDigit <= 26:
               dp[i] += dp[i+2]
         (we take 2 digits, remaining ways are dp[i+2])

3) Answer:
   - dp[0] is the number of ways to decode the entire string s.

================================================================================
CODE WITH SIMPLE EXPLANATION COMMENTS
================================================================================
*/

class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();

        // dp[i] = number of ways to decode substring s[i..n-1]
        vector<int> dp(n + 1, 0);

        // Base case: empty string (beyond last char) has 1 way (do nothing)
        dp[n] = 1;

        // Fill dp from right to left
        for (int i = n - 1; i >= 0; i--) {
            int temp = s[i] - '0';   // current digit as integer

            // If digit is '0', it cannot stand alone as a letter.
            // No decoding starts from '0'.
            if (temp == 0) {
                dp[i] = 0;
                continue;
            }

            // OPTION 1: take one digit s[i] (1..9)
            // Then remaining ways = dp[i+1]
            dp[i] = dp[i + 1];

            // OPTION 2: take two digits s[i..i+1] if valid (10..26)
            if (i + 1 < n) {
                int twoDigit = temp * 10 + (s[i + 1] - '0');
                if (twoDigit >= 10 && twoDigit <= 26) {
                    dp[i] += dp[i + 2];
                }
            }
        }

        // dp[0] = number of ways to decode the whole string s[0..n-1]
        return dp[0];
    }
};

/*
================================================================================
TESTING WITH EXAMPLES
================================================================================
*/

int main() {
    Solution sol;

    // Example 1
    string s1 = "12";
    // "1 2" → "AB"
    // "12"  → "L"
    // Total = 2
    cout << "Test 1: " << sol.numDecodings(s1)
         << "  // Expected: 2\n";

    // Example 2
    string s2 = "226";
    // "2 2 6" → "B B F"
    // "22 6"  → "V F"
    // "2 26"  → "B Z"
    // Total = 3
    cout << "Test 2: " << sol.numDecodings(s2)
         << "  // Expected: 3\n";

    // Example 3
    string s3 = "06";
    // Leading '0' cannot be decoded → 0 ways
    cout << "Test 3: " << sol.numDecodings(s3)
         << "  // Expected: 0\n";

    /*
    SUMMARY:
    - Brute force explores all possible decoding splits recursively.
    - This DP solution reuses previously computed results for each index i,
      so each position is processed once.
    - This reduces time from exponential O(2^n) to linear O(n),
      which is efficient for large strings.
    */

    return 0;
}
