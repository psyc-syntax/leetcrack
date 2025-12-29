/*
================================================================================
LEETCODE 237: DELETE NODE IN A LINKED LIST - TRICKY 1-PASS SOLUTION
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given a node in singly linked list (NOT head)
- DELETE this node (but you DON'T have head pointer!)
- Real life: Train compartments connected: A→B→C→D
- You're at compartment B, need to remove B (but can't access A!)
- TRICK: Copy C's data to B, then remove C instead!

LIST STRUCTURE:
A(1) → B(2) → C(3) → D(4)
       ^ You are here! Delete node B

RULES:
- You get ONLY the node to delete (no head, no prev)
- List has AT LEAST 2 nodes (node->next exists)
- Change node values/connections to "delete" it

MAGIC TRICK APPROACH (This Code):
1. Copy NEXT node's VALUE to current node
2. Skip NEXT node (connect to node after next)
3. Now original node "disappears" (has next node's data + connection)

TIME COMPLEXITY: O(1) - Perfect! (Single operation)
SPACE COMPLEXITY: O(1) - No extra space

WHY THIS IS GENIUS:
- No need for head/previous pointer
- Works in 1 pass, constant time
- Changes structure without actually "deleting"
- Interview favorite question!

EXAMPLE TRACE:
Original: 1→2→3→4    node points to 2
Step1: Copy 3 to node → 1→3→3→4  
Step2: Skip 3rd node → 1→3→4 ✓ (2 is gone!)
REAL MAGIC!

REAL-LIFE VISUAL:
Train: A→B→C→D
You're at B:
1. Copy C's cargo to B → A→[C's cargo]→C→D
2. Unhook C → A→[C's cargo]→D ✓ B gone!
*/

#include <bits/stdc++.h>
using namespace std;

// structure of the linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
}; 


class Solution {
public:
    // MAGIC FUNCTION: Delete node without head/prev pointer
    void deleteNode(ListNode* node) {
        // SAFETY CHECK: Empty node or last node? Do nothing
        if (node == NULL || node->next == NULL) return;
        
        // TRICK 1: Copy NEXT node's VALUE to current node
        node->val = node->next->val;      // B gets C's value: 2→3
        
        // TRICK 2: Skip NEXT node (connect to node after next)
        node->next = node->next->next;    // B→D (skips C)
        
        // DONE! Original node "disappears" but list intact
        // No actual memory delete needed (LeetCode handles)
    }
};

/*
TEST THE CODE (Simulation):
void printList(ListNode* head) {
    while(head) {
        cout << head->val << "→";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    // Create: 1→2→3→4
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    
    cout << "Before: "; printList(head);  // 1→2→3→4→NULL
    
    Solution sol;
    sol.deleteNode(head->next);  // Delete node 2
    
    cout << "After:  "; printList(head);  // 1→3→4→NULL ✓
    
    // Clean up memory (not needed for LeetCode)
}
OUTPUT:
Before: 1→2→3→4→NULL
After:  1→3→4→NULL

PERFECT SOLUTION! O(1) time, O(1) space - LeetCode Accepted ✅
Handles ALL valid cases perfectly!
WARNING: Don't call on last node (problem constraint)!
*/
