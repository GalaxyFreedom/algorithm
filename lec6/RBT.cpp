#include <iostream>
#include <string>
#include <queue>

enum COLOR {Red, Black};

struct Node {
  int data;
  struct Node *right;
  struct Node *left;
  struct Node *parent;
  enum COLOR color;
};

struct RedBlackTree {
  Node *root;
  Node *NIL;
};

Node* new_Node(int data) {
  Node* n = new Node();
  n->left = NULL;
  n->right = NULL;
  n->parent = NULL;
  n->data = data;
  n->color = Red;

  return n;
}

RedBlackTree* new_RedBlackTree() {
  RedBlackTree *t = new RedBlackTree();
  Node *nil_node = new Node();
  nil_node->left = NULL;
  nil_node->right = NULL;
  nil_node->parent = NULL;
  nil_node->color = Black;
  nil_node->data = 0;
  t->NIL = nil_node;
  t->root = t->NIL;

  return t;
}

void left_rotate(RedBlackTree *t, Node *x) {
  Node *y = x->right;
  x->right = y->left;
  if(y->left != t->NIL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->NIL) { //x is root
    t->root = y;
  }
  else if(x == x->parent->left) { //x is left child
    x->parent->left = y;
  }
  else { //x is right child
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void right_rotate(RedBlackTree *t, Node *x) {
  Node *y = x->left;
  x->left = y->right;
  if(y->right != t->NIL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if(x->parent == t->NIL) { //x is root
    t->root = y;
  }
  else if(x == x->parent->right) { //x is right child
    x->parent->right = y;
  }
  else { //x is left child
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

void insertion_fixup(RedBlackTree *t, Node *z) {
  while(z->parent->color == Red) {
    if(z->parent == z->parent->parent->left) { //z.parent is the left child

      Node *y = z->parent->parent->right; // uncle of z is the right child of z.p.p

      if(y->color == Red) { //case 1 : if uncle (y) is RED
        z->parent->color = Black; // make z.p black
        y->color = Black; // make y.p black
        z->parent->parent->color = Red; // make z.p.p red
        z = z->parent->parent; // z moved up 2 levels
      }
      else { //case 2 or case 3
        if(z == z->parent->right) { //case 2 : if uncle(y) is BLACK, z is right child
          z = z->parent; //marked z.parent as new z
          left_rotate(t, z); // left rotate z.parent
        }
        //case3 : if uncle(y) is BLACK, z is left child
        z->parent->color = Black; // made parent black
        z->parent->parent->color = Red; // made parent red
        right_rotate(t, z->parent->parent); // right rotate z.p.p
      }
    }
    else { //z.parent is the right child
      Node *y = z->parent->parent->left; // uncle of z is the left child of z.p.p

      if(y->color == Red) { // if uncle(y) is RED
        z->parent->color = Black; // make z.p black
        y->color = Black; // make y.p black
        z->parent->parent->color = Red; // make z.p.p red
        z = z->parent->parent; // z moved up 2 levels
      }
      else { // case 5 or 6
        if(z == z->parent->left) { // case 5 : if uncle(y) is BLACK, z is the left child
          z = z->parent; //marked z.parent as new z
          right_rotate(t, z); // right rotate z.p
        }
        // case 6 : if uncle(y) is BLACK, z is the right child
        z->parent->color = Black; //made parent black
        z->parent->parent->color = Red; //made parent red
        left_rotate(t, z->parent->parent); // left rotate z.p.p
      }
    }
  }
  t->root->color = Black; // make t->root->color black
}

void insert(RedBlackTree *t, Node *z) {
  Node* y = t->NIL; //variable for the parent of the added node
  Node* temp = t->root;

  while(temp != t->NIL) {
    y = temp;
    if(z->data < temp->data)
      temp = temp->left;
    else
      temp = temp->right;
  }
  z->parent = y;

  if(y == t->NIL) { // newly added node is root
    t->root = z;
  }
  else if(z->data < y->data) // data of child is less than its parent,
    y->left = z; // left child of y = z
  else // else data of child is larger than its parent,
    y->right = z; // right child of y = z

  z->right = t->NIL; // right child of z = t->NIL
  z->left = t->NIL; // left child of z = t->NIL

  insertion_fixup(t, z);
}

void inorder(RedBlackTree *t, Node *n) {
  if(n != t->NIL) {
    inorder(t, n->left);
    std::cout << n->data << " ";
    inorder(t, n->right);
  }
}

void printTree(RedBlackTree* t,Node* node, std::string indent, bool last)
{
  if (node != t->NIL)
  {
      std::cout << indent;
      if (last)
      {
          std::cout << "R----";
          indent += "   ";
      }
      else
      {
          std::cout << "L----";
          indent += "|  ";
      }

      std::string sColor = node->color ? "RED" : "BLACK";
      std::cout << node->data << "(" << sColor << ")" << std::endl;
      printTree(t, node->left, indent, false);
      printTree(t, node->right, indent, true);
  }
}



void print(RedBlackTree* t, Node* node)
{
    printTree(t, node, "", true);
}


int main() {
  RedBlackTree* tree = new_RedBlackTree();
  int number_of_nodes = 0;
  std::cout << "Enter the number of nodes: ";
  std::cin >> number_of_nodes;
  std::vector<int> array_of_nodes_data(number_of_nodes);

  std::cout << "Enter the array of nodes: ";
  for (int i = 0; i < number_of_nodes; i++) {
    std::cin >> array_of_nodes_data[i];
  }
  for (int i = 0; i < number_of_nodes; i++) {
    Node* new_node = new_Node(array_of_nodes_data[i]);
    insert(tree, new_node);
  }

  print(tree, tree->root);




// RedBlackTree *t = new_RedBlackTree();

// Node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
// a = new_Node(10);
// b = new_Node(20);
// c = new_Node(30);
// d = new_Node(100);
// e = new_Node(90);
// f = new_Node(40);
// g = new_Node(50);
// h = new_Node(60);
// i = new_Node(70);
// j = new_Node(80);
// k = new_Node(150);
// l = new_Node(110);
// m = new_Node(120);

// insert(t, a);
// insert(t, b);
// insert(t, c);
// insert(t, d);
// insert(t, e);
// insert(t, f);
// insert(t, g);
// insert(t, h);
// insert(t, i);
// insert(t, j);
// insert(t, k);
// insert(t, l);
// insert(t, m);

// inorder(t, t->root);

// std::cout << "\n";

// print(t, t->root);

return 0;
}
