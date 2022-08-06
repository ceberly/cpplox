#pragma once

#include <string>
#include <memory>
#include <vector>

#include "token.h"

class Scanner {
  const std::string source;
  std::vector<Token> tokens;

  std::size_t start = 0;
  std::size_t current = 0;
  std::size_t line = 1;

  bool isAtEnd() const { return current >= source.length(); }
  char advance() { return source[current++]; }
  void addToken(TokenType, Literal &&);
  void addToken(TokenType type) {
    return addToken(type, std::move(EmptyLiteral)); }
  void scanToken();
  bool match(const char expected);
  char peek() const { if (isAtEnd()) return '\0'; return source[current]; }
  void string();
  void number();

  static bool isDigit(char c) { return c > '0' && c <= '9'; }
public:
  Scanner(std::string source): source(source) {}
  Scanner (const Scanner &s) = delete;
  Scanner &operator=(const Scanner &s) = delete;

  const std::vector<Token> &scanTokens();
};
