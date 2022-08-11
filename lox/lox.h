#pragma once

#include <string>

// this is kind of a singleton class that supports the Java "main" class
// used in the book.
namespace Lox {
static bool hadError = false;

void report(int line, const std::string where, const std::string message);
void error(int line, const std::string message);
void run(const std::string line);
int runFile(const char *file);
int runPrompt();
} // namespace Lox
