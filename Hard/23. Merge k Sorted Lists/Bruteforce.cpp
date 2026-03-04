#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
MERGE K SORTED LINKED LISTS — BRUTE FORCE SELECTION APPROACH
================================================================================

PROBLEM (LeetCode 23 style):
- You are given `k` linked lists, each individually **sorted** in non-decreasing order.
- You must merge all of them into **one sorted linked list** and return its head.

REAL-LIFE FEEL:
- Think of `k` sorted queues of numbers.
- At every step, you look at the **front** of each queue, pick the smallest,
  and append it to your result queue.
- Repeat this until all queues are empty.

--------------------------------------------------------------------------------
BRUTE FORCE SELECTION IDEA (WHAT THIS CODE DOES)
--------------------------------------------------------------------------------
1) Maintain a pointer `lists[i]` to the **current node** of each list.
2) Repeatedly:
   - Scan through all `k` lists.
   - Among all `lists[i]` that are not null, choose the one with the **smallest value**.
   - Append that node to the result list.
   - Move that list’s pointer `lists[pos]` forward (to `lists[pos]->next`).

3) If during a full scan you find **no non-null nodes** (all lists finished),
   you stop and return the merged list.

This is a classic brute force “always scan all heads to find the minimum” approach.
It does not use a heap or divide & conquer, so each pick costs O(k).

================================================================================
CODE WITH BRUTE FORCE APPROACH
================================================================================
*/

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
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode *head = NULL; // head of the merged list
        ListNode *tail = NULL; // tail of the merged list

        while (true)
        {
            int minval = INT_MAX;
            int pos = -1; // index of list having current smallest node

            // Step 1: find the smallest current node among all lists
            for (int i = 0; i < (int)lists.size(); i++)
            {
                if (lists[i] != NULL && lists[i]->val < minval)
                {
                    minval = lists[i]->val;
                    pos = i;
                }
            }

            // If pos stayed -1, it means all lists[i] are NULL → all nodes used
            if (pos == -1)
                break;

            // Step 2: pick this smallest node and advance that list's pointer
            ListNode *small = lists[pos];  // smallest current node
            lists[pos] = lists[pos]->next; // move pointer forward

            // Step 3: append `small` to our result list
            if (head == NULL)
            {
                // First node in the merged list
                head = small;
                tail = small;
            }
            else
            {
                // Attach to the end and move tail
                tail->next = small;
                tail = tail->next;
            }
        }

        // Make sure the last node points to NULL
        if (tail)
            tail->next = NULL;

        return head;
    }
};

/*
================================================================================
TIME AND SPACE COMPLEXITY (BRUTE FORCE)
================================================================================
Let:
- k = number of linked lists.
- N = total number of nodes across all lists (sum of lengths).

- For each picked node:
  - We scan all k lists to find the minimum head → O(k).
- We repeat this process for all N nodes.
- Total time: O(N * k).

- Extra space:
  - We only use a few pointer variables and reuse existing nodes.
  - Space: O(1) auxiliary (not counting input/output lists.

This is the **brute force selection** solution.
Optimized solutions use:
- A **min-heap / priority_queue** of size k to get O(N log k) time, or
- **Divide and conquer** pairwise merge to also get O(N log k).
================================================================================
*/
