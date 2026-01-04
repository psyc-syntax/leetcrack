/*
================================================================================
LEETCODE 117: POPULATING NEXT RIGHT POINTERS IN PERFECT BINARY TREE
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given a PERFECT binary tree (all levels completely filled)
- Add "next" pointers to connect NODES AT SAME LEVEL
- next points to RIGHT neighbor at same level

Example Tree BEFORE:
       1
     /   \
    2     3
   / \   / \
  4  5 6   7
  next=next=next=next=NULL

Example Tree AFTER (next arrows):
       1 → NULL
     /   \
    2 → 3 → NULL
   / \   / \
  4→5→6→7→NULL

REAL-LIFE FEEL:
- Like seating arrangement in a classroom:
  - Each row (level) - students hold hands with neighbors
  - Student 1(row1) ↔ Student 2(row1) ↔ Student 3(row1)

RULES:
- Perfect binary tree (no missing nodes)
- Connect left→right neighbors at each level
- Rightmost node → next = NULL
- Root's next = NULL

APPROACH (BFS Level Order + Next Connection):
1. Use BFS queue (same as level order)
2. At each level, for i=0 to level-2: current.next = next node in queue
3. Rightmost node (i == level-1): current.next = NULL
4. Push children normally

TIME & SPACE: O(n) time, O(w) space where w=width

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/*
Definition for a Node.
*/
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    /*
    -------------------------------------------------------------------------
    q: BFS queue (same as level order traversal)
    -------------------------------------------------------------------------
    */
    queue<Node*> q;
    
    /*
    -------------------------------------------------------------------------
    connect(root): Connects same-level nodes with next pointers
    
    CORE LOGIC:
    1. BFS level-by-level (exactly like level order)
    2. SPECIAL PART: Connect current node → next node in SAME LEVEL
       - For nodes 0 to level-2: current.next = q.front() (next sibling)
       - Last node (level-1): current.next = NULL
    -------------------------------------------------------------------------
    */
    Node* connect(Node* root) {
        /*
        ================================================================
        BASE CASE: Empty tree
        ================================================================
        */
        if(root == NULL) return root;  // Note: return root (not {} for Node*)
        
        /*
        ================================================================
        START BFS: Push root (Level 0)
        ================================================================
        */
        q.push(root);
        
        /*
        ================================================================
        MAIN BFS LOOP: Process level by level
        ================================================================
        */
        while(!q.empty()){
            /*
            ===================================================
            Count nodes in current level
            ===================================================
            */
            int level = q.size();
            
            /*
            ===================================================
            Process ALL nodes in current level
            - Connect siblings LEFT→RIGHT
            ===================================================
            */
            for(int i = 0; i < level; i++){
                /*
                ==============================================
                Get current node
                ==============================================
                */
                Node* current = q.front();
                q.pop();
                
                /*
                ==============================================
                MAGIC: Connect to RIGHT SIBLING!
                ------------------------------------------------
                if(i < level - 1) 
                    current->next = q.front();
                else 
                    current->next = NULL;
                
                KEY INSIGHT:
                - i goes 0,1,2,...,level-1
                - When i < level-1 → NOT last node → has right sibling
                - q.front() = next node in queue = RIGHT SIBLING!
                - When i == level-1 → LAST node → next = NULL
                
                Example Level 1: nodes [2,3]
                - i=0 (node 2): 0 < 1 → 2->next = q.front()=3 ✓
                - i=1 (node 3): 1 == 1 → 3->next = NULL ✓
                ==============================================
                */
                if(i < level - 1) 
                    current->next = q.front();
                else 
                    current->next = NULL;
                
                /*
                ==============================================
                Push children for NEXT level (unchanged)
                - Left child first, then right child
                - Maintains left→right order for next level
                ==============================================
                */
                if(current->left) q.push(current->left);
                if(current->right) q.push(current->right);
            }
        }
        
        /*
        ================================================================
        Return original root (structure modified in-place)
        ================================================================
        */
        return root;
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
Node* buildPerfectTree(vector<int>& vals, int& idx) {
    if(idx >= vals.size()) return NULL;
    Node* node = new Node(vals[idx++]);
    node->left = buildPerfectTree(vals, idx);
    node->right = buildPerfectTree(vals, idx);
    return node;
}

void printTreeConnections(Node* root) {
    cout << "Tree with Next Pointers:" << endl;
    Node* levelStart = root;
    while(levelStart) {
        Node* curr = levelStart;
        cout << "Level: ";
        while(curr) {
            cout << curr->val;
            if(curr->next) {
                cout << " → " << curr->next->val;
                curr = curr->next;
            } else {
                cout << " → NULL";
                break;
            }
        }
        cout << endl;
        levelStart = levelStart->left ? levelStart->left : NULL;
    }
}

int main() {
    Solution sol;
    
    // Perfect binary tree: 1,2,3,4,5,6,7
    vector<int> vals = {1,2,3,4,5,6,7};
    int idx = 0;
    Node* root = buildPerfectTree(vals, idx);
    
    cout << "BEFORE connecting:" << endl;
    printTreeConnections(root);
    
    root = sol.connect(root);
    
    cout << "\nAFTER connecting:" << endl;
    printTreeConnections(root);
    
    cout << "\n Perfect! Each level connected left→right → NULL" << endl;
    return 0;
}
