/*
================================================================================
LEETCODE 994: ROTTING ORANGES (BFS MULTI-SOURCE + TIME TRACKING)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Grid cells: 0=empty, 1=fresh orange, 2=rotten orange
- Rotten oranges SPREAD to adjacent fresh oranges every MINUTE
- Find minimum MINUTES until ALL oranges rot (or return -1 if impossible)

Example Grid t=0:
[
  [2,1,1],
  [1,1,0], 
  [0,1,1]
]
2 = rotten (starting point)

t=1: Rotten spreads UP, RIGHT:
[
  [2,2,1],
  [1,2,0], 
  [0,1,1]
]

t=2: Continue spreading...
Final time = 4 minutes

REAL-LIFE FEEL:
- Like virus spreading in a room
- All infected people spread simultaneously each minute
- Track maximum infection time

RULES:
- 4 directions only (no diagonals)
- All rotten oranges spread AT SAME TIME (one minute = one layer)
- Return -1 if fresh oranges remain unrotted

APPROACH (MULTI-SOURCE BFS):
1. Find ALL rotten oranges → put in queue with time=0
2. BFS: Each minute, ALL rotten oranges infect neighbors
3. Track maximum time
4. Check if any fresh oranges left → return -1

TIME & SPACE: O(n*m)

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
    orangesRotting(grid): Find minutes to rot all oranges
    
    CORE ALGORITHM (Multi-Source BFS):
    1. Find ALL starting rotten oranges → queue with time=0
    2. BFS level-by-level = each level = 1 minute
    3. Track max time seen
    4. Final check: any fresh oranges left? → -1
    
    GENIUS INSIGHT:
    - Put ALL rotten oranges in queue AT START (multi-source)
    - First BFS layer = minute 1, second = minute 2, etc.
    -------------------------------------------------------------------------
    */
    int orangesRotting(vector<vector<int>>& grid) {
        /*
        ================================================================
        INITIALIZE: answer, dimensions, visited matrix
        ================================================================
        */
        int ans = 0;                           // max minutes seen
        int n = grid.size();                   // rows
        int m = grid[0].size();                // cols
        vector<vector<bool>> vis(n, vector<bool>(m, false));  // track visited
        
        /*
        ================================================================
        STEP 1: Find ALL ROTTEN ORANGES → Multi-source queue
        ------------------------------------------------
        queue<pair<pair<int,int>, int>> q
        - First pair: {row, col} = position
        - Second int: time elapsed
        
        Push ALL rotten oranges with time=0:
        - All start rotting AT SAME TIME
        - vis[i][j]=true prevents reinfection
        ================================================================
        */
        queue<pair<pair<int, int>, int>> q;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 2){           // Found rotten orange
                    q.push({{i, j}, 0});       // Push with time=0
                    vis[i][j] = true;          // Mark as processed
                }
            }
        }
        
        /*
        ================================================================
        STEP 2: BFS - Simulate rotting process minute-by-minute
        ================================================================
        */
        while(!q.empty()){
            /*
            ===================================================
            GET CURRENT ROTTEN ORANGE + ITS TIME
            -----------------------------------
            q.front().first.first  = row i
            q.front().first.second = col j  
            q.front().second       = time taken to reach here
            ===================================================
            */
            int i = q.front().first.first;
            int j = q.front().first.second;
            int time = q.front().second;
            q.pop();
            
            /*
            ===================================================
            UPDATE MAX TIME
            - Every rotten orange updates global max time
            - ans = max(ans, time)
            ===================================================
            */
            ans = max(ans, time);
            
            /*
            ===================================================
            STEP 3: INFECT 4 NEIGHBORS (if fresh oranges)
            
            For each direction, check 3 conditions:
            1. Within bounds
            2. Not visited  
            3. Fresh orange (grid[nr][nc] == 1)
            
            If YES → infect: push to queue with time+1, mark visited
            ===================================================
            */
            
            // UP
            if(i - 1 >= 0 && !vis[i - 1][j] && grid[i - 1][j] == 1){
                q.push({{i - 1, j}, time+1});    // Infect UP, time+1
                vis[i - 1][j] = true;            // Mark as now-rotten
            }
            
            // DOWN  
            if(i + 1 < n && !vis[i + 1][j] && grid[i + 1][j] == 1){
                q.push({{i + 1, j}, time+1});    // Infect DOWN, time+1
                vis[i + 1][j] = true;
            }
            
            // LEFT
            if(j - 1 >= 0 && !vis[i][j - 1] && grid[i][j - 1] == 1){
                q.push({{i, j - 1}, time+1});    // Infect LEFT, time+1
                vis[i][j - 1] = true;
            }
            
            // RIGHT
            if(j + 1 < m && !vis[i][j + 1] && grid[i][j + 1] == 1){
                q.push({{i, j + 1}, time+1});    // Infect RIGHT, time+1
                vis[i][j + 1] = true;
            }
        }
        
        /*
        ================================================================
        STEP 4: FINAL CHECK - Any fresh oranges left unrotted?
        ------------------------------------------------
        Scan entire grid:
        - Found grid[i][j]==1 AND !vis[i][j] → unreachable fresh orange
        - Return -1 (impossible to rot all)
        ================================================================
        */
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 1 && !vis[i][j]) 
                    return -1;  // Fresh orange remains!
            }
        }
        
        return ans;  // All oranges rotten! Return max time
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
void printGrid(vector<vector<int>>& grid, string title) {
    cout << title << endl;
    for(auto& row : grid) {
        for(int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // Test case: 4 minutes to rot all
    vector<vector<int>> grid = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };
    
    printGrid(grid, "Initial Grid:");
    int result = sol.orangesRotting(grid);
    cout << "Minutes to rot all: " << result << endl;
    cout << "Expected: 4" << endl;
    
    return 0;
}
