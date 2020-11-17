#include "AVL.h"
#include "Item.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void Node::updateHeight () {
    if (!l & !r) {
        height = 1;
    }
    else if (!l) {
        height = 1 + r->height;
    }
    else if (!r) {
        height = 1 + l->height;
    }
    else {
        height = 1 + (l->height > r->height ? l->height : r->height);
    }
}

int Node::bf () {
    if (!l & !r) {
        return 0;
    }
    else if (!l) {
        return -(r->height);
    }
    else if (!r) {
        return l->height;
    }
    else {
        return l->height - r->height;
    }
}

bool Node::isEqual (Node* node) {
    if (!node)
        return false;
    return value.sku == node->value.sku;
}

string save (Node* root) {
    if (root) {
        return root->value.printForFile() + "\n" + save(root->l) + save(root->r);
    }
    else {
        return "";
    }

}

Node* createNode (Item item) {
    Node* x = new Node;
    x->value = item;
    x->p = x->l = x->r = NULL;
    x->height = 1;
    return x;
}

Node* insert (Node* root, Item item) {
    Node* x = root;
    Node* z = createNode(item);

    if (!root)
        return z;

    while (x) {
        z->p = x;
        if (z->value.sku < x->value.sku) {
            x = x->l;
        }
        else if (z->value.sku > x->value.sku) {
            x = x->r;
        }
        else {
            // Duplicate SKU, add stockcount to existing item
            x->value.stockCount += item.stockCount;
            return root;
        }
    }
    if (z->value.sku < z->p->value.sku) {
        z->p->l = z;
    }
    else {
        z->p->r = z;
    }

    x = z;
    while (x) {
        x->updateHeight();

        if (x->bf() < -1 && x->r->bf() == -1) {
            x = lRotate(x);
        }
        else if (x->bf() < -1 && x->r->bf() == 1) {
            x = rlRotate(x);
        }
        else if (x->bf() > 1 && x->l->bf() == 1) {
            x = rRotate(x);
        }
        else if (x->bf() > 1 && x->l->bf() == -1) {
            x = lrRotate(x);
        }

        if (!x->p) {
            return x;
        }
        x = x->p;
    }
    return root;
}

Node* find (Node* root, int sku) {
    Node* x = root;
    while (x) {
        if (sku < x->value.sku){
            x = x->l;
        }
        else if (sku > x->value.sku) {
            x = x->r;
        }
        else {
            return x;
        }
    }
    return NULL;
}

Node* remove (Node* root, int sku) {
    Node* z = find(root, sku);
    if (z == NULL) return root;

    // Starting point for the fixup routine (will be different in the both childeren case)
    Node* startingPoint = z->p;

    bool isRoot = z->isEqual(root);
    bool isLeft = isRoot ? true : z->isEqual(z->p->l);

    if (!z->l && !z->r) {
        // No children
        if (isRoot) return NULL;

        if (isLeft) {
            z->p->l = NULL;
        }
        else {
            z->p->r = NULL;
        }
    }
    else if (!z->l || !z->r) {
        // One child
        Node* replacer = !z->l ? z->r : z->l;

        if (isRoot) return replacer;

        isLeft ? z->p->l = replacer : z->p->r = replacer;
        replacer->p = z->p;

        startingPoint = replacer;
    }
    else {
        // Both children, find min right child
        Node* y = z->r;
        while (y->l) {
            y = y->l;
        }
        if (y->isEqual(z->r)) {
            // y is z's right child
            z->value = y->value;
            z->r = y->r;
            z->r->p = z;

            startingPoint = z;
        }
        else {
            // Need to replace y with its right child before replacing z
            y->p->l = y->r;
            y->r->p = y->p;

            z->value = y->value;

            startingPoint = y->p;
        }
    }

    while (startingPoint) {
        startingPoint->updateHeight();

        if (startingPoint->bf() < -1 && startingPoint->r->bf() <= 0) {
            startingPoint = lRotate(startingPoint);
        }
        else if (startingPoint->bf() < -1 && startingPoint->r->bf() >= 0) {
            startingPoint = rlRotate(startingPoint);
        }
        else if (startingPoint->bf() > 1 && startingPoint->l->bf() >= 0) {
            startingPoint = rRotate(startingPoint);
        }
        else if (startingPoint->bf() > 1 && startingPoint->l->bf() <= -1) {
            startingPoint = lrRotate(startingPoint);
        }

        if (!startingPoint->p) {
            return startingPoint;
        }
        startingPoint = startingPoint->p;
    }
    return root;
}

void updateCount (Node* root, int sku, int newCount) {
    Node* node = find(root, sku);
    if (node != NULL) {
        node->value.stockCount = newCount;
    }
}

Node* lRotate (Node* target) {
    Node* newRoot = target->r;
    target->r = newRoot->l;
    if (target->r) target->r->p = target;
    newRoot->l = target;

    target->updateHeight();
    newRoot->updateHeight();

    if (!target->p) {
        // Target is root
        newRoot->p = NULL;
        target->p = newRoot;
    }
    else {
        target->isEqual(target->p->l) ? target->p->l = newRoot : target->p->r = newRoot;
        newRoot->p = target->p;
        target->p = newRoot;
    }

    return newRoot;
}

Node* lrRotate (Node* target) {
    target->l = lRotate(target->l);
    return rRotate(target);
}

Node* rRotate (Node* target) {
    Node* newRoot = target->l;
    target->l = newRoot->r;
    if (target->l) target->l->p = target;
    newRoot->r = target;

    target->updateHeight();
    newRoot->updateHeight();

    if (!target->p) {
        // Target is root
        newRoot->p = NULL;
        target->p = newRoot;
    }
    else {
        target->isEqual(target->p->l) ? target->p->l = newRoot : target->p->r = newRoot;
        newRoot->p = target->p;
        target->p = newRoot;
    }

    return newRoot;
}

Node* rlRotate (Node* target) {
    target->r = rRotate(target->r);
    return lRotate(target);
}

void inOrder(Node* root) {
    if (root) {
        cout << root->value.sku << " ("  << root->bf() << ")";

        cout << "[";
        inOrder(root->l);
        cout << "]";

        cout << "[";
        inOrder(root->r);
        cout << "]";
    }
}

vector<Item*> getRange (Node* root, int start, int end) {
    vector<Item*> arr;
    Node* smallest = min(root);
    Node* largest = max(root);
    start = (start < smallest->value.sku) ? smallest->value.sku : start;
    end = (end > largest->value.sku) ? largest->value.sku : end;

    for (int i = start; i <= end; i++) {
        Node* x = find(root, i);
        if (x) {
            arr.push_back(&x->value);
        }                
    }
    return arr;
}

Node* min (Node* root) {
    Node* x = root;
    while (x) {
        if (x->l){
            x = x->l;
        }
        else {
            return x;
        }
    }
    return NULL;
}

Node* max (Node* root) {
    Node* x = root;
    while (x) {
        if (x->r){
            x = x->r;
        }
        else {
            return x;
        }
    }
    return NULL;
}
