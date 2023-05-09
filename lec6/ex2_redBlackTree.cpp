#include<iostream>
#include<time.h>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;
    Node *parent;
    bool color; // 0 for black, 1 for red

    Node(int key) {
        this->key = key;
        left = right = parent = NULL;
        color = 1;
    }
};

class RedBlackTree {
public:
    Node* root;
    Node* null_node;

    RedBlackTree() {
        null_node = new Node(0);
        null_node->color = 0;
        null_node->left = null_node->right = null_node->parent = null_node;
        root = null_node;
    }

    // function to create a new code with the give key
    Node *create_node(int key) {
        Node* node = new Node(key);
        node->left = null_node; 
        node->right = null_node;
        node->parent = null_node;
        return node;
    }

    // function to print the tree in inorder
    void printTreeInorder(Node* node) {
        if(node == null_node) {
            return;
        }
        printTreeInorder(node->left);
        cout << node -> key << " ";
        printTreeInorder(node->right);
    }

    // function to rotate the subtree rooted with x to left
    void left_rotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;

        if(y->left!=null_node) {
            y->left->parent = x;
        } 

        y->parent = x->parent;

        if(x->parent == null_node) {
            root = y;
        } else if(x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    // function to rotate the subtree rooted with x to right
    void right_rotate(Node *x) {
        Node* y = x->left;
        x->left = y->right;

        if(y->right != null_node) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        
        if(x->parent == null_node) {
            root = y;
        } else if(x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    // function to fix the violation caused by insertion
    void fix_insert(Node *node) {
        while(node != root && node->parent->color == 1) {
            if(node->parent == node->parent->parent->right) {
                Node* uncle = node->parent->parent->left;
                if(uncle->color == 1) {
                    uncle->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else {
                    if(node == node->parent->left) {
                        node = node->parent;
                        right_rotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    left_rotate(node->parent->parent);
                }
            }
            else {
                Node* uncle = node->parent->parent->right;
                if(uncle->color == 1) {
                    uncle->color = 0;
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    node = node->parent->parent;
                }
                else {
                    if(node == node->parent->right) {
                        node = node->parent;
                        left_rotate(node);
                    }
                    node->parent->color = 0;
                    node->parent->parent->color = 1;
                    right_rotate(node->parent->parent);
                }
            }
        }
        root->color = 0;
    }

    
    // function to insert a new node with the given key
    void insert_node(int key) {
        Node* node = create_node(key);
        Node* y = null_node;
        Node* x = root;
        while(x != null_node) {
            y = x;
            if(node->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        node->parent = y;
        if(y == null_node) {
            root = node;
        }
        else if(node->key < y->key) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        if(node->parent == null_node) {
            node->color = 0;
            return;
        }

        if(node->parent->parent == null_node) {
            return;
        }

        fix_insert(node);
    }

    // function to search a node with the given key
    Node* search(Node* node, int key) {
        if(node == null_node || node->key == key) {
            return node;
        }
        if(node->key < key) {
            return search(node->right, key);
        }
        return search(node->left, key);
    }

    void printTree(Node* node, string indent, bool last)
    {
        if (node != null_node)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = node->color ? "RED" : "BLACK";
            cout << node->key << "(" << sColor << ")" << endl;
            printTree(node->left, indent, false);
            printTree(node->right, indent, true);
        }
    }



    void print(Node* node)
    {
        printTree(node,"", true);    
    }

};

int main() {
    int num_nodes = 20;
    RedBlackTree tree;

    // insert
    tree.insert_node(11);
    tree.insert_node(2);
    tree.insert_node(14);
    tree.insert_node(1);
    tree.insert_node(7);
    tree.insert_node(15);
    tree.insert_node(5);
    tree.insert_node(8);
    tree.insert_node(12);
    tree.insert_node(10);
    tree.insert_node(6);

    // print 
    tree.print(tree.root);
    cout << endl;

    // search
    int data = 5;
    Node* node = tree.search(tree.root, data);
    if(node != tree.null_node) {
        cout << "Found " << data << " in the tree" << endl;
    }
    else {
        cout << "Not found " << data << " in the tree" << endl;
    }
}