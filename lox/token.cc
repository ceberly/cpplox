#include <string>
#include <sstream>

#include "token.h"

struct Literal {
  int a;
};

std::ostream& operator<<(std::ostream &os, const Literal &literal) {
  return os << "<Literal a: " << literal.a << ">";
}

struct Token {
  TokenType type;
  std::string lexeme;
  Literal literal;
  int line;

  Token(TokenType type, std::string lexeme, Literal literal, int line) :
    type(type), lexeme(lexeme), literal(literal), line(line) {}

  const std::string toString() const {
    std::ostringstream s;
    s << TokenNames[type] << " " << lexeme << " " << literal;
    return s.str();
  }
};
