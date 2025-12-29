/*
 * BRUTEFORCE APPROACH - Poor Pigs Problem
 * 
 * SIMPLE ANALOGY:
 * You and your friends have 8 cups of juice. One cup is poisoned.
 * You have some pigs that can help you find which cup is bad.
 * When a pig drinks poisoned juice, it dies in 15 minutes.
 * You have 15 minutes total to find the bad cup.
 * 
 * HOW THE ENCODING SOLUTION WORKS:
 * This is actually an encoding problem. Think of it like a secret code!
 * 
 * First we figure out the number of attempts we can make.
 * attempts = minutesToTest / minutesToDie
 * In our example: 15 / 15 = 1 attempt
 * 
 * Next we figure out the base for our code.
 * base = attempts + 1
 * In our example: 1 + 1 = 2 (this means we use binary code, like 0 and 1)
 * 
 * With x pigs, you can test up to (base)^x cups.
 * With 3 pigs and base 2, we can test: 2^3 = 8 cups!
 * 
 * HOW TO USE THE CODE:
 * We give each cup a number from 0 to 7.
 * We write each cup number in binary code using 3 bits.
 * Each pig is in charge of one bit position.
 * 
 * Here is our encoding table:
 * Cup 0: 000
 * Cup 1: 001
 * Cup 2: 010
 * Cup 3: 011
 * Cup 4: 100
 * Cup 5: 101
 * Cup 6: 110
 * Cup 7: 111
 * 
 * STEP BY STEP EXAMPLE:
 * Pig 1 checks the first bit (rightmost). Pig 1 drinks from cups where bit 1 is 1.
 * So Pig 1 drinks: Cup 1, Cup 3, Cup 5, Cup 7
 * 
 * Pig 2 checks the second bit (middle). Pig 2 drinks from cups where bit 2 is 1.
 * So Pig 2 drinks: Cup 2, Cup 3, Cup 6, Cup 7
 * 
 * Pig 3 checks the third bit (leftmost). Pig 3 drinks from cups where bit 3 is 1.
 * So Pig 3 drinks: Cup 4, Cup 5, Cup 6, Cup 7
 * 
 * READING THE RESULTS:
 * After 15 minutes, we check which pigs died.
 * If Pig 1 dies, we know bit 1 is 1. If Pig 1 lives, bit 1 is 0.
 * If Pig 2 dies, we know bit 2 is 1. If Pig 2 lives, bit 2 is 0.
 * If Pig 3 dies, we know bit 3 is 1. If Pig 3 lives, bit 3 is 0.
 * 
 * Example: Say Pig 1 and Pig 3 died, but Pig 2 lived.
 * This tells us: bit 1 = 1, bit 2 = 0, bit 3 = 1
 * So the binary code is: 101
 * Cup 5 has the code 101, so Cup 5 is poisoned!
 * 
 * WHY THIS CODE IS WRONG:
 * The code below does not use this smart encoding idea.
 * Instead it just counts some bits in a silly way that does not solve the problem.
 * This code will give wrong answers.
 * The correct formula is: keep adding pigs until (base)^pigs >= buckets
 * 
 * TIME COMPLEXITY: O(n) where n is the number of buckets
 * The code loops through all numbers from 1 to n-1.
 * For each number it checks one bit.
 * 
 * SPACE COMPLEXITY: O(1)
 * The code only uses a few variables and a small bitset.
 * The space does not grow with the input size.
 * 
 * VERDICT: This approach is wrong and will not solve the problem correctly.
 */
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int n = buckets;
        int bits = floor(log2(n)) + 1;
        int count = 0;
        for(int i = 1; i < n; i++){
            const int bandwidth = 10;
            bitset<bandwidth> binary(i);
            if(binary[0] == 1) count ++;
        }
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
