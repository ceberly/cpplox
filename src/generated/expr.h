#ifndef EXPR_H
#define EXPR_H

#include "../token.h"

template<typename T, typename L>
struct Unary {
  Token<L> op;
  T right;

  Unary(Token<L> op, T right) : op(op), right(right) {}

  template<typename U, typename V>
  U accept(V visitor) { return visitor->visitUnaryExpr(this); }
};

template<typename L, typename R, typename LL>
struct Binary {
  L left;
  Token<LL> op;
  R right;

  Binary(L left, Token<LL> op, R right) : left(left), op(op), right(right) {}

  template<typename T, typename V>
  T accept(V visitor) { return visitor->visitBinaryExpr(this); }
};

template<typename L>
struct Literal {
  L value;

  Literal(L value) : value(value) {}

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
