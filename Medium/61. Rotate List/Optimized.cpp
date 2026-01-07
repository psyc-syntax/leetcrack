/*
================================================================================
ROTATE LINKED LIST TO THE RIGHT BY k PLACES
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given a singly linked list and an integer k, rotate the list to the right by k places.

Example:
List: 1 → 2 → 3 → 4 → 5,  k = 2
New list: 4 → 5 → 1 → 2 → 3

REAL-LIFE FEEL:
- Imagine people standing in a line.
- Rotating right by k means the last k people move to the front in the same order.

APPROACH:
1. Handle edge cases: empty list or k == 0 → return head directly.
2. Find the length of the list.
3. Reduce k with k = k % len (full rotations do nothing).
4. If k == 0 after modulo, return head.
5. Find the node that will become the new tail at position (len - k - 1).
6. The node after it becomes the new head.
7. Break the list at that point and connect the old tail to the old head.

TIME: O(n) (one pass to get length, one to cut/reconnect)
SPACE: O(1)

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/
#include<bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    // If list is empty or k is 0, no rotation is needed.
    if (!head || k == 0) return head;

    struct ListNode *ptr = head, *left, *final;
    int len = 0;

    /*
    ================================================================
    STEP 1: FIND LENGTH OF THE LIST
    ------------------------------------------------
    Traverse once to count total nodes.
    ================================================================
    */
    while (ptr != NULL) {
        ptr = ptr->next;
        len++;
    }

    /*
    ================================================================
    STEP 2: REDUCE k USING MODULO
    ------------------------------------------------
    Rotating by len, 2*len, etc. gives the same list,
    so we only care about k % len.
    ================================================================
    */
    k = k % len;
    if (k == 0) return head;  // no net rotation

    /*
    ================================================================
    STEP 3: FIND NEW TAIL POSITION
    ------------------------------------------------
    - New head will be at index (len - k).
    - New tail will be at index (len - k - 1).
    Example: len=5, k=2 → place = 5-2 = 3
      indices: 0  1  2  3  4
               1  2  3  4  5
      new head = index 3 (node 4)
      new tail = index 2 (node 3)
    ================================================================
    */
    int place = len - k;
    ptr = head;

    // Move ptr to the node just before the new head (new tail).
    for (int i = 0; i < place - 1; i++) {
        ptr = ptr->next;
    }

    /*
    ================================================================
    STEP 4: BREAK LIST AND RECONNECT
    ------------------------------------------------
    - final = ptr->next is the new head.
    - ptr->next = NULL makes ptr the new tail.
    - Now find the old tail starting from final and connect it to old head.
    ================================================================
    */
    final = ptr->next;     // new head
    ptr->next = NULL;      // break the list
    left = final;

    // Move left to the last node (old tail).
    while (left->next != NULL) left = left->next;

    // Connect old tail to old head.
    left->next = head;

    // Return new head.
    return final;
}

/*
================================================================================
SIMPLE TEST (CONCEPTUAL) — EXPECTED BEHAVIOR
================================================================================
Example:
List: 1 → 2 → 3 → 4 → 5,  k = 2

len = 5
k = 2 % 5 = 2
place = len - k = 3

Traverse to index 2 (0-based: node with value 3):
ptr = node 3
final = ptr->next = node 4 (new head)
ptr->next = NULL → list split:
  left side: 1 → 2 → 3 → NULL
  right side: 4 → 5 → NULL

Find tail of right side: node 5
Connect node 5 -> old head (1):
New list: 4 → 5 → 1 → 2 → 3
*/
