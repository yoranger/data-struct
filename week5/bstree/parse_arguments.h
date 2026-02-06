#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include <string>

struct Arguments {
  std::string input_file;
  std::string action;
  double key;
  bool key_provided;
  size_t random_size;
  bool random_provided;
  bool print_tree;
};

void printUsage();
Arguments parseArguments(int argc, char *argv[]);

#endif // PARSE_ARGUMENTS_H