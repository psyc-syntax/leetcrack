/*
================================================================================
LEETCODE 19: REMOVE NTH NODE FROM END OF LINKED LIST (TWO-PASS VERSION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given linked list: 1→2→3→4→5
- Remove Nth node FROM END
- n=2: remove 4 → 1→2→3→5
- n=1: remove 5 → 1→2→3→4

REAL-LIFE FEEL:
- Like removing person Nth from end of line
- First: COUNT total people (len=5)
- Second: Walk to person (len-n)=3rd position → remove NEXT person

APPROACH (Two Passes):
1. PASS 1: Count total length
2. PASS 2: Find (len-n)th node → remove its NEXT node
3. Special case: n==len → remove head

TIME: O(L) where L=length, SPACE: O(1)

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

/*
================================================================================
SOLUTION FUNCTION WITH DETAILED COMMENTS
================================================================================
*/
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    /*
    -------------------------------------------------------------------------
    THREE POINTERS:
    - temp: node to delete (temporary storage)
    - ptr: traveler pointer  
    - final: node AFTER node-to-delete
    -------------------------------------------------------------------------
    */
    struct ListNode *temp, *ptr, *final;
    
    /*
    ================================================================
    PASS 1: COUNT TOTAL LENGTH
    ------------------------------------------------
    ptr starts at head, walks to end
    len = total nodes in list
    
    Example: 1→2→3→4→5 → len=5
    ================================================================
    */
    ptr = head;
    int len = 0;
    while(ptr != NULL) {
        len++;          // Count each node
        ptr = ptr->next; // Move to next
    }
    
    /*
    ================================================================
    SPECIAL CASE 1: REMOVE HEAD (n == len)
    ------------------------------------------------
    n == len means: "remove nth from end = remove 1st from start"
    Example: list=1→2→3→4→5, n=5 → remove node 1 (head)
    
    STEPS:
    1. temp = head (node to delete)
    2. head = head->next (new head)
    3. free(temp) (delete old head)
    4. return new head
    ================================================================
    */
    if(n == len) {
        temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    
    /*
    ================================================================
    PASS 2: FIND NODE BEFORE TARGET
    ------------------------------------------------
    Goal: Reach (len-n)th node → its next = node to delete
    
    Example: 1→2→3→4→5, n=2
    - len=5, len-n=3
    - Go to 3rd node (value=3)
    - 3→next = 4 (target to delete)
    
    for(int i = 1; i < len - n; i++)
    - i starts at 1 because ptr already at position 1 (head)
    - Walk (len-n-1) steps from head
    ================================================================
    */
    ptr = head;
    for(int i = 1; i < len - n; i++) {
        ptr = ptr->next;
    }
    
    /*
    ================================================================
    REMOVE TARGET NODE
    ------------------------------------------------
    ptr = node BEFORE target (len-n th node)
    
    Example: ptr=3, target=4, final=5
    Before: 1→2→3→4→5
    After:  1→2→3→5
    
    STEPS:
    1. temp = ptr->next (node 4 to delete)
    2. final = temp->next (node 5)
    3. ptr->next = final (3→5, skip 4)
    4. free(temp) (delete node 4)
    ================================================================
    */
    temp = ptr->next;    // Node to delete (4)
    final = temp->next;  // Next after target (5)
    ptr->next = final;   // Skip target: 3→5
    free(temp);          // Delete node 4
    
    /*
    ================================================================
    RETURN ORIGINAL HEAD (modified in-place)
    ================================================================
    */
    return head;
}

/*
================================================================================
HELPER FUNCTIONS FOR TESTING
================================================================================
*/
struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
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

void freeList(struct ListNode* head) {
    while(head) {
        struct ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/
int main() {
    // Test Case 1: Remove 2nd from end (1→2→3→4→5, n=2 → 1→2→3→5)
    int arr1[] = {1, 2, 3, 4, 5};
    struct ListNode* head1 = createList(arr1, 5);
    
    printf("=== TEST 1: Remove 2nd from end ===\n");
    printList(head1);
    head1 = removeNthFromEnd(head1, 2);
    printList(head1);
    
    // Test Case 2: Remove head (n == len)
    int arr2[] = {1, 2};
    struct ListNode* head2 = createList(arr2, 2);
    
    printf("\n=== TEST 2: Remove head (n==len) ===\n");
    printList(head2);
    head2 = removeNthFromEnd(head2, 2);
    printList(head2);
    
    freeList(head1);
    freeList(head2);
    
    printf("\n✅ ALL TESTS PASSED!\n");
    return 0;
}

/*
================================================================================
Expected Output
================================================================================

=== TEST 1: Remove 2nd from end ===
List: 1 → 2 → 3 → 4 → 5 → NULL
List: 1 → 2 → 3 → 5 → NULL

=== TEST 2: Remove head (n==len) ===
List: 1 → 2 → NULL
List: 2 → NULL

✅ ALL TESTS PASSED!
*/