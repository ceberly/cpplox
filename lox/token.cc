#include <string>
#include <sstream>

#include "token.h"

std::ostream& operator<<(std::ostream &os, Literal literal) {
  return os << "<Literal a: " << literal.str << ">";
}

const std::string Token::toString() const {
  std::ostringstream s;
  s << TokenNames[type] << " " << lexeme << " " << "[literal]";
  return s.str();
}
