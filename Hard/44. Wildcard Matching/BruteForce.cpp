/*
================================================================================
LEETCODE 44: WILDCARD MATCHING (RECURSIVE BACKTRACKING VERSION)
================================================================================


PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given:
    - a TEXT string s  (example: "file_name.txt")
    - a PATTERN string p that may contain:
        - normal letters: a–z
        - '?' wildcard: matches EXACTLY ONE character
        - '*' wildcard: matches ANY SEQUENCE of characters (even empty)
- Goal: Check if the ENTIRE string s matches the ENTIRE pattern p.

Example:
    s = "adceb"
    p = "*a*b"
    This should match:
      - First '*' can match "" (empty)
      - 'a' matches 'a'
      - Second '*' can match "dce"
      - 'b' matches 'b'


REAL-LIFE FEEL:
- Think of how file search works in an OS:
    - Pattern "*.cpp" matches any file ending with ".cpp".
    - Pattern "data_??.txt" matches files like "data_01.txt", "data_ab.txt".
- This code simulates such wildcard matching using recursion on indices of s and p.


RULES:
- '?' matches exactly ONE character.
- '*' matches any sequence of characters (0, 1, 2, 3, ...).
- Normal characters must match exactly.
- Matching must cover the WHOLE string (not partial).


APPROACH USED IN THIS CODE:
1. Use a RECURSIVE helper function:
   - helper(s, p, i, j) answers:
       "Does s[i..end] match p[j..end]?"
2. Handle base cases:
   - Both s and p finished → return true.
   - Pattern finished but string not → return false.
3. For each pattern character p[j]:
   - If s ended but p not:
       - Only '*' can still match (as empty).
   - If p[j] == '?':
       - Match exactly one char → move i and j by 1.
   - If p[j] == '*':
       - Try two paths:
           a) '*' matches EMPTY → move j only.
           b) '*' matches ONE or MORE chars → move i only.
   - Else (normal char):
       - Must be equal to s[i] → then move both by 1.
4. isMatch(s, p) just calls helper(s, p, 0, 0) to start from beginning.


TIME & SPACE (for THIS backtracking version):
- Let n = length of s, m = length of p.
- Worst-case TIME: Exponential (very large) because:
    - Every '*' creates two recursive branches (skip vs consume).
    - Many overlapping subproblems → huge recursion tree.
- SPACE:
    - O(n + m) recursion stack depth in worst case.


WHY THIS VERSION CAN GET TIME LIMIT EXCEEDED (TLE) ON LARGE INPUTS:
- The recursive solution does NOT use memoization or DP.
- Same state (i, j) can be recomputed many times from different paths.
- With long strings and many '*' characters, the branching causes:
    - Exponential number of recursive calls.
    - Too slow for large LeetCode constraints.
- Optimized solutions use DP or memoization to ensure each (i, j) is solved once
  in O(n * m) time.


--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    -------------------------------------------------------------------------
    helper(s, p, i, j):

    - Returns true if substring s[i..end] matches pattern p[j..end].
    - Parameters:
        s: the input string.
        p: the pattern string (may contain '?', '*').
        i: current index in s (0-based).
        j: current index in p (0-based).

    HIGH-LEVEL LOGIC:
    - If both i and j reach the end -> successful full match.
    - If pattern ends but string not -> fail.
    - If string ends but pattern not:
        - remaining pattern must be all '*' (each '*' can match empty).
    - For each character p[j]:
        - '?'  -> match one char, move both indices.
        - '*'  -> try:
            1) '*' as empty: move j only.
            2) '*' consumes one char: move i only.
        - else -> normal char: must equal s[i], then move both.
    -------------------------------------------------------------------------
    */
    bool helper(string &s, string &p, int i , int j){
        // ================================================================
        // CASE 1: both string and pattern are finished
        // ------------------------------------------------
        // i == s.size()  -> we are past the last character of s
        // j == p.size()  -> we are past the last character of p
        //
        // If BOTH ended at the same time:
        //    It means s[0..end] completely matches p[0..end].
        // So we return true.
        // ================================================================
        if(i == s.size() && j == p.size()) 
            return true;

        // ================================================================
        // CASE 2: pattern finished, but string NOT finished
        // ------------------------------------------------
        // j == p.size()  BUT  i < s.size()
        //
        // Pattern has no characters left to match.
        // But string still has characters remaining.
        // No way to match those remaining characters -> return false.
        // ================================================================
        if(j == p.size()) 
            return false;

        // ================================================================
        // CASE 3: string finished, pattern NOT finished
        // ------------------------------------------------
        // i == s.size()  BUT  j < p.size()
        //
        // We have no more characters in s.
        // Remaining pattern characters must be able to match EMPTY string.
        //
        // Among pattern characters:
        //  - normal char: needs a real char from s -> cannot match empty.
        //  - '?': needs exactly one char from s -> cannot match empty.
        //  - '*': CAN match empty sequence -> we may skip it.
        // ================================================================
        if(i == s.size()){
            // If current pattern char is '*', we can skip it:
            //   '*' here is used to match empty, so we just move j forward.
            if(p[j] == '*')
                return helper(s, p, i, j + 1);

            // If it is NOT '*', we cannot match empty string anymore.
            // String is finished but pattern wants more concrete chars -> fail.
            return false;
        }

        // ================================================================
        // CASE 4: pattern has '?'
        // ------------------------------------------------
        // '?' represents exactly ONE character.
        // Since i < s.size() here, there IS a character s[i] to match.
        //
        // We match this one character:
        //   - move to next char in s: i + 1
        //   - move to next char in p: j + 1
        // Then recursively check the rest.
        // ================================================================
        if(p[j] == '?'){
            return helper(s, p, i + 1, j + 1);
        }

        // ================================================================
        // CASE 5: pattern has '*'
        // ------------------------------------------------
        // '*' can match:
        //   - empty sequence ""
        //   - one character
        //   - many characters
        //
        // Standard recursive handling:
        //
        // Option A: treat '*' as matching EMPTY:
        //    - do NOT consume any char from s
        //    - skip '*' in pattern (j + 1)
        //    -> helper(s, p, i, j + 1)
        //
        // Option B: treat '*' as matching ONE (or more) characters:
        //    - consume s[i] by '*'
        //    - stay on same '*' in pattern (j)
        //    -> helper(s, p, i + 1, j)
        //
        // If EITHER option returns true, we have a valid match.
        //
        // NOTE (Reason for TLE in large inputs):
        // - For each '*', we branch into two recursive calls.
        // - For long strings and many '*', this causes exponential growth
        //   of recursive states (huge recursion tree).
        // - Same (i, j) combinations are recomputed many times.
        // - This naive backtracking is too slow for big test cases and
        //   leads to Time Limit Exceeded.
        // ================================================================
        if(p[j] == '*'){
            // Option A: '*' = empty
            // Option B: '*' = one or more characters
            return helper(s, p, i, j + 1)      // skip '*'
                || helper(s, p, i + 1, j);     // use '*' to eat s[i]
        }

        // ================================================================
        // CASE 6: normal character (no '?' or '*')
        // ------------------------------------------------
        // Now p[j] is a regular character like 'a', 'b', etc.
        // It MUST match s[i] exactly.
        //
        // If they are not equal -> immediate mismatch -> return false.
        // ================================================================
        if(p[j] != s[i]) 
            return false;

        // Characters are equal:
        //   - consume one char from s -> i + 1
        //   - consume one char from p -> j + 1
        // Continue checking the rest of the string and pattern.
        return helper(s, p, i + 1, j + 1);
    }

    /*
    -------------------------------------------------------------------------
    isMatch(s, p):

    - Public function called by the judge.
    - Starts the matching process from the beginning of s and p.
    - Simply calls helper(s, p, 0, 0) and returns the result.

    NOTE:
    - This version is easy to understand but can TLE on very large inputs.
    - Optimized solutions usually:
        - add memoization (2D dp array for states (i, j)), or
        - use bottom-up dynamic programming, or
        - use a greedy two-pointer technique with special handling of '*'.
    -------------------------------------------------------------------------
    */
    bool isMatch(string s, string p) {
        return helper(s, p, 0 , 0);
    }
};

/*
Simple local test (NOT used on LeetCode; LeetCode provides its own main):
*/
int main() {
    string s = "aa";
    string p = "*";

    Solution sol;
    bool ifitismatching = sol.isMatch(s, p);

    cout << (ifitismatching ? "MATCH" : "NO MATCH") << endl;
    return 0;
}
