#ifndef AVL_H 
#define AVL_H

#include "Item.h"
#include <string>
#include <vector>

// Class for nodes in the AVL tree
class Node {  
    public: 
        Node* p;  
        Item value;  
        Node* l;  
        Node* r; 
        int height; 
        void updateHeight (); 
        int bf ();
        bool isEqual (Node* node);
}; 

/*
Collapses the tree into a string to be saved to a file. The string is every 
item in the tree in pre-order seperated by newlines.
Inputs: 
    root: root of the tree to be broken down
Outputs:
    A collapsed tree (root first/pre-order) with each item being seperated by a newline
*/
string save (Node* root);

/*
Creates node representation of an item.
Inputs: 
    item: An item to be added to the tree
Outputs:
    A pointer to a node representing that item
*/
Node* createNode (Item item); 

// ---- Core Tree Functionalities ----

/*
Inserts an item into a provided AVL Tree root node, 
inserting an Item with an SKU already existing in the tree
will result in the stockCount of that item being added to the existing Item
Inputs:   
    root: The root node of the tree
    x: An Item to be inserted into the AVL Tree
Outputs:
    A pointer to the new root (can stay the same)
*/
Node* insert (Node* root, Item x);

/*
Finds an Item in the tree and returns the node containing that Item.
Returns null if item is not found
Inputs:   
    root: The root node of the tree
    sku: An SKU number to be found in the AVL Tree
Outputs:
    The node containing the Item with the provided SKU or 
    null if Item is not in tree
*/
Node* find (Node* root, int sku);

/*
Removes an Item from the tree. If item is not in tree 'remove' will 
have no effect
Inputs:   
    root: The root node of the tree
    sku: SKU number of the item to be removed from the tree
Outputs:
    A pointer to the new root (can stay the same)
*/
Node* remove (Node* root, int sku);

/*
Updates the stockCount of an Item in the tree. If item is not in tree 'updateCount' will 
have no effect
Inputs:   
    root: The root node of the tree
    sku: SKU number of the item to be updated in the tree
    newCount: the new stockCount for the item
Outputs:
    N/A
*/
void updateCount (Node* root, int sku, int newCount);


// ---- Tree Balancing and Transformation ----

/*
For all the forms of rotation below:
Inputs:   
    target: Node to be the target for a rotation
Outputs:
    A pointer to the new root (can stay the same)
*/

Node* lRotate (Node* target);

Node* lrRotate (Node* target);

Node* rRotate (Node* target);

Node* rlRotate (Node* target);

/*
Console logs a pre-order traversal of the tree for debug purposes
Inputs:
    root: root node of the tree to be displayed
Outputs:
    N/A
*/
void inOrder (Node* root);

/*
Gets all items in the tree with SKUs inside a given range
Inputs:
    root: root node of the tree of items
    start: Lower bound of the SKU range
    end: Upper bound of the SKU range
    arr: A reference to the vector of item pointers we are building up
Outputs:
    vector of pointers to the items within the given range
*/
vector<Item*> getRange (Node* root, int start, int end);

/*
Helper functions to get the min and max nodes in the AVL tree
Inputs:   
    root: The root node of the tree    
Outputs:
    The node containing the Item with the minimum SKU
*/
Node* min (Node* root);
Node* max (Node* root);

#endif
