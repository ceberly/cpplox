#ifndef SCANNER_H
#define SCANNER_H

#include <string_view>
#include <vector>

#include "token.h"

class Scanner {
  const std::string_view source;
  std::string_view::size_type start = 0;
  std::string_view::size_type current = 0;
  int line = 1;

  inline bool isAtEnd() { return current >= source.size(); }
  inline char advance() { return source[current++]; }
  inline char peek() { return isAtEnd() ? '\0' : source[current]; }
  inline char peekNext() {
    return current >= source.size() - 1 ? '\0' : source[current + 1];
  }

  void addToken(TokenType, Token::Literal);
  void addToken(TokenType);
  void identifier();
  void number();
  void scanToken();
  void string();
  bool match(const char expected);

public:
  std::vector<Token> tokens;
  bool hadError = false;

  Scanner(const std::string_view source) : source(source) {}

  void scanTokens();
  void report(int line, const char *where, const char *message);
  void error(int line, const char *message);
};

#endif
