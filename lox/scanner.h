#pragma once

#include <string>
#include <vector>

#include "token.h"

class Scanner {
public:
  std::vector<Token> tokens;

private:
  const std::string source;

  std::size_t start = 0;
  std::size_t current = 0;
  std::size_t line = 1;

  bool isAtEnd() const { return current >= source.length(); }
  char advance() { return source[current++]; }
  void addToken(TokenType, Literal);
  void addToken(TokenType type) { return addToken(type, Literal{nullptr}); }
  void scanToken();
  bool match(const char expected);
  char peek() const {
    if (isAtEnd())
      return '\0';
    return source[current];
  }
  char peekNext() const {
    if (current + 1 >= source.length())
      return '\0';
    return source[current + 1];
  }
  void string();
  void number();
  void identifier();

  static bool isDigit(char c) { return c >= '0' && c <= '9'; }
  static bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
  }
  static bool isAlphaNumeric(char c) { return isAlpha(c) || isDigit(c); }

public:
  Scanner(std::string source) : source(source) {}
  Scanner(const Scanner &s) = delete;
  Scanner &operator=(const Scanner &s) = delete;

  const std::vector<Token> &scanTokens();
};
