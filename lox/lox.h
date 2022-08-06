#pragma once

#include <string>

// this is kind of a singleton class that supports the Java "main" class 
// used in the book.
struct Lox {
  static bool hadError;

  static void report(int line, const std::string where, const std::string message);
  static void error(int line, const std::string message);
  static void run(const std::string line);
  static int runFile(const char *file);
  static int runPrompt();
};
