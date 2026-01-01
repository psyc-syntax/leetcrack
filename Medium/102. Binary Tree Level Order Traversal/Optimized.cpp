/*
================================================================================
LEETCODE 102: BINARY TREE LEVEL ORDER TRAVERSAL (BFS/QUEUE VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given a BINARY TREE (like a family tree or company hierarchy).
- Goal: Visit nodes LEVEL BY LEVEL and collect their values.
  
Example Tree:
       3
      / \
     9  20
       /  \
      15   7

Output should be:
[[3], [9,20], [15,7]]
- Level 0: [3]
- Level 1: [9,20] 
- Level 2: [15,7]

REAL-LIFE FEEL:
- Think of BFS (Breadth-First Search) like flood water spreading:
  - Water touches level 0 → records 3
  - Water spreads to level 1 → records 9 and 20  
  - Water spreads to level 2 → records 15 and 7
- Or like reading a book page-by-page (not jumping around).

RULES:
- Empty tree → return empty result
- Process nodes strictly level-by-level (left-to-right within each level)
- Each level's values go in ONE array
- All levels' arrays go in final result

APPROACH USED IN THIS CODE (BFS with Queue):
1. If tree is empty → return empty vector
2. Put ROOT in queue (starting point)
3. While queue is NOT empty:
   a) Count nodes IN CURRENT level (queue.size())
   b) Process exactly that many nodes:
      - Take front node, add its value to current level array
      - Push its LEFT child to queue (if exists)
      - Push its RIGHT child to queue (if exists)
   c) After processing all nodes of current level:
      - Add current level array to final answer
      - Clear current level array (prepare for next level)
4. Return final answer

TIME & SPACE:
- TIME: O(n) where n = total nodes (visit each node exactly once)
- SPACE: O(w) where w = max width of tree (queue size)

WHY THIS IS PERFECT SOLUTION:
- Clean, intuitive BFS using queue
- Handles all edge cases (empty tree, single node)
- Optimal time and space complexity

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
**/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    /*
    -------------------------------------------------------------------------
    CLASS-LEVEL VARIABLES (shared across function calls):
    
    ans: vector<vector<int>> 
         - Final result: each inner vector = one level's values
         - Example: [[3],[9,20],[15,7]]
    
    Q: queue<TreeNode*>
       - Queue holds nodes waiting to be processed
       - FIFO (First-In-First-Out): processes level-by-level
       - Why queue? BFS needs to process nodes in order they were discovered
    -------------------------------------------------------------------------
    */
    vector<vector<int>> ans;
    queue<TreeNode*> Q;
    
    /*
    -------------------------------------------------------------------------
    levelOrder(root): MAIN PUBLIC FUNCTION
    
    WHAT IT DOES:
    - Takes tree root as input
    - Returns level-order traversal as vector of vectors
    
    HIGH-LEVEL ALGORITHM (BFS):
    1. Check if tree is empty → return empty result
    2. Start BFS using queue:
       While queue has nodes:
       - Process ALL nodes of current level together
       - Add their values to temporary array
       - Push their children to queue for next level
       - Save current level array to final answer
       - Clear temp array for next level
    3. Return final answer
    
    WHY PROCESS LEVEL-BY-LEVEL:
    - queue.size() tells us exactly how many nodes are in current level
    - We process exactly that many nodes before moving to next level
    - This naturally separates levels
    -------------------------------------------------------------------------
    */
    vector<vector<int>> levelOrder(TreeNode* root) {
        /*
        ================================================================
        BASE CASE: EMPTY TREE
        ------------------------------------------------
        if(root == NULL) → no nodes to process
        return {} → empty vector<vector<int>> (standard for empty result)
        ================================================================
        */
        if(root == NULL) return {};
        
        /*
        ================================================================
        STEP 1: START BFS - Put root in queue
        ------------------------------------------------
        Q.push(root)
        - Queue now contains: [root]
        - This is Level 0 (just the root node)
        - Ready to process first level
        ================================================================
        */
        Q.push(root);
        
        /*
        ================================================================
        STEP 2: Temporary array for current level values
        ------------------------------------------------
        vector<int> arr;
        - Holds values of nodes in CURRENT level only
        - Gets cleared after each level
        - Example: for level 1 → arr = [9, 20]
        ================================================================
        */
        vector<int> arr;
        
        /*
        ================================================================
        MAIN BFS LOOP: while(!Q.empty())
        ------------------------------------------------
        Keep processing until no more nodes left in queue
        
        LOGIC for each iteration:
        1. int level = Q.size()
           - Tells us: "How many nodes are in CURRENT level?"
           - Example: First iteration → level = 1 (just root)
           - Second iteration → level = 2 (nodes 9 and 20)
           
        2. for(int i = 0; i < level; i++)
           - Process EXACTLY 'level' number of nodes
           - This ensures we finish current level before moving to next
           
        3. After inner for-loop:
           - ans.push_back(arr) → save current level to final answer
           - arr.clear() → prepare for next level
        ================================================================
        */
        while(!Q.empty()){
            /*
            ===================================================
            COUNT NODES IN CURRENT LEVEL
            -----------------------------------
            level = Q.size()
            - Captures exact number of nodes for this level
            - Once we start processing children, queue.size() will grow
            - So we save the count FIRST
            - Example: queue=[3], level=1
                     After pushing children: queue=[9,20], but level still=1
            ===================================================
            */
            int level = Q.size();
            
            /*
            ===================================================
            PROCESS ALL NODES OF CURRENT LEVEL
            -----------------------------------
            for(int i = 0; i < level; i++)
            - Loop runs exactly 'level' times
            - Processes every node in current level
            - Each iteration handles ONE node
            ===================================================
            */
            for(int i = 0; i < level; i++){
                /*
                ==============================================
                STEP 3A: GET CURRENT NODE
                ----------------------------------
                TreeNode* current = Q.front();
                Q.pop();
                
                front() → peek at first element (don't remove)
                pop() → remove first element
                
                WHY front() + pop()?
                - Queue is FIFO: first node added = first node processed
                - This maintains left-to-right order within level
                
                Example:
                Queue: [3] → current=3, queue becomes []
                Queue: [9,20] → first i=0: current=9, queue=[20]
                              second i=1: current=20, queue=[]
                ==============================================
                */
                TreeNode* current = Q.front();
                Q.pop();
                
                /*
                ==============================================
                STEP 3B: ADD CURRENT NODE'S VALUE TO LEVEL ARRAY
                ----------------------------------
                arr.push_back(current->val);
                
                Collect all values from current level into ONE array
                Example: processing level 1 → arr = [9], then arr = [9,20]
                ==============================================
                */
                arr.push_back(current->val);
                
                /*
                ==============================================
                STEP 3C: PUSH CHILDREN TO QUEUE (for NEXT level)
                ----------------------------------
                if(current->left)  Q.push(current->left);
                if(current->right) Q.push(current->right);
                
                IMPORTANT: Check if child EXISTS before pushing
                - nullptr children → skip (don't push null pointers)
                - These children will be processed in NEXT iteration
                
                Order matters (left before right):
                - Maintains left-to-right traversal within levels
                
                Example: current=3
                - Push left=9 → queue=[9]
                - Push right=20 → queue=[9,20]
                Next level will process 9 first, then 20 (correct order!)
                ==============================================
                */
                if(current->left)  Q.push(current->left);
                if(current->right) Q.push(current->right);
            } // end of for-loop (finished current level)
            
            /*
            ===================================================
            STEP 4: SAVE CURRENT LEVEL & PREPARE FOR NEXT
            -----------------------------------
            After processing ALL nodes of current level:
            
            ans.push_back(arr)
            - Copy current level array to final result
            - Example: ans = [[3]] after level 0
                     ans = [[3],[9,20]] after level 1
            
            arr.clear()
            - Empty array for next level's values
            - Ensures each level starts fresh
            
            Now queue contains ONLY next level's nodes
            Loop continues if queue not empty
            ===================================================
            */
            ans.push_back(arr);
            arr.clear();
        } // end of while-loop (all levels processed)
        
        /*
        ================================================================
        STEP 5: RETURN FINAL RESULT
        ------------------------------------------------
        All levels processed, queue empty
        ans contains: [[3],[9,20],[15,7]]
        return ans → perfect level-order traversal!
        ================================================================
        */
        return ans;
    }
};
