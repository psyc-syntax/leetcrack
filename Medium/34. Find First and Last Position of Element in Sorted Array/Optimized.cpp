/*
================================================================================
LEETCODE 34: FIND FIRST AND LAST POSITION OF ELEMENT IN SORTED ARRAY
(LINEAR SCAN VERSION - WORKS BUT NOT OPTIMAL O(n))
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given SORTED array: [5,7,7,8,8,10]
- Find FIRST and LAST position of target
- target=8 → return [3,4] (first 8 at index 3, last 8 at index 4)
- target=6 → return [-1,-1] (not found)

REAL-LIFE FEEL:
- Like finding all seats with number "8" in sorted row
- First scan finds leftmost 8, keeps updating rightmost 8

CURRENT APPROACH: Linear scan O(n) - simple but slow for large arrays
OPTIMAL: Binary search O(log n) - much faster

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    /*
    ================================================================
    STEP 1: CREATE RESULT ARRAY
    ------------------------------------------------
    int *arr = (int *) malloc(2 * sizeof(int));
    - Allocates space for [first, last] positions
    - Initialize both to -1 (not found)
    ================================================================
    */
    int *arr = (int *) malloc(2 * sizeof(int));
    arr[0] = -1;  // First occurrence (-1 = not found)
    arr[1] = -1;  // Last occurrence (-1 = not found)
    
    /*
    ================================================================
    STEP 2: LINEAR SCAN - Find all occurrences of target
    ------------------------------------------------
    for(int i = 0; i < numsSize; i++)
    - Check every element one-by-one
    - When found:
      * FIRST time: arr[0] = i (set first occurrence)
      * EVERY time: arr[1] = i (always update last occurrence)
    ================================================================
    */
    for(int i = 0; i < numsSize; i++) {
        /*
        ===================================================
        FOUND TARGET AT INDEX i
        ------------------------------------------------
        Example: nums=[5,7,7,8,8,10], target=8
        
        i=0: 5!=8 → continue
        i=1: 7!=8 → continue  
        i=2: 7!=8 → continue
        i=3: 8==8 → FIRST: arr[0]=3, LAST: arr[1]=3
        i=4: 8==8 → FIRST: arr[0]=3, LAST: arr[1]=4 ✓
        i=5:10!=8 → continue
        
        Result: [3,4] ✓
        ===================================================
        */
        if(nums[i] == target) {
            if(arr[0] == -1) arr[0] = i;  // FIRST occurrence
            arr[1] = i;                     // LAST occurrence (always update)
        }
    }
    
    /*
    ================================================================
    STEP 3: SET RETURN SIZE & RETURN RESULT
    ------------------------------------------------
    *returnSize = 2;  // Always return array of size 2
    return arr;       // [first, last] or [-1,-1]
    ================================================================
    */
    *returnSize = 2;
    return arr;  
}

/*
================================================================================
OPTIMAL BINARY SEARCH VERSION O(log n) - RECOMMENDED
================================================================================
*/
/*
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int left = 0, right = numsSize - 1;
    int first = -1, last = -1;
    
    // Find leftmost (first true where nums[i] >= target)
    while(left <= right) {
        int mid = left + (right - left)/2;
        if(nums[mid] >= target) right = mid - 1;
        else left = mid + 1;
        if(nums[left] == target) first = left;
    }
    
    // Find rightmost (last true where nums[i] <= target)  
    left = 0; right = numsSize - 1;
    while(left <= right) {
        int mid = left + (right - left)/2;
        if(nums[mid] <= target) left = mid + 1;
        else right = mid - 1;
        if(nums[right] == target) last = right;
    }
    
    int* arr = malloc(2 * sizeof(int));
    arr[0] = first; arr[1] = last;
    *returnSize = 2;
    return arr;
}
*/

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
void printRange(int* arr, int returnSize) {
    printf("[%d, %d]\n", arr[0], arr[1]);
}

int main() {
    // Test case 1: Multiple occurrences
    int nums1[] = {5,7,7,8,8,10};
    int numsSize1 = 6;
    int returnSize1;
    
    printf("=== TEST 1: Multiple 8s ===\n");
    printf("Array: [5,7,7,8,8,10]\n");
    int* result1 = searchRange(nums1, numsSize1, 8, &returnSize1);
    printf("Target 8: "); printRange(result1, returnSize1);  // [3,4]
    
    // Test case 2: Not found
    int* result2 = searchRange(nums1, numsSize1, 6, &returnSize1);
    printf("Target 6: "); printRange(result2, returnSize1);  // [-1,-1]
    
    // Test case 3: Single occurrence  
    int nums2[] = {1};
    int numsSize2 = 1;
    int* result3 = searchRange(nums2, numsSize2, 1, &returnSize1);
    printf("\n=== TEST 3: Single ===\n");
    printf("Array: [1]\n");
    printf("Target 1: "); printRange(result3, returnSize1);  // [0,0]
    
    free(result1);
    free(result2); 
    free(result3);
    
    printf("\n⚠️  NOTE: This is O(n) linear scan!\n");
    printf("✅ BINARY search version is O(log n) - much faster!\n");
    
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== TEST 1: Multiple 8s ===
Array: [5,7,7,8,8,10]
Target 8: [3, 4]
Target 6: [-1, -1]

=== TEST 3: Single ===
Array: [1]
Target 1: [0, 0]

⚠️  NOTE: This is O(n) linear scan!
✅ BINARY search version is O(log n) - much faster!

*/
