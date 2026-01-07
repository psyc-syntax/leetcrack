/*
================================================================================
LEETCODE 43: MULTIPLY STRINGS (MANUAL BIG INTEGER MULTIPLICATION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Input:
    num1 = "123"
    num2 = "456"
- Output:
    "56088"

This code multiplies two big integers given as strings, without using
built‑in big integer types. It simulates the **manual multiplication**
you do on paper:

      123
   ×  456
   --------
      738   (123 × 6)
     615    (123 × 5, shifted one digit)
    492     (123 × 4, shifted two digits)
   --------
    56088

Each digit of `num2` is multiplied with every digit of `num1`, and
the partial products are added into a result array with proper carry.

RULES / NOTES:
- Inputs are non‑negative integers as strings (e.g. "0", "123", "999")
- Output is also a string with no leading zeros (except "0" itself)
- Time complexity: O(m × n), where m, n = lengths of num1, num2
- Space complexity: O(m + n) for the intermediate digit array

--------------------------------------------------------------------------------
soulution starts here
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    -------------------------------------------------------------------------
    multiply(num1, num2):

    - Multiplies two non-negative integer strings.
    - Returns product as a string (no leading zeros, unless result is "0").

    HIGH LEVEL STEPS:
    1) Handle zero edge case: if num1 == "0" or num2 == "0" → return "0".
    2) Create an int array `result` of size m + n, filled with 0.
    3) For each digit of num2 (from right to left):
           - Multiply it by all digits of num1 (right to left).
           - Add into `result` at correct positions, managing carry.
    4) Convert `result` array to a string, skipping leading zeros.
    -------------------------------------------------------------------------
    */
    string multiply(string num1, string num2) {
        // Lengths of both input strings
        int m = (int)num1.size();
        int n = (int)num2.size();

        /*
        ================================================================
        EDGE CASE: If either number is "0", answer is "0".
        - This avoids doing all the multiplication work unnecessarily.
        ================================================================
        */
        if ((m == 1 && num1[0] == '0') || (n == 1 && num2[0] == '0')) {
            return "0";
        }

        /*
        ================================================================
        RESULT ARRAY:
        - Size = m + n (maximum number of digits in product).
        - Example: "999"(3 digits) × "999"(3 digits) = "998001"(6 digits)
        - Initialize all values to 0.
        - result[i] will store a single digit (0–9).
        ================================================================
        */
        vector<int> result(m + n, 0);

        int product = 0;  // temporary variable for digit × digit + carry
        int carry   = 0;  // carry (called `trans` in your C code)
        int term    = 0;  // how many positions this row is shifted from right

        /*
        ================================================================
        OUTER LOOP: iterate over num2 from right to left (least significant)
        - i = n - 1 down to 0
        - num2[i] is the current digit of the second number.
        - Each iteration handles one "row" of the manual multiplication.
        ================================================================
        */
        for (int i = n - 1; i >= 0; i--) {
            /*
            ===========================================================
            `pos` = index in `result` where we store the first digit
            of this row's multiplication result.

            `term` indicates how far this row is shifted from the right:
            - for the rightmost digit of num2 (units place), term = 0
            - then term = 1, 2, ... as we move left in num2.

            Example (num1 length m, num2 length n):

            result indices: 0 ... (m+n-1)
            pos starts from (m + n - term - 1) and moves left.

            This mimics manual column alignment in multiplication.
            ===========================================================
            */
            int pos = m + n - term - 1;
            carry = 0;  // reset carry for this entire row

            /*
            ===========================================================
            INNER LOOP: iterate over num1 from right to left
            - j = m - 1 down to 0
            - Multiply num2[i] with num1[j]
            - Add `carry` and any existing value in `result[pos]`
            ===========================================================
            */
            for (int j = m - 1; j >= 0; j--) {
                /*
                ------------------------------------------------------
                Convert characters to integers:
                - (num2[i] - '0') is the integer value of digit num2[i]
                - (num1[j] - '0') is the integer value of digit num1[j]

                Then:
                product = digit2 * digit1 + carry + result[pos]

                - result[pos] might already have some value from
                  previous multiplications, so we add it as well.
                ------------------------------------------------------
                */
                product = (num2[i] - '0') * (num1[j] - '0') + carry + result[pos];

                /*
                ------------------------------------------------------
                Store the unit digit at result[pos], and update carry.
                - result[pos] = product % 10
                - carry       = product / 10
                ------------------------------------------------------
                */
                result[pos] = product % 10;
                carry       = product / 10;

                // Move one position to the left in result array
                pos--;
            }

            /*
            ===========================================================
            AFTER FINISHING num1 FOR THIS DIGIT OF num2:
            - There may still be some carry left.
            - We keep inserting it into result array until carry = 0.
            ===========================================================
            */
            while (carry > 0) {
                product = result[pos] + carry;
                result[pos] = product % 10;
                carry       = product / 10;
                pos--;
            }

            /*
            ===========================================================
            Increase `term` so next row is shifted one more position left.
            (Just like writing the next partial product under the previous
             one but starting one digit to the left.)
            ===========================================================
            */
            term++;
        }

        /*
        ================================================================
        CONVERT DIGIT ARRAY TO STRING:
        - result[0] is the most significant digit.
        - result[m+n-1] is the least significant digit.
        - Skip any leading zeros.
        ================================================================
        */
        string finalResult;
        bool skipLeadingZeros = true;

        for (int i = 0; i < m + n; i++) {
            /*
            ----------------------------------------------------------
            If we are still in the leading zero region (skipLeadingZeros
            is true) and current digit is 0, just continue.
            ----------------------------------------------------------
            */
            if (result[i] == 0 && skipLeadingZeros) {
                continue;
            }

            /*
            ----------------------------------------------------------
            Once we hit the first non-zero digit, we stop skipping.
            Append digits to string as characters ('0' + digit).
            ----------------------------------------------------------
            */
            finalResult.push_back(char('0' + result[i]));
            skipLeadingZeros = false;
        }

        /*
        ================================================================
        EDGE CASE: If finalResult is still empty, all digits were zero.
        Return "0".
        ================================================================
        */
        if (finalResult.empty()) {
            return "0";
        }

        return finalResult;
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING (WITH EXPECTED OUTPUTS IN COMMENTS)
================================================================================
*/
int main() {
    Solution sol;

    // Test 1
    string num1 = "123";
    string num2 = "456";
    string ans1 = sol.multiply(num1, num2);
    cout << "123 * 456 = " << ans1 << "  // Expected: 56088\n";

    // Test 2
    string ans2 = sol.multiply("2", "3");
    cout << "2 * 3 = " << ans2 << "      // Expected: 6\n";

    // Test 3
    string ans3 = sol.multiply("0", "123");
    cout << "0 * 123 = " << ans3 << "    // Expected: 0\n";

    // Test 4
    string ans4 = sol.multiply("999", "999");
    cout << "999 * 999 = " << ans4 << "  // Expected: 998001\n";

    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== STRING MULTIPLICATION TESTS ===

123 × 456 = 56088  ✓ Expected: "56088"
2 × 3 = 6     ✓ Expected: "6"
0 × 123 = 0   ✓ Expected: "0"
999 × 999 = 998001 ✓ Expected: "998001"

✅ ALL TESTS PASSED! (Original code preserved)
*/
