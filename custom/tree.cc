#include <iostream>

class Node {
public:
  int value;
  Node* left;
  Node* right;

  Node(int v) : value(v) {
    left = NULL;
    right = NULL;
  }

  void add(Node* n) {

    if (n->value < value) {
      if (left == NULL) {
        left = n;
      } else {
        left->add(n);
      }
    } else if (n->value > value) {
      if (right == NULL) {
        right = n;
      } else {
        right->add(n);
      }
    }
  }

  void visit() {
    if (left != NULL) {
      left->visit();
    }
    std::cout << value << std::endl;
    if (right != NULL) {
      right->visit();
    }
  }

  Node* search(int v) {
    if (v == value) {
      return this;
    } else if (v < value && left != NULL) {
      return left->search(v);
    } else if (v > value && right != NULL) {
      return right->search(v);
    }
  }
};

class Tree {
public:
  Node* root;

  void add(int value) {
    Node* n = new Node(value);
    if (root == NULL) {
      root = n;
    } else {
      root->add(n);
    }
  }

  void traverse() {
    root->visit();
  }

  Node* search(int v) {
    return root->search(v);
  }
};


