/*
================================================================================
LEETCODE 24: SWAP NODES IN PAIRS (RECURSIVE VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given linked list: 1→2→3→4→5
- Swap EVERY TWO adjacent nodes: 2→1→4→3→5

Input:  1→2→3→4→5
Output: 2→1→4→3→5

REAL-LIFE FEEL:
- Like swapping partners in a dance line:
  - (1,2) swap → 2→1
  - (3,4) swap → 4→3  
  - 5 stays alone

RULES:
- Swap positions of pairs: (1st,2nd) → (2nd,1st)
- If odd number of nodes, last node stays unchanged
- Return new head

APPROACH (RECURSIVE):
- Base case: 0 or 1 node → return as-is
- Swap first TWO nodes
- Recursively swap rest of list
- Connect: new_first→new_second→recursive_result

TIME: O(n), SPACE: O(n) recursion depth

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

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

struct ListNode* swapPairs(struct ListNode* head) {
    /*
    -------------------------------------------------------------------------
    POINTERS EXPLANATION:
    ptr   = first node of current pair (1)
    temp1 = second node of current pair (2)  
    temp2 = third node (start of next pair) (3)
    dum   = new head after swap (2)
    -------------------------------------------------------------------------
    */
    struct ListNode *ptr = head, *temp1, *temp2, *dum;
    
    /*
    ================================================================
    BASE CASE: 0 or 1 node → Nothing to swap
    ------------------------------------------------
    Examples:
    - head=NULL → return NULL
    - head=1→NULL → return 1→NULL (single node)
    ================================================================
    */
    if(head == NULL || head->next == NULL) return head;
    
    /*
    ================================================================
    STEP 1: IDENTIFY THE PAIR TO SWAP
    ------------------------------------------------
    Original: ptr(1)→temp1(2)→temp2(3)→...
    
    ptr    = head = 1
    temp1  = ptr->next = 2  
    temp2  = temp1->next = 3
    dum    = temp1 = 2 (will be new head)
    ================================================================
    */
    temp1 = ptr->next;       // temp1 = node 2
    temp2 = temp1->next;     // temp2 = node 3 (next pair start)
    dum = temp1;             // dum = node 2 (new head)
    
    /*
    ================================================================
    STEP 2: SWAP FIRST TWO NODES
    ------------------------------------------------
    BEFORE: 1→2→3→4→...
           ptr→temp1→temp2
    
    SWAP:
    1. temp1->next = ptr  → 2→1
    2. ptr->next = swapPairs(temp2) → 1→(recursive result)
    
    AFTER: 2→1→(swapped rest)
    ================================================================
    */
    temp1->next = ptr;           // 2→1
    ptr->next = swapPairs(temp2); // 1→(recursive result)
    
    /*
    ================================================================
    RETURN NEW HEAD (node 2)
    - dum = temp1 = node 2
    - Entire swapped pair returned
    ================================================================
    */
    return dum;
}

/*
================================================================================
VISUAL STEP-BY-STEP (Input: 1→2→3→4→5)
================================================================================
Original: 1→2→3→4→5

FIRST CALL (nodes 1,2,3):
ptr=1, temp1=2, temp2=3
1. dum = 2
2. 2→1 
3. 1→swapPairs(3→4→5)
   ↓ RECURSE

SECOND CALL (nodes 3,4,5):  
ptr=3, temp1=4, temp2=5
1. dum = 4  
2. 4→3
3. 3→swapPairs(5)
   ↓ RECURSE

THIRD CALL (node 5):
Base case → return 5

BACK UP:
3→5
2→1→4→3→5 ✓

Result: 2→1→4→3→5
*/

/*
================================================================================
HELPER FUNCTIONS + SIMPLE MAIN
================================================================================
*/
struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* createList(int arr[], int size) {
    if(size == 0) return NULL;
    struct ListNode* head = createNode(arr[0]);
    struct ListNode* curr = head;
    for(int i = 1; i < size; i++) {
        curr->next = createNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

void printList(struct ListNode* head) {
    struct ListNode* curr = head;
    printf("List: ");
    while(curr) {
        printf("%d", curr->val);
        if(curr->next) printf(" → ");
        curr = curr->next;
    }
    printf(" → NULL\n");
}

void freeList(struct ListNode* head) {
    while(head) {
        struct ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Test 1: Even length (1→2→3→4)
    int arr1[] = {1, 2, 3, 4};
    struct ListNode* head1 = createList(arr1, 4);
    
    printf("=== TEST 1: Even length ===\n");
    printList(head1);              // 1→2→3→4
    head1 = swapPairs(head1);
    printList(head1);              // 2→1→4→3
    
    // Test 2: Odd length (1→2→3)
    int arr2[] = {1, 2, 3};
    struct ListNode* head2 = createList(arr2, 3);
    
    printf("\n=== TEST 2: Odd length ===\n");
    printList(head2);              // 1→2→3
    head2 = swapPairs(head2);
    printList(head2);              // 2→1→3
    
    freeList(head1);
    freeList(head2);
    
    printf("\n✅ PERFECT PAIR SWAPPING!\n");
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== TEST 1: Even length ===
List: 1 → 2 → 3 → 4 → NULL
List: 2 → 1 → 4 → 3 → NULL

=== TEST 2: Odd length ===
List: 1 → 2 → 3 → NULL
List: 2 → 1 → 3 → NULL

✅ PERFECT PAIR SWAPPING!

*/
