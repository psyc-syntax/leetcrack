#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
POW(x, n) USING FAST EXPONENTIATION (FIXED INT_MIN CASE)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Compute x raised to the power n (x^n), where n can be positive, zero, or negative.

Examples:
- myPow(2.0, 10)  → 1024
- myPow(2.0, -2)  → 0.25  (since 2^-2 = 1 / 2^2)
- myPow(2.0, 0)   → 1

REAL-LIFE FEEL:
- Think of x as a growth factor and n as the number of steps.
  - Positive n: apply growth repeatedly.
  - Negative n: undo growth (go backwards).

APPROACH (Fast Power / Binary Exponentiation):
1. Use these rules:
   - x^0 = 1
   - If n is even: x^n  = (x^(n/2))^2
   - If n is odd:  x^n  = (x^(n/2))^2 * x
2. For n < 0:
   - x^n = (1/x)^(-n)
3. Recursively compute x^(n/2), square it, and multiply by x if n is odd.
4. Time: O(log |n|), Space: O(log |n|) (recursion depth).

INT_MIN BUG (and how this version fixes it):
- For 32‑bit int: INT_MIN = -2147483648.
- In plain code, doing n = -n when n == INT_MIN overflows.
- This version handles that specific case BEFORE negating n:
  - If n == -2147483648:
      x^n = x * x^(n+1)  (because x^n = x * x^(n-1), rearranged)
      use x * myPow(x, -(n+1)) so -(n+1) is now in range.

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

double myPow(double x, int n) {
    // Base case: x^0 = 1
    if (n == 0) return 1.0;

    // Handle negative exponent
    if (n < 0) {
        x = 1.0 / x;  // x^n = (1/x)^(-n)

        // Special handling for INT_MIN = -2147483648
        // Directly doing n = -n would overflow here.
        if (n == -2147483648) {
            // Idea:
            // x^(-2147483648) = (1/x)^2147483648
            // We know (1/x)^2147483648 = (1/x) * (1/x)^2147483647
            // In this code form:
            //   current x = 1/x, n = -2147483648
            //   return x * myPow(x, 2147483647)
            return x * myPow(x, -(n + 1));
        }

        // Safe to negate for all other negative n
        n = -n;
    }

    // Recursively compute x^(n/2)
    double ans = myPow(x, n / 2);

    // Square the half result
    ans *= ans;

    // If n is odd, multiply one extra x
    if (n % 2 != 0) ans *= x;

    return ans;
}

/*
================================================================================
TEST FUNCTION WITH EXAMPLES (INCLUDING INT_MIN EDGE CASE)
================================================================================
*/
int main() {
    cout.setf(ios::fixed);
    cout << setprecision(10);

    // Positive exponent
    cout << "myPow(2.0, 10)  = " << myPow(2.0, 10)
         << "   // Expected: 1024\n";

    // Negative exponent (normal case)
    cout << "myPow(2.0, -2)  = " << myPow(2.0, -2)
         << "   // Expected: 0.25\n";

    // Zero exponent
    cout << "myPow(2.0, 0)   = " << myPow(2.0, 0)
         << "   // Expected: 1\n";

    // INT_MIN edge case (previous version failed here)
    int mn = INT_MIN; // -2147483648
    cout << "myPow(2.0, INT_MIN) = " << myPow(2.0, mn)
         << "   // This version avoids overflow on n = INT_MIN\n";

    return 0;
}

/*
================================================================================
WHY THE PREVIOUS VERSION FAILED AND THIS ONE WORKS
================================================================================
- Previous version:
  if (n < 0) {
      x = 1/x;
      n = -n;   // overflow when n == INT_MIN
  }
  → For n == INT_MIN, -n is out of int range, causing undefined behavior.

- This version:
  if (n < 0) {
      x = 1/x;
      if (n == INT_MIN)
          return x * myPow(x, -(n + 1)); // now -(n+1) = 2147483647 in range
      n = -n;  // safe for all other negative values
  }

So:
- Logic (fast exponentiation) remains the same.
- The INT_MIN case is explicitly handled to avoid overflow.
*/
