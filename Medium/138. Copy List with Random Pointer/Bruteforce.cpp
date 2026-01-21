/*
// Definition for a Node.
*/
#include<bits/stdc++.h>
using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    /*
    ============================================================================
    PROBLEM (Copy List with Random Pointer - Brute Force Version)
    ----------------------------------------------------------------------------
    - Each node has:
        - next   → pointer to next node
        - random → pointer to ANY node in the list (or NULL)
    - Goal: Construct a **deep copy**:
        - New list has new nodes (no node from old list reused).
        - Structure of next and random pointers is the same.

    SIMPLE REAL-LIFE FEEL:
    - Think of a list of people where:
        - next = next person in line
        - random = a friend they randomly point to in the same line
      You want to create a second line with **new people** but with the
      same next and friend (random) relationships.

    APPROACH (Brute Force, O(n^2)):
    1) First pass:
       - Copy all nodes with correct val and next pointers (simple cloning).
       - random pointers are temporarily set to NULL.
    2) Second pass:
       - For each original node:
           - If original.random is not NULL:
               - Find its index in the original list by scanning from head.
               - Then move the same number of steps in the copied list.
               - Set copied.random to that corresponding copied node.

    DRAWBACK / WHY THIS IS BRUTE FORCE AND CAN “FAIL” ON LARGE n:
    - For each node, you scan the list again to find random targets.
    - That is O(n) per node, so total O(n^2) time.
    - On platforms with large constraints (like LeetCode) this can be too slow
      and **Time Limit Exceeded (TLE)** for big lists.
    - Also it's less elegant than map-based or interleaving O(n) solutions.
    ============================================================================
    */

    Node* copyRandomList(Node* head) {
        // Handle empty list directly.
        if (head == NULL) return NULL;

        // -------------------------
        // FIRST PASS: COPY NODES (val + next)
        // -------------------------
        Node* temp = head;

        // Create the head of the copied list.
        Node* copy = new Node(head->val);
        copy->random = NULL;
        copy->next = NULL;

        Node* copytemp = copy;
        temp = temp->next;

        // Clone remaining nodes with correct next chain.
        while (temp != NULL) {
            Node* ptr = new Node(temp->val);
            ptr->random = NULL;        // random will be fixed later
            copytemp->next = ptr;      // link in copied list
            copytemp = ptr;
            temp = temp->next;
        }

        // Ensure last node's pointers are well-defined.
        copytemp->next = NULL;
        copytemp->random = NULL;

        // -------------------------
        // SECOND PASS: FIX RANDOM POINTERS (BRUTE FORCE)
        // -------------------------
        copytemp = copy;
        temp = head;

        while (temp != NULL) {
            if (temp->random == NULL) {
                // If original node's random is NULL, copied node's random is also NULL.
                copytemp->random = NULL;
            } else {
                /*
                ---------------------------------------------------------------
                BRUTE FORCE PART (O(n^2) CAUSE):
                - We need to find which copied node corresponds to temp->random.

                Steps:
                1) Start t1 from original head.
                2) Move t1 forward until t1 == temp->random, counting steps.
                3) Start t2 from copied head.
                4) Move t2 forward the same number of steps.
                5) Set copytemp->random = t2.

                This inner scan (t1 loop + t2 loop) is O(n) for each node.
                Since outer while runs O(n) times, total time is O(n^2).

                WHY THIS CAN “FAIL” IN PRACTICE:
                - For large n (like 10^5 nodes), O(n^2) ≈ 10^10 operations,
                  which is too slow and leads to Time Limit Exceeded (TLE)
                  in competitive programming / interview platforms.
                ---------------------------------------------------------------
                */
                Node* t1 = head;
                Node* t2 = copy;
                int count = 0;

                // Find index of temp->random in original list
                while (t1 != temp->random) {
                    count++;
                    t1 = t1->next;
                }

                // Move t2 same number of steps in copied list
                for (int i = 0; i < count; i++) {
                    t2 = t2->next;
                }

                // Set random of copied node
                copytemp->random = t2;
            }

            copytemp = copytemp->next;
            temp = temp->next;
        }

        return copy;
    }
};

/*
================================================================================
NOTES:
- This code is logically correct for building a deep copy:
  - Every node is newly allocated.
  - next and random pointers in the copy match the structure of the original.
- Main issue is performance: O(n^2) time due to inner scanning loops.
- Optimized approaches achieve O(n) time using:
  - A hashmap from original→copy nodes, or
  - Interweaving original and copied nodes in one list, then splitting.
================================================================================
*/

/*
================================================================================
HELPER FUNCTIONS FOR TESTING
================================================================================
*/

// Create a node
Node* newNode(int v) {
    return new Node(v);
}

// Print list: show val and random->val (or - if NULL)
void printList(Node* head, const string& name) {
    cout << name << ":\n";
    Node* cur = head;
    int idx = 0;
    while (cur) {
        cout << "Node " << idx << " val=" << cur->val << ", random=";
        if (cur->random) cout << cur->random->val;
        else cout << "NULL";
        cout << "\n";
        cur = cur->next;
        idx++;
    }
    cout << "\n";
}

/*
================================================================================
MAIN WITH SMALL DEMO (BRUTE FORCE IS OK FOR SMALL n)
================================================================================
Expected structure:
Original list:
  7 -> 13 -> 11 -> 10 -> 1
Random pointers:
  7.random   = NULL
  13.random  = 7
  11.random  = 1
  10.random  = 11
  1.random   = 7

The copied list should print the same values and random targets, but with
different node addresses (deep copy).
================================================================================
*/

int main() {
    // Build a small test list manually (LeetCode-style example)
    Node* n0 = newNode(7);
    Node* n1 = newNode(13);
    Node* n2 = newNode(11);
    Node* n3 = newNode(10);
    Node* n4 = newNode(1);

    // Set next pointers: 7 -> 13 -> 11 -> 10 -> 1
    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = NULL;

    // Set random pointers
    n0->random = NULL;  // 7.random
    n1->random = n0;    // 13.random  → 7
    n2->random = n4;    // 11.random  → 1
    n3->random = n2;    // 10.random  → 11
    n4->random = n0;    // 1.random   → 7

    Solution sol;
    Node* copied = sol.copyRandomList(n0);

    printList(n0, "Original list");
    printList(copied, "Copied list (brute force)");

    /*
    NOTE ABOUT FAILURE / LIMITATION:
    - For small lists like this, the brute-force O(n^2) approach works fine.
    - For very large lists (n up to 10^5), this double nested scanning for each
      random pointer is too slow (≈ n * n) and can cause Time Limit Exceeded
      on competitive platforms like LeetCode.
    */

    return 0;
}
