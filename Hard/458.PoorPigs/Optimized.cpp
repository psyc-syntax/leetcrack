/*
 * OPTIMIZED SOLUTION: Poor Pigs Problem
 * 
 * PROBLEM RECAP:
 * We have some buckets of juice, one of which is poisoned. We need to figure out 
 * which bucket is poisoned using the minimum number of pigs. Each pig can drink from
 * multiple buckets, and we have a limited time window with multiple test rounds.
 * If a pig drinks poison, it will die within minutesToDie minutes.
 * 
 * THE JUICE AND PIGS ANALOGY - OPTIMIZED APPROACH:
 * 
 * Let's use the SAME example: 8 cups of juice, 1 pig, 2 test rounds (60 min to test, 15 min to die)
 * 
 * In the BRUTE FORCE approach, we tested one cup at a time:
 *   Round 1: Test cup 0 → if pig dies, poison is in cup 0; otherwise continue
 *   Round 2: Test cup 1 → if pig dies, poison is in cup 1; otherwise continue
 *   ...
 * This meant we could only test 2 cups with 1 pig and 2 rounds.
 * 
 * WHY BRUTE FORCE WAS INEFFICIENT:
 * The brute force approach wasted information! When a pig survives, we learn:
 *   "The poison is NOT in the cups the pig drank from"
 * But we only tested ONE cup per round, so we only eliminated ONE possibility.
 * 
 * THE OPTIMAL INSIGHT - INFORMATION THEORY:
 * Each pig, over the entire testing period, can exist in (minutesToTest / minutesToDie) + 1 STATES:
 *   - Dies after round 1
 *   - Dies after round 2
 *   - Dies after round 3
 *   - ...
 *   - Dies after round N
 *   - NEVER dies (survives all rounds)
 * 
 * For our example: (60 / 15) + 1 = 4 + 1 = 5 possible states per pig
 * 
 * STEP-BY-STEP WALKTHROUGH WITH 8 CUPS, 1 PIG, 2 TEST ROUNDS:
 * 
 * Our pig can be in 3 states:
 *   State 0: Dies in round 1 (after drinking at minute 0)
 *   State 1: Dies in round 2 (after drinking at minute 15)
 *   State 2: Survives all rounds
 * 
 * Wait, that's only 3 states, but we have 8 cups!
 * The formula says: states_per_pig^number_of_pigs >= buckets
 *                   3^1 = 3, but we need 8!
 * 
 * This means 1 pig with 2 rounds is NOT ENOUGH for 8 cups in the optimal solution either.
 * We'd need at least 2 pigs: 3^2 = 9 >= 8 ✓
 * 
 * Let me redo the example with 4 cups, 1 pig, 2 test rounds:
 * 
 * OPTIMAL STRATEGY FOR 4 CUPS, 1 PIG, 2 TEST ROUNDS:
 * Pig can be in 3 states (dies round 1, dies round 2, or survives)
 * 3^1 = 3, but we need 4... still not enough!
 * 
 * Let me use the PERFECT example: 3 CUPS, 1 PIG, 2 TEST ROUNDS
 * 
 * States: 3 (dies R1, dies R2, survives) → 3^1 = 3 = 3 cups ✓ PERFECT!
 * 
 * Strategy:
 *   Round 1 (minute 0):  Pig drinks from Cup 0
 *   Round 2 (minute 15): Pig drinks from Cup 1
 *   
 * Outcomes:
 *   - Pig dies after round 1 → Poison in Cup 0
 *   - Pig dies after round 2 → Poison in Cup 1  
 *   - Pig survives        → Poison in Cup 2 (the cup we never tested!)
 * 
 * BACK TO OUR ORIGINAL EXAMPLE: 8 CUPS
 * 
 * For 8 cups with (60/15) = 4 test rounds:
 * States per pig = 4 + 1 = 5 (dies R1, R2, R3, R4, or survives)
 * Need: 5^pigs >= 8
 *       5^1 = 5 < 8 ✗
 *       5^2 = 25 >= 8 ✓
 * Answer: 2 pigs needed!
 * 
 * THE MATH - WHY THIS IS OPTIMAL:
 * 
 * Each pig can encode (rounds + 1) states through WHEN it dies (or if it survives).
 * With multiple pigs, we can combine their states:
 *   1 pig:  (rounds + 1)^1 buckets
 *   2 pigs: (rounds + 1)^2 buckets
 *   3 pigs: (rounds + 1)^3 buckets
 *   N pigs: (rounds + 1)^N buckets
 * 
 * We need: (rounds + 1)^N >= buckets
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

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // Edge case: only 1 bucket, no pigs needed
        if (buckets == 1) return 0;
        
        // Calculate number of test rounds possible
        int rounds = minutesToTest / minutesToDie;
        
        // Each pig can be in (rounds + 1) states:
        // - Dies after round 1, 2, 3, ..., rounds
        // - Survives all rounds (never dies)
        int states = rounds + 1;
        
        // We need: states^pigs >= buckets
        // Therefore: pigs >= log(buckets) / log(states)
        // Using ceiling to get minimum integer pigs
        return (int)ceil(log(buckets) / log(states));
    }
};
