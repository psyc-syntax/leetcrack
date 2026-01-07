/*
================================================================================
POW(x, n) USING FAST EXPONENTIATION (RECURSIVE) — WITH BUG EXPLANATION
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given a number x and an integer power n.
- You need to compute x raised to the power n, i.e., x^n, including negative n.

Examples:
- x = 2.0,  n = 10 → 2^10 = 1024
- x = 2.0,  n = -2 → 2^-2 = 1 / (2^2) = 0.25
- x = 2.0,  n = 0  → 2^0 = 1

REAL-LIFE FEEL:
- Think of x as a growth factor (like interest rate multiplier per year).
- n is the number of years:
  - Positive n: growth going forward in time.
  - Negative n: going backwards (undoing growth).

APPROACH (Fast Power / Binary Exponentiation):
1. Use these identities:
   - x^0 = 1
   - If n is even: x^n  = (x^(n/2))^2
   - If n is odd:  x^n  = (x^(n/2))^2 * x
2. For negative n:
   - x^n = (1/x)^(-n)
3. Use recursion:
   - Recursively compute x^(n/2), then square it.
   - Multiply one more x if n is odd.
4. Overall complexity:
   - Time: O(log |n|), because we divide n by 2 each step.
   - Space: O(log |n|) from recursion depth.

IMPORTANT BUG (WHY THIS SOLUTION CAN FAIL):
- When n is the smallest 32-bit integer (INT_MIN = -2147483648),
  the line `n = -n;` overflows, because +2147483648 does not fit in int.
- This causes undefined behavior and wrong answers for cases like:
  - myPow(2.0, INT_MIN)
  - myPow(0.5, INT_MIN) [web:71][web:77]

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS (INCLUDING BUG LOCATION)
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

double myPow(double x, int n) {
    /*
    ================================================================
    BASE CASE:
    - Any number raised to the power 0 is 1.
    - This is also the recursion stopping condition.
    ================================================================
    */
    if (n == 0) return 1.0;

    /*
    ================================================================
    HANDLE NEGATIVE EXPONENT:
    ------------------------------------------------
    Idea:
    - x^(-n) = (1/x)^n
    Steps:
    1. Replace x with 1/x.
    2. Replace n with -n (make exponent positive).
    
    BUG / FAILURE POINT:
    - n is a 32-bit signed int with range [-2^31, 2^31 - 1].
    - INT_MIN = -2147483648.
    - +2147483648 cannot be represented as an int.
    - So when n == INT_MIN, `n = -n;` overflows and produces
      an invalid value (often still INT_MIN).
    - That means for calls like myPow(2.0, INT_MIN), the code
      computes with a corrupted exponent and returns a wrong result.
    ================================================================
    */
    if (n < 0) {
        x = 1.0 / x;
        n = -n;  // <-- BUG HERE when n == INT_MIN (overflow)
    }

    /*
    ================================================================
    RECURSIVE STEP: COMPUTE x^(n/2)
    ------------------------------------------------
    - Divide the exponent by 2.
    - This reduces the problem size logarithmically.
    ================================================================
    */
    double ans = myPow(x, n / 2);

    /*
    ================================================================
    SQUARE THE RESULT:
    - If n is even, x^n = (x^(n/2))^2.
    - If n is odd, we handle the extra x later.
    ================================================================
    */
    ans *= ans;

    /*
    ================================================================
    HANDLE ODD EXPONENT:
    - If n is odd, then:
      x^n = (x^(n/2))^2 * x.
    - Example:
      n = 5 → x^5 = (x^2)^2 * x.
    ================================================================
    */
    if (n % 2 != 0) ans *= x;

    return ans;
}

/*
================================================================================
TEST FUNCTION WITH EXAMPLES AND BUG DEMO
================================================================================
*/
int main() {
    cout.setf(ios::fixed);
    cout << setprecision(10);

    // Test 1: positive exponent
    cout << "myPow(2.0, 10)  = " << myPow(2.0, 10)
         << "   // Expected: 1024\n";

    // Test 2: negative exponent (works for most n < 0)
    cout << "myPow(2.0, -2)  = " << myPow(2.0, -2)
         << "   // Expected: 0.25\n";

    // Test 3: zero exponent
    cout << "myPow(2.0, 0)   = " << myPow(2.0, 0)
         << "   // Expected: 1\n";

    // Test 4: BUG case for INT_MIN
    int mn = INT_MIN; // -2147483648
    cout << "myPow(2.0, INT_MIN) = " << myPow(2.0, mn)
         << "   // BUG: n = -n overflows when n == INT_MIN, result incorrect\n";

    return 0;
}

/*
================================================================================
WHY / WHERE THIS SOLUTION FAILS
================================================================================
1. Binary exponentiation idea is correct:
   - Reduces the exponent by half each step.
   - Uses at most O(log |n|) multiplications.

2. The flaw is in handling the most negative integer exponent:
   - n is int, so max positive is 2147483647.
   - But -INT_MIN = 2147483648, which is out of range.
   - This makes `n = -n;` overflow, a form of integer overflow. [web:71][web:77]

3. For almost all practical exponents (like -1000, -2, 5, 10), the code works.
   - Only when n == INT_MIN does the overflow make the result wrong.

4. A robust implementation must:
   - Either use a wider type (like long long) for n,
   - Or specially handle INT_MIN before negating,
   - Or convert n to long long at the start and work with that.
*/
