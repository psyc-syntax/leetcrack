/*
================================================================================
LEETCODE 17: LETTER COMBINATIONS OF PHONE NUMBER (RECURSIVE BACKTRACKING)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Feel):
- Old phone keypads: '2'=abc, '3'=def, '4'=ghi, etc.
- Input: "23" 
- Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

REAL-LIFE EXAMPLE:
- "23" → 2=a/b/c + 3=d/e/f → 3×3=9 combinations
- Like choosing 1 letter from each group and combining them

LIKE: 
- Shirt color (R/G/B) × Pant color (Black/Blue) = 6 outfits
- Each digit = "group of choices" → multiply all group sizes

APPROACH (Backtracking - Build combination digit-by-digit):
1. pattern map: '2'→"abc", '3'→"def", etc.
2. Recursion: for each digit, try ALL its letters
3. Build string step-by-step: digit0 + digit1 + digit2 + ...

TIME: O(3^N × 4^M) where N=digits with 3 letters, M=digits with 4 letters

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
    CLASS VARIABLES:
    - totalcomb: counter (not used in this version)
    - ans: stores ALL valid combinations
    - pattern: phone keypad mapping
      '2'→"abc" (3 letters)
      '7'→"pqrs" (4 letters) 
      '9'→"wxyz" (4 letters)
    -------------------------------------------------------------------------
    */
    int totalcomb;
    vector<string> ans;
    
    map<char, string> pattern = {
        {'2', "abc"},    // 3 letters
        {'3', "def"},    // 3 letters  
        {'4', "ghi"},    // 3 letters
        {'5', "jkl"},    // 3 letters
        {'6', "mno"},    // 3 letters
        {'7', "pqrs"},   // 4 letters
        {'8', "tuv"},    // 3 letters
        {'9', "wxyz"}    // 4 letters
    };
    
    /*
    -------------------------------------------------------------------------
    findcombinations(digits, currentcombo, index): BUILD COMBINATIONS
    
    CORE LOGIC:
    1. index == digits.size() → finished all digits → SAVE combination
    2. Get letters for current digit: pattern[digits[index]]
    3. Try EACH letter → add to currentcombo → recurse to next digit
    
    LIKE: Choosing outfit piece-by-piece
    - Digit0: try a/b/c
    - Digit1: try d/e/f (for each previous choice)
    - Result: ad,ae,af,bd,be,bf,cd,ce,cf
    -------------------------------------------------------------------------
    */
    void findcombinations(string digits, string currentcombo, int index){
        /*
        ================================================================
        BASE CASE: FINISHED ALL DIGITS!
        ------------------------------------------------
        index == digits.size() → processed every digit
        
        Example: digits="23", index=2
        - currentcombo = "ad","ae","af","bd", etc.
        - SAVE to answer array
        ================================================================
        */
        if(index == digits.size()){
            ans.push_back(currentcombo);
            return;
        }
        
        /*
        ================================================================
        STEP 1: Get letters for CURRENT DIGIT
        ------------------------------------------------
        string currentletters = pattern[digits[index]];
        
        Examples:
        - digits[0]='2' → currentletters="abc"
        - digits[1]='3' → currentletters="def"
        ================================================================
        */
        string currentletters = pattern[digits[index]];
        
        /*
        ================================================================
        STEP 2: TRY EACH LETTER IN CURRENT GROUP (BACKTRACKING)
        ------------------------------------------------
        for(int i = 0; i < currentletters.size(); i++){
            findcombinations(digits, currentcombo + currentletters[i], index + 1);
        }
        
        BACKTRACKING FLOW for "23":
        Level 0 (digit '2'): try 'a','b','c'
           ↓ 'a'
        Level 1 (digit '3'): try 'd','e','f' → "ad","ae","af"
           ↓ 'b'  
        Level 1 (digit '3'): try 'd','e','f' → "bd","be","bf"
           ↓ 'c'
        Level 1 (digit '3'): try 'd','e','f' → "cd","ce","cf"
        ================================================================
        */
        for(int i = 0; i < currentletters.size(); i++){
            findcombinations(digits, currentcombo + currentletters[i], index + 1);
        }
    }
    
    /*
    -------------------------------------------------------------------------
    letterCombinations(digits): MAIN PUBLIC FUNCTION
    - Empty input → return empty vector
    - Start backtracking from index 0, empty string
    -------------------------------------------------------------------------
    */
    vector<string> letterCombinations(string digits) {
        /*
        ================================================================
        EMPTY INPUT CHECK
        ================================================================
        */
        if(digits.size() == 0) return {};
        
        /*
        ================================================================
        START BACKTRACKING
        - digits: input like "23"
        - currentcombo: "" (builds up: "a","ad","ad", etc.)
        - index: 0 (first digit)
        ================================================================
        */
        findcombinations(digits, "", 0);
        return ans;
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
void printCombinations(vector<string>& combos) {
    cout << "All combinations [" << combos.size() << "]: " << endl;
    for(string combo : combos) {
        cout << "\"" << combo << "\" ";
    }
    cout << endl << endl;
}

int main() {
    Solution sol;
    
    // Test case 1: "23"
    string digits1 = "23";
    auto result1 = sol.letterCombinations(digits1);
    printCombinations(result1);
    
    // Test case 2: "2"  
    string digits2 = "2";
    auto result2 = sol.letterCombinations(digits2);
    printCombinations(result2);
    
    // Test case 3: ""
    string digits3 = "";
    auto result3 = sol.letterCombinations(digits3);
    printCombinations(result3);
    
    return 0;
}
/*
Expected output:

All combinations [9]: 
"ad" "ae" "af" "bd" "be" "bf" "cd" "ce" "cf" 

All combinations [3]: 
"a" "b" "c" 

All combinations [0]: 
*/

/*
*/

