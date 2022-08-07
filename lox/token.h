#pragma once

#include <string>
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

typedef union {
  std::nullptr_t empty;
  std::string_view str;
  double number;
} Literal;

struct Token {
  Literal literal;
  size_t line;
  std::string_view lexeme;
  TokenType type;

  Token(TokenType type, std::string_view &&lexeme, Literal literal, size_t line)
      : literal(literal), line(line), lexeme(lexeme), type(type) {}

  const std::string toString() const;
};
