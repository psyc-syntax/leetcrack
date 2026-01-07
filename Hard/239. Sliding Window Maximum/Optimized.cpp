/*
================================================================================
LEETCODE 239: SLIDING WINDOW MAXIMUM (DEQUE MONOTONIC QUEUE VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given array: [1,3,-1,-3,5,3,6,7], k=3
- Find MAXIMUM in every window of size k
- Output: [3,3,5,5,6,7]

Windows:
[1,3,-1] → 3
 [3,-1,-3] → 3  
  [-1,-3,5] → 5
   [-3,5,3] → 5
    [5,3,6] → 6
     [3,6,7] → 7

REAL-LIFE FEEL:
- Like monitoring temperature every 3 hours
- Always know MAX temperature in last 3 hours

APPROACH (Deque - Monotonic Queue):
- Deque stores INDEXES in DECREASING order of values
- Front = MAX of current window
- Remove outdated (out of window) and useless (smaller) elements

TIME: O(n), SPACE: O(k)

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
    KEY DATA STRUCTURES:
    - dq: deque<int> stores INDEXES (not values)
          - Front: MAX index of current window
          - Back: Smallest values (potential future max)
    - res: stores max of each window
    -------------------------------------------------------------------------
    */
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        
        deque<int> dq;           // Stores indices
        vector<int> res;         // Result array
        
        /*
        ================================================================
        STEP 1: PROCESS FIRST WINDOW [0, k-1]
        ------------------------------------------------
        Goal: dq contains indices i where nums[dq.front()] = MAX
        
        MONOTONIC DEQUE PROPERTY:
        nums[dq[0]] > nums[dq[1]] > ... > nums[dq.back()]
        
        Example: nums=[1,3,-1], k=3
        i=0: dq=[0] (1)
        i=1: 3>1 → pop 0 → dq=[1] (3)
        i=2: -1<3 → dq=[1,2] (3,-1)
        dq.front()=1 → nums[1]=3 ✓ MAX!
        ================================================================
        */
        for(int i = 0; i < k; i++) {
            /*
            ===================================================
            REMOVE USELESS ELEMENTS FROM BACK
            - While back element ≤ current → pop_back()
            - Smaller elements can't be max while larger exists
            ===================================================
            */
            while(!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            
            /*
            ===================================================
            ADD CURRENT INDEX
            ===================================================
            */
            dq.push_back(i);
        }
        
        /*
        ================================================================
        STEP 2: SLIDE WINDOW (i = k to n-1)
        ------------------------------------------------
        For each new window position i:
        1. ADD previous window's max to result
        2. REMOVE outdated indices (out of window)
        3. REMOVE useless elements from back  
        4. ADD new index i
        ================================================================
        */
        for(int i = k; i < nums.size(); i++) {
            /*
            ===================================================
            1. SAVE MAX of PREVIOUS window
            - dq.front() = index of maximum in [i-k, i-1]
            ===================================================
            */
            res.push_back(nums[dq.front()]);
            
            /*
            ===================================================
            2. REMOVE OUTDATED indices (out of current window)
            - Current window: [i-k+1, i]
            - If dq.front() ≤ i-k → outside window → remove
            ===================================================
            */
            while(!dq.empty() && dq.front() <= i - k)
                dq.pop_front();
            
            /*
            ===================================================
            3. REMOVE USELESS from back (same as first window)
            ===================================================
            */
            while(!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            
            /*
            ===================================================
            4. ADD new index i
            ===================================================
            */
            dq.push_back(i);
        }
        
        /*
        ================================================================
        STEP 3: LAST WINDOW
        - After loop, dq.front() = max of final window [n-k, n-1]
        ================================================================
        */
        res.push_back(nums[dq.front()]);
        return res;
    }
};

/*
================================================================================
TEST FUNCTION WITH VISUAL OUTPUT
================================================================================
*/
int main() {
    Solution sol;
    
    // Test case: [1,3,-1,-3,5,3,6,7], k=3
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    
    cout << "Input: nums = [1,3,-1,-3,5,3,6,7], k = 3" << endl;
    cout << "Windows & Maximums:" << endl;
    
    auto result = sol.maxSlidingWindow(nums, k);
    
    cout << "Output: [";
    for(int i = 0; i < result.size(); i++) {
        cout << result[i];
        if(i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;
    
    // VISUAL REPRESENTATION
    cout << "Visual:" << endl;
    cout << "nums:  ";
    for(int x : nums) cout << x << " ";
    cout << endl;
    cout << "max:   ";
    for(int x : result) cout << x << " ";
    cout << endl;
    
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Windows & Maximums:
Output: [3, 3, 5, 5, 6, 7]

Visual:
nums:  1 3 -1 -3 5 3 6 7 
max:     3  3  5  5 6 7 

*/