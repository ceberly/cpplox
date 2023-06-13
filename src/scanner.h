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

  inline bool isAtEnd() { return current > source.size(); }
  inline char advance() { return source[current++]; }

  void addToken(TokenType, Token::Literal);
  void addToken(TokenType);
  void scanToken();

public:
  std::vector<Token> tokens;

  Scanner(const std::string_view source) : source(source) {}

  void scanTokens();
};

#endif
