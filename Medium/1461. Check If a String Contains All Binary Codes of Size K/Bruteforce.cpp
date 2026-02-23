#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROBLEM: CHECK IF STRING CONTAINS ALL BINARY CODES OF SIZE k  (BRUTE FORCE)
================================================================================
You are given:
- A binary string `s` (only '0' and '1').
- An integer `k`.

You must check:
- Are **all** possible binary strings of length `k` present as substrings of `s`?
- If yes → return true, else → return false.[web:116][web:124]

Example:
- s = "00110110", k = 2
  All 2‑bit codes are: "00", "01", "10", "11".
  All of them appear as substrings → answer = true.[web:121]

--------------------------------------------------------------------------------
BRUTE FORCE IDEA (WHAT YOUR CODE DOES)
--------------------------------------------------------------------------------
1) Generate **all binary strings of length k**:
   - There are \(2^k\) such strings.
   - You build them using DP style expansion:
     - Length 1: "0", "1".
     - Length 2: from each of them: append '0' and '1' → "00","01","10","11".
     - Continue up to length k.[web:122][web:124]

2) For each generated k‑length binary code:
   - Scan through string `s`.
   - For every starting position `j` from 0 to `s.size() - k`:
     - Compare `s.substr(j, k)` with this code.
     - If you find a match, mark this code as found and stop scanning further for this code.
   - If after scanning entire `s` the code was **not** found → return false.[web:122][web:125]

3) If **every** code of length k is found somewhere in `s`, return true.[web:124]

This is exactly the straightforward brute‑force approach: “generate all possibilities, then check each one in the string”.[web:124][web:122]

================================================================================
CODE (YOUR BRUTE FORCE VERSION WITH COMMENTS)
================================================================================
*/

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        // Edge cases:
        if (k == 0) return true;          // empty code: trivially true
        if (k > (int)s.size()) return false; // string too short to contain any k-length code

        // dp[i] will store all binary strings of length i
        vector<vector<string>> dp(k + 1);

        // Base: all binary strings of length 1
        dp[1].push_back("0");
        dp[1].push_back("1");

        // Build all binary strings from length 2 to k
        for (int i = 2; i <= k; i++) {
            // For every string of length i-1, append '0' and '1'
            for (int j = 0; j < (int)dp[i - 1].size(); j++) {
                dp[i].push_back(dp[i - 1][j] + "0");
                dp[i].push_back(dp[i - 1][j] + "1");
            }
        }

        // Now dp[k] contains all binary strings of length k (total 2^k strings)

        // For each possible k-length code, check if it appears in s
        for (int i = 0; i < (int)dp[k].size(); i++) {
            bool found = false;

            // Slide a window of size k over s
            for (int j = 0; j <= (int)s.size() - k; j++) {
                // Compare substring with this code
                if (s.substr(j, k) == dp[k][i]) {
                    found = true;
                    break;  // no need to search further for this code
                }
            }

            // If this particular code never appears, we can immediately return false
            if (!found) return false;
        }

        // All 2^k codes were found
        return true;
    }
};

/*
Sample testcases (from typical descriptions)[web:116][web:121][web:124]

1) s = "00110110", k = 2 → true
   All codes of length 2: "00","01","10","11" all appear.

2) s = "00110", k = 2 → true
   Codes: "00","01","10","11"; all appear.

3) s = "0110", k = 2 → false
   "00" does not appear.

4) s = "0000000000", k = 1 → false
   Codes: "0","1"; "1" does not appear.

5) s = "0001011100", k = 3 → true (all 3‑bit codes appear in this one).[web:120][web:124]
*/

int main() {
    Solution sol;

    vector<pair<string,int>> tests = {
        {"00110110", 2},
        {"00110", 2},
        {"0110", 2},
        {"0000000000", 1},
        {"0001011100", 3}
    };

    for (auto &t : tests) {
        string s = t.first;
        int k = t.second;
        bool ans = sol.hasAllCodes(s, k);
        cout << "s = \"" << s << "\", k = " << k
             << " -> " << (ans ? "true" : "false") << '\n';
    }

    return 0;
}

/*
================================================================================
TIME AND SPACE COMPLEXITY (BRUTE FORCE STYLE)
================================================================================
Let:
- n = s.size()
- Number of different k‑bit codes = 2^k.[web:121][web:124]

1) Generating all binary strings of length k:
   - At each level i, number of strings doubles.
   - Total strings of length k = 2^k.
   - Time ~ O(2^k * k) to build all strings (each length is k).

2) For each of the 2^k codes:
   - You scan all windows of length k in s.
   - There are (n - k + 1) windows.
   - Comparing strings length k → O(k) per compare.
   - So checking one code ≈ O((n - k + 1) * k).
   - For all codes → O(2^k * (n - k + 1) * k).[web:122][web:124]

Overall:
- Time: O(2^k * n * k)  → exponential in k (classic brute force).[web:122][web:124]
- Space: O(2^k * k) to store all binary codes in dp[k].

================================================================================
NOTE:
- Optimal/typical solutions use a hash set or rolling bit mask to track seen
  substrings and only iterate over `s` once, with time around O(n * k) or O(n).[web:120][web:121][web:124]
- But the above implementation is intentionally the **brute force** method:
  “generate every possible code and search each one in the string”.
================================================================================
*/

