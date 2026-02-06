#include "bstree.h"
#include <iostream>

// Node constructor
BSTree::Node::Node(double k)
    : key(k), left(nullptr), right(nullptr), parent(nullptr) {}

// BSTree constructor
BSTree::BSTree() : root(nullptr) {}

// BSTree destructor
BSTree::~BSTree() { deleteSubtree(root); }

// Helper function to delete a subtree
void BSTree::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
  }
}

// Insert function (iterative version)
void BSTree::insert(double k) {
  Node *newNode = new Node(k);
  if (!root) {
    root = newNode;
    return;
  }

  Node *parent = nullptr;
  Node *current = root;
  while (current) {
    parent = current;
    if (k < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  newNode->parent = parent;
  if (k < parent->key) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
}

// Print the tree in-order
void BSTree::printInOrder() const { printInOrder(root); }

// Helper function to print the tree in-order
void BSTree::printInOrder(const Node *node) const {
  if (node) {
    printInOrder(node->left);
    std::cout << node->key << " ";
    printInOrder(node->right);
  }
}

// Print the structure of the tree for debugging
void BSTree::printTreeStructure() const { printTreeStructure(root); }

void BSTree::printTreeStructure(const Node *node) const {
  if (node) {
    std::cout << "Node: " << node->key;
    if (node->parent) {
      std::cout << ", Parent: " << node->parent->key;
    } else {
      std::cout << ", Parent: nullptr";
    }
    if (node->left) {
      std::cout << ", Left Child: " << node->left->key;
    } else {
      std::cout << ", Left Child: nullptr";
    }
    if (node->right) {
      std::cout << ", Right Child: " << node->right->key;
    } else {
      std::cout << ", Right Child: nullptr";
    }
    std::cout << std::endl;
    printTreeStructure(node->left);
    printTreeStructure(node->right);
  }
}

// Search for a node with the given key
BSTree::Node *BSTree::search(double k) const { return search(root, k); }

BSTree::Node *BSTree::search(Node *node, double k) const {

  if(!node || node->key == k)
    return node;
  if(node->key > k)
    return search(node->left, k);
  else
    return search(node->right, k);
}

// Find the node with the minimum key
BSTree::Node *BSTree::findMin() const { return findMin(root); }

BSTree::Node *BSTree::findMin(Node *node) const 
{
  while (node->left)
    node = node->left;
  return node;
}

// Find the node with the maximum key
BSTree::Node *BSTree::findMax() const { return findMax(root); }

BSTree::Node *BSTree::findMax(Node *node) const 
{
  while(node->right)
    node = node->right;
  return node;
}

// Delete a node with the given key
void BSTree::deleteNode(double k) {
  Node *node = search(k);
  if (node) {
    deleteNode(node);
  }
}

void BSTree::deleteNode(Node *node) 
{
  if(!node->left)
      transplant(node, node->right);
  else if(!node->right)
    transplant(node, node->left);
  else {
    Node *y = findMin(node->right);
    if(y->parent != node) {
      transplant(y, y->right);
      y->right = node->right;
      y->right->parent = y;
    }
    transplant(node, y);
    y->left = node->left;
    y->left->parent = y;
  }
  delete node;
}

void BSTree::transplant(Node *u, Node *v) 
{
  if(!u->parent)
    root = v;
  else if(u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if(v)
    v->parent = u->parent;
}
