#include "token.h"

#include <sstream>

template <> std::string Token::toString() {
  std::ostringstream out;

  out << TokenString[type] << " " << lexeme << " " << literal;
  // std::visit([&out](const auto &x) { out << x; }, literal.value_or(""));

  return out.str();
}
