/*
================================================================================
LEETCODE 2: ADD TWO NUMBERS (LINKED LIST) - SIMPLE C IMPLEMENTATION
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- You are given TWO numbers, but each number is stored in a linked list.
- Digits are stored in REVERSE order: 342 is stored as 2 -> 4 -> 3.[web:20]
- Example:
    l1 = 2 -> 4 -> 3  (represents 342)
    l2 = 5 -> 6 -> 4  (represents 465)
    Result should be: 7 -> 0 -> 8 (represents 807)  because 342 + 465 = 807.[web:20]

REAL-LIFE FEEL:
- Imagine two kids writing numbers on paper from RIGHT to LEFT (units first).
- You add them column-by-column (units, tens, hundreds) and carry over when sum ≥ 10.
- This code does the SAME, but using linked lists instead of paper.[web:13]

RULES:
- Each node has ONE digit (0–9).
- Lists are in reverse order (head = least significant digit).[web:20]
- You must RETURN a NEW linked list that stores the SUM in the same reverse format.
- You must HANDLE carry properly (like normal addition on paper).[web:18]

APPROACH USED IN THIS CODE:
1. Use TWO pointers:
   - ptr  → moves on l1
   - temp → moves on l2
2. At each step:
   - Take digit from l1 (if exists).
   - Take digit from l2 (if exists).
   - Add them + previous carry.
3. Create a NEW node with (sum % 10) as digit.
4. If sum ≥ 10 → set carry = 1 for next step (here stored in boolean 'me').
5. Move pointers forward until BOTH lists are fully processed.
6. After loop, if carry still 1 → add extra node with value 1.[web:13][web:18]

TIME & SPACE COMPLEXITY:
- Let n = length of l1, m = length of l2.
- TIME COMPLEXITY: O(max(n, m)) → each node from both lists is visited once.[web:18]
- SPACE COMPLEXITY: O(max(n, m)) → result list uses 1 node per digit, plus maybe 1 carry node.[web:18]

EXAMPLE TRACE (Numbers: 342 + 465):
l1: 2 -> 4 -> 3
l2: 5 -> 6 -> 4

Step 1:
  2 + 5 = 7, carry = 0 → node 7
Step 2:
  4 + 6 = 10, write 0, carry = 1 → node 0
Step 3:
  3 + 4 + carry(1) = 8 → node 8
Result list: 7 -> 0 -> 8  (807)

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Definition of singly-linked list node (given by LeetCode):
*/
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // temp will walk on l2, ptr will walk on l1
    struct ListNode *temp = l2;
    struct ListNode *ptr = l1;

    // prev: last created node
    // tail: tail of result list
    // main: head of result list
    struct ListNode *prev, *tail = NULL, *main = NULL;

    // 'me' works as carry flag:
    // me = false → carry = 0
    // me = true  → carry = 1
    bool me = false;

    // Loop until BOTH lists are completely processed
    // As long as either ptr or temp is not NULL, there is still a digit to add
    while (ptr != NULL || temp != NULL) {
        int sum = 0;  // sum of current digit position

        // Case 1: both lists have a node
        if (ptr != NULL && temp != NULL) {
            sum = ptr->val + temp->val;    // add both digits
        }
        // Case 2: l1 finished, but l2 still has digits
        else if (ptr == NULL) {
            sum = temp->val;               // only l2 digit
        }
        // Case 3: l2 finished, but l1 still has digits
        else {
            sum = ptr->val;                // only l1 digit
        }

        // If there was a carry from previous addition, add +1
        if (me) sum += 1;

        // Reset carry for this step; will set again if needed
        me = false;

        // If sum is 10 or more, we keep last digit and carry 1
        if (sum >= 10) {
            sum %= 10;     // keep only last digit (e.g., 12 → 2)
            me = true;     // set carry for next position
        }

        // Create a NEW node for this digit in the result list
        prev = (struct ListNode*) malloc(sizeof(struct ListNode));
        // In real code, check malloc failure:
        // if (!prev) handle error. Here we assume success except below.
        prev->val = sum;   // store the digit
        prev->next = NULL; // currently last node

        // If this is the FIRST node of the result list
        if (main == NULL) {
            main = prev;   // main points to head
            tail = prev;   // tail also points to this node
        } else {
            // Attach new node at end and move tail
            tail->next = prev;
            tail = prev;
        }

        // Move pointer in l1 if not finished
        if (ptr != NULL) ptr = ptr->next;
        // Move pointer in l2 if not finished
        if (temp != NULL) temp = temp->next;
    }

    // After both lists end, there may still be a carry
    // Example: 999 + 1 → 0 -> 0 -> 0 and carry 1 remaining
    if (me) {
        prev = (struct ListNode*) malloc(sizeof(struct ListNode));
        if (prev == NULL) return NULL;   // simple safety check
        prev->val = 1;                   // extra carry digit
        prev->next = NULL;
        tail->next = prev;               // attach final node
    }

    // Return head of the resulting sum list
    return main;
}

/*
SUMMARY (IN PLAIN WORDS):
- This function simulates normal addition from right to left using linked lists.
- It adds corresponding digits and carry to build a NEW linked list for the sum.
- TIME: O(max(n, m))  → linear in size of longer list.[web:18]
- SPACE: O(max(n, m)) → one new node per output digit.[web:18]
*/
