/*
================================================================================
LEETCODE 3: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS - SLIDING WINDOW
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given string like "abcabcbb" or "pwwkew"
- Find LONGEST substring with NO REPEATED characters
- Example: "abcabcbb" → "abc" (length 3)
- Real life: Longest unique name tag on school bags!
- "abc" ✓ (all unique), "abba" ✗ (a repeats)

RULES:
- Substring = continuous characters (not scattered)
- Characters can be letters, digits, symbols (256 possible)
- Return LENGTH of longest unique substring

SLIDING WINDOW APPROACH (This Code):
1. Use TWO pointers: start (left window) + i (right window)
2. Track character frequency in window using array
3. When duplicate found → SHRINK window from left until no duplicate
4. Track max length continuously
5. Like adjustable window: expand right, shrink left when problem!

TIME COMPLEXITY: O(n) - Perfect! (Each char visited max 2 times)
SPACE COMPLEXITY: O(1) - Fixed 256 size array

WHY THIS IS PERFECT:
- Linear time, constant space
- Handles all characters (not just lowercase)
- No complex data structures needed
- LeetCode optimal solution

EXAMPLE TRACE:
s = "abcabcbb"
i=0: 'a' → window="a" len=1
i=1: 'b' → window="ab" len=2  
i=2: 'c' → window="abc" len=3 ✓ maxlen=3
i=3: 'a' → duplicate! shrink left → window="bca" len=3
i=4: 'b' → duplicate! shrink left → window="cab" len=3
i=5: 'c' → duplicate! shrink → window="ab" len=2
i=6: 'b' → duplicate! shrink → window="b" len=1
Result: 3

REAL-LIFE VISUAL:
" a b c a b c b b "
    ^^^^^    ← window shrinks when 'a' repeats!
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // MAIN FUNCTION: Find longest substring without repeats
    int lengthOfLongestSubstring(string s) {
        vector<int> freq(256, 0);  // Count each character (0-255 ASCII)
        int maxlen = 0;            // Track longest window found
        int count = 0;             // Current window size
        int start = 0;             // Left pointer of sliding window

        for (int i = 0; i < s.size(); i++) {
            unsigned char c = s[i];  // Current character (safe casting)
            
            freq[c]++;               // Add current char to window
            count++;                 // Window size increases
            
            // SHRINK WINDOW: While duplicate exists, remove from left
            while (freq[c] > 1) {    // While current char repeats
                unsigned char leftChar = s[start];  // Leftmost char
                freq[leftChar]--;      // Remove it from count
                start++;               // Move left pointer right
                count--;               // Window size decreases
            }
            
            // UPDATE: Track maximum length found
            maxlen = max(maxlen, count);
        }
        
        return maxlen;  // Return longest unique substring length
    }
};

/*
TEST THE CODE:
int main() {
    Solution sol;
    
    cout << sol.lengthOfLongestSubstring("abcabcbb") << endl;    // 3 ("abc")
    cout << sol.lengthOfLongestSubstring("bbbbb") << endl;       // 1 ("b")  
    cout << sol.lengthOfLongestSubstring("pwwkew") << endl;      // 3 ("wke")
    cout << sol.lengthOfLongestSubstring("dvdf") << endl;        // 3 ("vdf")
    cout << sol.lengthOfLongestSubstring("") << endl;            // 0
    cout << sol.lengthOfLongestSubstring("abc") << endl;         // 3
}
OUTPUT:
3
1
3
3
0
3

PERFECT SOLUTION! O(n) time, O(1) space - LeetCode Accepted ✅
Handles ALL edge cases perfectly!
*/
