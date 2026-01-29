#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
LRU CACHE — “BRUTE FORCE-ish” PERSPECTIVE (BUT ACTUALLY OPTIMAL O(1))
================================================================================

PROBLEM EXPLANATION (Like before problems):
- You want a cache that can store at most `capacity` key–value pairs.
- Operations:
  - get(key): return value if present, else -1.
  - put(key, value): insert/update key with value.
- When cache is full and you add a new key:
  - You must evict the **Least Recently Used (LRU)** key.

REAL-LIFE FEEL:
- Imagine a small desk that can hold only a few books.
- Whenever you read a book (get/put), that book becomes the **most recently used**.
- When a new book comes and the desk is full, you remove the book you have not touched for the longest time (LRU).

WHAT A TRUE BRUTE-FORCE LRU MIGHT DO (for comparison):
- Store all items in a simple list or array.
- On every get/put, scan the list to:
  - Find the key.
  - Decide which key is least recently used.
- This would be **O(n)** per operation (linear scan), which is slow for big caches.[web:94][web:92]

THIS IMPLEMENTATION (YOUR CODE) — OPTIMIZED IDEA:
- Combines:
  1) **Doubly Linked List**:
     - Stores nodes with (key, value).
     - Head = **most recently used**.
     - Tail = **least recently used**.
     - We can move nodes to front and remove from back in O(1).[web:92][web:93]
  2) **unordered_map<int, Node*>**:
     - Maps key → pointer to its node in the list.
     - Lookup by key is O(1) average.[web:92][web:96]

- So:
  - get(key) can:
    - Find node in O(1) using map.
    - Move node to head in O(1).
  - put(key, value) can:
    - Insert/update node and adjust list in O(1).
    - Remove tail node (LRU) in O(1) when needed.

Compared to true brute force O(n) scanning, this is **optimized O(1)** per operation.[web:96][web:101]

--------------------------------------------------------------------------------
CODE WITH STEP-BY-STEP COMMENTS (IN BRUTE-FORCE STYLE EXPLANATION)
--------------------------------------------------------------------------------
*/

class LRUCache {
public:
    // Doubly linked list node: stores key and value
    struct Node {
        int key;
        int val;
        Node* next;
        Node* prev;
        Node(int k, int v) {
            key = k;
            val = v;
            next = NULL;
            prev = NULL;
        }
    };

    Node* head = NULL;                // Most recently used (MRU)
    Node* tail = NULL;                // Least recently used (LRU)

    // Map from key to node pointer for O(1) direct access
    unordered_map<int, Node*> mp;

    int size = 0;                     // Current number of items
    int limit = 0;                    // Capacity

    LRUCache(int capacity) {
        limit = capacity;
    }

    /*
    ============================================================================
    GET(key) EXPLANATION:
    ----------------------------------------------------------------------------
    - Brute-force style would:
        * Scan a list/array to find key (O(n)).
        * Then mark it as recently used somehow.
    - Our optimized version:
        1) Look up key in hashmap in O(1).
        2) If not found → return -1.
        3) If found:
           - Move its node to HEAD of the doubly linked list (mark as MRU).
           - Return its value.
    ============================================================================
    */
    int get(int key) {
        // Key does not exist
        if (mp.find(key) == mp.end())
            return -1;

        Node* temp = mp[key];  // node associated with key

        // Move this node to the front (head) if it's not already head
        if (temp != head) {
            // Remove temp from its current position in list
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == tail) tail = temp->prev;  // if it was tail, update tail

            // Insert temp at head
            temp->prev = NULL;
            temp->next = head;
            if (head) head->prev = temp;
            head = temp;
        }

        return temp->val;
    }

    /*
    ============================================================================
    PUT(key, value) EXPLANATION:
    ----------------------------------------------------------------------------
    - Brute-force idea:
        * If key exists: find it by scanning → O(n), then update and move to front.
        * If key doesn't exist and cache full:
            - Decide LRU by scanning timestamps/order → O(n).
            - Remove that node, insert new one.
    - Our optimized logic:
        1) If key already exists:
           - Update its value.
           - Move its node to head (MRU) like in get.
        2) If key does NOT exist:
           - Create new node and link it at head.
           - Add key → node in hashmap.
           - If size == limit:
               · Remove tail node (LRU) from list and erase its key from map.
           - Else:
               · Just increase size.
    ============================================================================
    */
    void put(int key, int value) {
        // Case 1: key already in cache
        if (mp.find(key) != mp.end()) {
            Node* temp = mp[key];
            temp->val = value;  // update value

            // Move to head (MRU) if not already there
            if (temp != head) {
                // unlink from current position
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == tail) tail = temp->prev;

                // insert at head
                temp->prev = NULL;
                temp->next = head;
                if (head) head->prev = temp;
                head = temp;
            }
            return;
        }

        // Case 2: key not in cache, insert new node
        Node* temp = new Node(key, value);
        mp[key] = temp;

        // Insert new node at head
        temp->next = head;
        if (head) head->prev = temp;
        head = temp;

        // If cache was empty, tail also points to this new node
        if (!tail) tail = temp;

        // If cache is full, remove LRU node (tail)
        if (size == limit) {
            // Remove from map
            mp.erase(tail->key);

            // Remove from list
            Node* tail_prev = tail->prev;
            if (tail_prev) tail_prev->next = NULL;
            delete tail;
            tail = tail_prev;
        } else {
            size++;
        }
    }
};

/*
================================================================================
WHY THIS IS “BRUTE FORCE FIXED” / COMPARED TO NAIVE:
--------------------------------------------------------------------------------
- Naive LRU:
  - Would linearly scan to find keys and LRU entries → O(n) per get/put.[web:94]
- This implementation:
  - Uses hashmap for direct key lookup → O(1).[web:92][web:96]
  - Uses doubly linked list for O(1) move-to-front and remove-tail.[web:92][web:93]
  - Thus, get and put are both **O(1)** average, which is the optimal design
    expected in interviews and CP problems.[web:96][web:101]
================================================================================
*/
