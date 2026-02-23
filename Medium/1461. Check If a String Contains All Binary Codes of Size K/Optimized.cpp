#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
CHECK IF STRING CONTAINS ALL BINARY CODES OF SIZE k — OPTIMIZED (SET + WINDOW)
================================================================================

PROBLEM EXPLANATION (same style as LRU one):
- You are given a binary string `s` (only '0' and '1').
- You are given an integer `k`.
- Question: Does `s` contain **every** possible binary string of length `k`
  as a substring at least once?

Example:
- s = "00110110", k = 2
  All 2‑bit codes: "00", "01", "10", "11".
  All of them appear somewhere in s → return true.

REAL-LIFE FEEL:
- Think of all binary codes of length k as different “passwords”.
- The string `s` is like a log of what passwords were typed over time.
- You need to check if **every** possible password of length k appears at
  least once in this log as a contiguous sequence.

--------------------------------------------------------------------------------
NAIVE / BRUTE FORCE IDEA (for comparison, like before):
--------------------------------------------------------------------------------
- Generate all \(2^k\) binary strings of length k.
- For each code:
  - Scan every substring of length k in `s` and check if this code appears.
- This is clearly exponential in k: about O(2^k * n * k).

--------------------------------------------------------------------------------
THIS IMPLEMENTATION — OPTIMIZED (SET + SLIDING WINDOW)
--------------------------------------------------------------------------------
MAIN OBSERVATION:
- There are exactly \(2^k\) possible binary strings of length k.
- Instead of generating them, just **look at all substrings of length k**
  that actually appear in `s` and count how many *distinct* ones we see.

STEPS:
1) If string `s` is shorter than k, it can’t contain *any* k‑length code,
   so immediately return false.

2) Slide a window of size k over `s` from left to right:
   - For each start index i (0 ≤ i ≤ n - k):
     - Take the substring `s.substr(i, k)`.
     - Insert it into a `set<string>`. The set automatically keeps only
       unique substrings.

3) At the end, the size of the set tells you how many **distinct** k‑length
   codes you saw in `s`.
   - Total possible distinct codes = \(2^k\), which we can compute as `1u << k`.
   - If `codes.size() == (1u << k)`, then `s` contains **all** binary codes
     of length k.
   - Otherwise, at least one code is missing → return false.

So instead of:
- “all codes → search each in s”
we do:
- “all substrings in s → count uniques, compare with 2^k”.

================================================================================
CODE WITH STEP-BY-STEP COMMENTS (OPTIMIZED SET VERSION)
================================================================================
*/

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = (int)s.size();

        // If s is shorter than k, it can't contain any k-length substring
        if (k > n) return false;

        // Set to store all distinct substrings of length k
        set<string> codes;

        // Slide a window of size k over s:
        // i = starting index of each k-length substring
        for (int i = 0; i <= n - k; i++) {
            // Extract substring from i of length k
            string sub = s.substr(i, k);
            // Insert into the set (duplicates are ignored automatically)
            codes.insert(sub);
        }

        // Total different binary strings of length k = 2^k
        // Use bit shift instead of pow to avoid floating point issues.
        unsigned int totalCodes = 1u << k;

        // If number of distinct k-length substrings equals total possible codes,
        // then s contains all binary codes of size k.
        return codes.size() == totalCodes;
    }
};

/*
Sample testcases (from typical descriptions)

1) s = "00110110", k = 2 → true
   All codes of length 2: "00","01","10","11" all appear.

2) s = "00110", k = 2 → true
   Codes: "00","01","10","11"; all appear.

3) s = "0110", k = 2 → false
   "00" does not appear.

4) s = "0000000000", k = 1 → false
   Codes: "0","1"; "1" does not appear.

5) s = "0001011100", k = 3 → true (all 3‑bit codes appear in this one).
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
TIME AND SPACE COMPLEXITY (OPTIMIZED vs BRUTE FORCE)
================================================================================
Let:
- n = s.size()
- Each substring length = k

1) Generating all k-length substrings:
   - You have (n - k + 1) windows.
   - Each `substr(i, k)` costs O(k).
   - So substring extraction total: O((n - k + 1) * k) ≈ O(n * k).

2) Inserting into set:
   - At most 2^k distinct elements (all codes).
   - set insertion is O(log M), where M ≤ 2^k.
   - Total ≈ O((n - k + 1) * log(2^k)) = O(n * k) for typical constraints.

Overall:
- Time: about O(n * k) in common analysis (or O(n * k * log(2^k)) more precisely).
- Space: O(2^k * k) to store all distinct codes of length k.[web:121][web:124]

Compared to the brute-force “generate all codes then search each in s”
approach O(2^k * n * k), this is significantly more efficient and is the
standard optimized set-based solution used in interviews.
================================================================================
*/
