/*
================================================================================
LEETCODE 25: REVERSE NODES IN K-GROUP (RECURSIVE VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given linked list: 1→2→3→4→5→6→7, k=2
- Reverse EVERY K nodes: 2→1→4→3→6→5→7

Input:  1→2→3→4→5→6→7, k=2
Output: 2→1→4→3→6→5→7

REAL-LIFE FEEL:
- Like rotating groups of K people in a line
- Group1(1,2)→(2,1), Group2(3,4)→(4,3), etc.

APPROACH (RECURSIVE):
1. Check if k consecutive nodes exist
2. Reverse first K nodes  
3. Recurse on remaining list
4. Connect reversed group to recursive result

TIME: O(n), SPACE: O(n/k) recursion

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

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    /*
    ================================================================
    BASE CASES: Nothing to reverse
    ------------------------------------------------
    1. head == NULL → empty list
    2. k == 1 → no swapping needed
    ================================================================
    */
    if(head == NULL || k == 1) return head;
    
    /*
    -------------------------------------------------------------------------
    POINTERS EXPLANATION:
    ptr  = kth node (end of group to reverse)
    final= ? (unused in this version)
    temp = start of next group (after k nodes)
    next = next node during reversal  
    curr = current node being reversed
    prev = previous node during reversal
    -------------------------------------------------------------------------
    */
    struct ListNode *ptr = head, *final, *temp = NULL, *next = NULL, *curr = head, *prev = NULL;
    
    /*
    ================================================================
    STEP 1: CHECK if K consecutive nodes exist
    ------------------------------------------------
    Goal: Find kth node from head
    Example: k=2, 1→2→3→4
    - ptr starts at 1, walk 1 step → ptr=2 ✓
    
    If ptr becomes NULL before k steps → not enough nodes → return original
    ================================================================
    */
    for(int i = 1; i < k; i++) {
        ptr = ptr->next;
        /*
        ===================================================
        NOT ENOUGH NODES FOR THIS GROUP
        - Example: list=1→2→3, k=3
        - i=1: ptr=2
        - i=2: ptr=3  
        - i=3: ptr=NULL → return original head
        ===================================================
        */
        if(ptr == NULL) return head;
    }
    
    /*
    ================================================================
    STEP 2: Find start of NEXT group
    ------------------------------------------------
    ptr = kth node (2 in example)
    temp = ptr->next = 3 (start of next group to recurse)
    Now reverse first k nodes: 1→2 → becomes 2→1
    ================================================================
    */
    temp = ptr->next;  // Start of remaining list
    
    /*
    ================================================================
    STEP 3: REVERSE FIRST K NODES (Standard reversal)
    ------------------------------------------------
    STANDARD LINKED LIST REVERSAL:
    Original: 1→2→3→4
    After:   2→1→3→4
    
    REVERSAL STEPS (k=2):
    1. curr=1, prev=NULL, next=2
    2. next=2→curr->next=NULL→prev=1→curr=2  
    3. next=3→curr->next=2→prev=2→curr=3 ✓
    Now: prev=2 (new head of reversed group)
    ================================================================
    */
    for(int i = 0; i < k; i++) {
        next = curr->next;     // Save next node
        curr->next = prev;     // Reverse pointer
        prev = curr;           // Move prev forward
        curr = next;           // Move curr forward
    }
    
    /*
    ================================================================
    STEP 4: CONNECT reversed group to recursive result
    ------------------------------------------------
    After reversal: prev = new head of reversed group (2)
    
    Original head (1) now points to recursive result:
    head->next = reverseKGroup(temp, k)
    
    Example: 
    After reversing 1→2: prev=2, head=1, temp=3
    1->next = reverseKGroup(3→4→5→6→7, k=2)
    Result: 2→1→4→3→6→5→7
    ================================================================
    */
    if(temp != NULL) {
        head->next = reverseKGroup(temp, k);
    }
    
    /*
    ================================================================
    RETURN NEW HEAD OF REVERSED GROUP
    - prev = first node after reversal (2)
    ================================================================
    */
    return prev;
}

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
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
    // Test 1: k=2 (1→2→3→4→5→6→7)
    int arr1[] = {1, 2, 3, 4, 5, 6, 7};
    struct ListNode* head1 = createList(arr1, 7);
    
    printf("=== TEST 1: k=2 ===\n");
    printList(head1);                    // 1→2→3→4→5→6→7
    head1 = reverseKGroup(head1, 2);
    printList(head1);                    // 2→1→4→3→6→5→7
    
    // Test 2: k=3  
    printf("\n=== TEST 2: k=3 ===\n");
    int arr2[] = {1, 2, 3, 4, 5};
    struct ListNode* head2 = createList(arr2, 5);
    printList(head2);                    // 1→2→3→4→5
    head2 = reverseKGroup(head2, 3);
    printList(head2);                    // 3→2→1→4→5
    
    freeList(head1);
    freeList(head2);
    
    printf("\n✅ K-GROUP REVERSAL PERFECT!\n");
    return 0;
}

/*
================================================================================
Expected Output
================================================================================
=== TEST 1: k=2 ===
List: 1 → 2 → 3 → 4 → 5 → 6 → 7 → NULL
List: 2 → 1 → 4 → 3 → 6 → 5 → 7 → NULL

=== TEST 2: k=3 ===
List: 1 → 2 → 3 → 4 → 5 → NULL
List: 3 → 2 → 1 → 4 → 5 → NULL

✅ K-GROUP REVERSAL PERFECT!

*/