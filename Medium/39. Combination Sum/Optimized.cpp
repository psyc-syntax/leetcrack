/*
================================================================================
LEETCO DE 39: COMBINATION SUM (BACKTRACKING WITH UNLIMITED REUSE)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given numbers: [2,3,7], target=7
- Find ALL combinations that sum to 7
- Output: [[2,2,3],[7]]

KEY FEATURE: Same number can be used UNLIMITED times!
- 2+2+3=7 ✓ (2 used twice)
- 7=7 ✓ (7 used once)

REAL-LIFE FEEL:
- Like making exact change $7 using coins [2,3,7]
- Can use same coin multiple times
- Find ALL possible coin combinations

APPROACH (Backtracking - Two Choices Per Number):
1. present: current combination being built
2. ans: all valid combinations found
3. At each step: TWO CHOICES:
   a) USE current number (add it, recurse SAME index)
   b) SKIP to next number (index+1)

TIME: O(N^(T/M+1)) where N=length, T=target, M=min(candidates)

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    -------------------------------------------------------------------------
    GLOBAL VARIABLES:
    - present: CURRENT combination being built [2] → [2,2] → [2,2,3]
    - ans: FINAL result storing all valid combinations
    -------------------------------------------------------------------------
    */
    vector<int> present;
    vector<vector<int>> ans;
    
    /*
    -------------------------------------------------------------------------
    findans(candidates, target, index, sum): BACKTRACKING FUNCTION
    
    PARAMETERS:
    - candidates: array of numbers [2,3,7]
    - target: goal sum (7)
    - index: current position in candidates (0=2, 1=3, 2=7)
    - sum: current sum so far (0→2→4→7)
    
    TWO CHOICES AT EACH STEP:
    1. USE candidates[index] (add it to present)
    2. SKIP to next candidate (index+1)
    -------------------------------------------------------------------------
    */
    void findans(vector<int>& candidates, int target, int index, int sum) {
        /*
        ================================================================
        BASE CASE 1: SUCCESS! Found combination = target
        ------------------------------------------------
        if(sum == target) {
            ans.push_back(present);  // Save COPY of current combination
            return;                  // Stop this path
        }
        Example: sum=7, present=[2,2,3] → ans = { [2,2,3] }
        ================================================================
        */
        if(sum == target) {
            ans.push_back(present);
            return;
        }
        
        /*
        ================================================================
        BASE CASE 2: FAILURE - Prune invalid paths
        ------------------------------------------------
        Two failure conditions:
        1. sum > target → overshot, impossible to recover
        2. index >= candidates.size() → no more numbers to try
        
        Example: sum=8 > target=7 → STOP
        Example: index=3, candidates.size()=3 → STOP  
        ================================================================
        */
        if(sum > target || index >= candidates.size()) {
            return;
        }
        
        /*
        ================================================================
        CHOICE 1: USE CURRENT NUMBER (can reuse same number!)
        ------------------------------------------------
        KEY FEATURE: index stays SAME (unlimited reuse)
        
        STEPS:
        1. present.push_back(candidates[index])  → add number
        2. findans(..., index, sum + candidates[index]) → recurse
        3. present.pop_back() → BACKTRACK (remove for next try)
        
        Example: at index=0 (number=2), sum=2
        - present=[2], recurse with sum=2+2=4
        - present=[2,2], recurse with sum=4+2=6 ✓
        - present=[2,2,3], sum=6+3=9 → prune (>target)
        ================================================================
        */
        present.push_back(candidates[index]);
        findans(candidates, target, index, sum + candidates[index]);
        present.pop_back();  // BACKTRACK
        
        /*
        ================================================================
        CHOICE 2: SKIP CURRENT NUMBER → Try NEXT number
        ------------------------------------------------
        findans(candidates, target, index + 1, sum)
        
        Move to next candidate, same sum
        Example: at index=0 (skip 2), try index=1 (number=3)
        ================================================================
        */
        findans(candidates, target, index + 1, sum);
    }
    
    /*
    -------------------------------------------------------------------------
    combinationSum(): MAIN PUBLIC FUNCTION
    - Sort candidates (optional, helps avoid duplicates in some cases)
    - Start backtracking from index=0, sum=0
    -------------------------------------------------------------------------
    */
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        /*
        ================================================================
        SORT CANDIDATES (optional but good practice)
        - Ensures smaller numbers tried first
        - [2,3,7] instead of [7,3,2]
        ================================================================
        */
        sort(candidates.begin(), candidates.end());
        
        /*
        ================================================================
        START BACKTRACKING
        - index=0: start from first candidate
        - sum=0: nothing chosen yet
        ================================================================
        */
        findans(candidates, target, 0, 0);
        return ans;
    }
};


/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
void printCombinations(vector<vector<int>>& result) {
    cout << "All combinations [" << result.size() << "]:" << endl;
    for(auto& combo : result) {
        cout << "[";
        for(int i = 0; i < combo.size(); i++) {
            cout << combo[i];
            if(i < combo.size() - 1) cout << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // Test case 1: [2,3,7], target=7
    vector<int> candidates1 = {2, 3, 7};
    auto result1 = sol.combinationSum(candidates1, 7);
    printCombinations(result1);
    
    // Test case 2: [2,3,5], target=8  
    vector<int> candidates2 = {2, 3, 5};
    auto result2 = sol.combinationSum(candidates2, 8);
    printCombinations(result2);
    
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
All combinations [2]:
[2 2 3]
[7]

All combinations [3]:
[2 2 2 2]
[2 3 3]
[3 5]

*/

/*
================================================================================
 BACKTRACKING TREE (for, target=7)
================================================================================

index=0(2)     index=1(3)     index=2(7)
  |              |              |
  +--use2(2)     +--use3(5)     +--use7(7)✓SAVE
  |    |         |  
  +--2+use2(4)   +--use3(8)>7✂  +--skip
  |    |              |
  +--2+2+use2(6)  +--skip to 7
       |         /
   +--2+2+use3(9)>7✂

*/