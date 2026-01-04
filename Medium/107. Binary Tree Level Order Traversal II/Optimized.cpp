/*
================================================================================
LEETCODE 107: BINARY TREE LEVEL ORDER TRAVERSAL II (BOTTOM-UP VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- SAME as Level Order Traversal BUT **BOTTOM-UP** order!
- Normal: [[3],[9,20],[15,7]]  (top → bottom)
- Bottom-up: [[15,7],[9,20],[3]]  (bottom → top)

Example Tree:
       3
      / \
     9  20
       /  \
      15   7

Bottom-up Output: [[15,7],[9,20],[3]]

REAL-LIFE FEEL:
- Like reading a book BACKWARDS (last chapter first)
- Or stacking plates: bottom plate added first, top plate last

RULES:
- Collect levels using normal BFS (top→bottom)
- **FINAL STEP:** Reverse entire result (bottom→top)

APPROACH (SIMPLEST POSSIBLE):
1. Do REGULAR level order BFS (exactly same as LeetCode 102)
2. After ALL levels collected: `reverse(ans.begin(), ans.end())`
3. Done! 99% same code as normal level order!

TIME & SPACE:
- TIME: O(n) + O(n) for reverse = O(n)
- SPACE: O(n) for result + O(w) for queue

GENIUS INSIGHT:
- No need to change BFS logic
- Just reverse final answer
- Cleanest solution ever!

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
*/
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
    IDENTICAL TO NORMAL LEVEL ORDER:
    - ans: stores levels top→bottom initially
    - q: BFS queue
    -------------------------------------------------------------------------
    */
    vector<vector<int>> ans;
    queue<TreeNode*> q;
    
    /*
    -------------------------------------------------------------------------
    levelOrderBottom(root): BOTTOM-UP LEVEL ORDER
    
    MAGIC TRICK:
    1. Do EXACT SAME BFS as normal level order
       - Collects: [[3],[9,20],[15,7]] (top→bottom)
    2. SINGLE LINE: reverse(ans.begin(), ans.end())
       - Becomes: [[15,7],[9,20],[3]] (bottom→top)
    3. Return result
    
    99% identical to LeetCode 102!
    Only difference = final reverse()
    -------------------------------------------------------------------------
    */
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        /*
        ================================================================
        BASE CASE: Empty tree (unchanged)
        ================================================================
        */
        if(root == NULL) return {};
        
        /*
        ================================================================
        START BFS: Push root (unchanged)
        ================================================================
        */
        q.push(root);
        
        /*
        ================================================================
        TEMP ARRAY for current level (unchanged)
        ================================================================
        */
        vector<int> arr;
        
        /*
        ================================================================
        NORMAL LEVEL ORDER BFS (IDENTICAL TO LEETCODE 102!)
        - Processes level-by-level, left→right
        - Builds ans = [[3],[9,20],[15,7]] (top→bottom)
        ================================================================
        */
        while(!q.empty()){
            /*
            ===================================================
            Count nodes in current level (unchanged)
            ===================================================
            */
            int level = q.size();
            
            /*
            ===================================================
            Process current level L→R (unchanged)
            ===================================================
            */
            for(int i = 0; i < level; i++){
                TreeNode* current = q.front();
                q.pop();
                
                /*
                Add to current level array (unchanged)
                */
                arr.push_back(current->val);
                
                /*
                Push children for next level (unchanged)
                */
                if(current->left) q.push(current->left);
                if(current->right) q.push(current->right);
            }
            
            /*
            ===================================================
            Save current level (unchanged)
            - ans grows: [ [3] ] → [ [3],[9,20] ] → [ [3],[9,20],[15,7] ]
            ===================================================
            */
            ans.push_back(arr);
            arr.clear();
        }
        
        /*
        ================================================================
        THE ONLY DIFFERENCE: REVERSE FINAL RESULT!
        ------------------------------------------------
        reverse(ans.begin(), ans.end());
        
        Before: [[3],[9,20],[15,7]]  ← top→bottom
        After:  [[15,7],[9,20],[3]]  ← bottom→top ✓
        
        O(n) reverse operation - perfect!
        ================================================================
        */
        reverse(ans.begin(), ans.end());
        
        return ans;
    }
};

/*
================================================================================
SUPER SIMPLE MAIN FUNCTION (3 Test Cases)
================================================================================
*/
TreeNode* buildTree(vector<int>& nums, int& idx) {
    if(idx >= nums.size() || nums[idx] == INT_MIN) {
        idx++;
        return nullptr;
    }
    TreeNode* node = new TreeNode(nums[idx++]);
    node->left = buildTree(nums, idx);
    node->right = buildTree(nums, idx);
    return node;
}

void printResult(vector<vector<int>>& res, string title) {
    cout << title << endl;
    for(auto& level : res) {
        cout << "[";
        for(int i = 0; i < level.size(); i++) {
            cout << level[i];
            if(i < level.size()-1) cout << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

int main() {
    Solution sol;
    
    // Test 1: Standard tree
    vector<int> t1 = {3,9,20,INT_MIN,INT_MIN,15,7};
    int i1 = 0;
    auto r1 = sol.levelOrderBottom(buildTree(t1, i1));
    printResult(r1, "TEST 1 - BOTTOM UP:");
    
    // Test 2: Single node  
    vector<int> t2 = {1};
    int i2 = 0;
    auto r2 = sol.levelOrderBottom(buildTree(t2, i2));
    printResult(r2, "TEST 2 - Single:");
    
    // Test 3: Empty
    auto r3 = sol.levelOrderBottom(nullptr);
    printResult(r3, "TEST 3 - Empty:");
    
    return 0;
}
