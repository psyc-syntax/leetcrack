#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
PROCESS STRING WITH SPECIAL OPERATIONS — OPTIMIZED SINGLE PASS
================================================================================

PROBLEM:
Given a string s, process it **from left to right** with these rules:
- Normal character (letter, digit, etc.): append it to the result.
- '*' : delete the **last** character in the result (if any), like a backspace.
- '#' : duplicate the current result (result = result + result).
- '%' : reverse the current result in-place.

You must return the final string after applying all operations.

KEY IDEA (WHY THIS IS OPTIMIZED):
- We use a single string `result` and process s **in one pass**.
- Operations mutate `result` in-place:
  - `push_back` / `pop_back` for normal chars and '*'.
  - `result += result` for duplication.
  - `reverse(result.begin(), result.end())` for reversing.
- No extra data structures like stacks or extra arrays are needed.
- Time is O(total work of operations); in terms of implementation, one simple loop.

================================================================================
CODE WITH STEP-BY-STEP COMMENTS
================================================================================
*/

class Solution {
public:
    string processStr(string s) {
        string result;  // will store the processed string as we go

        for (char c : s) {
            if (c == '*') {
                // '*' means backspace: remove the last character if it exists
                if (!result.empty())
                    result.pop_back();      // erase last character
            }
            else if (c == '#') {
                // '#' means duplicate the current result
                // result becomes: old_result + old_result
                result += result;
            }
            else if (c == '%') {
                // '%' means reverse the current result in-place
                reverse(result.begin(), result.end());
            }
            else {
                // Any normal character: append to result
                result.push_back(c);
            }
        }

        return result;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
Let:
- n = s.length().
- R = final length of result (it grows and shrinks due to '#', '*').

- We traverse s once → O(n) iterations.
- Each operation:
  - Normal char / '*' : O(1) via push_back / pop_back.
  - '#' : `result += result` copies current result → O(|result|).
  - '%' : `reverse(result.begin(), result.end())` → O(|result|).

Worst-case:
- Many '#' operations can cause result to grow exponentially, so in strict
  theory, time is proportional to the total size of all intermediate results.
- Practically, for bounded input sizes, this is still the natural **one-pass,
  in-place** optimized approach: single accumulator string, no extra containers.

Space:
- O(R) for the result string, where R is the maximum size it reaches.
- No additional data structures beyond a few variables.

================================================================================
*/