#include "token.h"

#include <sstream>

std::string Token::toString() {
  std::ostringstream out;

  out << TokenString[type] << " " << lexeme << " ";
  std::visit([&out](const auto &x) { out << x; }, literal.value_or(""));

  return out.str();
}
