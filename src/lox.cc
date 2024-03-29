#include <cassert>
#include <cstdio>

#include <iostream>

#include "mmap_file.h"
#include "scanner.h"

static bool hadError = false;

void run(const char *source) {
  Scanner scanner(source);

  scanner.scanTokens();

  if (scanner.hadError) {
    hadError = true;
  }

  for (auto &token : scanner.tokens) {
    std::cout << token.toString() << "\n";
  }

  return;
}

static int runFile(const char *filename) {
  if (hadError) {
    return 65;
  }

  return 0;
}

static int runPrompt() {
  std::string line;

  while (1) {
    std::cout << "> ";
    std::getline(std::cin, line);

    if (line.empty()) {
      break;
    }

    run(line.c_str());

    hadError = false;
  }

  return 0;
}

static void usage() { printf("Usage: lox [script]\n"); }

int main(int argc, const char **argv) {
  if (argc > 2) {
    usage();

    return 64;
  }

  if (argc == 2) {
    const char *file = mmap_file(argv[1]);

    assert(file != nullptr);

    return runFile(argv[1]);
  }

  return runPrompt();
}
