#include "bstree.h"
#include "import_numbers_from_file.h"
#include "parse_arguments.h"
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

int main(int argc, char *argv[]) {
  Arguments args = parseArguments(argc, argv);

  BSTree bst;
  std::vector<double> numbers;

  if (args.random_provided) {

    // Generate random_size random keys distributed uniformly in [0, 1)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    for (size_t i = 0; i < args.random_size; ++i) {
      numbers.push_back(dist(gen));
    }
  } else {
    numbers = importNumbersFromFile(args.input_file);
  }

  // Insert the numbers into the BST
  for (double num : numbers) {
    bst.insert(num);
  }

  if (args.action.empty()) {

    // No action provided, just print the tree in order
    std::cout << "In-order traversal: ";
    bst.printInOrder();
    std::cout << std::endl;
    return 0;
  }

  // Perform the specified action
  if (args.action == "search") {

    // Search for the specified key in the BST
    BSTree::Node *result = bst.search(args.key);
    if (result) {
      std::cout << "Key " << args.key << " found at address " << result << "."
                << std::endl;
    } else {
      std::cout << "Key " << args.key << " not found, address: nullptr."
                << std::endl;
    }
  } else if (args.action == "find_min") {

    // Find the minimum key in the subtree rooted at the specified key
    if (args.key_provided) {
      BSTree::Node *subtree_root = bst.search(args.key);
      if (subtree_root) {
        BSTree::Node *minNode = bst.findMin(subtree_root);
        if (minNode) {
          std::cout << "Minimum key in the subtree rooted at " << args.key
                    << " is " << minNode->key << "." << std::endl;
        } else {
          std::cout << "The subtree rooted at " << args.key << " is empty."
                    << std::endl;
        }
      } else {
        std::cout << "Key " << args.key << " not found in the tree."
                  << std::endl;
      }
    } else {

      // Find the minimum key in the entire BST
      BSTree::Node *minNode = bst.findMin();
      if (minNode) {
        std::cout << "Minimum key in the tree is " << minNode->key << "."
                  << std::endl;
      } else {
        std::cout << "The tree is empty." << std::endl;
      }
    }
  } else if (args.action == "find_max") {

    // Find the maximum key in the entire BST
    BSTree::Node *maxNode = bst.findMax();
    if (maxNode) {
      std::cout << "Maximum key in the tree is " << maxNode->key << "."
                << std::endl;
    } else {
      std::cout << "The tree is empty." << std::endl;
    }
  } else if (args.action == "delete") {

    // Delete the specified key from the BST
    BSTree::Node *result = bst.search(args.key);
    if (result) {
      bst.deleteNode(args.key);
      std::cout << "Key " << args.key << " deleted from the tree." << std::endl;
    } else {
      std::cout << "Key " << args.key << " not found in the tree." << std::endl;
    }
  } else {
    printUsage();
    return 1;
  }

  // Print the tree in order if requested
  if (args.print_tree) {
    std::cout << "In-order traversal: ";
    bst.printInOrder();
    std::cout << std::endl;
  }

  // Print the tree structure for debugging
  // std::cout << "Tree structure:" << std::endl;
  // bst.printTreeStructure();

  return 0;
}
