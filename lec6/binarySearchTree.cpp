#include <iostream>
#include <queue>
// Define a structure to represent a node in a binary search tree
struct Node {
    // Data member to store the key of the node
    int key;
    // Data members to store pointers to the left and right children of the node
    Node *left, *right;
    // Data member to store a pointer to the parent of the node
    Node *p;
    // Constructor that takes an integer argument key
    Node(int key) : key(key), left(nullptr), right(nullptr), p(nullptr) {}
};

// Define a structure to represent a binary search tree
struct Tree {
    // Data member to store a pointer to the root node of the tree
    Node *root;
    // Constructor that takes no arguments
    Tree() : root(nullptr) {}
};

void preorderTreeWalk(Node *x) {
    // If x is not a null pointer
    if (x != nullptr) {
        // Print the key of x
        std::cout << x->key << " ";
        // Recursively call preorderTreeWalk on the left child of x
        preorderTreeWalk(x->left);
        // Recursively call preorderTreeWalk on the right child of x
        preorderTreeWalk(x->right);
    }
}

void inorderTreeWalk(Node *x) {
    // If x is not a null pointer
    if (x != nullptr) {
        // Recursively call inorderTreeWalk on the left child of x
        inorderTreeWalk(x->left);
        // Print the key of x
        std::cout << x->key << " ";
        // Recursively call inorderTreeWalk on the right child of x
        inorderTreeWalk(x->right);
    }
}

void postorderTreeWalk(Node *x) {
    // If x is not a null pointer
    if (x != nullptr) {
        // Recursively call postorderTreeWalk on the left child of x
        postorderTreeWalk(x->left);
        // Recursively call postorderTreeWalk on the right child of x
        postorderTreeWalk(x->right);
        // Print the key of x
        std::cout << x->key << " ";
    }
}

void levelOrder(Node *root) {
    if (root == nullptr) // If tree is empty, return
        return;

    std::queue<Node *> q; // create an empty queue
    q.push(root); // add the root of the tree to the queue

    while (!q.empty()) { // while the queue is not empty
        Node *temp = q.front(); // get the node at the front of the queue
        std::cout << temp->key << " "; // print its data
        q.pop(); // remove it from the queue

        if (temp->left != nullptr) // if the node has a left child
            q.push(temp->left); // add its left child to the queue

        if (temp->right != nullptr) // if the node has a right child
            q.push(temp->right); // add its right child to the queue
    }
}

void treeInsert(Tree &T, Node *z) {
    // Insert node z into the tree
    Node *y = nullptr;
    Node *x = T.root;
    // Find the position in the tree where z should be inserted
    while (x != nullptr) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y; // Set z's parent to y
    if (y == nullptr) // The tree is empty
        T.root = z; // z becomes the root of the tree
    else if (z->key < y->key) // z's key is less than y's key
        y->left = z; // z becomes the left child of y
    else // z's key is greater than or equal to y's key
        y->right = z; // z becomes the right child of y
}

Node* iterativeTreeSearch(Node *x, int k) {
    // While x is not a null pointer and k is not equal to the key of x
    while (x != nullptr && k != x->key) {
        // If k is less than the key of x
        if (k < x->key)
            // Go to the left child of x
            x = x->left;
        // Otherwise
        else
            // Go to the right child of x
            x = x->right;
    }
    // Return a pointer to the node with key k if it exists, otherwise return a null pointer
    return x;
}

Node* treeMinimum(Node* x) {
    while (x->left != nullptr)
        x = x->left;
    return x;
}

Node* treeMaximum(Node *x) {
    while (x->right != nullptr)
        x = x->right;
    return x;
}

Node* treeSuccessor(Node *x) {
    // If the right subtree of node x is not empty
    if (x->right != nullptr)
        // The successor of x is just the leftmost node in its right subtree
        return treeMinimum(x->right);
    // If the right subtree of node x is empty
    Node *y = x->p;
    // Go up the tree from x using the parent pointers
    while (y != nullptr && x == y->right) {
        x = y;
        y = y->p;
    }
    // Return the lowest ancestor of x whose left child is also an ancestor of x
    return y;
}

