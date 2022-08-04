#pragma once

#include <string>
#include <vector>

#include "token.h"

class Scanner {
  const std::string source;
  const std::vector<TokenType> tokens;

public:
  Scanner(std::string source): source(source) {}
  Scanner (const Scanner &s) = delete;
  Scanner &operator=(const Scanner &s) = delete;

  const std::vector<TokenType> &scanTokens() const;
};
