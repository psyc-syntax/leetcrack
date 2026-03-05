#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
ODD-EVEN LINKED LIST — OPTIMIZED IN-PLACE REARRANGEMENT
================================================================================

PROBLEM (LeetCode 328 style):
- Given the head of a singly linked list, group all nodes at **odd indices**
  together followed by all nodes at **even indices**, and return the new head.[web:170][web:177]
- Indexing is 1-based:
  - 1st node → odd
  - 2nd node → even
  - 3rd node → odd, etc.
- The **relative order** inside the odd group and inside the even group
  must remain the same as in the original list
- Required: O(n) time, O(1) extra space.

YOUR APPROACH (OPTIMIZED BUT DIFFERENT FROM TYPICAL TWO-POINTER SOLUTION):
- First pass:
  - Walk to the end of the list to find the **tail** and count the number of nodes.
- Second pass:
  - You know there are `moves = count / 2` even nodes to move.
  - Starting from head (position 1, odd), repeatedly:
    - Take the node at position 2 (current even node).
    - Remove it from its current spot.
    - Append it to the end (tail).
    - Move `temp` to the next odd node.
- This effectively:
  - Keeps odd-positioned nodes in place.
  - Moves all even-positioned nodes to the end, preserving **relative order**
    for both odd and even groups.[web:179]

Time: O(n) (two passes), Space: O(1) extra — so it’s an **optimized in-place** solution.[web:171][web:174]

================================================================================
CODE WITH STEP-BY-STEP EXPLANATION COMMENTS
================================================================================
*/

/**
 * Definition for singly-linked list.
 **/
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *oddEvenList(ListNode *head)
    {
        // If the list has 0, 1, or 2 nodes, it's already in required form
        if (head == NULL || head->next == NULL || head->next->next == NULL)
            return head;

        // Step 1: find the tail and count the number of nodes
        ListNode *tail = head;
        int count = 1;
        while (tail->next != NULL)
        {
            tail = tail->next;
            count++;
        }

        // Step 2: we will move all even-positioned nodes to the end
        // Number of even nodes = floor(count / 2)
        int moves = count / 2;
        ListNode *temp = head; // temp always points to current odd node

        while (moves--)
        {
            // 'even' is the even-positioned node after 'temp'
            ListNode *even = temp->next;

            // Remove 'even' from its position
            temp->next = even->next;

            // Append 'even' at the tail
            tail->next = even;
            tail = even;
            even->next = NULL;

            // Move temp to the next odd node
            temp = temp->next;
        }

        return head;
    }
};

/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================
- Let n be the number of nodes.
- First while loop: walk from head to tail, count nodes → O(n).
- Second while loop: `moves = floor(n/2)` iterations, each does O(1) pointer ops → O(n).
- Total Time: O(n).
- Extra Space: O(1) (only a few pointers and integers).

This satisfies the optimized requirement: **single list, in-place pointer changes, no extra arrays or lists**, and preserves relative order of odd and even nodes.
================================================================================
*/
