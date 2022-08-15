#pragma once

#include <string>
#include <string_view>
#include <vector>

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  LOX_EOF
};

constexpr const char *TokenNames[] = {
    // Single-character tokens.
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "COMMA", "DOT",
    "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",

    // One or two character tokens.
    "BANG", "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL", "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",

    // Literals.
    "IDENTIFIER", "STRING", "NUMBER",

    // Keywords.
    "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR", "PRINT",
    "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",

    "EOF"};

enum LiteralType: std::uint8_t {
  LITERAL_EMPTY,
  LITERAL_STRING,
  LITERAL_NUMBER,
};

struct Literal {
  LiteralType tag;
  union {
    const std::nullptr_t empty;
    const char *str;
    const double number;
  };

  Literal(std::nullptr_t n) : tag{LITERAL_EMPTY}, empty{n} {}
  Literal(double n) : tag{LITERAL_NUMBER}, number{n} {}
  Literal(const std::string &s) : tag{LITERAL_STRING} {
    auto p = new char[s.length() + 1];
    s.copy(p, s.length());
    p[s.length()] = '\0';

    str = p;
  }

  ~Literal() {
    if (tag == LITERAL_STRING)
      delete[] str;
  }
};

struct Token {
  TokenType type;
  size_t line;
  std::string_view lexeme;
  Literal literal;

  const std::string toString() const;
};
