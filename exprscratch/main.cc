#include <iostream>

#include "../lox/token.h"

template <typename T, typename U> struct Binary {
  T left;
  Token op;
  U right;
};

int main() { 
  Binary<Literal, Literal> b{
    Literal{nullptr},
    Token{Literal{nullptr}, 100, "hello", WHILE},
    Literal{nullptr},
  }
  return 0;
}
