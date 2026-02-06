#include "parse_arguments.h"
#include <iostream>
#include <string>

void printUsage() {
  std::cout << "Usage: ./bs_tree.out [--input <filename> | --random <size_t>] "
               "[--action <search/find_min/find_max/delete> --key <double>] "
               "[--print_tree]"
            << std::endl;
}

Arguments parseArguments(int argc, char *argv[]) {
  Arguments args = {"", "", 0.0, false, 0, false, false};

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--input" && i + 1 < argc) {
      args.input_file = argv[++i];
    } else if (arg == "--action" && i + 1 < argc) {
      args.action = argv[++i];
    } else if (arg == "--key" && i + 1 < argc) {
      args.key = std::stod(argv[++i]);
      args.key_provided = true;
    } else if (arg == "--random" && i + 1 < argc) {
      args.random_size = std::stoul(argv[++i]);
      args.random_provided = true;
    } else if (arg == "--print_tree") {
      args.print_tree = true;
    } else {
      printUsage();
      exit(1);
    }
  }

  // Ensure exactly one of --input or --random is provided
  if ((args.input_file.empty() && !args.random_provided) ||
      (!args.input_file.empty() && args.random_provided)) {
    printUsage();
    exit(1);
  }

  if (!args.action.empty() &&
      (args.action == "search" || args.action == "delete") &&
      !args.key_provided) {
    printUsage();
    exit(1);
  }

  return args;
}