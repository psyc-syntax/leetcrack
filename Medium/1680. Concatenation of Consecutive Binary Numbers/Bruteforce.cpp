#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
CONCATENATION OF CONSECUTIVE BINARY NUMBERS — BRUTE FORCE STRING APPROACH
================================================================================

PROBLEM (LeetCode 1680 style):
- Given an integer n.
- For each i from 1 to n:
  - Take the **binary representation** of i.
  - Concatenate all these binaries into one big binary string.
- Return the **decimal value** of this big binary string modulo 1e9+7.[web:140][web:145][web:147]

Example:
- n = 3
  1   -> "1"
  2   -> "10"
  3   -> "11"
  concatenation = "11011" (binary) = 27 (decimal) → answer = 27.[web:145][web:146]

--------------------------------------------------------------------------------
NAIVE / BRUTE FORCE IDEA (WHAT THIS CODE DOES)
--------------------------------------------------------------------------------
1) For each i from 1 to n:
   - Convert i to its binary string using a helper `findbin(i)`.
   - Append it to a global string `s`.

2) After the loop, `s` holds the entire concatenated binary representation
   from 1 to n.

3) Now convert this big binary string `s` to a number:
   - Start from the **rightmost bit** (least significant).
   - Maintain a running power of two `current_pow` (1, 2, 4, 8, ...).
   - For each bit from right to left:
     - If bit is '1', add `current_pow` to the answer (modulo 1e9+7).
     - Update `current_pow = (current_pow * 2) % mod`.

This simulates exactly what the brute force description says:
build the **whole binary string**, then evaluate it as a binary number.[web:141][web:145]

================================================================================
CODE WITH BRUTE FORCE STYLE COMMENTS
================================================================================
*/

class Solution {
public:
    typedef long long ll;

    // Convert an integer n to its binary representation as a string
    // e.g., 5 -> "101", 1 -> "1", 4 -> "100"
    string findbin(int n) {
        string ans = "";
        // build in reverse (LSB to MSB)
        while (n) {
            ans += char((n % 2) + '0'); // add '0' or '1'
            n /= 2;
        }
        // reverse to get correct order (MSB to LSB)
        int i = 0;
        int j = (int)ans.length() - 1;
        while (i < j) {
            char temp = ans[i];
            ans[i] = ans[j];
            ans[j] = temp;
            i++;
            j--;
        }
        return ans; // binary string of n
    }

    int concatenatedBinary(int n) {
        ll finalVal = 0;
        string s = "";

        // Step 1: concatenate binary strings of all numbers from 1 to n
        for (int i = 1; i <= n; i++) {
            s += findbin(i);
        }

        // Step 2: interpret this big binary string s as a number (mod 1e9+7)
        int len = (int)s.length();
        ll mod = pow(10, 9) + 7;
        ll current_pow = 1; // represents 2^0, then 2^1, 2^2, ...

        // traverse from right to left (least significant bit to most)
        for (int i = len - 1; i >= 0; i--) {
            if (s[i] == '1') {
                finalVal = (finalVal + current_pow) % mod;
            }
            current_pow = (current_pow * 2) % mod; // move to next power of 2
        }

        return (int)finalVal;
    }
};

/*
================================================================================
TIME AND SPACE COMPLEXITY (BRUTE FORCE)
================================================================================
Let n be the input.

- Binary length of each i:
  - i has about floor(log2(i)) + 1 bits.
- Total length of concatenated binary string s:
  - ≈ sum_{i=1..n} log2(i) ≈ n * log2(n).[web:141][web:145]

1) Building the string s:
   - For each i, findbin(i) takes O(log i).
   - Appending to s overall is O(n log n).
2) Converting s to number:
   - Loop over all bits once: O(length of s) ≈ O(n log n).

Total Time: O(n log n).[web:141][web:146]  
Space:
- String s stores O(n log n) bits.
- Plus small overhead for helper variables.

This is the **naive/brute force** string-building approach;  
optimized solutions avoid building the string and instead use bit shifts and
bit-length tricks to get O(n) time and O(1) extra space.[web:141][web:146][web:147]
================================================================================
*/
