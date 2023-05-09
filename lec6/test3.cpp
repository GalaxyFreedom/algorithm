#include <iostream>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;

    // Constructor
    Node(int data)
    {
       this->data = data;
       left = right = parent = NULL;
       this->color = RED;
    }
};
class RBTree
{
private:
    Node *root;
protected:
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
    void inorderHelper(Node *root);
    Node* BSTInsert(Node* root, Node *pt);
    void fixInsertRBTree(Node *&root, Node *&pt);
public:
    // Constructor
    RBTree() { root = NULL; }
    void insert(const int &data);
    void inorder();
};