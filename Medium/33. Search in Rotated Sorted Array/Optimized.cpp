/*
================================================================================
LEETCODE 704: BINARY SEARCH (LINEAR SCAN VERSION - NOT OPTIMAL)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given SORTED array: [-1,0,3,5,9,12]
- Find target: 9 → return index 4
- Target not found → return -1

REAL-LIFE FEEL:
- Like finding book in sorted library shelf
- CURRENT CODE: Check every book one-by-one (SLOW)
- BETTER: Use binary search (check middle → left/right half)

CURRENT ISSUE: This is LINEAR SEARCH O(n), not BINARY SEARCH O(log n)

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS (Original Linear Version)
--------------------------------------------------------------------------------
*/

#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    /*
    ================================================================
    LINEAR SCAN: Check every element one-by-one
    ------------------------------------------------
    for(int i = 0; i < numsSize; i++)
    - Start from index 0
    - Check nums[0], nums[1], nums[2], ..., nums[numsSize-1]
    - Found target? → return index i immediately
    ================================================================
    */
    for(int i = 0; i < numsSize; i++) {
        /*
        ===================================================
        FOUND TARGET!
        - nums[i] == target → return current index
        - Example: nums=[-1,0,3,5,9,12], target=9
        - i=4: nums[4]=9 == target → return 4
        ===================================================
        */
        if(nums[i] == target) return i;
    }
    
    /*
    ================================================================
    TARGET NOT FOUND
    - Scanned entire array, no match
    - return -1 (standard "not found" signal)
    ================================================================
    */
    return -1;
}

/*
================================================================================
BETTER VERSION: TRUE BINARY SEARCH O(log n)
================================================================================
*/
// UNCOMMENT BELOW FOR OPTIMAL SOLUTION:
/*
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if(nums[mid] == target) return mid;
        else if(nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
*/

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
int main() {
    // Test sorted array
    int nums[] = {-1, 0, 3, 5, 9, 12};
    int numsSize = 6;
    
    // Test cases
    int targets[] = {9, 2, 1};
    
    printf("=== LINEAR SEARCH TEST ===\n");
    printf("Array: [-1, 0, 3, 5, 9, 12]\n\n");
    
    for(int i = 0; i < 3; i++) {
        int result = search(nums, numsSize, targets[i]);
        if(result != -1) {
            printf("Target %d found at index %d\n", targets[i], result);
        } else {
            printf("Target %d NOT FOUND\n", targets[i]);
        }
    }
    
    printf("\n⚠️  NOTE: This is O(n) LINEAR search!\n");
    printf("✅ BINARY search would be O(log n) - much faster!\n");
    
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== LINEAR SEARCH TEST ===
Array: [-1, 0, 3, 5, 9, 12]

Target 9 found at index 4
Target 2 NOT FOUND
Target 1 NOT FOUND

⚠️  NOTE: This is O(n) LINEAR search!
✅ BINARY search would be O(log n) - much faster!

*/