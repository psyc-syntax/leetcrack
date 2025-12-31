/*
================================================================================
LEETCODE 7: REVERSE INTEGER – SIMPLE MATH + 32-BIT RANGE CHECK
================================================================================


PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given a 32-bit signed integer x (can be positive or negative).
- You must reverse its digits and return the new number.
- BUT: If the reversed number goes OUTSIDE 32-bit signed range [-2^31, 2^31 - 1],
  you must return 0 instead.

Examples:
- x = 123    → 321
- x = -123   → -321
- x = 120    → 21    (leading zero is dropped automatically)
- x = 1534236469 → reverse overflows 32-bit → return 0.

REAL-LIFE FEEL:
- Imagine you write a number on paper, then read it from right to left.
- That new number is the “reversed” number.
- But if the reversed number is too large for a 32-bit box, you throw it away (return 0).


RULES:
- Input x is within 32-bit signed range initially.
- Must handle negative numbers too (sign stays with reversed digits).
- If reversed value < -2^31 or > 2^31 - 1 → return 0.


CORE IDEA (This Code):
1. Use a variable `rev` to build the reversed number.
2. While x is not 0:
   - Take last digit: `digit = x % 10`.
   - Append digit to rev: `rev = rev * 10 + digit`.
   - Remove last digit from x: `x /= 10`.
3. After loop, check if `rev` is still in 32-bit signed range.
4. If out of range, return 0; else return `rev` as int.


TIME & SPACE COMPLEXITY:
- Let x have k digits.
- Loop runs k times → TIME = O(k) = O(log|x|) w.r.t. numeric value.
- Only uses a few variables → SPACE = O(1).


================================================================================
YOUR CODE REWRITTEN WITH SIMPLE ENGLISH COMMENTS
================================================================================
*/

#include <cmath>  // for pow

int reverse(int x) {
    // Use long long so we have extra range while building reversed number.
    // This helps us detect overflow before returning as int.
    long long rev = 0;

    int i = 1; // loop counter (not really needed for logic, but kept from your code)

    // Repeat until x becomes 0 (no digits left)
    while (x != 0) {

        // These checks try to ensure 'x' is inside 32-bit range.
        // In the LeetCode problem, 'x' is already guaranteed to be 32-bit,
        // so this check is not necessary.
        if (x >= pow(2, 31) || x <= pow(-2, 31)) return 0;

        // STEP 1: Take the last digit of x.
        // Example: x = 123 → x % 10 = 3
        int lastDigit = x % 10;

        // STEP 2: Append lastDigit to the reversed number.
        // Example: rev = 45, lastDigit = 3 → new rev = 453
        rev = rev * 10 + lastDigit;

        // STEP 3: Remove the last digit from x.
        // Example: x = 123 → x = 12
        x /= 10;

        i++; // increment counter (not used for anything important)
    }

    // After the loop, all digits have been reversed into 'rev'.

    // Final safety check:
    // If rev is outside 32-bit signed integer range, return 0.
    if (rev >= pow(2, 31) || rev <= pow(-2, 31)) return 0;

    // If within range, cast to int and return.
    return (int)rev;
}


/*
NOTES / BETTER PRACTICE (for interviews):
- Using pow(2, 31) involves floating point and can be avoided.
- Better:
    const int INT_MAX_32 = 2147483647;
    const int INT_MIN_32 = -2147483648;
- Best solutions check for overflow BEFORE doing rev * 10 + digit,
  with logic using INT_MAX / 10 and INT_MIN / 10.
- But conceptually, your logic:
  - take last digit
  - build reversed
  - check 32-bit range
  matches the standard Reverse Integer solution.
*/
