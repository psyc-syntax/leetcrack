/*
================================================================================
BRUTE FORCE VERSION OF "MULTIPLY STRINGS" USING long long
================================================================================

PROBLEM:
- Given two non‑negative integers as strings: num1, num2
- Return their product as a string.

THIS BRUTE FORCE APPROACH:
1. Convert num1 from string → integer (long long m)
2. Convert num2 from string → integer (long long n)
3. Compute n = n * m
4. Convert n back to string (manual digit extraction)

LIMITATION:
- Uses type long long (usually 64 bits).
- Maximum value around 9e18.
- LeetCode 43 allows numbers up to length 200 digits. [web:78]
- So for large inputs, this code **overflows** and returns WRONG answers. [web:71][web:77]

================================================================================
solution starts here
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

char* multiply(char* num1, char* num2) {
    long long n = 0, m = 0;

    // Convert num1 string → integer m
    for (int i = 0; i < (int)strlen(num1); i++) {
        m = m * 10 + (num1[i] - '0');
    }

    // Convert num2 string → integer n
    for (int i = 0; i < (int)strlen(num2); i++) {
        n = n * 10 + (num2[i] - '0');
    }

    // Multiply the two integers
    n = n * m;
    m = n;  // keep a copy in m for later digit extraction

    // If product is 0, directly return "0"
    if (n == 0) {
        // NOTE: For LeetCode, this must be dynamically allocated.
        // Here, to match your original logic, we return a string literal.
        return (char*)"0";
    }

    // Count number of digits in the product
    int len = 0;
    while (n != 0) {
        n /= 10;
        len++;
    }

    // Allocate char array for the result string (+1 for '\0')
    char *num = (char *) malloc((len + 1) * sizeof(char));
    num[len] = '\0';  // null terminator

    // Fill digits from the end (least significant → most significant)
    for (int i = len - 1; i >= 0; i--) {
        num[i] = (char)((m % 10) + '0');  // last digit to char
        m /= 10;                          // remove last digit
    }

    return num;
}

/*
================================================================================
TESTING + EXPECTED OUTPUT (for small numbers only)
================================================================================
*/

int main() {
    // SMALL inputs: these are safe within long long

    char a1[] = "123";
    char b1[] = "456";
    char* r1 = multiply(a1, b1);
    cout << "123 * 456 = " << r1 << "   // Expected: 56088\n";
    free(r1);

    char a2[] = "2";
    char b2[] = "3";
    char* r2 = multiply(a2, b2);
    cout << "2 * 3 = " << r2 << "       // Expected: 6\n";
    free(r2);

    char a3[] = "0";
    char b3[] = "123";
    char* r3 = multiply(a3, b3);
    cout << "0 * 123 = " << r3 << "     // Expected: 0\n";
    // NOTE: r3 points to string literal "0" in this code, so DO NOT free(r3).

    // BIG input (demonstrates FAILURE due to overflow)
    char a4[] = "123456789123456789";
    char b4[] = "987654321987654321";
    char* r4 = multiply(a4, b4);
    cout << "123456789123456789 * 987654321987654321 = " << r4
         << "   // WRONG for big numbers (overflow)\n";
    free(r4);  // undefined behavior in general, but included for symmetry

    return 0;
}

/*
Where this solution fails
Overflow for large inputs

Problem constraints allow up to 200 digits per number.
​

A 200‑digit number is far beyond long long capacity (64‑bit ≈ 19 digits max).
​

Even much smaller numbers like "123456789123456789" * "987654321987654321" already overflow.
​

Undefined behavior and wrong answers

Once n * m overflows, the result is not mathematically correct and is technically undefined behavior in C/C++.
​

The final string you build is a correct decimal representation of this wrong / overflowed integer, not of the real product.

Not acceptable for LeetCode 43

The intention of the problem is to avoid numeric overflow by working at the digit level and returning the correct product as a string for up to 200‑digit inputs.
​
​

This brute‑force approach only works for cases where both numbers and their product fit inside long long.
*/
