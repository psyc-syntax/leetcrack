/*
================================================================================
LEETCODE 133: CLONE GRAPH (DFS WITH MEMOIZATION)
================================================================================

PROBLEM EXPLANATION (Simple Real-Life Example):
- Given an UNDIRECTED GRAPH (nodes + edges between them)
- Create EXACT DEEP COPY (new nodes, same connections)
- Nodes can have MULTIPLE neighbors (not just binary left/right)

Example Graph:
   1 --- 2
   |     |
   4 --- 3

Goal: Clone entire structure with NEW nodes but SAME connections

REAL-LIFE FEEL:
- Like photocopying an entire social network
- Everyone gets a clone, all connections preserved
- But MUST avoid copying same person twice (use a lookup table)

RULES:
- Graph may have cycles (node A→B→C→A)
- Deep copy: new Node objects, NOT shared references
- Return clone of starting node

APPROACH (DFS + HashMap Memoization):
1. hashmap clone: original→clone node mapping
2. DFS: clone current node → recursively clone neighbors
3. Memoization: if node already cloned, return existing clone

TIME & SPACE: O(V + E) where V=nodes, E=edges

--------------------------------------------------------------------------------
CODE WITH SIMPLE EXPLANATION COMMENTS
--------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/*
Definition for a Node.
*/

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() { val = 0; neighbors = vector<Node*>(); }
    Node(int _val) { val = _val; neighbors = vector<Node*>(); }
    Node(int _val, vector<Node*> _neighbors) { 
        val = _val; neighbors = _neighbors; 
    }
};

class Solution {
public:
    /*
    -------------------------------------------------------------------------
    clone: HASHMAP (original node → cloned node)
    - Key: original Node* 
    - Value: cloned Node* 
    - Prevents cloning same node multiple times
    - Handles cycles perfectly!
    -------------------------------------------------------------------------
    */
    unordered_map<Node*, Node*> clone;
    
    /*
    -------------------------------------------------------------------------
    cloneGraph(node): DEEP COPY GRAPH USING DFS + MEMOIZATION
    
    CORE LOGIC:
    1. Base case: NULL → return NULL
    2. Check if already cloned: return cached clone
    3. Create NEW node with same value
    4. Cache it: clone[original] = new_node
    5. Recursively clone ALL neighbors
    6. Connect cloned neighbors to new node
    7. Return cloned node
    
    GENIUS: Memoization handles cycles automatically!
    -------------------------------------------------------------------------
    */
    Node* cloneGraph(Node* node) {
        /*
        ================================================================
        BASE CASE 1: Empty graph
        ================================================================
        */
        if(node == NULL) return NULL;
        
        /*
        ================================================================
        BASE CASE 2: ALREADY CLONED? (MEMOIZATION CHECK)
        ------------------------------------------------
        if(clone.find(node) != clone.end())  // node exists in hashmap
            return clone[node];              // return cached clone
        
        CRITICAL: Prevents infinite recursion in cycles!
        Example: A→B→A (cycle)
        - First call: A not cloned → create clone_A
        - B calls A: A already cloned → return clone_A instantly!
        ================================================================
        */
        if(clone.find(node) != clone.end()){
            return clone[node];
        }
        
        /*
        ================================================================
        STEP 1: CREATE NEW CLONE NODE (same value)
        ------------------------------------------------
        Node* temp = new Node(node->val);
        - new Node with SAME VALUE as original
        - neighbors vector initially empty
        - temp is "shallow copy" so far
        ================================================================
        */
        Node* temp = new Node(node->val);
        
        /*
        ================================================================
        STEP 2: CACHE CLONE MAPPING
        ------------------------------------------------
        clone[node] = temp;
        - original → clone mapping stored
        - Future calls to this node will return temp instantly
        
        WHY CACHE BEFORE recursing neighbors?
        - Handles cycles: neighbor might point back to current node
        - Ensures clone[node] exists when recursive calls return
        ================================================================
        */
        clone[node] = temp;
        
        /*
        ================================================================
        STEP 3: DEEP COPY NEIGHBORS (RECURSIVE)
        ------------------------------------------------
        for(Node* neigh : node->neighbors){
            temp->neighbors.push_back(cloneGraph(neigh));
        }
        
        KEY INSIGHT:
        - Recursively clone EACH neighbor
        - cloneGraph(neigh) returns ALREADY-CLONED neighbor (or new)
        - Push cloned neighbor to temp's neighbors list
        
        Example: Node 1 neighbors [2,4]
        - cloneGraph(2) → returns clone_2  
        - cloneGraph(4) → returns clone_4
        - temp.neighbors = [clone_2, clone_4]
        ================================================================
        */
        for(Node* neigh : node->neighbors){
            temp->neighbors.push_back(cloneGraph(neigh));
        }
        
        /*
        ================================================================
        RETURN COMPLETELY CLONED NODE
        - temp has: correct val + all neighbors cloned + cached
        ================================================================
        */
        return temp;
    }
};

/*
================================================================================
SIMPLE MAIN FUNCTION FOR TESTING
================================================================================
*/

Node* createNode(int val) {
    return new Node(val);
}

void printGraph(Node* node, unordered_set<Node*>& printed) {
    if(!node || printed.count(node)) return;
    printed.insert(node);
    
    cout << "Node " << node->val << " neighbors: [";
    for(int i = 0; i < node->neighbors.size(); i++) {
        cout << node->neighbors[i]->val;
        if(i < node->neighbors.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    
    for(Node* neigh : node->neighbors) {
        printGraph(neigh, printed);
    }
}

int main() {
    Solution sol;
    
    // Create sample graph: 1↔2, 1↔4, 2↔3, 4↔3
    Node* n1 = createNode(1);
    Node* n2 = createNode(2);
    Node* n3 = createNode(3);
    Node* n4 = createNode(4);
    
    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};
    
    cout << "ORIGINAL GRAPH:" << endl;
    unordered_set<Node*> printed;
    printGraph(n1, printed);
    
    Node* cloned = sol.cloneGraph(n1);
    
    cout << "\nCLONED GRAPH:" << endl;
    unordered_set<Node*> printed2;
    printGraph(cloned, printed2);
    
    cout << "\n✅ CLONE SUCCESS! Separate memory, same structure!" << endl;
    return 0;
}
