#include "scanner.h"

void Scanner::addToken(TokenType type, Token::Literal literal) {
  auto lexeme = source.substr(start, current);
  tokens.push_back(Token{type, lexeme, literal, line});
}

void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }

void Scanner::scanToken() {
  const char c = advance();
  switch (c) {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  }
}

void Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(Token{IS_EOF, std::string_view{""}, std::nullopt, line});
}
