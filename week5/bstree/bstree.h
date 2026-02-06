#ifndef BSTREE_H
#define BSTREE_H

class BSTree {
public:
  struct Node {
    double key;
    Node *left;
    Node *right;
    Node *parent;

    Node(double k);
  };

  BSTree();
  ~BSTree();
  void insert(double k);
  void printInOrder() const;
  Node *search(double k) const;
  Node *findMin() const;
  Node *findMin(Node *node) const; // Make this method public
  Node *findMax() const;
  void deleteNode(double k);
  void printTreeStructure() const;

private:
  Node *root;

  void printInOrder(const Node *node) const;
  Node *search(Node *node, double k) const;
  Node *findMax(Node *node) const;
  void deleteNode(Node *node);
  void transplant(Node *u, Node *v);
  void printTreeStructure(const Node *node) const;
  void deleteSubtree(Node *node);
};

#endif // BSTREE_H