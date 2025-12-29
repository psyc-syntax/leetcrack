 /* We need: (rounds + 1)^N >= buckets
 * Solving for N: N >= log(buckets) / log(rounds + 1)
 * Therefore: N = ceil(log(buckets) / log(rounds + 1))
 * 
 * This is LOGARITHMIC time complexity!
 * 
 * COMPARISON TO BRUTE FORCE:
 * 
 * Example: 8 buckets, 4 test rounds
 * 
 * BRUTE FORCE:
 *   - Tests one bucket per round per pig
 *   - 1 pig can test 4 buckets in 4 rounds
 *   - For 8 buckets: need 8/4 = 2 pigs
 *   - Formula: ceil(buckets / rounds)
 *   - Time Complexity: O(1) - simple division
 * 
 * OPTIMIZED:
 *   - Uses each pig's death timing as information
 *   - 1 pig with 4 rounds has 5 states → can distinguish 5 buckets
 *   - For 8 buckets: need ceil(log(8) / log(5)) = ceil(1.29) = 2 pigs  
 *   - Formula: ceil(log(buckets) / log(rounds + 1))
 *   - Time Complexity: O(log buckets) - logarithmic calculation
 * 
 * In this case, both give 2 pigs, but let's try 1000 buckets, 4 rounds:
 * 
 * BRUTE FORCE: ceil(1000 / 4) = 250 pigs (!!)
 * OPTIMIZED: ceil(log(1000) / log(5)) = ceil(4.29) = 5 pigs
 * 
 * OPTIMIZED IS DRAMATICALLY BETTER!
 * 
 * WHY THE OPTIMIZED METHOD WINS:
 * 
 * 1. Information Efficiency: Every pig provides log(rounds+1) bits of information
 *    through WHEN it dies, not just IF it dies.
 * 
 * 2. Exponential Growth: N pigs can distinguish (rounds+1)^N buckets, not just N*rounds.
 * 
 * 3. Real-world Parallel: This is like binary search vs linear search!
 *    - Brute force = linear search (check one at a time)
 *    - Optimized = multi-dimensional search (use all available information)
 * 
 * THE CODE IMPLEMENTATION:
 * 
 * We simply calculate: ceil(log(buckets) / log(rounds + 1))
 * 
 * Using C++ logarithms:
 *   log(buckets) / log(rounds + 1) = log_base_(rounds+1) (buckets)
 * Then ceil() gives us the minimum integer pigs needed.
 * 
 * Edge case: if buckets = 1, no testing needed → 0 pigs
 */

#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // STEP 1: Calculate the number of rounds available
        // ------------------------------------------------
        // T represents how many complete test rounds we can perform
        // Example: If we have 60 minutes to test and each pig takes 15 minutes to die,
        //          then T = 60/15 = 4 rounds
        // This is crucial because it determines how many "states" each pig can have
        int T = minutesToTest / minutesToDie;
        
        // STEP 2: Initialize the pig counter
        // ----------------------------------
        // We start with 0 pigs and increment until we have enough to distinguish all buckets
        // Think of this as: "How many dimensions do we need for our search space?"
        int count = 0;
        
        // STEP 3: Find minimum pigs needed using exponential growth
        // ---------------------------------------------------------
        // KEY INSIGHT: Each pig can be in (T+1) different states:
        //   - Dies in round 1, 2, 3, ..., T, or doesn't die at all
        //   - That's T+1 total states per pig!
        // 
        // With N pigs, we can distinguish (T+1)^N different scenarios
        // Example: 2 pigs with 4 rounds each → (4+1)^2 = 5^2 = 25 buckets!
        // 
        // The formula: (T+1)^count >= buckets
        // We keep incrementing count until this inequality is satisfied
        // 
        // WHY THIS WORKS (Real-world analogy):
        //   - Imagine each pig as a digit in a base-(T+1) number system
        //   - Pig 1 can represent positions 0 to T (dies at different rounds or not at all)
        //   - Pig 2 can represent positions 0 to T (independent of Pig 1)
        //   - Together they can represent (T+1) × (T+1) = (T+1)^2 unique combinations
        //   - This is like how 2 decimal digits can represent 10^2 = 100 numbers (0-99)
        while(pow((T+ 1) , count) < buckets){
            // Not enough pigs yet! Each additional pig multiplies our capacity by (T+1)
            // Example progression with T=4:
            //   0 pigs: 5^0 = 1 bucket
            //   1 pig:  5^1 = 5 buckets  
            //   2 pigs: 5^2 = 25 buckets
            //   3 pigs: 5^3 = 125 buckets
            //   4 pigs: 5^4 = 625 buckets
            count++;
        }
        
        // STEP 4: Return the minimum number of pigs needed
        // ------------------------------------------------
        // At this point, (T+1)^count >= buckets
        // This means 'count' pigs are sufficient to identify the poisoned bucket
        // 
        // EDGE CASE HANDLING (automatically covered):
        //   - If buckets = 1: pow(T+1, 0) = 1 >= 1, so count stays 0 (no pigs needed!)
        //   - This makes sense: if there's only 1 bucket, it must be the poisoned one
        // 
        // EFFICIENCY NOTE:
        //   - Time Complexity: O(log_base_(T+1) buckets) ≈ O(log buckets)
        //   - Space Complexity: O(1)
        //   - This is exponentially better than brute force O(buckets/rounds)
        return count;
    }

    int main() {
    Solution sol;

    // Test Case 1
    // buckets = 1000, die = 15, test = 60
    // States = (60/15) + 1 = 5
    // 5^p = 1000 -> p = 5
    cout << "Test 1 (1000, 15, 60): " << sol.poorPigs(1000, 15, 60) << " pigs" << endl;

    // Test Case 2
    cout << "Test 2 (4, 15, 15): " << sol.poorPigs(4, 15, 15) << " pigs" << endl;

    // Test Case 3
    cout << "Test 3 (4, 15, 30): " << sol.poorPigs(4, 15, 30) << " pigs" << endl;

    return 0;
}
};
