#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cerr;
using std::endl;

static bool hadError = false;

void report(int line, const std::string where, const std::string message) {
  cerr << "[line " << line << "] Error" << where << ": " << message << endl;
  hadError = true;
}

void error(int line, const std::string message) {
  report(line, "", message);
}

void run(const std::string line) {
  cout << line << endl;
}

int runFile(const char *file) {
  std::ifstream f(file, std::ios::in);
  if (!f.is_open()) {
    std::cerr << "could not open '" << file << "' for reading." << endl;
    return 1;
  }
  

  return 0;
}

int runPrompt() {
  cout << "Welcome to lox ..." << endl;

  std::string line;
  while(std::getline(std::cin, line)) {
    run(line);
    if (hadError) return(65);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    cerr << "Usage: lox [script]" << endl;
    return 64;
  } else if (argc == 2) {
    return runFile(argv[1]);
  }

  return runPrompt();
}
