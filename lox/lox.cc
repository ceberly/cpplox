#include "lox.h"

#include <fstream>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

bool Lox::hadError = false;

void Lox::report(int line, const std::string where, const std::string message) {
  cerr << "[line " << line << "] Error" << where << ": " << message << endl;
  hadError = true;
}

void Lox::error(int line, const std::string message) {
  report(line, "", message);
}

void Lox::run(const std::string line) { cout << line << endl; }

int Lox::runFile(const char *file) {
  std::ifstream f(file, std::ios::in);
  if (!f.is_open()) {
    std::cerr << "could not open '" << file << "' for reading." << endl;
    return 1;
  }

  return 0;
}

int Lox::runPrompt() {
  cout << "Welcome to lox ..." << endl;

  std::string line;
  while (std::getline(std::cin, line)) {
    run(line);
    if (hadError)
      return (65);
  }

  return 0;
}
