#include <iostream>
using namespace std;

struct Node {
  int NodeData;
  Node *parentNode;
  Node *leftNode;
  Node *rightNode;
  int NodeColor;
};

typedef Node *NodePtr;

class REDBLACKTREE {
   private:
  NodePtr root;
  NodePtr TNULL;

  void INITIALIZENULLNode(NodePtr node, NodePtr parentNode) {
    node->NodeData = 0;
    node->parentNode = parentNode;
    node->leftNode = nullptr;
    node->rightNode = nullptr;
    node->NodeColor = 0;
  }
  NodePtr SEARCHTREEHELPER(NodePtr node, int key) {
    if (node == TNULL || key == node->NodeData) {
      return node;
    }

    if (key < node->NodeData) {
      return SEARCHTREEHELPER(node->leftNode, key);
    }
    return SEARCHTREEHELPER(node->rightNode, key);
  }

  // For balancing the tree after deletion
  void INSERTFIX(NodePtr k) {
    NodePtr u;
    while (k->parentNode->NodeColor == 1) {
      if (k->parentNode == k->parentNode->parentNode->rightNode) {
        u = k->parentNode->parentNode->leftNode;
        if (u->NodeColor == 1) {
          u->NodeColor = 0;
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          k = k->parentNode->parentNode;
        } else {
          if (k == k->parentNode->leftNode) {
            k = k->parentNode;
            RIGHTNODEROTATE(k);
          }
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          LEFTROTATE(k->parentNode->parentNode);
        }
      } else {
        u = k->parentNode->parentNode->rightNode;

        if (u->NodeColor == 1) {
          u->NodeColor = 0;
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          k = k->parentNode->parentNode;
        } else {
          if (k == k->parentNode->rightNode) {
            k = k->parentNode;
            LEFTROTATE(k);
          }
          k->parentNode->NodeColor = 0;
          k->parentNode->parentNode->NodeColor = 1;
          RIGHTNODEROTATE(k->parentNode->parentNode);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->NodeColor = 0;
  }

  void PRINTHELPER(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R-----";
        indent += "    ";
      } else {
        cout << "L-----";
        indent += "|   ";
      }

      string sNodeColor = root->NodeColor ? "RED" : "BLACK";
      cout << root->NodeData << "(" << sNodeColor << ")" << endl;
      PRINTHELPER(root->leftNode, indent, false);
      PRINTHELPER(root->rightNode, indent, true);
    }
  }
   public:
  REDBLACKTREE() {
    TNULL = new Node;
    TNULL->NodeColor = 0;
    TNULL->leftNode = nullptr;
    TNULL->rightNode = nullptr;
    root = TNULL;
  }
  void LEFTROTATE(NodePtr x) {
    NodePtr y = x->rightNode;
    x->rightNode = y->leftNode;
    if (y->leftNode != TNULL) {
      y->leftNode->parentNode = x;
    }
    y->parentNode = x->parentNode;
    if (x->parentNode == nullptr) {
      this->root = y;
    } else if (x == x->parentNode->leftNode) {
      x->parentNode->leftNode = y;
    } else {
      x->parentNode->rightNode = y;
    }
    y->leftNode = x;
    x->parentNode = y;
  }
  void RIGHTNODEROTATE(NodePtr x) {
    NodePtr y = x->leftNode;
    x->leftNode = y->rightNode;
    if (y->rightNode != TNULL) {
      y->rightNode->parentNode = x;
    }
    y->parentNode = x->parentNode;
    if (x->parentNode == nullptr) {
      this->root = y;
    } else if (x == x->parentNode->rightNode) {
      x->parentNode->rightNode = y;
    } else {
      x->parentNode->leftNode = y;
    }
    y->rightNode = x;
    x->parentNode = y;
  }
  void INSERTNODE(int key) {
    NodePtr node = new Node;
    node->parentNode = nullptr;
    node->NodeData = key;
    node->leftNode = TNULL;
    node->rightNode = TNULL;
    node->NodeColor = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->NodeData < x->NodeData) {
        x = x->leftNode;
      } else {
        x = x->rightNode;
      }
    }
    node->parentNode = y;
    if (y == nullptr) {
      root = node;
    } else if (node->NodeData < y->NodeData) {
      y->leftNode = node;
    } else {
      y->rightNode = node;
    }

    if (node->parentNode == nullptr) {
      node->NodeColor = 0;
      return;
    }

    if (node->parentNode->parentNode == nullptr) {
      return;
    }

    INSERTFIX(node);
  }
  NodePtr getRoot() {
    return this->root;
  }
  void printTree() {
    if (root) {
      PRINTHELPER(this->root, "", true);
    }
  }
};

int main() {
  REDBLACKTREE DEMOBST;
  DEMOBST.INSERTNODE(51);
  DEMOBST.INSERTNODE(44);
  DEMOBST.INSERTNODE(62);
  DEMOBST.INSERTNODE(34);
  DEMOBST.INSERTNODE(85);
  DEMOBST.INSERTNODE(54);

  DEMOBST.printTree();
}