#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
MAXIMUM TWIN SUM OF A LINKED LIST — OPTIMIZED O(n) TIME, O(1) EXTRA SPACE
================================================================================

PROBLEM (LeetCode 2130 style):
- You are given the head of a **singly linked list** of even length n.
- Nodes are 0-indexed in the original statement, but conceptually:
  - Node 0 pairs with node n-1
  - Node 1 pairs with node n-2
  - ...
- The **twin sum** of a node is: value at position i + value at position (n-1-i).
- You must return the **maximum twin sum** among all such pairs.[web:203][web:200][web:208]

NAIVE IDEA (for comparison):
- Copy all values into an array.
- Then use two pointers `i = 0`, `j = n-1`, compute sums and track max.
- Time: O(n), but needs O(n) extra space.[web:200][web:208]

--------------------------------------------------------------------------------
OPTIMIZED IDEA (WHAT THIS CODE DOES)
--------------------------------------------------------------------------------
Goal: O(n) time and **O(1) extra space**.

Steps:
1) **Count length n**:
   - Traverse the list once with pointer `h2` to count nodes.[web:200]

2) **Find start of second half**:
   - Move `h2` forward by `n / 2` steps.
   - Now:
     - `h1` points to head (start of first half).
     - `h2` points to first node of the second half.[web:200][web:204]

3) **Reverse the second half in-place**:
   - Use standard iterative reverse:
     - `prev`, `curr`, `next`.
   - After reversing:
     - `h2` (reassigned to `prev`) points to the **new head of reversed second half**, which aligns with the “twin” of `head`.[web:200][web:204][web:207]

4) **Scan both halves together to compute twin sums**:
   - For i from 0 to `n/2 - 1`:
     - Sum `h1->val + h2->val`.
     - Update `maxsum` with the maximum twin sum seen.
     - Move both pointers one step forward.[web:200][web:202][web:208]

5) Return `maxsum`.

This avoids extra arrays or stacks, modifying only the list pointers.

================================================================================
CODE WITH STEP-BY-STEP COMMENTS
================================================================================
*/


 /* Definition for singly-linked list.*/
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


class Solution {
public:
    int pairSum(ListNode* head) {
        ListNode* h1 = head;
        ListNode* h2 = head;

        // Edge cases: empty or single-node list (LeetCode guarantees even length >= 2,
        // but we keep these for safety/completeness).
        if (head == NULL) return 0;
        if (head->next == NULL) return head->val;

        // Step 1: count number of nodes n
        int n = 0;
        while (h2 != NULL) {
            h2 = h2->next;
            n++;
        }

        // Step 2: move h2 to the start of the second half (n/2 steps from head)
        h2 = head;
        for (int i = 0; i < n / 2; i++) {
            h2 = h2->next;
        }

        // Step 3: reverse the second half starting from h2
        ListNode* prev = NULL;
        ListNode* curr = h2;

        while (curr != NULL) {
            ListNode* curr_next = curr->next; // store next
            curr->next = prev;                // reverse link
            prev = curr;                      // move prev forward
            curr = curr_next;                 // move curr forward
        }

        // Now 'prev' is the head of the reversed second half
        h2 = prev;

        // Step 4: compute twin sums using h1 (from start) and h2 (from reversed second half)
        int maxsum = 0;
        for (int i = 0; i < n / 2; i++) {
            int sum = h1->val + h2->val;
            maxsum = max(maxsum, sum);
            h1 = h1->next;
            h2 = h2->next;
        }

        return maxsum;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
- Let n be the number of nodes.
- Counting length: one pass → O(n).
- Moving to middle: O(n/2) → O(n).
- Reversing second half: at most n/2 nodes → O(n).
- Final twin-sum pass: n/2 iterations → O(n).

Total Time: O(n).  
Extra Space: O(1), since we only use a few pointers and integers.

This is the standard optimized in-place solution for “Maximum Twin Sum of a Linked List”.
================================================================================
*/