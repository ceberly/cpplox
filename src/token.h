#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN = 0,
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

  IS_EOF
};

static constexpr const char *TokenString[]{
    "LEFT_PAREN", "RIGHT_PAREN",   "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA",      "DOT",           "MINUS",      "PLUS",
    "SEMICOLON",  "SLASH",         "STAR",

    "BANG",       "BANG_EQUAL",    "EQUAL",      "EQUAL_EQUAL",
    "GREATER",    "GREATER_EQUAL", "LESS",       "LESS_EQUAL",

    "IDENTIFIER", "STRING",        "NUMBER",

    "AND",        "CLASS",         "ELSE",       "FALSE",
    "FUN",        "FOR",           "IF",         "NIL",
    "OR",         "PRINT",         "RETURN",     "SUPER",
    "THIS",       "TRUE",          "VAR",        "WHILE",

    "IS_EOF"};

template <typename L> struct Token {
  const TokenType type;
  const std::string_view lexeme;
  const L literal;
  const int line;

  Token(const TokenType type, const std::string_view lexeme, L literal,
        const int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}

  std::string toString();
};

#endif
