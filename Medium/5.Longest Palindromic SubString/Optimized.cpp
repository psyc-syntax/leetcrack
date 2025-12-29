/*
================================================================================
LEETCODE 5: LONGEST PALINDROMIC SUBSTRING - EXPAND AROUND CENTER APPROACH
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given string like "babad" or "cbbd"
- Find LONGEST substring that reads same forward/backward (PALINDROME)
- Example: "bab" or "aba" in "babad" (both length 3)
- Real life: Mirror words like "racecar" - same in mirror!
- "abcba" ✓ (palindrome), "abca" ✗ (not)

RULES:
- Return ANY longest palindromic substring if multiple exist
- Single characters ("a") are always palindromes (length 1)
- Empty string returns empty string

EXPAND AROUND CENTER APPROACH (This Code):
1. Every palindrome has a CENTER (single char OR between 2 chars)
2. From each possible center, EXPAND left/right while characters match
3. Check TWO centers per position:
   - ODD length: center at i    → "aba" (center 'b')
   - EVEN length: center i,i+1  → "aa"  (center between two 'a's)
4. Track longest palindrome found

TIME COMPLEXITY: O(n²) - Optimal! (Each center expands max 2n steps)
SPACE COMPLEXITY: O(1) - Just storing result string

WHY THIS WORKS PERFECTLY:
- Covers ALL possible palindromes (odd + even lengths)
- No duplicates, no missed cases
- Linear expansion per center = efficient
- Beats DP O(n²) space solutions

EXAMPLE TRACE:
s = "babad"
i=0: center 'b' → "b" (len1)
i=1: center 'a' → "aba" (len3) ✓ longest
i=2: center 'b' → "bab" (len3) ✓ same length
i=3: center 'a' → "a" (len1)
i=4: center 'd' → "d" (len1)
Between chars: "ba","ab","ba","ad" → no even palindromes longer
Result: "aba" or "bab"

REAL-LIFE VISUAL:
"b a b a d"
 ^center    → expand: b==b ✓ → "bab"
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // CORE LOGIC: Expand around given left-right center while palindrome
    string expandedpalin(string s, int left, int right) {
        // EXPANSION LOOP: Keep expanding while valid bounds AND characters match
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;   // Move LEFT pointer outward
            right++;  // Move RIGHT pointer outward
        }
        // RETURN: Substring from (left+1) to (right-1) = actual palindrome found
        // Example: left=-1, right=3 → substr(0, 3) = first 3 chars
        return s.substr(left + 1, right - left - 1);
    }
    
    // MAIN FUNCTION: Check every possible center
    string longestPalindrome(string s) {
        if (s.empty()) return "";  // EDGE CASE: Empty string
        
        string longest = "";  // Track longest palindrome found
        
        for (int i = 0; i < s.size(); i++) {
            // CASE 1: ODD LENGTH PALINDROME (center at single char i)
            // Example: "aba" center='b' at i=1
            string p1 = expandedpalin(s, i, i);
            if (p1.size() > longest.size()) {
                longest = p1;  // Update if longer found
            }
            
            // CASE 2: EVEN LENGTH PALINDROME (center between i and i+1)
            // Example: "aa" centers between two 'a's
            string p2 = expandedpalin(s, i, i + 1);
            if (p2.size() > longest.size()) {
                longest = p2;  // Update if longer found
            }
        }  
        return longest;  // Return longest palindrome
    }
};

/*
TEST THE CODE:
int main() {
    Solution sol;
    
    cout << sol.longestPalindrome("babad") << endl;    // "bab" or "aba"
    cout << sol.longestPalindrome("cbbd") << endl;     // "bb"
    cout << sol.longestPalindrome("a") << endl;        // "a"
    cout << sol.longestPalindrome("ac") << endl;       // "a" or "c"
    cout << sol.longestPalindrome("aaa") << endl;      // "aaa"
}
OUTPUT:
bab
bb
a
a
aaa

PERFECT SOLUTION! O(n²) time, O(1) space - Accepted on LeetCode ✅
No optimizations needed - This is already optimal!
*/
