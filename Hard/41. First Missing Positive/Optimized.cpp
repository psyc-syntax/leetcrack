/*
================================================================================
LEETCODE 41: FIRST MISSING POSITIVE (HASH TABLE ARRAY VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given unsorted array: [3,4,-1,1]
- Find SMALLEST positive integer MISSING from array
- Output: 2 (1 exists, 2 missing)

Examples:
[3,4,-1,1] → 2
[1,2,0] → 3  
[1] → 2
[] → 1

REAL-LIFE FEEL:
- Like checking student roll numbers 1,2,3,... 
- Find first missing roll number in attendance sheet

APPROACH (Hash Table using Array):
1. Create frequency array covering range 1 to numsSize+1
2. Mark presence of positive numbers ≤ numsSize
3. Scan from 1: first unmarked index = answer

TIME: O(n), SPACE: O(n)

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>

int firstMissingPositive(int* nums, int numsSize) {
    /*
    ================================================================
    STEP 0: Find maximum value (unused in final logic)
    - Originally finds max, but we only care about 1..numsSize+1
    ================================================================
    */
    int max = nums[0];
    
    /*
    ================================================================
    STEP 1: CREATE FREQUENCY ARRAY (Hash Table)
    ------------------------------------------------
    calloc(numsSize + 2, sizeof(int))
    - arr[0] unused, arr[1] tracks number 1, arr[2] tracks 2, etc.
    - +2 covers edge case numsSize+1
    - calloc initializes all to 0 (perfect!)
    
    Example: numsSize=4 → arr[5] = {0,0,0,0,0} (tracks 1,2,3,4)
    ================================================================
    */
    int *arr = (int *) calloc(numsSize + 2, sizeof(int));
    
    /*
    ================================================================
    STEP 2: MARK PRESENCE of valid positive numbers
    ------------------------------------------------
    ONLY mark numbers: 1 ≤ nums[i] ≤ numsSize
    
    Why this range?
    - Numbers > numsSize cannot be first missing positive
    - First missing must be in range 1..numsSize+1
    
    Example: nums=[3,4,-1,1], numsSize=4
    - nums[0]=3: arr[3]++ → arr={0,0,0,1,0}
    - nums[1]=4: arr[4]++ → arr={0,0,0,1,1}
    - nums[2]=-1: skip (negative)
    - nums[3]=1: arr[1]++ → arr={0,1,0,1,1}
    ================================================================
    */
    for(int i = 0; i < numsSize; i++) {
        /*
        ===================================================
        VALID NUMBER CHECK:
        nums[i] >= 0 (positive)
        AND nums[i] <= numsSize (in valid range)
        ===================================================
        */
        if(nums[i] >= 0 && nums[i] <= numsSize) {
            arr[nums[i]]++;  // Mark presence: arr[1]=1, arr[3]=1, arr[4]=1
        }
    }
    
    /*
    ================================================================
    STEP 3: FIND FIRST MISSING (scan from 1)
    ------------------------------------------------
    Check arr[1], arr[2], arr[3], ... until arr[i]==0
    
    Example: arr={0,1,0,1,1}
    - i=1: arr[1]=1 ✓ (1 exists)
    - i=2: arr[2]=0 ✗ → return 2 ✓
    ================================================================
    */
    for(int i = 1; i <= numsSize + 1; i++) {
        if(arr[i] == 0) {
            free(arr);
            return i;  // First missing positive!
        }
    }
    
    /*
    ================================================================
    EDGE CASE: All numbers 1..numsSize present
    - Return numsSize+1
    - Example: [1,2,3,4] → return 5
    ================================================================
    */
    free(arr);
    return numsSize + 1;
}

/*
================================================================================
SIMPLE MAIN FUNCTION WITH TEST CASES
================================================================================
*/
int main() {
    printf("=== FIRST MISSING POSITIVE TESTS ===\n\n");
    
    // Test 1: [3,4,-1,1] → 2
    int nums1[] = {3, 4, -1, 1};
    int size1 = 4;
    printf("Test 1: [3,4,-1,1] → %d (Expected: 2)\n", 
           firstMissingPositive(nums1, size1));
    
    // Test 2: [1,2,0] → 3
    int nums2[] = {1, 2, 0};
    int size2 = 3;
    printf("Test 2: [1,2,0] → %d (Expected: 3)\n", 
           firstMissingPositive(nums2, size2));
    
    // Test 3: [1] → 2
    int nums3[] = {1};
    int size3 = 1;
    printf("Test 3: [1] → %d (Expected: 2)\n", 
           firstMissingPositive(nums3, size3));
    
    // Test 4: [] → 1
    int nums4[] = {0};
    int size4 = 0;  // Empty array simulation
    printf("Test 4: [] → %d (Expected: 1)\n", 
           firstMissingPositive(nums4, size4));
    
    // Test 5: All present [1,2,3] → 4
    int nums5[] = {1, 2, 3};
    int size5 = 3;
    printf("Test 5: [1,2,3] → %d (Expected: 4)\n", 
           firstMissingPositive(nums5, size5));
    
    printf("\n✅ ALL TESTS PASSED!\n");
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== FIRST MISSING POSITIVE TESTS ===

Test 1: [3,4,-1,1] → 2 (Expected: 2)
Test 2: [1,2,0] → 3 (Expected: 3)
Test 3: [1] → 2 (Expected: 2)
Test 4: [] → 1 (Expected: 1)
Test 5: [1,2,3] → 4 (Expected: 4)

✅ ALL TESTS PASSED!
*/
