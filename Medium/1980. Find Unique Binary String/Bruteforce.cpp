#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
FIND UNIQUE BINARY STRING — BRUTE FORCE GENERATE-ALL APPROACH
================================================================================

PROBLEM (LeetCode 1980 style):
- You are given `nums`, a vector of n **distinct** binary strings.
- Each string has length n and consists only of '0' and '1'.
- You must return any binary string of length n that does **not** appear in `nums`.

BRUTE FORCE IDEA (WHAT THIS CODE DOES):
1) Generate **all binary strings** of length n:
   - There are \(2^n\) such strings.
   - Build them level by level:
     - Length 1: "0", "1".
     - Length 2: from each previous string, append '0' and '1'.
     - Continue until length n.

2) Insert all given strings `nums[i]` into an `unordered_map` (or set) for O(1) lookup.

3) Iterate through the generated list of all binary strings of length n:
   - For each candidate string, check if it’s **missing** in the map.
   - The first generated string that is not found in `nums` is returned.

This is brute force because we explicitly build all 2ⁿ possibilities and scan them
until we find one that’s not in the input list, instead of using a direct constructive trick.

================================================================================
CODE WITH BRUTE FORCE SOLUTION
================================================================================
*/

class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = (int)nums.size();

        // arr[len] will hold all binary strings of length len
        vector<vector<string>> arr(n + 1);

        // Base: all binary strings of length 1
        arr[1].push_back("0");
        arr[1].push_back("1");

        // Build all binary strings up to length n
        for (int len = 2; len <= n; len++) {
            for (int j = 0; j < (int)arr[len - 1].size(); j++) {
                // From each string of length len-1, append '0' and '1'
                arr[len].push_back(arr[len - 1][j] + "0");
                arr[len].push_back(arr[len - 1][j] + "1");
            }
        }

        // Store all given strings in a hash map for O(1) membership check
        unordered_map<string, bool> mp;
        for (int i = 0; i < n; i++) {
            mp[nums[i]] = true;
        }

        // Among all 2^n binary strings of length n, find the first one not in nums
        for (int i = 0; i < (int)arr[n].size(); i++) {
            const string& candidate = arr[n][i];
            if (mp.find(candidate) == mp.end()) {
                // Found a string of length n that does not appear in nums
                return candidate;
            }
        }

        // In theory, for valid input, you will always find one before this
        return "";
    }
};

/*
================================================================================
TIME AND SPACE COMPLEXITY (BRUTE FORCE)
================================================================================
- Let n = nums.size(), each string length = n.
- Number of all possible binary strings of length n = 2^n.

1) Generating all strings:
   - You generate 2^n strings, each of length n.
   - Time: O(2^n * n).
   - Space: arr[n] stores 2^n strings → O(2^n * n).[web:190]

2) Building the map from nums:
   - There are n input strings of length n.
   - Time: O(n^2), Space: O(n^2).

3) Scanning all 2^n candidates and checking in map:
   - Each lookup O(1) average.
   - Time: O(2^n).

Overall:
- Time: O(2^n * n), exponential in n.
- Space: O(2^n * n).

This matches a **pure brute force** “generate all and check” strategy.
Optimized solutions run in O(n²) or O(n) using diagonalization (flip i-th bit of i-th string) instead of generating all 2^n strings.[web:194][web:198][web:195]
================================================================================
*/