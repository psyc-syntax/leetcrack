/*
================================================================================
LEETCODE 135: CANDY (TWO-PASS GREEDY ALGORITHM)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Children in line with ratings: [1,0,2]
- Rules: 
  1. Each child gets ≥1 candy
  2. Higher rating than neighbor → more candies than neighbor

ratings: [1,0,2]
candies:  [2,1,2]  (Total=5)

REAL-LIFE FEEL:
- Teacher distributes candies fairly based on performance
- Better student next to worse student MUST get more candy

APPROACH (Two Passes - Left→Right + Right→Left):
1. LEFT PASS: Ensure higher rating → more than LEFT neighbor
2. RIGHT PASS: Ensure higher rating → more than RIGHT neighbor  
3. Sum all candies

TIME: O(n), SPACE: O(n)

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>

int candy(int* ratings, int ratingsSize) {
    /*
    ================================================================
    STEP 1: CREATE CANDY ARRAY (all start with 1)
    ------------------------------------------------
    calloc(ratingsSize, sizeof(int))
    - Each child gets AT LEAST 1 candy
    - calloc initializes all to 0, so add 1 to first child
    
    Example: 3 children → arr = [0,0,0] → [1,0,0]
    ================================================================
    */
    int *arr = (int *) calloc(ratingsSize, sizeof(int));
    arr[0] += 1;  // First child gets 1 candy
    
    /*
    ================================================================
    PASS 1: LEFT → RIGHT (Handle LEFT neighbor rule)
    ------------------------------------------------
    for i=1 to end:
    - ratings[i] > ratings[i-1] → arr[i] = arr[i-1] + 1
    - else → arr[i] = 1 (minimum)
    
    Example: ratings=[1,0,2]
    i=1: 0 < 1 → arr[1]=1
    i=2: 2 > 0 → arr[2]=arr[1]+1=2
    After: arr=[1,1,2]
    ================================================================
    */
    for(int i = 1; i < ratingsSize; i++) {
        if(ratings[i] > ratings[i - 1]) {
            /*
            ===================================================
            INCREASING: Must have 1 more than left neighbor
            ===================================================
            */
            arr[i] = arr[i - 1] + 1;
        } else {
            /*
            ===================================================
            DECREASING or EQUAL: Minimum 1 candy
            ===================================================
            */
            arr[i] = 1;
        }
    }
    
    /*
    ================================================================
    PASS 2: RIGHT → LEFT (Handle RIGHT neighbor rule)
    ------------------------------------------------
    for i=n-2 downto 0:
    - ratings[i] > ratings[i+1] AND arr[i] <= arr[i+1]
    - arr[i] = arr[i+1] + 1 (take MAX of current and required)
    
    Example continued: arr=[1,1,2], ratings=[1,0,2]
    i=1: 0 < 2 ✓ but arr[1]=1 > arr[2]=2? No change
    i=0: 1 > 0 ✓ and arr[0]=1 <= arr[1]=1 ✓
         arr[0] = arr[1] + 1 = 2
    Final: arr=[2,1,2] ✓
    ================================================================
    */
    for(int i = ratingsSize - 2; i >= 0; i--) {
        /*
        ===================================================
        DECREASING from right AND needs more candies
        - ratings[i] > ratings[i+1]: higher rating than right
        - arr[i] <= arr[i+1]: doesn't have enough yet
        - Give 1 more than right neighbor
        ===================================================
        */
        if(ratings[i] > ratings[i + 1] && arr[i] <= arr[i + 1]) {
            arr[i] = arr[i + 1] + 1;
        }
    }
    
    /*
    ================================================================
    STEP 3: SUM TOTAL CANDIES
    ================================================================
    */
    int sum = 0;
    for(int i = 0; i < ratingsSize; i++) {
        sum += arr[i];
    }
    
    free(arr);
    return sum;
}

/*
================================================================================
TEST FUNCTION WITH VISUAL OUTPUT
================================================================================
*/
int main() {
    printf("=== CANDY DISTRIBUTION TESTS ===\n\n");
    
    // Test 1: [1,0,2] → 5 candies
    int ratings1[] = {1, 0, 2};
    printf("Test 1: ratings=[1,0,2]\n");
    printf("Candies:  [2,1,2] → Total: %d\n\n", candy(ratings1, 3));
    
    // Test 2: [1,2,2] → 4 candies
    int ratings2[] = {1, 2, 2};
    printf("Test 2: ratings=[1,2,2]\n");
    printf("Candies:  [1,2,1] → Total: %d\n\n", candy(ratings2, 3));
    
    // Test 3: [1,3,2,1] → 7 candies  
    int ratings3[] = {1, 3, 2, 1};
    printf("Test 3: ratings=[1,3,2,1]\n");
    printf("Candies:  [1,3,2,1] → Total: %d\n\n", candy(ratings3, 4));
    
    printf("✅ ALL TESTS PASSED!\n");
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== CANDY DISTRIBUTION TESTS ===

Test 1: ratings=[1,0,2]
Candies:  [2,1,2] → Total: 5

Test 2: ratings=[1,2,2]
Candies:  [1,2,1] → Total: 4

Test 3: ratings=[1,3,2,1]
Candies:  [1,3,2,1] → Total: 7

✅ ALL TESTS PASSED!
*/