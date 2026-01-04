/*
================================================================================
LEETCODE 200: NUMBER OF ISLANDS (DFS FLOOD FILL VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given a 2D grid of '1' (LAND) and '0' (WATER)
- Count SEPARATE ISLANDS (connected '1's form 1 island)
- 8-directional connection: up, down, left, right

Example Grid:
[
  ["1","1","0","0","0"],
  ["1","1","0","0","0"], 
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]

ISLANDS: 3
Island 1: top-left 2x2 block of 1's
Island 2: single '1' at [2,2]  
Island 3: bottom-right two '1's

REAL-LIFE FEEL:
- Like counting separate landmasses on a map
- Or flood fill in MS Paint (click → fills entire connected area)

RULES:
- '1' = land, '0' = water
- Diagonals DON'T count as connected (only 4 directions)
- One island = group of '1's connected horizontally/vertically

APPROACH (DFS + Visited Mark):
1. Create visited matrix (track explored cells)
2. Scan grid cell-by-cell:
   - Found unvisited '1' → NEW ISLAND → DFS flood fill → mark entire island
3. Count islands found

TIME & SPACE: O(n*m) where n=rows, m=cols

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
    dfs(i, j, vis, grid): FLOOD FILL ONE ISLAND
    
    WHAT IT DOES:
    - Marks entire island (all connected '1's) as visited
    - Uses recursion to explore 4 directions from current cell
    
    BASE CASES (STOP CONDITIONS):
    1. Out of bounds (i<0, j<0, i>=n, j>=m)
    2. Already visited (vis[i][j] == true)
    3. Water cell (grid[i][j] != '1')
    
    FLOOD FILL LOGIC:
    1. Mark current cell visited
    2. Recursively visit 4 neighbors:
       - Right: dfs(i, j+1, ...)
       - Left:  dfs(i, j-1, ...)
       - Down:  dfs(i+1, j, ...)
       - Up:    dfs(i-1, j, ...)
    -------------------------------------------------------------------------
    */
    void dfs(int i, int j, vector<vector<bool>> &vis, vector<vector<char>> &grid){
        /*
        ================================================================
        BASE CASE 1-4: STOP FLOOD FILL (don't explore further)
        ------------------------------------------------
        1. i < 0 || j < 0 → LEFT/TOP boundary crossed
        2. i >= grid.size() → BOTTOM boundary crossed  
        3. j >= grid[0].size() → RIGHT boundary crossed
        4. vis[i][j] → ALREADY explored (prevents cycles)
        5. grid[i][j] != '1' → WATER, not land
        
        ALL 5 conditions → return (stop recursion)
        ================================================================
        */
        if(i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size() || 
           vis[i][j] || grid[i][j] != '1')
            return;
        
        /*
        ================================================================
        STEP 1: MARK CURRENT LAND CELL AS VISITED
        ------------------------------------------------
        vis[i][j] = true;
        - Prevents revisiting this cell
        - One cell marked = one step of flood fill complete
        ================================================================
        */
        vis[i][j] = true;
        
        /*
        ================================================================
        STEP 2: FLOOD FILL 4 DIRECTIONS (RECURSION)
        ------------------------------------------------
        Explore all neighboring land cells:
        
        RIGHT: dfs(i, j + 1, ...) → same row, next column
        LEFT:  dfs(i, j - 1, ...) → same row, prev column  
        DOWN:  dfs(i+1, j, ...) → next row, same column
        UP:    dfs(i - 1, j, ...) → prev row, same column
        
        Each recursive call handles ONE direction
        Together they mark ENTIRE connected component (island)
        ================================================================
        */
        dfs(i, j + 1, vis, grid);  // RIGHT
        dfs(i, j - 1, vis, grid);  // LEFT  
        dfs(i+1, j, vis, grid);    // DOWN
        dfs(i - 1, j, vis, grid);  // UP
    }
    
    /*
    -------------------------------------------------------------------------
    numIslands(grid): MAIN FUNCTION - COUNT ISLANDS
    
    ALGORITHM:
    1. Initialize visited matrix (all false)
    2. Scan every cell in grid:
       - Found unvisited '1' → NEW ISLAND!
       - Call dfs() → mark entire island visited
       - islands++ (count this island)
    3. Return total islands found
    -------------------------------------------------------------------------
    */
    int numIslands(vector<vector<char>>& grid) {
        /*
        ================================================================
        INITIALIZE: islands counter and grid dimensions
        ================================================================
        */
        int islands = 0;
        int n = grid.size();        // number of rows
        int m = grid[0].size();     // number of columns
        
        /*
        ================================================================
        CREATE VISITED MATRIX
        ------------------------------------------------
        vis[n][m] all initialized to false
        - Same size as grid
        - Tracks which cells we've explored
        ================================================================
        */
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        
        /*
        ================================================================
        SCAN ENTIRE GRID: Find all islands
        ------------------------------------------------
        for i=0 to n-1 (all rows)
          for j=0 to m-1 (all columns)
        
        CORE LOGIC:
        if(!vis[i][j] && grid[i][j] == '1')
        → Found NEW unvisited land → NEW ISLAND!
        ================================================================
        */
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                /*
                ===================================================
                FOUND NEW ISLAND!
                - !vis[i][j] → never explored this cell
                - grid[i][j] == '1' → it's land
                → Call DFS to mark ENTIRE island visited
                → islands++ (count this island)
                ===================================================
                */
                if(!vis[i][j] && grid[i][j] == '1'){
                    dfs(i, j, vis, grid);  // Flood fill entire island
                    islands++;             // Count this island
                }
            }
        }
        
        return islands;
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
void printGrid(vector<vector<char>>& grid, string title) {
    cout << title << endl;
    for(auto& row : grid) {
        for(char c : row) cout << c << " ";
        cout << endl;
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // Test case: 3 islands
    vector<vector<char>> grid = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    
    printGrid(grid, "Original Grid:");
    cout << "Number of Islands: " << sol.numIslands(grid) << endl;
    cout << "Expected: 3" << endl;
    
    return 0;
}
