/*
================================================================================
LEETCODE 37: SOLVE SUDOKU (BACKTRACKING VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given 9x9 Sudoku grid (some cells filled with 1-9, some empty '.')
- Fill empty cells so grid follows Sudoku rules
- Rules: No repeat numbers in same ROW, COLUMN, or 3x3 SUBGRID

Example Empty Sudoku:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  // ... etc
]

REAL-LIFE FEEL:
- Like solving Sudoku puzzle in newspaper
- Try number → check if valid → if wrong, ERASE and try next
- "Backtrack" when stuck (go back to previous cell)

APPROACH (BACKTRACKING):
1. itsok(): Check if number is LEGAL in row/col/subgrid
2. solveit(): Try numbers 1-9 in empty cells recursively
3. Backtrack: Wrong number? ERASE and try next number

TIME: O(9^k) where k=empty cells (exponential but practical)

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
    itsok(board, row, col, num): VALIDITY CHECKER
    
    CHECKS 3 SUDOKU RULES:
    1. Same ROW has no duplicate
    2. Same COLUMN has no duplicate  
    3. Same 3x3 SUBGRID has no duplicate
    
    num = 1-9 (integer), converts to char: '1' to '9'
    RETURNS: true if number is LEGAL to place
    -------------------------------------------------------------------------
    */
    bool itsok(vector<vector<char>> &board, int row, int col, int num){
        /*
        ================================================================
        RULE 1: CHECK ENTIRE ROW
        ------------------------------------------------
        for(int i = 0; i < 9; i++)
            if(board[row][i] == num + '0') return false;
            
        Scan columns 0-8 in SAME ROW
        num + '0' converts 1→'1', 2→'2', etc.
        Found duplicate? → INVALID
        ================================================================
        */
        for(int i = 0; i < 9; i++){
            if(board[row][i] == num + '0') return false;
        }
        
        /*
        ================================================================
        RULE 2: CHECK ENTIRE COLUMN
        ------------------------------------------------
        for(int i = 0; i < 9; i++)
            if(board[i][col] == num + '0') return false;
            
        Scan rows 0-8 in SAME COLUMN
        Found duplicate? → INVALID
        ================================================================
        */
        for(int i = 0; i < 9; i++){
            if(board[i][col] == num + '0') return false;
        }
        
        /*
        ================================================================
        RULE 3: CHECK 3x3 SUBGRID
        ------------------------------------------------
        MAGIC FORMULA for subgrid corners:
        rowsr = (row / 3) * 3;  // 0,3,6 depending on row
        colsr = (col / 3) * 3;  // 0,3,6 depending on col
        
        Examples:
        - row=0, col=1 → rowsr=0, colsr=0 → check 0-2,0-2
        - row=4, col=5 → rowsr=3, colsr=3 → check 3-5,3-5  
        - row=8, col=8 → rowsr=6, colsr=6 → check 6-8,6-8
        
        Scan 3x3 block for duplicates
        ================================================================
        */
        int rowsr = (row / 3) * 3;  // Top-left row of subgrid
        int colsr = (col / 3) * 3;  // Top-left col of subgrid
        
        for(int i = rowsr; i < rowsr + 3; i++){
            for(int j = colsr; j < colsr + 3; j++){
                if(board[i][j] == num + '0') return false;
            }
        }
        
        return true;  // All 3 rules passed!
    }
    
    /*
    -------------------------------------------------------------------------
    solveit(board, row, col): BACKTRACKING SOLVER
    
    CORE BACKTRACKING LOGIC:
    1. Track position (row,col) like reading book left→right, top→bottom
    2. Empty cell (.)? → Try numbers 1-9
    3. Valid number? → PLACE it → recurse next cell
    4. Stuck? → BACKTRACK: ERASE → try next number
    5. row==9 → SOLUTION FOUND!
    
    GENIUS: "Try → If fail, undo → Try next" automatically finds solution
    -------------------------------------------------------------------------
    */
    bool solveit(vector<vector<char>> &board, int row, int col){
        /*
        ================================================================
        BASE CASE 1: FINISHED ALL ROWS!
        ------------------------------------------------
        if(row == 9) return true;
        Reached row 9 = entire grid solved!
        ================================================================
        */
        if(row == 9) return true;
        
        /*
        ================================================================
        BASE CASE 2: END OF ROW → Next row
        ------------------------------------------------
        if(col == 9) return solveit(board, row + 1, 0);
        Column 9 = end of current row → go to next row, col 0
        ================================================================
        */
        if(col == 9){
            return solveit(board, row + 1, 0);
        }
        
        /*
        ================================================================
        BASE CASE 3: ALREADY FILLED CELL → Skip
        ------------------------------------------------
        if(board[row][col] != '.') 
            return solveit(board, row, col + 1);
        Already has number → move to next cell
        ================================================================
        */
        if(board[row][col] != '.') {
            return solveit(board, row, col + 1);
        }
        
        /*
        ================================================================
        TRY ALL NUMBERS 1-9 (BACKTRACKING MAGIC)
        ------------------------------------------------
        for(int i = 1; i <= 9; i++){
            if(itsok(...)){
                // TRY: Place number
                board[row][col] = i + '0';
                if(solveit(board, row, col + 1)) return true;  // SOLUTION!
                
                // BACKTRACK: Wrong path → ERASE
                board[row][col] = '.';
            }
        }
        ================================================================
        */
        for(int i = 1; i <= 9; i++){
            if(itsok(board, row, col, i)){
                /*
                TRY NUMBER:
                - Place it on board
                - Recurse to next cell
                - SUCCESS? → return true (bubble up)
                */
                board[row][col] = i + '0';
                if(solveit(board, row, col + 1)) return true;
                
                /*
                BACKTRACK:
                - Previous choice was WRONG
                - ERASE number
                - Try next number i+1
                */
                board[row][col] = '.';
            }
        }
        
        /*
        ================================================================
        NO SOLUTION FROM THIS PATH
        - Tried all 1-9, all failed
        - Return false (backtrack to previous cell)
        ================================================================
        */
        return false;
    }
    
    /*
    -------------------------------------------------------------------------
    solveSudoku(board): PUBLIC ENTRY POINT
    - Starts backtracking from top-left (0,0)
    - Modifies board IN-PLACE
    - LeetCode only cares about RESULT, not return value
    -------------------------------------------------------------------------
    */
    void solveSudoku(vector<vector<char>>& board) {
        solveit(board, 0, 0);
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
void printBoard(vector<vector<char>>& board) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // Classic Sudoku (1 empty cell for demo)
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    
    cout << "BEFORE:" << endl;
    printBoard(board);
    
    sol.solveSudoku(board);
    
    cout << "AFTER (SOLVED):" << endl;
    printBoard(board);
    
    return 0;
}
