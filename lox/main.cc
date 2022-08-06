#include <iostream>

#include "lox.h"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cerr << "Usage: lox [script]" << std::endl;
    return 64;
  } else if (argc == 2) {
    return Lox::runFile(argv[1]);
  }

  return Lox::runPrompt();
}
