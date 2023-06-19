#ifndef EXPR_H
#define EXPR_H

#include "../token.h"

template<typename T>
struct Unary {
  Token op;
  T right;

  Unary(Token op, T right) : op(op), right(right) {}

  template<typename U, typename V>
  U accept(V visitor) { return visitor->visitUnaryExpr(this); }
};

template<typename L, typename R>
struct Binary {
  L left;
  Token op;
  R right;

  Binary(L left, Token op, R right) : left(left), op(op), right(right) {}

  template<typename T, typename V>
  T accept(V visitor) { return visitor->visitBinaryExpr(this); }
};

struct Literal {
  Token::Literal value;

  Literal(Token::Literal value) : value(value) {}

  template<typename T, typename V>
  T accept(V visitor) { return visitor->visitLiteralExpr(this); }
};

template<typename T>
struct Grouping {
  T expression;

  Grouping(T expression) : expression(expression) {}

  template<typename U, typename V>
  U accept(V visitor) { return visitor->visitGroupingExpr(this); }
};

#endif
