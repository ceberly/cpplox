#include "lox.h"
#include "scanner.h"

#include <fstream>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

namespace Lox {
void report(int line, const std::string where, const std::string message) {
  cerr << "[line " << line << "] Error" << where << ": " << message << endl;
  hadError = true;
}

void error(int line, const std::string message) { report(line, "", message); }

void run(const std::string source) {
  Scanner scanner(source);
  auto tokens = scanner.scanTokens();

  for (auto &token : tokens) {
    cout << token.toString() << endl;
  }
}

int runFile(const char *file) {
  std::ifstream f(file, std::ios::in);
  if (!f.is_open()) {
    std::cerr << "could not open '" << file << "' for reading." << endl;
    return 1;
  }

  //  if (hadError)
  //    return (65);

  return 0;
}

int runPrompt() {
  cout << "Welcome to lox ..." << endl;

  std::string line;
  while (std::getline(std::cin, line)) {
    run(line);
    hadError = false;
  }

  return 0;
}
} // namespace Lox