Node* treePredecessor(Node *x) {
    // If the left subtree of node x is not empty
    if (x->left != nullptr)
        // The predecessor of x is just the rightmost node in its left subtree
        return treeMaximum(x->left);
    // If the left subtree of node x is empty
    Node *y = x->p;
    // Go up the tree from x using the parent pointers
    while (y != nullptr && x == y->left) {
        x = y;
        y = y->p;
    }
    // Return the lowest ancestor of x whose right child is also an ancestor of x
    return y;
}

// In order to move subtrees around within the binary search tree, we define a
// subroutine TRANSPLANT, which replaces one subtree as a child of its parent with
// another subtree. When TRANSPLANT replaces the subtree rooted at node u with
// the subtree rooted at node v, node u’s parent becomes node v’s parent, and u’s
// parent ends up having v as its appropriate child.
void transplant(Tree &T, Node *u, Node *v) {
    // Replace the subtree rooted at u with the subtree rooted at v
    if (u->p == nullptr) // u is the root of the tree
        T.root = v; // v becomes the new root
    else if (u == u->p->left) // u is a left child
        u->p->left = v; // v becomes the new left child of u's parent
    else // u is a right child
        u->p->right = v; // v becomes the new right child of u's parent
    if (v != nullptr) // if v is not null
        v->p = u->p; // update v's parent pointer to point to u's parent
}

// - If z has no children, then we simply remove it by modifying its parent to replace z with NIL as its child.
// - If z has just one child, then we elevate that child to take z’s position in the tree
// by modifying z’s parent to replace z by z’s child.
// - If z has two children, then we find z’s successor y—which must be in z’s right
// subtree—and have y take z’s position in the tree. The rest of z’s original right
// subtree becomes y’s new right subtree, and z’s left subtree becomes y’s new
// left subtree. This case is the tricky one because, as we shall see, it matters
// whether y is z’s right child.
void treeDelete(Tree &T, Node *z) {
    // Delete node z from the tree
    if (z->left == nullptr) // z has no left child
        transplant(T, z, z->right); // replace z with its right child
    else if (z->right == nullptr) // z has no right child
        transplant(T, z, z->left); // replace z with its left child
    else { // z has two children
        Node *y = treeMinimum(z->right); // find the inorder successor of z
        if (y->p != z) { // y is not a direct child of z
            transplant(T, y, y->right); // replace y with its right child
            y->right = z->right; // set y's right child to z's right child
            y->right->p = y; // update the parent pointer of y's right child
        }
        transplant(T, z, y); // replace z with y
        y->left = z->left; // set y's left child to z's left child
        y->left->p = y; // update the parent pointer of y's left child
    }
}

int main() {
    Tree T;

    treeInsert(T, new Node(1));
    treeInsert(T, new Node(2));
    treeInsert(T, new Node(3));
    treeInsert(T, new Node(4));
    treeInsert(T, new Node(5));
    treeInsert(T, new Node(6));
    treeInsert(T, new Node(7));

    // Print the inorder traversal of the tree
    std::cout << "Inorder traversal: ";
    inorderTreeWalk(T.root);
    std::cout << std::endl;

    std::cout << "Search for key 4: "<<iterativeTreeSearch(T.root, 4)->key << std::endl; // 4
    std::cout << "Search for key 9: "<<iterativeTreeSearch(T.root, 9) << std::endl; // 0

    // Find the node with key 4 and delete it from the tree
    Node *nodeToDelete = iterativeTreeSearch(T.root, 4);
    if (nodeToDelete != nullptr) {
        treeDelete(T, nodeToDelete);
        std::cout << "Node with key 4 deleted" << std::endl;
    } else {
        std::cout << "Node with key 4 not found" << std::endl;
    }

    // Print the inorder traversal of the tree
    std::cout << "Inorder traversal: ";
    inorderTreeWalk(T.root);
    std::cout << std::endl;

    std::cout << "Level-order traversal: ";
    levelOrder(T.root);
    std::cout << std::endl;
    return 0;
}
