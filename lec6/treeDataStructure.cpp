#include <iostream>
#include <string>

using namespace std;

// structure of a node with a data and two pointers to children nodes
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Node() = default;
    Node(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}
};

// tree search : find the node that contains the given key from the root
Node* treeSearch(Node* root, int key) {
    while ( root != nullptr && key != root->data ) {
        if ( key < root->data ) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return root;
}

// tree insert : create a new node if root is nullptr, else insert a new node
Node* treeInsert(Node*& root, int key){
    // create a new node if the root is null
    if (root == nullptr)
        return new Node(key);
    Node* temp;
    // if key is smaller than the root data,
    if (key < root->data){
        // go down the left subtree
        temp = treeInsert(root->left, key);
        root->left = temp;
        temp->parent = root;
    }
    // else if key is larger than the root data
    else{
        // go down the right subtree
        temp = treeInsert(root->right, key);
        root->right = temp;
        temp->parent = root;
    }
    return root;
}

// pre-order tree traversal algorithm:
// data, left, right
void preOrderTraverse(Node* root) {
    if ( root != nullptr ) {
        cout << root->data << " ";
        preOrderTraverse(root->left);
        preOrderTraverse(root->right);
    }
    else return;
}

// in-order traversal algorithm:
// left, data, right
void inOrderTraversal(Node* root) {
    if ( root != nullptr ) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
    else return;
}

// post-order traversal algorithm:
// left, right, data
void postOrderTraversal(Node* root) {
    if ( root != nullptr ){
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->data << " ";
    }
    else return;
}

// tree minimum : the left-most leaf from the root node
Node* treeMinimum(Node* root) {
    while ( root->left != NULL ) {
        root = root->left;
    }
    return root;
}

// tree maximum : the right-most leaf from the root node
Node* treeMaximum(Node* root) {
    while ( root->right != NULL ) {
        root = root->right;
    }
    return root;
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root */
Node* deleteNode(Node* root, int k)
{
    // Base case
    if (root == NULL)
        return root;

    // Recursive calls for ancestors of
    // node to be deleted
    if (root->data > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->data < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        Node* temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        Node* temp = root->left;
        delete root;
        return temp;
    }

    // If both children exist
    else {

        Node* succParent = root;

        // Find successor
        Node* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        root->data = succ->data;

        // Delete Successor and return root
        delete succ;
        return root;
    }
}

// successor: node with smallest data that greater than x
Node* nodeSuccessor(Node* root, int key) {
    // search for the node that contains given key from the root
    Node* currNode = treeSearch(root, key);
    // 1st situation: x has a right subtree : successor is minimum node in right subtree
    if (currNode->right != nullptr) {
        return treeMinimum(currNode->right);
    }
    // 2nd situation : x has no right subtree, traverse up using the parent pointer
    Node* y = currNode->parent;
        // x is the right child of its parent : successor is the first right ancestor of its parent
    while ( y != NULL && currNode == y->right ) {
        currNode = y;
        y = y->parent;
    }
        // else x is the left child of its parent : successor is its parent
    return y;
}

// predecessor: node with greatest data that smaller than x
Node* nodePredecessor(Node* root, int key) {
    // search for the node that contains given key from the root
    Node* currNode = treeSearch(root, key);
    // 1st situation: x has a left subtree : predecessor is maximum node in the left subtree
    if ( currNode->left != nullptr ) {
        return treeMaximum(currNode->left);
    }
    // 2nd situation: x has no left subtree, traverse up using the parent pointer
    Node* y = currNode->parent;
        // x is the left child of its parent : predecessor is the first left ancestor of parent
    while ( y != nullptr && currNode == y->left ) {
        currNode = y;
        y = y->parent;
    }
        // else x is the right child of its parent : predecessor is its parent
    return y;
}

void TreeInsert(Node* &T, Node* z) {
    Node* y = nullptr;
    Node* x = T;
    while (x != nullptr) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        T = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
}

void t_deleteTree(Node* node)
{
    if (node == NULL) return;

    /* first delete both subtrees */
    t_deleteTree(node->left);
    t_deleteTree(node->right);

    /* then delete the node */
    cout << "Deleting node: " << node->data << endl;
    delete node;
}

/* Deletes a tree and sets the root as NULL */
void deleteTree(Node** node_ref)
{
    t_deleteTree(*node_ref);
    *node_ref = NULL;
}

int main() {
    Node* root = nullptr;
    int arr[] = {13,6,15,17,20,9,4,3,7,2,18};
    int size = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < size; i++) {
        root = treeInsert(root, arr[i]);
    }
    cout << "\n----------------------------------------------" << endl;
    cout << "Root " << endl;
    cout << "In-order traverse: " << endl;
    inOrderTraversal(root);

    cout << "\nPre-order Traverse: " << endl;
    preOrderTraverse(root);

    cout << "\nPost-order Traverse: " << endl;
    postOrderTraversal(root);

    cout << "\n----------------------------------------------" << endl;

    Node* succ;
    for (int i = 0; i < size; i++) {
        succ = nodeSuccessor(root, arr[i]);
        if (succ != nullptr)
            cout << "The successor of node " << arr[i] << " is " << succ->data;
        else
            cout << "The successor of node " << arr[i] << " is NULL." ;
        cout << endl;
    }
    cout << "\n----------------------------------------------" << endl;



    cout << "\n----------------------------------------------" << endl;

    cout << "\nDelete key (2)" << endl;
    root = deleteNode(root, 2);
    inOrderTraversal(root);

    cout << "\n----------------------------------------------" << endl;
    cout << "\nDeleting tree " << endl;
    deleteTree(&root);
    return 0;
}