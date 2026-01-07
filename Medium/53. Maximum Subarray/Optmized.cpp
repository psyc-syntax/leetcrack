/*
================================================================================
MAXIMUM SUBARRAY SUM (KADANE'S ALGORITHM)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given an array of integers (can be positive, negative, or zero).
- You need to find the **maximum possible sum** of a **contiguous** subarray.

Example:
nums = [-2,1,-3,4,-1,2,1,-5,4]
Best subarray is [4,-1,2,1] with sum 6.
Answer: 6

REAL-LIFE FEEL:
- Imagine daily profit/loss over days.
- You want to find the contiguous period with the highest total profit.

APPROACH (Kadane’s Algorithm):
1. Traverse from left to right, maintaining:
   - sum    = current subarray sum.
   - maxsum = best (maximum) sum seen so far.
2. If current sum becomes ≤ 0, **drop it** and start a new subarray.
3. Keep updating maxsum whenever sum is greater than maxsum.
4. Time: O(n), Space: O(1).

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <stdio.h>

int maxSubArray(int* nums, int numsSize) {
    // Initialize sum and maxsum with first element.
    // This ensures correct behavior when all numbers are negative.
    int sum = nums[0];
    int maxsum = nums[0];

    for (int i = 1; i < numsSize; i++) {
        /*
        ============================================================
        If current sum is ≤ 0, it is not helpful to extend it.
        - A non-positive sum will only reduce or not increase
          any future sum.
        - So we "drop" the previous subarray by resetting sum to 0.
        ============================================================
        */
        if (sum <= 0) sum = 0;

        // Add current element to the running sum.
        sum += nums[i];

        // Update global maximum if current sum is better.
        if (sum > maxsum) maxsum = sum;
    }

    return maxsum;
}

/*
================================================================================
TEST FUNCTION WITH EXAMPLES
================================================================================
*/
int main() {
    int nums1[] = {-2,1,-3,4,-1,2,1,-5,4};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Test 1: maxSubArray = %d   // Expected: 6\n", maxSubArray(nums1, size1));
    // Explanation: best subarray [4,-1,2,1] → 4-1+2+1 = 6

    int nums2[] = {1};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Test 2: maxSubArray = %d   // Expected: 1\n", maxSubArray(nums2, size2));

    int nums3[] = {5,4,-1,7,8};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("Test 3: maxSubArray = %d   // Expected: 23\n", maxSubArray(nums3, size3));
    // Explanation: entire array gives max sum: 5+4-1+7+8 = 23

    int nums4[] = {-3,-2,-5,-1};
    int size4 = sizeof(nums4) / sizeof(nums4[0]);
    printf("Test 4: maxSubArray = %d   // Expected: -1\n", maxSubArray(nums4, size4));
    // Explanation: all negatives → pick the largest (least negative) single element: -1

    return 0;
}

/*
================================================================================
NOTES
================================================================================
- This is Kadane's Algorithm.
- Works correctly even when all elements are negative, because:
  - sum and maxsum start from nums[0], not 0.
- Space usage is constant, only a few integer variables.
*/

/*
================================================================================
EXPECTED OUTPUT
================================================================================
Test 1: maxSubArray = 6   // Expected: 6
Test 2: maxSubArray = 1   // Expected: 1
Test 3: maxSubArray = 23  // Expected: 23
Test 4: maxSubArray = -1  // Expected: -1
*/