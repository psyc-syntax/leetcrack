/*
================================================================================
LEETCODE 15: 3SUM PROBLEM - COMPLETE EXPLANATION WITH BACKTRACKING APPROACH
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given an array of numbers like [-1, 0, 1, 2, -1, -2]
- Find ALL unique triplets (3 numbers) that add up to EXACTLY 0
- Example: [-1, 0, 1] because -1 + 0 + 1 = 0
- Real life: 3 friends splitting ₹0 bill - A owes ₹1, B pays ₹1, C pays nothing

RULES:
- No duplicate triplets allowed ([-1,0,1] only once)
- Numbers can be negative, zero, positive
- Return ALL such unique triplets

BRUTEFORCE BACKTRACKING APPROACH (This Code):
1. Like picking 3 fruits from basket - for each fruit: TAKE it or SKIP it
2. Build "path" (current triplet) step by step
3. When path has exactly 3 numbers, check if sum == 0
4. Sort triplet + check if already added (avoid duplicates)
5. Backtrack: undo choices to try other combinations

TIME COMPLEXITY: O(2^n * n) - Exponential! (FAILS on LeetCode for n>30)
SPACE COMPLEXITY: O(n) recursion stack + O(k*n) output storage

WHY THIS FAILS:
- Tries ALL combinations (2^n branches)
- Linear search for duplicates = very slow
- LeetCode timeout for large inputs

BETTER SOLUTION (Two Pointers - O(n²)):
1. Sort array first
2. Fix 1st number, use 2 pointers for remaining 2 numbers
3. Move pointers based on sum >0 or <0
4. Skip duplicates during iteration

EXAMPLE TRACE:
nums = [-1,0,1,2,-1,-4]
Path builds: [-1,0,1] -> sum=0 ✓ (add after sorting)
           [-1,2,-1] -> sum=0 ✓ (add after sorting)
All paths explored systematically!
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> ans;  // FINAL RESULT: All unique triplets that sum to 0
    vector<int> path;         // CURRENT TRIPLET: Building step by step (like shopping cart)

    // CORE LOGIC: Backtracking helper function
    void helper(vector<int> &nums, int index) {
        // BASE CASE 1: Got exactly 3 numbers in path?
        if (path.size() == 3) {
            // LOGIC: Check if these 3 numbers sum to 0
            if (path[0] + path[1] + path[2] == 0) {
                vector<int> temp = path;           // Copy current triplet
                sort(temp.begin(), temp.end());    // Sort: [-1,1,0] -> [-1,0,1] (normalize)
                
                // DUPLICATE CHECK: Linear search if already exists
                if (find(ans.begin(), ans.end(), temp) == ans.end()) {
                    ans.push_back(temp);           // Add only UNIQUE triplets
                }
            }
            return;  // STOP: Don't explore further (depth reached)
        }
        
        // BASE CASE 2: No more numbers left to choose
        if (index >= nums.size()) return;
        
        // CHOICE 1: TAKE current number (add to path)
        path.push_back(nums[index]);     // Add to current triplet
        helper(nums, index + 1);         // Explore NEXT position
        path.pop_back();                 // BACKTRACK: Undo (remove) to try other paths
        
        // CHOICE 2: SKIP current number (don't add)
        helper(nums, index + 1);         // Just move to next position
    }
    
    // MAIN FUNCTION: Entry point
    vector<vector<int>> threeSum(vector<int>& nums) {
        helper(nums, 0);  // Start backtracking from index 0
        return ans;       // Return all unique triplets found
    }
};


int main() {
    Solution sol;
    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> result = sol.threeSum(nums);
    
    cout << "All triplets summing to 0:" << endl;
    for (auto& triplet : result) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "]" << endl;
    }
    // Output:
    // [-1,0,1]
    // [-1,-1,2]
};
