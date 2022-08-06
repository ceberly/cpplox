#include <string>
#include <sstream>

#include "token.h"

//std::ostream& operator<<(std::ostream &os, const Literal &literal) {
//  return os << "<Literal a: " << literal << ">";
//}

const std::string Token::toString() const {
  std::ostringstream s;
  s << TokenNames[type] << " " << lexeme << " " << " [literal]";
  return s.str();
}
