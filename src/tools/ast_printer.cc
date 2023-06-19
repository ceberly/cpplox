#include <iostream>
#include <sstream>

#include <tuple>
#include <utility>

#include "../generated/expr.h"

template <typename T> struct AstPrinter {
  std::ostringstream out;

  template <typename U> void actuallyAccept(U expr) {
    expr.template accept<decltype(AstPrinter<T>::actuallyAccept(expr))>(this);
  }

  template <typename P, std::size_t... Is>
  void doAcceptImp(const P &tuple, std::index_sequence<Is...>) {
    (actuallyAccept(std::get<Is>(tuple)), ...);
  }

  template <typename... Exprs>
  void parenthesize(std::string_view name, Exprs... exprs) {
    out << "(" << name;

    auto exprs_tuple = std::make_tuple(exprs...);
    doAcceptImp(exprs_tuple, std::make_index_sequence<sizeof...(Exprs)>{});

    out << ")";
  }

  inline void print(T expr) { return actuallyAccept(expr); }

  template <typename L, typename R, typename LL>
  void visitBinaryExpr(Binary<L, R, LL> *expr) {
    parenthesize(expr->op.lexeme, expr->left, expr->right);
  }

  template <typename U> void visitGroupingExpr(Grouping<U> *expr) {
    parenthesize("group", expr->expression);
  }

  template <typename U, typename L> void visitUnaryExpr(Unary<U, L> *expr) {
    parenthesize(expr->op.lexeme, expr->right);
  }

  template <typename L> void visitLiteralExpr(Literal<L> *expr) {
    out << expr->value;
  }
};

int main() {
  auto program = Binary(Unary(Token(MINUS, "-", nullptr, 1), Literal(123.)),
                        Token(STAR, "*", nullptr, 1), Grouping(Literal(45.67)));

  AstPrinter<decltype(program)> printer;

  printer.print(program);

  std::cout << printer.out.str() << "\n";

  return 0;
}
