#include <sstream>
#include <string>

#include "token.h"

const std::string Token::toString() const {
  std::ostringstream s;
  std::ostringstream l;

  switch (type) {
    case STRING:
      l << literal.str;
      break;
    case NUMBER:
      l << literal.number;
      break;
    default:
      l << "[empty literal]";
  }

  s << "{ " << TokenNames[type] << " " << lexeme << " "
    << l.str() << " }";
  return s.str();
}
