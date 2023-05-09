#include <iostream>
#include <string>
#include <queue>
using namespace std;

// 1. Every node is either red or black.
// 2. The root is black.
// 3. Every leaf (NIL) is black.
// 4. If a node is red, then both its children are black.
// 5. For each node, all simple paths from the node to descendant leaves contain the
// same number of black nodes.

// INSERT: 4 scenarios
// 1. z = root -> black
// 2. z.uncle = red -> recolor z.p, z.grandparent, z.uncle
// 3. z.uncle = black, triangle is formed with z.grandparent, z.p, z -> rotate z.p
// 4. z.uncle = black, line is formed with z.grandparent, z.p, z -> rotate z.grandparent + recolor
struct Node {
    int key;
    bool color;
    Node *left, *right, *p;
};

typedef Node *NodePtr;
class RedBlackTree {
private:
    NodePtr root;
    NodePtr nil; // nil sentinel
    void inOrderHelper(NodePtr x) {
        if (x != nil) {
            inOrderHelper(x->left);
            std::cout << x->key << ":" << x->color << " ";
            inOrderHelper(x->right);
        }
    }
    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            this->root = y;
        }
        else if (x == x->p->left) {
            x->p->left = y;
        }
        else {
            x->p->right = y;
        }
        y->left = x;
        x->p = y;
    }
    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != nil) {
            y->right->p = x;
        }
        y->p = x->p;
        if (x->p == nil) {
            this->root = y;
        }
        else if (x == x->p->right) {
            x->p->right = y;
        }
        else {
            x->p->left = y;
        }
        y->right = x;
        x->p = y;
    }

    // For balancing the tree after insertion
    void insertFixup(NodePtr k) {
        NodePtr u;
        while (k->p->color == 1) {
            if (k->p == k->p->p->right) {
                u = k->p->p->left;
                if (u->color == 1) {
                u->color = 0;
                k->p->color = 0;
                k->p->p->color = 1;
                k = k->p->p;
                } else {
                if (k == k->p->left) {
                    k = k->p;
                    rightRotate(k);
                }
                k->p->color = 0;
                k->p->p->color = 1;
                leftRotate(k->p->p);
                }
            }
            else {
                u = k->p->p->right;

                if (u->color == 1) {
                    u->color = 0;
                    k->p->color = 0;
                    k->p->p->color = 1;
                    k = k->p->p;
                }
                else {
                if (k == k->p->right) {
                    k = k->p;
                    leftRotate(k);
                }
                k->p->color = 0;
                k->p->p->color = 1;
                rightRotate(k->p->p);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }
    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == nil || key == node->key) {
            return node;
        }
        if (key < node->key) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }
    void printHelper(NodePtr root, string indent, bool last) {
        if ( root != nil ) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }
            string sColor = root->color ? "RED" : "BLACK";
            cout << root->key << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }
public:
    RedBlackTree() {
        nil = new Node();
        nil->color = false; // black
        nil->left = nil->right = nullptr;
        root = nil;
    }
    void inOrder() {
        inOrderHelper(this->root);
    }

    NodePtr minimum(NodePtr x) {
        while (x->left != nil)
            x = x->left;
        return x;
    }

    NodePtr maximum(NodePtr x) {
        while (x->right != nil)
            x = x->right;
        return x;
    }

    NodePtr successor(NodePtr x) {
        if ( x->right != nil ) {
            return minimum(x->right);
        }
        NodePtr y = x->p;
        while ( y !=  nil && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x) {
        if ( x->left != nil ) {
            return maximum(x->left);
        }
        NodePtr y = x->p;
        while ( y != nil && x == y->left ) {
            x = y;
            y = y->p;
        }
        return y;
    }

    NodePtr search(int k) {
        return searchTreeHelper(this->root, k);
    }

    void insert(int key) {
        NodePtr z = new Node;
        z->p = nullptr;
        z->key = key;
        z->left = nil;
        z->right = nil;
        z->color = true;

        NodePtr y = nullptr;
        NodePtr x = this->root;
        while (x != nil) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->p = y;
        if (y == nullptr) {
            root = z;
        }
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }

        if ( z->p == nullptr ) {
            z->color = false;
            return;
        }

        if ( z->p->p == nullptr ) {
            return;
        }
        insertFixup(z);
    }

    NodePtr getRoot() {
        return this->root;
    }

    void printTree() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }

};




int main() {
    RedBlackTree bst;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(57);

    bst.inOrder();
    cout << endl;
    bst.printTree();

}